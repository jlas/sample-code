#!/bin/python

import sys

inpt = sys.stdin.read()
l = map(int, inpt.split())
n = l[0]
r = l[1:]

indices = map(lambda x: x[1], sorted(zip(r, range(n)), key=lambda x: x[0]))

candies = [1] * n

for i in indices:
    rank = r[i]
    if i > 0 and rank > r[i-1] and candies[i-1] >= candies[i]:
        candies[i] = candies[i-1] + 1
    if i < n - 1 and rank > r[i+1] and candies[i+1] >= candies[i]:
        candies[i] = candies[i+1] + 1
print sum(candies)
