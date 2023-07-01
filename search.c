#include "basic.h"


node *hilbert_rtree_search(node **root, point *p) 
{   
    node *n= *root;
    if (n == NULL) return NULL;
   
    if (n->is_leaf) 
    {
        for (int i = 0; i < n->count; i++) 
        {
            if (n->entries[i]->x == p->x && n->entries[i]->y == p->y) 
            {
                return n;
            }
        }
        return NULL;
    }
   
    int i = 0;
    while (i < n->count && hilbert_cmp(n->entries[i], p) < 0) i++;
   
    return hilbert_rtree_search(n->children[i], p);
}
