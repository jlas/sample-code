#!/bin/env python

import subprocess

import pandas as pd

OUTFILE = 'perf.out'

# benchmark -t option
BENCH_REPS = 1000000

metrics = {
    'seconds_elapsed': 'seconds time elapsed',
    'L1_cache_misses': 'L1-dcache-load-misses'
    }

def parse_output():
    with open(OUTFILE) as f:
        out = f.read()
    split = lambda line: list(map(lambda s: s.replace(',','').strip(), line.split()))[0]
    d = {}
    lines = out.splitlines()
    for line in lines:
        for label, snippet in metrics.items():
            if snippet in line:
                d[label] = float(split(line))
    return d

def exec_cmd(nelements, bench_reps=1, perf_reps=10, veb=False, seed=None):
    veb_flag = ''
    if veb:
        veb_flag = '-v'
    seed_opt = []
    if seed:
        seed_opt = ['-s', '{}'.format(seed)]
    subprocess.check_call(['perf', 'stat',
                           '-o', OUTFILE,
                           '-r', str(perf_reps),
                           '-e', 'L1-dcache-load-misses',
                           './benchmark',
                           veb_flag,
                           '-n', str(nelements),
                           '-t', str(bench_reps)] + seed_opt)
    return parse_output()

configs = [
    {
        'label': 'bs_baseline',
        'bench_reps': 0,
        'veb': False
    }, {
        'label': 'bs',
        'bench_reps': BENCH_REPS,
        'veb': False
    }, {
        'label': 'veb_baseline',
        'bench_reps': 0,
        'veb': True
    }, {
        'label': 'veb',
        'bench_reps': BENCH_REPS,
        'veb': True
    }
]

def main():
    df = pd.DataFrame()
    for i in range(20,28):
        seed = 1
        d = {}
        d['nelements'] = 2**i - 1
        for cfg in configs:
            d2 = exec_cmd(d['nelements'], bench_reps=cfg['bench_reps'],
                          veb=cfg['veb'], seed=seed)
            d.update(dict([(cfg['label']+'_'+k,v) for k, v in d2.items()]))
        df = df.append(d, ignore_index=True)
        df.to_csv('results.csv')

    for metric in metrics.keys():
        df['diff_bs_'+metric] = df['bs_'+metric] - df['bs_baseline_'+metric]
        df['diff_veb_'+metric] = df['veb_'+metric] - df['veb_baseline_'+metric]
    df.to_csv('results.csv')

if __name__ == '__main__':
    subprocess.check_call('make clean benchmark', shell=True)
    main()
