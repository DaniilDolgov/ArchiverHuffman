#ifndef ALICOMPRESSOR_BIN_TREE_H
#define ALICOMPRESSOR_BIN_TREE_H

#include <stdlib.h>
#include <stdint.h>
#include "tree_node.h"

typedef struct tree0 {
    node* tree_root;
    uint64_t cnt_nodes;
} tree;

tree* creating_a_tree();
void add_node(tree* t, node* nodeNew);
void add_node0(node *nodeCurrent, node *nodeNew);

#endif