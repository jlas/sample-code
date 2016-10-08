#!/usr/bin/env python

"""
Problem 33: Digit canceling fractions
Find the value of the denominator of the simplified product of the 4 digit-
canceling fractions.
http://projecteuler.net/problem=33

My solution ignored 3 of the 4 ways of finding digit canceling fractions. I
picked the correct method on a whim and it just worked. The other 3 are not
viable methods as explained here:
http://www.mathblog.dk/project-euler-33-fractions-unorthodox-cancelling-method/
"""

from operator import mul
import time

fractions = set()
quots = list()
def findem():
    for i in xrange(1, 10):
        for j in xrange(i, 10):
            numerator = int(str(i) + str(j))
            for k in xrange(1, 10):
                denominator = int(str(j) + str(k))
                quot = float(numerator)/denominator
                if quot != 1 and quot != 0 and quot == float(i)/k:
                    fractions.add(str(numerator) + '/' + str(denominator))
                    quots.append(quot)

    # print fractions just for show
    print fractions

    # get denominator from reduced product fraction
    # i.e. solve 1/x = quotient1 * quotient2 * ...
    print 1/reduce(mul, quots)

if __name__ == '__main__':
    t1 = time.time()
    findem()
    print 'time:', time.time() - t1
