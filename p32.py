#!/usr/bin/env python

"""
Problem 32: Pandigital products
Find the sum of all products whose multiplicand/multiplier/product identity can
be written as a 1 through 9 pandigital.
http://projecteuler.net/problem=32
"""

import time

pan = '123456789'
prods = set()

def pandigital():
    for i in xrange(1, 10000):
        for j in xrange(1, 10000):
            prod = i*j
            _pan = ''.join(sorted(str(i) + str(j) + str(prod)))
            if len(_pan) > 9:  # bail since results just getting bigger now
                break
            if pan == _pan and not prod in prods:
                prods.add(prod)
    print sum(prods)

if __name__ == '__main__':
    t1 = time.time()
    pandigital()
    print "time:", time.time() - t1
