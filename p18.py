#!/usr/bin/env python

"""
Problem 18
Find the max total gotten by traversing the tree.
http://projecteuler.net/problem=18
"""

from collections import deque
import time

treetxt = """75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23"""

class Node(object):
    def __init__(self, val):
        """@param val: int
        """
        self.val = val
        self.left = None
        self.right = None

def createtree(text):
    """Create tree from a string like the one above & return root.
    """
    lines = deque(text.splitlines())
    root = Node(int(lines.popleft()))  # first line, has a single item
    parents = deque([root])
    for l in lines:
        _parents = deque()
        children = deque(map(Node, (map(int, l.split()))))
        for p in parents:
            p.left = popped = children.popleft()
            p.right = children[0]
            _parents.append(popped)
        parents = _parents
        parents.append(children[0])
    return root

def pathsum(node):
    if node is None:
        return 0
    return max(pathsum(node.left), pathsum(node.right)) + node.val

if __name__ == '__main__':
    t1 = time.time()
    print pathsum(createtree(treetxt))
    print 'time:', time.time() - t1
