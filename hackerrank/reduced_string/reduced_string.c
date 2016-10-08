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
