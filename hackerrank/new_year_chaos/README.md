# New Year Chaos

https://www.hackerrank.com/challenges/new-year-chaos

It's New Year's Day and everyone's in line for the Wonderland rollercoaster
ride! There are N people queued up, and each person wears a sticker indicating
their initial position in the queue (i.e.: 1 2 ... n - 1. n  with the first
number denoting the frontmost position). Any person in the queue can bribe
the person directly in front of them to swap positions. If two people swap
positions, they still wear the same sticker denoting their original place
in line. One person can bribe at most two other persons.

That is to say, if n=8 and person 5 bribes person 4, the queue will look like this:
1 2 3 5 4 6 7 8.

Fascinated by this chaotic queue, you decide you must know the minimum number of
bribes that took place to get the queue into its current state!

## Input Format:

The first line contains an integer, T, denoting the number of test cases.
Each test case is comprised of two lines; the first line has n (an integer
indicating the number of people in the queue), and the second line has n
space-separated integers describing the final state of the queue.

## Output format:

Print an integer denoting the minimum number of bribes needed to get the
queue into its final state; print Too chaotic if the state is invalid
(requires Person X to bribe more than 2 people).

## Sample input:

    2
    5
    2 1 5 3 4
    5
    2 5 1 3 4

## Sample output:

    3
    Too chaotic
