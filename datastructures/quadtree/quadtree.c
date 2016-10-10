#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include "quadtree.h"

int QT_CAPACITY = 12;

int containsPoint(AABB boundary, XY xy) {
  return ((fabs(xy.x - boundary.center.x) <= boundary.halfDimension) &&
          (fabs(xy.y - boundary.center.y) <= boundary.halfDimension));
}

void initTree(QuadTree * qt, double x, double y, double halfDimension) {
  bzero(qt, sizeof(QuadTree));
  qt->boundary.center.y = y;
  qt->boundary.center.x = x;
  qt->boundary.halfDimension = halfDimension;
  qt->nodes = (Node **) malloc(sizeof(Node *)*QT_CAPACITY);
}

void subdivide(QuadTree * qt) {
  int i;

  double halfHalf = qt->boundary.halfDimension/2;
  double n = (qt->boundary.center.y + halfHalf);
  double w = (qt->boundary.center.x + halfHalf);
  double s = (qt->boundary.center.y - halfHalf);
  double e = (qt->boundary.center.x - halfHalf);

  qt->northWest = (QuadTree *) malloc(sizeof(QuadTree));
  initTree(qt->northWest, w, n, halfHalf);
  qt->northEast = (QuadTree *) malloc(sizeof(QuadTree));
  initTree(qt->northEast, e, n, halfHalf);
  qt->southWest = (QuadTree *) malloc(sizeof(QuadTree));
  initTree(qt->southWest, w, s, halfHalf);
  qt->southEast = (QuadTree *) malloc(sizeof(QuadTree));
  initTree(qt->southEast, e, s, halfHalf);

  for (i = 0; i < qt->nnodes; i++) {
    if (insert(qt->northWest, qt->nodes[i])) continue;
    if (insert(qt->northEast, qt->nodes[i])) continue;
    if (insert(qt->southWest, qt->nodes[i])) continue;
    if (insert(qt->southEast, qt->nodes[i])) continue;
  }

  qt->nnodes = QT_NONLEAF;
  free(qt->nodes);
  qt->nodes = NULL;
}

int insert(QuadTree * qt, Node * node) {

  XY xy;
  xy.x = node->x;
  xy.y = node->y;

  if (!containsPoint(qt->boundary, xy)) {
    return 0;
  }

  if (qt->nnodes != QT_NONLEAF &&
      qt->nnodes < QT_CAPACITY) {
    qt->nodes[qt->nnodes++] = node;
    return 1;
  }

  if (qt->nnodes != QT_NONLEAF) {
    subdivide(qt);
  }

  if(insert(qt->northWest, node)) return 1;
  if(insert(qt->northEast, node)) return 1;
  if(insert(qt->southWest, node)) return 1;
  if(insert(qt->southEast, node)) return 1;

  return 0;
}

QuadTree * makeTree(Node *nodes, int N) {
  QuadTree * qt;
  int i;
  double minX = DBL_MAX;
  double minY = DBL_MAX;
  double maxX = -DBL_MAX;
  double maxY = -DBL_MAX;
  double x, y, halfDimension;

  for (i = 0; i < N; i++) {
    x = nodes[i].x;
    y = nodes[i].y;
    if (x < minX) {
      minX = x;
    } else if (x > maxX) {
      maxX = x;
    }
    if (y < minY) {
      minY = y;
    } else if (y > maxY) {
      maxY = y;
    }
  }

  halfDimension = fmax(maxX - minX, maxY - minY)/2;

  qt = (QuadTree *) malloc(sizeof(QuadTree));
  initTree(qt, minX + halfDimension, minY + halfDimension, halfDimension);

  for (i = 0; i < N; i++) {
    insert(qt, &nodes[i]);
  }

  return qt;
}
