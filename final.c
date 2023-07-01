#include "basic.c"


node *hilbert_rtree_search(node *root, point *p) 
{
    if (root == NULL) return NULL;
   
    if (root->is_leaf) {
        for (int i = 0; i < root->count; i++) {
            if (root->entries[i]->x == p->x && root->entries[i]->y == p->y) {
                return root;
            }
        }
        return NULL;
    }
   
    int i = 0;
    while (i < root->count && hilbert_cmp(root->entries[i], p) < 0) i++;
   
    return hilbert_rtree_search(root->children[i], p);
}
