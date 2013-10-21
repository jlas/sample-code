#!/usr/bin/env python

"""
Problem 17
Count number of letters used if numbers 1 - 1000 were written out.
http://projecteuler.net/problem=17
"""

import time

ones = {
    '1': 'one',
    '2': 'two',
    '3': 'three',
    '4': 'four',
    '5': 'five',
    '6': 'six',
    '7': 'seven',
    '8': 'eight',
    '9': 'nine'
    }

teens = {
    '10': 'ten',
    '11': 'eleven',
    '12': 'twelve',
    '13': 'thirteen',
    '14': 'fourteen',
    '15': 'fifteen',
    '16': 'sixteen',
    '17': 'seventeen',
    '18': 'eighteen',
    '19': 'nineteen'
    }

tens = {
    '2': 'twenty',
    '3': 'thirty',
    '4': 'forty',
    '5': 'fifty',
    '6': 'sixty',
    '7': 'seventy',
    '8': 'eighty',
    '9': 'ninety'
    }

# convert a integer to a string of characters
def to_words(num):

    words = []
    numstr = str(num)

    if len(numstr) == 4:
        words.extend([ones[numstr[0]], 'thousand'])
        numstr = numstr[1:]

    if len(numstr) == 3:
        if not numstr.startswith('0'):
            words.extend([ones[numstr[0]], 'hundred'])
        numstr = numstr[1:]

    if len(numstr) == 2:
        if not numstr.startswith('0'):
            words.append(teens.get(numstr) or tens[numstr[0]])
            if teens.get(numstr) is not None:
                numstr = numstr[1:]
        numstr = numstr[1:]

    if len(numstr) == 1:
        if not numstr.startswith('0'):
            words.append(ones[numstr])

    # insert the 'and' between hundred and the tens place
    if 'hundred' in words and words[-1] != 'hundred':
        words.insert(words.index('hundred') + 1, 'and')

    return ''.join(words)

def count_letters():
    return sum((len(to_words(i)) for i in xrange(1, 1001)))

if __name__ == '__main__':
    t1 = time.time()
    print count_letters()
    print 'time:', time.time() - t1
