#ifndef ALICOMPRESSOR_QUEUE_H
#define ALICOMPRESSOR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tree_node.h"

typedef struct priority_queue0 {
    uint64_t capacity;
    uint64_t size;
    node** data;
} prior_queue;

enum realloc_type {
    INCREASE,
    DECREASE,
};

void deleting_a_root(prior_queue* queue, char symb);
void realloc_the_memory(prior_queue* queue, enum realloc_type type);
void heapify(prior_queue *queue, int64_t idx);
void Insert(prior_queue *queue, node *new_number);
void deallocating_the_queue(prior_queue* queue);


prior_queue* build_the_queue();

#endif