#include "queue.h"

void deallocating_the_queue(prior_queue* queue) {
    for (uint64_t i = 0; i < queue->size; ++i)
        free(queue->data[i]);
    free(queue->data);
}

void realloc_the_memory(prior_queue *queue, enum realloc_type type) {
    if (type == INCREASE) {
        if (queue->capacity == 0)
            queue->capacity = 1;
        else
            queue->capacity *= 2;
        node** per = (node**)malloc(sizeof(node*) * queue->capacity);
        for (uint64_t i = 0; i < queue->size; ++i)
            per[i] = queue->data[i];
        free(queue->data);
        queue->data = per;
    }
    else {
        if (queue->capacity == 1) {
            queue->capacity = 0;
            free(queue->data);
            queue->data = NULL;
        }
        else {
            queue->capacity /= 2;
            node** per = (node**)malloc(sizeof(node*) * queue->capacity);
            for (uint64_t i = 0; i < queue->size; ++i)
                per[i] = queue->data[i];
            free(queue->data);
            queue->data = per;
        }
    }
}

void heapify(prior_queue* queue, int64_t idx) {
    if (queue->size != 1) {
        int64_t max = idx;
        int64_t l = 2 * idx + 1;
        int64_t r = 2 * idx + 2;
        if (r < queue->size && queue->data[r]->freq < queue->data[max]->freq)
            max = r;
        if (l < queue->size && queue->data[l]->freq < queue->data[max]->freq)
            max = l;
        if (idx != max) {
            swap_elements(queue->data[idx], queue->data[max]);
            heapify(queue, max);
        }
    }
}

prior_queue *build_the_queue() {
    prior_queue* queue = (prior_queue*)malloc(sizeof(prior_queue));
    queue->data = NULL;
    queue->capacity = 0;
    queue->size = 0;
    return queue;
}

void deleting_a_root(prior_queue* queue, char symb) {
    int64_t id = 0;
    for (; id < queue->size; id++)
        if (symb == queue->data[id]->sym)
            break;
    swap_elements(queue->data[id], queue->data[queue->size - 1]);
    queue->size -= 1;
    for (id = (int64_t)(queue->size) / 2 - 1; id > -1; id--)
        heapify(queue, id);
}

void Insert(prior_queue *queue, node *new_number) {
    if (queue->size + 1 > queue->capacity)
        realloc_the_memory(queue, INCREASE);
    if (queue->size == 0) {
        queue->data[0] = new_number;
        queue->size ++;
    }
    else {
        queue->data[queue->size] = new_number;
        queue->size += 1;
        for (int64_t i = (int64_t) (queue->size) / 2 - 1; i >= 0; i--)
            heapify(queue, i);
    }
}