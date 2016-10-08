#!/usr/bin/env python

"""
Problem 8: Largest product in a series
Find the greatest product of five consecutive digits in the 1000-digit number.
http://projecteuler.net/problem=8
"""

from collections import deque
import operator
import time

num = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450"

def method_a():
    """Iterate through each 5 digit segment in the string. On each iteration:
    get the next slice, coerce them to int, then multiply.
    """
    prod = 0
    idx = 5
    last = len(num)

    while idx <= last:
        l = [int(n) for n in list(num[idx-5:idx])]
        _prod = reduce(operator.mul, l, 1)
        if _prod > prod:
            prod = _prod
        idx += 1

    print prod

def method_b():
    """Use deques. Dequeue a single number on each iteration and reuse digits
    from the last iteration.
    """
    prod = 0
    l = deque([int(n) for n in num[:5]])
    dnum = deque(num[5:])
    while dnum:
        l.popleft()
        l.append(int(dnum.popleft()))
        _prod = reduce(operator.mul, l, 1)
        if _prod > prod:
            prod = _prod
    print prod

def method_c():
    """Keep a running product. Use deques to store current window of factors.
    """
    l = deque([int(n) for n in num[:5]])
    dnum = deque(num[5:])
    runprod = prod = reduce(operator.mul, l, 1)

    while dnum:
        divisor = l.popleft()
        if divisor != 0:
            runprod /= divisor
        else:
            runprod = reduce(operator.mul, l, 1)

        factor = int(dnum.popleft())
        l.append(factor)
        runprod *= factor
        if runprod > prod:
            prod = runprod

    print prod

if __name__ == "__main__":
    for meth in [method_a, method_b, method_c]:
        t1 = time.time()
        meth()
        print "time:", time.time() - t1
