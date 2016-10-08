#!/bin/python

import sys


T = int(raw_input().strip())
for a0 in xrange(T):
    n = int(raw_input().strip())
    q = map(int,raw_input().strip().split(' '))
    nbribes = 0
    skipped = []
    for _i, label in enumerate(q):
        i = _i + 1

        if label != i:
            prev2 = max(_i - 2, 0)
            if not i in q[prev2:_i]:
                skipped.append(i)

        if label in skipped:
            if label == skipped[0]:
                skipped.pop(0)
            elif label == skipped[1]:
                skipped.pop(1)
                nbribes += 1

        elif label == i and len(skipped):
            nbribes += len(skipped)

        elif label > i:
            bribes = label - i
            if bribes > 2:
                print("Too chaotic")
                break
            nbribes += bribes

        elif label < i or \
            len(skipped) > 2:
            print ("Too chaotic")
            break

    else:
        print nbribes
