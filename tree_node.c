#include "tree_node.h"

void swap_elements(node* x, node* y) {
    node per = *y;
    *y = *x;
    *x = per;
}

node *build_the_node(char sym, uint64_t freq) {
    node* n = (node*)malloc(sizeof(node));
    n->sym = sym;
    n->freq = freq;
    n->right = NULL;
    n->left = NULL;
    return n;
}