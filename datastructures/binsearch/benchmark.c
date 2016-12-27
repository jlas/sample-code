#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include "binsearch.c"
#include "veb.c"

#define USAGE \
"usage:\n" \
"  driver [options]\n" \
"options:\n" \
"  -n [list_length]    Length of the list\n" \
"  -t [num_trials]     Number of trials to run\n" \
"  -s [seed]           Seed to use for srand\n" \
"  -v                  van Emde Boas mode\n" \
"  -h                  Show this help message\n"

int main (int argc, char* argv[]) {
  int N = 1L << 20;
  int T = 1;
  int i = 0;
  int use_veb = 0;
  int option_char;
  time_t seed = time(NULL);

  while ((option_char = getopt(argc, argv, "n:t:s:hdv")) != -1) {
    switch (option_char) {
    case 'n':
      N = atoi(optarg);
      break;
    case 't':
      T = atoi(optarg);
      break;
    case 's':
      seed = atoi(optarg);
      break;
    case 'h':
      fprintf(stderr, "%s\n", USAGE);
      exit(EXIT_SUCCESS);
    case 'v':
      use_veb = 1;
      break;
    default:
      fprintf(stderr, "%s\n", USAGE);
      exit(EXIT_FAILURE);
    }
  }

  srand(seed);

  // binary search function to use
  int (*bsfn)(int * arr, int x, int start, int end) = &binsearch;

  // initialize random array
  int* inarr = malloc(sizeof(int)*N);
  for (i = 0; i < N; i++) {
    inarr[i] = rand();
  }

  qsort(inarr, N, sizeof(int), compare);

  if (use_veb) {
    bsfn = &binsearch_veb;
    inorder2veb(inarr, 0, N);
  }

  for (i = 0; i < T; i++) {
    bsfn(arr, rand(), 0, N);
  }

  free(inarr);
  return 0;
}
