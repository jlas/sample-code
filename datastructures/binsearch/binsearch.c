int compare (const void* a, const void* b) {
  int a1 = *(const int *)a;
  int b1 = *(const int *)b;
  if (a1 < b1) {
    return -1;
  } else if (a1 == b1) {
    return 0;
  } else {
    return 1;
  }
}

int binsearch(int * arr, int x, int start, int end) {
  int midx, m;
  while (end > start) {
    midx = (start + end) / 2;
    m = arr[midx];
    if (x == m) {
      return x;
    }
    if (x < m) {
      end = midx;
    } else {
      start = midx+1;
    }
  }
  return m;
}
