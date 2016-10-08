#!/usr/bin/env python

"""
Problem 15
Count the number of routes through a lattice graph.
http://projecteuler.net/problem=15
"""

# Lattice paths can be represented as a bitfield where each bit represents
# either a movement down or right. The total number of movements is constained
# to the sum of segments along 2 sides of the graph. For example in a 2x2
# graph, there are 2 segments on each of 2 sides, summing to a total of 4 sides.
# A 3x3 graph has 6 total segments, 4x4 has 8, and so on. So the problem is
# about counting the combinations of bitfields where there are half 1s and the
# other half 0s (half the steps are moving down and the other are moving right).
# We can use the binomial coeffecient to count these combinations.

import math
import time

def count_paths(sides):
    # Use binomial coeffecient, C(2*sides, sides)
    return math.factorial(2*sides)/(math.factorial(sides)**2)

if __name__ == "__main__":
    t1 = time.time()
    print count_paths(20)
    print "time:", time.time() - t1
