#include <math.h>
#include "basic.h"

void update_mbr(node *n) ;
void update_mbr_recursive(node *n) ;

void insert_into_leaf(node *leaf, point *p) ;
void split_leaf(node *leaf, node **new_leaf, point *p) ;
node *choose_node(node *root, point *p) ;

void insert(node **root, point *point);
void print_preorder(node* n) ;

