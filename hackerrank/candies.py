#!/bin/python

# https://www.hackerrank.com/challenges/candies
#
# Alice is a kindergarden teacher. She wants to give some candies to the
# children in her class.  All the children sit in a line (their positions
# are fixed), and each of them has a rating score according to his or her
# performance in the class. Alice wants to give at least 1 candy to each
# child. If two children sit next to each other, then the one with the
# higher rating must get more candies. Alice wants to save money, so she
# needs to minimize the total number of candies given to the children.
#
# Input format:
#   The first line of the input is an integer N, the number of children in
# Alice's class. Each of the following N lines contains an integer that
# indicates the rating of each child.
#
# Sample input:
# 3
# 1
# 2
# 2
#
# Sample output:
# 4

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
