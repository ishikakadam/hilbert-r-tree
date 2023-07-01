#include "print.h"

void print_preorder(node* n) 
{
    if (n == NULL) {
        return;
    }
    printf("Count: %d\n", n->count);
    printf("Is Leaf: %d\n", n->is_leaf);
    printf("MBRs:\n");
    for (int i = 0; i < n->count; i++) {
        printf("(%d,%d),(%d,%d)\n", n->mbrs[i].bottom_left.x, n->mbrs[i].bottom_left.y, n->mbrs[i].top_right.x, n->mbrs[i].top_right.y);
    }
    printf("Entries:\n");
    for (int i = 0; i < n->count; i++) {
        if (n->is_leaf) {
            printf("(%d,%d)\n", n->entries[i]->x, n->entries[i]->y);
        } else {
            print_preorder(n->children[i]);
        }
    }
    if (!n->is_leaf) 
    {
        print_preorder(n->children[n->count]);
    }
}