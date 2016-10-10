#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "quadtree.h"

#define BOUNDARY 1
#define POINT 2

int SCALE = 640;

/**
 *  Mark a quadtree boundary in the pixel buffer. Start from the center and
 *  progress outwards toward the limits or until another boundary encountered.
 */
void addLine(unsigned char ** px, double top, double right, double bottom,
             double left, double x, double y) {
  double h = top - bottom;
  double w = right - left;
  int _x = SCALE * (right - x)/w;
  int _y = SCALE * (top - y)/h;

  int i;
  for (i = _x; i <= SCALE && px[_y][i] != BOUNDARY; i++) {
    px[_y][i] = BOUNDARY;
  }
  for (i = _x - 1; i >= 0 && px[_y][i] != BOUNDARY; i--) {
    px[_y][i] = BOUNDARY;
  }
  for (i = _y + 1; i <= SCALE && px[i][_x] != BOUNDARY; i++) {
    px[i][_x] = BOUNDARY;
  }
  for (i = _y - 1; i >= 0 && px[i][_x] != BOUNDARY; i--) {
    px[i][_x] = BOUNDARY;
  }
}

void addElement(unsigned char ** px, double top, double right, double bottom,
                double left, double x, double y) {
  double h = top - bottom;
  double w = right - left;
  int _x = SCALE * (right - x)/w;
  int _y = SCALE * (top - y)/h;
  px[_y][_x] = POINT;
}

void tree2ppmHlpr(QuadTree * qt, unsigned char ** px, double top, double right,
                  double bottom, double left) {
  int i;

  if (qt == NULL) {
    return;
  }

  // Add the boundaries for this tree
  addLine(px, top, right, bottom, left, qt->boundary.center.x, qt->boundary.center.y);

  if (qt->nnodes == QT_NONLEAF) {
    // Recurse down into subtrees
    tree2ppmHlpr(qt->northWest, px, top, right, bottom, left);
    tree2ppmHlpr(qt->northEast, px, top, right, bottom, left);
    tree2ppmHlpr(qt->southWest, px, top, right, bottom, left);
    tree2ppmHlpr(qt->southEast, px, top, right, bottom, left);

  } else {
    // Add each node in this tree to the pixel buffer
    for (i = 0; i < qt->nnodes; i++) {
      addElement(px, top, right, bottom, left, qt->nodes[i]->x, qt->nodes[i]->y);
    }
  }
}

/**
 * Output a quadtree visualization by recursively traversing down through
 * subtrees and marking boundaries and points in a pixel buffer. Then write
 * out a .ppm file to stdout.
 */
void tree2ppm(QuadTree * qt) {
  int i, j;
  double top = qt->boundary.center.y + qt->boundary.halfDimension;
  double right = qt->boundary.center.x + qt->boundary.halfDimension;
  double bottom = qt->boundary.center.y - qt->boundary.halfDimension;
  double left = qt->boundary.center.x - qt->boundary.halfDimension;

  // Create and initialize pixel buffer
  unsigned char ** px = (unsigned char **) malloc(sizeof(unsigned char *)*(SCALE+1));
  for (i = 0; i <= SCALE; i++) {
    px[i] = (unsigned char *) malloc(sizeof(unsigned char)*(SCALE+1));
    bzero(px[i], sizeof(unsigned char)*(SCALE+1));
  }

  tree2ppmHlpr(qt, (unsigned char **) px, top, right, bottom, left);
  printf("P6 %d %d 255 ", SCALE+1, SCALE+1);

  for (i = 0; i <= SCALE; i++) {
    for (j = 0; j <= SCALE; j++) {
      if (px[i][j] == BOUNDARY) {
        printf("%c%c%c", 0, 255, 0);  // green
      } else if (px[i][j] == POINT) {
        printf("%c%c%c", 255, 255, 255);  // white
      } else {
        printf("%c%c%c", 0, 0, 0);  // black
      }
    }
  }

  for (i = 0; i <= SCALE; i++) {
    free(px[i]);
  }
  free(px);
}
