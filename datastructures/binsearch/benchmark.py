#!/bin/env python

import re
import subprocess

import pandas as pd

OUTFILE = 'perf.out'

# benchmark -t option
BENCH_REPS = 10000000

metrics = {
    'seconds_elapsed': 'seconds time elapsed',
    'L1_cache_misses': 'L1-dcache-load-misses'
    }

def parse_output():
    with open(OUTFILE) as f:
        out = f.read()
    def split(line):
        nums = map(lambda s: re.match('[0-9\.]+', s), line.replace(',','').split())
        return list(map(lambda r: float(r.group()), filter(bool, nums)))
    d = {}
    lines = out.splitlines()
    for line in lines:
        for label, snippet in metrics.items():
            if snippet in line:
                val, std = split(line)
                d[label] = val
                d[label+'_std'] = std
    return d

def exec_cmd(nelements, bench_reps=1, perf_reps=10, veb=False, seed=None):
    veb_flag = ''
    if veb:
        veb_flag = '-v'
    seed_opt = []
    if seed:
        seed_opt = ['-s', '{}'.format(seed)]
    cmd = ['perf', 'stat',
           '-o', OUTFILE,
           '-r', str(perf_reps),
           '-e', 'L1-dcache-load-misses',
           './benchmark',
           veb_flag,
           '-n', str(nelements),
           '-t', str(bench_reps)] + seed_opt
    print(' '.join(cmd))
    subprocess.check_call(cmd)
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

if __name__ == '__main__':
    subprocess.check_call('make clean benchmark', shell=True)
    main()
