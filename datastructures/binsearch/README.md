# Cache Oblivious Binary Search

Here we implement some ideas from the paper: "Cache Oblivious Search Trees via
Binary Trees of Small Height" by Brodal, Fagerberg, and Jacob. [link](http://dl.acm.org/citation.cfm?id=545386)

We also provide an implementation to convert a binary search tree from an
implicit inorder layout to implicit van Emde Boas layout.

## Results

The procedure used:

 * Search trees were constructed using random data with sizes between ~ 1M - 100M.
 * Both inorder and van Emde Boas variants were constructed.
  * The conversion time / cache misses from inorder to vEB is included in the
  observations. Although this impact is non-trivial, the hope is that by
  performing many searches the upfront cost of conversion will be amortized.
 * 10M searches for random numbers were performed.

Initial results look promising. vEB searches show about 50% reduction in cache
misses, although improvement seems to wane for larger search tree sizes.

The big concern is the significant longer execution time. Even with fewer cache
misses, the vEB searches take longer to perform. And the execution time is
increasing at a faster rate than the inorder scheme. This could be due to the
non-trivial overhead of traversing a vEB tree.

Future research might include observing the results of using the van Emde Boas
binary search scheme on external search trees, i.e. when the tree size is too
large to fit in RAM.

### Cache Misses

![cache_misses](https://raw.githubusercontent.com/jlas/sample-code/master/datastructures/binsearch/experiments/media/cache_misses.png)

### Running time

![time_elapsed](https://raw.githubusercontent.com/jlas/sample-code/master/datastructures/binsearch/experiments/media/time_elapsed.png)

## van Emde Boas Layout

Not to be confused with the [van Emde Boas tree](https://en.wikipedia.org/wiki/Van_Emde_Boas_tree),
the layout is a way to encode a binary tree in an 1 dimensional array. This
scheme has also been called a "height partitioned layout" by Ronn [1]. Compare
the two layouts below (the node values are indices in an encoded 1D array):

### Inorder layout

<pre>
          8
         / \
       /     \
     /         \
    4           12
   /  \        /  \
  2    6      10   14
 /\    /\    /\    /\
1  3  5  7  9  11 13 15
</pre>

### vEB Layout

<pre>
          1
         / \
       /     \
     /         \
    2           3
   /  \        /  \
  4    7      10   13
 /\    /\    /\    /\
5  6  8  9  11 12 14 15
</pre>

## Cache Oblivious Algorithms

The goal of [Cache Oblivious algorithms](https://en.wikipedia.org/wiki/Cache-oblivious_algorithm)
is to efficiently use data in a CPU cache and reduce unnecessary swapping of
data between slow to fast memory. The big win of a cache oblivious algo is that
this efficiency works at any level of a memory hierarchy, e.g. from RAM to CPU
cache or from Hard Disk to RAM.

[1] Rønn, Frederik. Cache-oblivious searching and sorting. Diss. Master’s thesis, University of Copenhagen, 2003.
