/* https://www.hackerrank.com/challenges/bigger-is-greater */

/**
 * Given a word w, rearrange the letters of w to construct another word s in
 * such a way that s is lexicographically greater than w. In case of multiple
 * possible answers, find the lexicographically smallest one among them.
 *
 * Input format:
 *   The first line of input contains t, the number of test cases. Each of the
 * next t lines contains w.
 *
 * Sample input:
 * 5
 * ab
 * bb
 * hefg
 * dhck
 * dkhc
 *
 * Sample output:
 * ba
 * no answer
 * hegf
 * dhkc
 * hcdk
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int i, j;
  char tmp;
  char * s = NULL;
  size_t len = 0;
  ssize_t r;
  getline(&s, &len, stdin);
  while ((r=getline(&s, &len, stdin)) != -1) {
    /* sometimes there's a newline in the count */
    if (s[r-1] == '\n') {
      r--;
    }
    if (r<=1) {
      printf("no answer\n");
      continue;
    }
    /* case: x_n-1 < x_n */
    if (s[r-2] < s[r-1]) {
      tmp = s[r-2];
      s[r-2] = s[r-1];
      s[r-1] = tmp;
      printf("%s", s);
      continue;
    }
    /* find first x_n from right side that ends an ascending substring, label it x_i */
    for (i=r-2; i>=0 && s[i] >= s[i+1]; i--);
    if (i<0) {
      printf("no answer\n");
      continue;
    }
    /* find smallest x_j greater than x_i */
    for (j=i; s[j+1] > s[i]; j++);
    /* swap x_j and x_i */
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    /* sort x ascending for n > i, reverse since already sorted */
    for (i=i+1, j=r-1; i<j; i++, j--) {
      tmp = s[i];
      s[i] = s[j];
      s[j] = tmp;
    }
    printf("%s", s);
  }
  free(s);
  return 0;
}
