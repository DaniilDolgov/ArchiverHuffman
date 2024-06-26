#ifndef ALICOMPRESSOR_TREE_NODE_H
#define ALICOMPRESSOR_TREE_NODE_H

#include <stdlib.h>
#include <stdint.h>

typedef struct node0 {
    char sym;
    uint64_t freq;
    struct node0* right;
    struct node0 *left;
} node;

void swap_elements(node *x, node *y);

node* build_the_node(char sym, uint64_t freq);

#endif