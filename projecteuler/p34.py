#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Problem 34: Digit factorials
Find the sum of all numbers which are equal to the sum of the factorial of their digits.
http://projecteuler.net/problem=34
"""

## Solution note:
##   To solve this problem I thought about what range of numbers might have this
## specific factorial sum = num property. I figured there must be some range
## where this property no longer applies so that we can numerically compute the
## answer.
##   So I figured since the largest value the factorial sum can take for any n
## digit number is factorial(9)*n there must be a point where x = y crosses
## above that.
##   I determined that starting with 1e8 was a good cutoff point because between
## 1e8 and (1e9 - 1) aka 99,999,999 the factorial(9)*n function never intersects
## with x = y.
##   So then I set out to find all of the combinations with repetitions of 7
## digit numbers (since 1e8 was the cutoff, that means 7 digit numbers are the
## last range of numbers where factorial digit sums and x = y can intersect).
## Combinations of the digits 0 - 9 and "no digit", i.e. 1 and 01 are two
## separate combinations. 0 is distinct from "no digit" because factorial of 0
## is 1, so 0s definitely affect the factorial digit sum.
##  I used combinations because the factorial digit sum function is agnostic to
## digit placement, i.e. fact_sum(145) == fact_sum(451) == etc. And to check
## the factorial sum against the original number, I just sorted both of them
## (as strings) to ensure they had the same unique characters.


import math
import time


## Plotting functions x=y and the factorial sums, not used for the solution.

def fact_sum_range(end, start=0):
    return map(lambda s: sum([math.factorial(int(d)) for d in s]), [str(i) for i in range(start, end)])

def plot_it(end, start=0):
    """Plot x = y and the digit factorial function, matplotlib required"""
    import pylab as pl
    r = range(start, end)
    pl.plot(r, r)
    pl.plot(r, fact_sum_range(end, start=start))
    pl.show()

# constants used for combinations generator below
GEN_NEXT = 1
GEN_TERM = 2

def gen_comb_rep_lex_next(v, n, k):
    """Helper function for generating combinations"""
    # easy case increase rightmost element
    if v[k - 1] < n - 1:
        v[k-1] += 1
        return GEN_NEXT

    # find rightmost element to increase
    j = k - 2
    while j >= 0:
        if v[j] != n - 1:
            break
        j -= 1

    # terminate if all elements eq. n - 1
    if j < 0:
        return GEN_TERM

    v[j] += 1

    # set right hand elements
    j += 1
    while j < k:
        v[j] = v[j-1]
        j += 1

    return GEN_NEXT

def gen_comb_rep_lex(n, k):
    """Generate a k-combination with repetition
    from http://www.aconnect.de/friends/editions/computer/combinatoricode_e.html#k-combinations_with_repetition_in_lexicographic_order
    """
    combos = []
    v = [0]*k
    ret = None
    while ret != GEN_TERM:
        ret = gen_comb_rep_lex_next(v, n, k)

        # the final item, n-1 is actually a placeholder for "no value"
        # so remove it here
        v2 = filter(lambda x: x != n - 1, v)

        combos.append(''.join([str(i) for i in v2]))
    return combos

def fact_sum(num):
    """Evaluate the sum of factorials of num's digits"""
    if len(num) == 1:
        return 0
    return sum([math.factorial(int(d)) for d in str(num)])

def main():
    combos = gen_comb_rep_lex(11, 7)
    runsum = 0
    for combo in combos:
        fsum = fact_sum(combo)

        # since order doesnt matter for factorial sums, we sort numbers
        if sorted(str(fsum)) == sorted(combo):
            runsum += fsum

    return runsum

if __name__ == "__main__":
    t1 = time.time()
    print main()
    print "time:", time.time() - t1
