/* https://www.hackerrank.com/challenges/reduced-string */

/**
 * Shil has a string, S, consisting of N lowercase English letters. In one
 * operation, he can delete any pair of adjacent letters with same value.
 * For example, string "aabcc" would become either "aab" or "bcc" after 1
 * operation.
 *
 * Shil wants to reduce S as much as possible. To do this, he will repeat
 * the above operation as many times as it can be performed. Help Shil out
 * by finding and printing S's non-reducible form!
 *
 * Note: If the final string is empty, print Empty String.
 *
 * Input format:
 *   A single string, S
 *
 * Sample input / output:
 * aaabccddd => abd
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  char s[101];
  if (fgets(s, 101, stdin) == NULL) {
    printf("error");
  }
  char last;
  int i = 0;
  int shift = 0;
  while(s[i] != '\0') {
    if (shift != 0) {
      s[i] = s[i+shift];
      if (s[i] == '\0') {
        break;
      }
    }
    if (last == s[i]) {
      i -= 2;
      shift += 2;
      last = '\0';
      if (i >= 0) {
        last = s[i];
      }
    } else {
      last = s[i];
    }
    i++;
  }
  if (s[0] == '\0') {
    printf("Empty String");
  }
  printf("%s", s);
  return 0;
}
