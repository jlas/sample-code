#!/bin/python

# Use quick-union approach described here:
#   https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

from collections import deque

N, Q = map(int,input().strip().split(' '))

# 1st index is dummy placeholder since input is 1-indexed
s = [i for i in range(N+1)]
cnt = [0]+[1 for i in range(N)]

# follow parent indices to root, store intermediates in list
def findparent(c, d):
    while c != s[c]:
        d.append(c)
        c = s[c]
    return c

# set all intermediate indices to parent
def percolate(p, d):
    for i in d:
        s[i] = p

for i in range(Q):
    inpt = input().strip().split(' ')
    qry = inpt[0]
    a = sorted(map(lambda x: int(x),inpt[1:]))
    i0 = a[0]

    if qry == 'Q':
        if i0 != s[i0]:
            d = deque()
            i0 = findparent(i0, d)
            percolate(i0, d)
        print(cnt[i0])
        continue

    # qry == 'M'
    i1 = a[1]
    if s[i0] != s[i1]:
        d = deque()
        i0 = findparent(i0, d)
        i1 = findparent(i1, d)
        if s[i0] != s[i1]:
            cnt[i0] += cnt[i1]
            d.append(i1)
            percolate(i0, d)
