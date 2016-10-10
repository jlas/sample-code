#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "quadtree.h"
#include "viz.h"

int main() {
  QuadTree * qt;
  int count = 0;
  int size = 2;
  double x, y, data;
  Node * nodes = malloc(sizeof(struct Node)*size);
  Node * tmpnodes;

  while (fscanf(stdin, "%lf,%lf,%lf", &x, &y, &data) == 2) {
    nodes[count].x = x;
    nodes[count].y = y;
    nodes[count].data = data;
    count++;
    if (count == size) {
      size *= 2;
      tmpnodes = malloc(sizeof(Node)*size);
      memcpy(tmpnodes, nodes, count*sizeof(Node));
      free(nodes);
      nodes = tmpnodes;
      tmpnodes = NULL;
    }
  }

  qt = makeTree(nodes, count);
  tree2ppm(qt);
  free(nodes);
}
