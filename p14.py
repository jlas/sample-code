#!/usr/bin/env python

"""
Problem 14: Longest Collatz sequence
Find the starting number, under 1 million, that produces the longest Collatz chain.
http://projecteuler.net/problem=14
"""

import time

# memoize the calls to chainlen
memoize = {1: 1}

def chainlen(startnum):
    if memoize.get(startnum):
        return memoize.get(startnum)
    if (startnum & 1):  # is odd
        _len = chainlen(startnum*3 + 1)
    else:  # is even
        _len = chainlen(startnum/2)
    _len += 1  # add 1 for this link in the chain
    memoize[startnum] = _len
    return _len

def main():
    # base case, the Collatz chain: [1]
    largeststart = 1
    largestlen = 1

    for x in xrange(2, 1000000):
        _len = chainlen(x)
        if _len > largestlen:
            largestlen = _len
            largeststart = x
    print largeststart

if __name__ == "__main__":
    t1 = time.time()
    main()
    print "time:", time.time() - t1
