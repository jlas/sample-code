#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>

#define CALC_DEPTH(N) ceil(log2((N)+1))
#define CALC_TOP_DEPTH(d) ceil((d)/2.0)

/**
 * Metadata for traversing a vEB tree
 * @param D - depth of the root of top tree
 * @param T - size of top tree
 * @param B - size of bottom tree
 */
typedef struct veb_meta {
  int depth;
  int * D;
  int * T;
  int * B;
} veb_meta;

/**
 * Convert binary tree in an inorder layout to Van Emde Boas layout, e.g.
 * 1 2 3 4 5 6 7 8 => 4 2 6 1 3 5 7
 *
 * The approach is to break down the inorder layout into smaller and smaller
 * blocks until the base case (3 elements) is reached, where we can do the
 * actual vEB conversion. e.g. for a length 15 tree the breaking down would
 * look like:
 *
 * 1 => 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
 *
 * 2 => 4  8  12 1  2  3  5  6  7  9  10 11 13 14 15
 *      |<- top  |<- b1   |<- b2   |<- b3   |<- b4
 *
 * 3 => 8  4  12 2  1  3  6  5  7  10 9  11 14 13 15
 *      |<- top  |<- b1   |<- b2   |<- b3   |<- b4
 *
 */
void inorder2veb(int * arr, int start, int end) {
  int i, j, tmp, idepth, itgt, isrc, bottomstart;
  int N = end - start;

  // base case
  if (1 == N) {
    return;
  }

  // base case: inorder to vEB
  if (3 == N) {
    tmp = arr[start+1];
    arr[start+1] = arr[start];
    arr[start] = tmp;
    return;
  }

  int * arr2 = malloc(sizeof(int)*N);
  int depth = CALC_DEPTH(N);  // tree depth

  // expect N to be of the form 2^i - 1
  assert(pow(2, depth) == N+1);

  int tdepth = CALC_TOP_DEPTH(depth);  // top tree depth
  int bnum = pow(2, tdepth);  // num of bottom trees
  int tsize = bnum - 1;  // top tree size
  int bsize = (N - tsize)/bnum;  // num elements in each bottom tree

  // track depth of "target" tree i.e. array block where it'll be stored
  int tgtdepth = tdepth - 1;

  // start by traversing top tree
  for (idepth = depth - 1; idepth >= depth/2; idepth--, tgtdepth--) {
    for (isrc = pow(2, idepth)-1, itgt = pow(2, tgtdepth)-1;
         isrc < N && itgt < N;
         isrc += pow(2, idepth+1), itgt += pow(2, tgtdepth+1)) {
      arr2[itgt] = arr[start+isrc];
    }
  }

  //
  // done traversing top tree, now traverse bottom trees

  // iterate over bottom trees and calculate destination indices
  int * tgtrng = malloc(sizeof(int)*(N - tsize));
  for (j = 0, tgtdepth = depth - tdepth - 1; tgtdepth >= 0; tgtdepth--) {
    for (i = 0; i < bnum; i++) {
      for (itgt = pow(2, tgtdepth)-1; itgt < bsize; itgt += pow(2, tgtdepth+1)) {
        tgtrng[j++] = itgt+(bnum-1)+i*bsize;
      }
    }
  }

  for (j = 0, idepth = depth/2 - 1; idepth >= 0; idepth--) {
    for (isrc = pow(2, idepth)-1; isrc < N; isrc += pow(2, idepth+1)) {
      arr2[tgtrng[j++]] = arr[start+isrc];
    }
  }

  free(tgtrng);

  // copy over and free tmp array
  for (i = 0; i < N; i++) {
    arr[start+i] = arr2[i];
  }
  free(arr2);

  // start of bottom trees in the array
  bottomstart = start+bnum-1;

  // recursively convert the top tree
  inorder2veb(arr, start, bottomstart);

  // recursively convert the bottom trees
  for (i = 0; i < bnum; i++) {
    inorder2veb(arr, bottomstart + i*bsize, bottomstart + (i+1)*bsize);
  }
}

// Recursively construct metadata for traversing a vEB tree
void init_veb_meta_hlpr(int N, int d, veb_meta * meta) {

  // base case
  if (N == 1) {
    return;
  }

  int depth = CALC_DEPTH(N);  // tree depth
  int tdepth = CALC_TOP_DEPTH(depth);  // top tree depth
  int bnum = pow(2, tdepth);  // num of bottom trees
  int tsize = bnum - 1;  // top tree size
  int bsize = (N - tsize)/bnum;  // num elements in each bottom tree
  int rel_blvl = tdepth + 1;  // relative level of bottom trees
  int abs_blvl = d + rel_blvl - 1;  // absolute level of bottom trees

  meta->D[abs_blvl] = d;
  meta->T[abs_blvl] = tsize;
  meta->B[abs_blvl] = bsize;

  init_veb_meta_hlpr(tsize, d, meta);
  init_veb_meta_hlpr(bsize, abs_blvl, meta);
}

// Construct metadata for traversing a vEB tree
veb_meta * init_veb_meta(int N) {
  size_t sz;
  veb_meta * meta = malloc(sizeof(veb_meta));
  meta->depth = CALC_DEPTH(N);
  // +1 because we use 1-based indices
  sz = sizeof(int)*(meta->depth+1);
  meta->D = malloc(sz);
  bzero(meta->D, sz);
  meta->T = malloc(sz);
  bzero(meta->T, sz);
  meta->B = malloc(sz);
  bzero(meta->B, sz);
  init_veb_meta_hlpr(N, 1, meta);
  return meta;
}

void free_veb_meta(veb_meta * meta) {
  free(meta->D);
  free(meta->T);
  free(meta->B);
  free(meta);
}

/**
 * Recursively search for element in arr, technique for traversing vEB
 * taken from the paper:
 *   "Cache Oblivious Search Trees via Binary Trees of Small Height"
 *   by Brodal, Fagerberg, & Jacob.
 */
int binsearch_veb_hlpr(int * arr, int x, int d, int path, int * pos, veb_meta * meta) {
  if (d > 1) {
    pos[d] = pos[meta->D[d]] + meta->T[d] + (path & meta->T[d])*meta->B[d];
  }

  // found element
  if (x == arr[pos[d]-1]) {
    return x;
  }

  path = path << 1;
  if (x > arr[pos[d]-1]) {  // traverse rightward
    path |= 1;
  }

  // reached last level without finding element
  if (d == meta->depth) {
    return arr[pos[d]-1];
  }

  return binsearch_veb_hlpr(arr, x, d+1, path, pos, meta);
}

/**
 * Perform binary search using a vEB layout
 * @param arr - array of elements already in vEB layout
 * @param x - data element to search for
 * @param start - start location of data in arr
 * @param end - end location of data in arr
 */
int binsearch_veb(int * arr, int x, int start, int end) {
  int result;
  int N = end - start;
  veb_meta * meta = init_veb_meta(N);
  int * pos = malloc(sizeof(int)*(meta->depth+1));
  pos[1] = 1;
  result = binsearch_veb_hlpr(arr, x, 1, 1, pos, meta);
  free_veb_meta(meta);
  free(pos);
  return result;
}
