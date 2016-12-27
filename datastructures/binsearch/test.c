#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "binsearch.c"
#include "veb.c"

// Test the output of vEB based binary search vs. vanilla binary search
void test(int N, int T) {
  int i, r, bs, bsv;
  int* arr = malloc(sizeof(int)*N);
  int* arr_veb = malloc(sizeof(int)*N);

  // initialize random array
  srand(time(NULL));
  for (i = 0; i < N; i++) {
    arr[i] = rand();
  }

  qsort(arr, N, sizeof(int), compare);

  //
  // construct vEB layout

  for (i = 0; i < N; i++) {
    arr_veb[i] = arr[i];
  }

  inorder2veb(arr_veb, 0, N);

  //
  // compare binary searches

  for (i = 0; i < T; i++) {
    r = rand();
    bs = binsearch(arr, r, 0, N);
    bsv = binsearch_veb(arr_veb, r, 0, N);
    assert(bs == bsv);
  }

  free(arr);
  free(arr_veb);
}

int main() {
  int i;
  for (i = 2; i < 11; i++) {
    printf("Testing %d elements\n", (int) pow(2,i)-1);
    test(pow(2,i)-1, 1000000);
  }
  printf("Success\n");
  return 0;
}
