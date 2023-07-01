// Global variables
#include "basic.h"

node *root = NULL;   // root of the tree
int depth = 0;       // depth of the tree

// Calculate the Hilbert value for a 2-dimensional point
int hilbertValue(int x, int y) 
{
    int bits= 8;
    int d = 0, rx, ry, t;
    for (int s = bits/2; s > 0; s /= 2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        t = (rx << 1) | ry;
        d = (d << 2) | t;
        if (t == 0 || t == 3) {
            int tmp = x;
            x = y;
            y = tmp;
            if (t == 0) {
                x = (1 << s) - 1 - x;
                y = (1 << s) - 1 - y;
            }
        }
    }
    return d;
}

int hilbertValueP(point *p) 
{
   return hilbertValue(p->x,p->y);
}


// Calculate the Hilbert curve distance between two 2-dimensional points
// int hilbertDistance(point p1, point p2) 
// {
//     return hilbertValue(p1.x ^ p2.x, p1.y ^ p2.y);
// }


int hilbert_cmp(point *p1, point *p2) 
{
    int h1 = hilbertValue(p1->x, p1->y);
    int h2 = hilbertValue(p2->x, p2->y);
    if (h1 < h2) return -1;
    if (h1 > h2) return 1;
    return 0;
}


point *create_point(float x, float y) 
{
    point *p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

node *create_node() 
{
    node *n = malloc(sizeof(node));
    n->count = 0;
    return n;
}
