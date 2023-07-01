#include "insert.h"

mbr mbr_union(mbr a, mbr b)
{
    mbr result;
    result.bottom_left.x = a.bottom_left.x < b.bottom_left.x ? a.bottom_left.x : b.bottom_left.x;
    result.bottom_left.y = a.bottom_left.y < b.bottom_left.y ? a.bottom_left.y : b.bottom_left.y;
    result.top_right.x = a.top_right.x > b.top_right.x ? a.top_right.x : b.top_right.x;
    result.top_right.y = a.top_right.y > b.top_right.y ? a.top_right.y : b.top_right.y;
    return result;
}

void update_mbr(node *n) 
{
    int i;
    n->mbrs[0] = (mbr){*n->entries[0], *n->entries[0]};
    for (i = 1; i < n->count; i++) 
    {
        point *p = n->entries[i];
        if (p->x < n->mbrs[0].bottom_left.x) 
        {
            n->mbrs[0].bottom_left.x = p->x;
        }
        if (p->y < n->mbrs[0].bottom_left.y) 
        {
            n->mbrs[0].bottom_left.y = p->y;
        }
        if (p->x > n->mbrs[0].top_right.x) 
        {
            n->mbrs[0].top_right.x = p->x;
        }
        if (p->y > n->mbrs[0].top_right.y) 
        {
            n->mbrs[0].top_right.y = p->y;
        }
    }
}


void update_mbr_recursive(node *n) 
{
    if (n->is_leaf) 
    {
        update_mbr(n);
    } 
    else 
    {
        int i;
        for (i = 0; i < n->count; i++) 
        {
            update_mbr_recursive(n->children[i]);
            if (i == 0) 
            {
                n->mbrs[0] = n->children[0]->mbrs[0];
            } 
            else 
            {
                n->mbrs[0] = mbr_union(n->mbrs[0], n->children[i]->mbrs[0]);
            }
        }
    }
}


void insert_into_leaf(node *leaf, point *p) 
{
    // entry_t entry = { p, hilbertValueP(p) };
    leaf->entries[leaf->count++] = p;
    qsort(leaf->entries, leaf->count, sizeof(point), hilbert_cmp);
    update_mbr_recursive(leaf);

}


// split a leaf node into two
void split_leaf(node *leaf, node **new_leaf, point *p) 
{
    *new_leaf = create_node();
    (*new_leaf)->is_leaf=1;
    int i, j;
    int split_index = leaf->count / 2;
    leaf->count = split_index;
    (*new_leaf)->count = leaf->count;
    for (i = split_index, j = 0; i < leaf->count; i++, j++) 
        {
            (*new_leaf)->entries[j] = leaf->entries[i];
        }
    leaf->entries[split_index] = p;
    if (hilbertValueP(p) > hilbertValueP((*new_leaf)->entries[0])) 
        {
            insert_into_leaf(*new_leaf, p);
        } 
    else 
        {
            insert_into_leaf(leaf, p);
        }
    
    update_mbr_recursive(leaf);
    update_mbr_recursive(*new_leaf);
}


// choose a node to insert a new entry into
node *choose_node(node *root, point *p) 
{
    node *n = root;
    while (!n->is_leaf) 
    {
        int i, j;
        int min_dist = 10000;
        node *min_child = NULL;
        for (i = 0; i < n->count; i++) 
        {
            point *child_point = n->children[i]->entries[0];
            int dist = 0;
            dist += pow(p->x - child_point->x, 2);
            dist += pow(p->y - child_point->y, 2);
            if (dist < min_dist) 
            {
                min_dist = dist;
                min_child = n->children[i];
            }
        }
        n = min_child;
    }
    return n;
}


// insert a point into the tree
void insert(node **root, point *point) 
{
    if (*root == NULL) 
    {
        *root = create_node();
        (*root)->is_leaf=1;
        insert_into_leaf(*root, point);
        update_mbr_recursive(*root);
    } 
    else 
    {
        node *leaf = choose_node(*root, point);
        if (leaf->count < MAX_ENTRIES) 
        {
            insert_into_leaf(leaf, point);
            update_mbr_recursive(leaf);
        } 
        else 
        {
            node *new_leaf;
            split_leaf(leaf, &new_leaf, point);
            if (leaf == *root) 
            {
                node *new_root = create_node();
                new_root->children[0] = leaf;
                new_root->children[1] = new_leaf;
                *root = new_root;
                update_mbr_recursive(*root);
            } 
            else 
            {
                insert(root, new_leaf->entries[0]);
                update_mbr_recursive(*root);
            }
            
        }
        
        
    }
}

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