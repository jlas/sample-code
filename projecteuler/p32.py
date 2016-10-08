#!/usr/bin/env python

"""
Problem 32: Pandigital products
Find the sum of all products whose multiplicand/multiplier/product identity can
be written as a 1 through 9 pandigital.
http://projecteuler.net/problem=32
"""

import time

prods = set()

def pandigital():
    for i in xrange(1, 10000):
        stri = str(i)
        for j in xrange(1, 10000):
            prod = i*j
            _pan = stri + str(j) + str(prod)
            if len(_pan) > 9:  # bail since results just getting bigger now
                break
            if '123456789' == ''.join(sorted(_pan)) and not prod in prods:
                prods.add(prod)
    print sum(prods)

if __name__ == '__main__':
    t1 = time.time()
    pandigital()
    print "time:", time.time() - t1
