#include "bin_tree.h"

void add_node0(node *nodeCurrent, node *nodeNew) {
    if (nodeCurrent->left == NULL)
        nodeCurrent = nodeNew;
    else {
        if (nodeCurrent->left->freq <= nodeNew->freq)
            nodeCurrent->right = nodeNew;
        else {
            nodeCurrent->right = nodeCurrent->left;
            nodeCurrent->left = nodeNew;
        }
    }
    nodeCurrent->freq += nodeNew->freq;
}

tree* creating_a_tree() {
    tree* t = (tree*)malloc(sizeof(tree));
    t->cnt_nodes = 0;
    t->tree_root = NULL;
    return t;
}

void add_node(tree *t, node *nodeNew) {
    add_node0(t->tree_root, nodeNew);
}