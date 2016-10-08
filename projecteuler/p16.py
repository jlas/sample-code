#!/usr/bin/env python

"""
Problem 16
Sum the digits in the number 2^1000
http://projecteuler.net/problem=16
"""

import time

def main():
    return sum(map(int, str(2**1000)))

if __name__ == "__main__":
    t1 = time.time()
    print main()
    print 'time:', time.time() - t1
