#include <stdlib.h>
#include "veb.c"

#define N 255

// Helper to debug vEB routines
int main() {
  int i;
  int * arr = malloc(sizeof(int)*N);

  for (i = 0; i < N; i++) {
    arr[i] = i+1;
  }

  // check inorder conversion
  printf("# inorder conversion\n");
  inorder2veb(arr, 0, N);
  for (i = 0; i < N; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // check some binary searches
  printf("\n# binary searches\n");
  int searchfor[4] = {1, 2, N/2, N};
  for (i = 0; i < sizeof(searchfor)/sizeof(searchfor[0]); i++) {
    printf("%d:%d\n", searchfor[i], binsearch_veb(arr, searchfor[i], 0, N));
  }

  free(arr);

  // check meta construction
  printf("\n# meta\n");
  veb_meta * meta = init_veb_meta(N);
  for (i = 1; i <= CALC_DEPTH(N); i++) {
    printf("d:%d, D:%d, T:%d, B:%d\n", i, meta->D[i], meta->T[i], meta->B[i]);
  }
  printf("\n");

  return 0;
}
