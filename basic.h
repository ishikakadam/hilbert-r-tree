#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M 4   // maximum number of entries in a node
#define m 2   // minimum number of entries in a node
#define DIM 2           // number of dimensions
#define MAX_CHILDREN 4  // maximum number of children per node
#define MAX_ENTRIES 2   // maximum number of entries per node

// 2-dimensional point
typedef struct point 
{
    int x;
    int y;
} point;

// Minimum bounding rectangle (MBR)
typedef struct mbr 
{
    point bottom_left;
    point top_right;
} mbr;

// Node of the tree
typedef struct node 
{
    int is_leaf;    // is the node a leaf node or not
    int count;      // number of entries in the node
    mbr mbrs[M];    // MBRs of the entries in the node
    struct node *children[M];  // pointers to the child nodes or data
    point *entries[M];  //entires of the node

} node;

int hilbertValue(int x, int y) ;
int hilbertValueP(point *p) ;
int hilbertDistance(point *p1, point *p2); 


int hilbert_cmp(point *p1, point *p2) ;

point *create_point(float x, float y) ;

node *create_node() ;


