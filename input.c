#include <stdio.h>
#include <stdlib.h>
// #include "basic.c"
#include "insert.h"
// #include "print.h"

// Update the MBR of a node




int main() 
{
        printf("Starting the program.");

    // open the file for reading
    FILE* fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open file\n");
        return 1;
    }

    // read in the points and insert them into the Hilbert R-tree
    node* root = create_node();
    float x, y;
    while (fscanf(fp, "%f %f", &x, &y) == 2) 
    {
        point* p = create_point(x, y);
        // printf("%d,%d, %d\n", p->x,p->y,hilbertValue(x,y));
        
        insert(&root , p);
    }

    // close the file
    fclose(fp);
    printf("The tree has been built.");

    print_preorder(root);
    
    printf("The Traversal is completed.");

    return 0;
}