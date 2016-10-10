#define QT_NONLEAF -1

typedef struct Node {
  double x;
  double y;
  double data;
} Node;

typedef struct XY {
  double x;
  double y;
} XY;

typedef struct AABB {
  XY center;
  double halfDimension;
} AABB;

typedef struct QuadTree {
  Node ** nodes;
  int nnodes;
  AABB boundary;
  struct QuadTree * northWest;
  struct QuadTree * northEast;
  struct QuadTree * southWest;
  struct QuadTree * southEast;
} QuadTree;

int containsPoint(AABB boundary, XY xy);
void initTree(QuadTree * qt, double x, double y, double halfDimension);
void subdivide(QuadTree * qt);
int insert(QuadTree * qt, Node * node);
QuadTree * makeTree(Node *nodes, int N);
