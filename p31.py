#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Problem 31: Coin Sums
How many different ways can £2 be made using coins?
http://projecteuler.net/problem=31
"""

import time

coinset = [1, 2, 5, 10, 20, 50, 100, 200]
memoize = {}

def addCoins(_sum, _max):
    """Add a coin to the sum and recurse until we get to 200p.
    - Only add coins that are equal or lesser than the max valued coin already
    used. This prevents double counting.
    - Use memoization to speed things up.
    """
    if _sum == 200:
        return 1
    elif _sum > 200:
        return 0

    total = 0
    for coin in [c for c in coinset if c <= _max]:
        _newsum = _sum + coin
        count = memoize.get((_newsum, coin))
        if count is None:
            count = addCoins(_newsum, coin)
            memoize[(_newsum, coin)] = count
        total += count
    return total

if __name__ == "__main__":
    t1 = time.time()
    print addCoins(0, 200)
    print "time:", time.time() - t1
