#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "../linked list/linkedlist.h"

typedef struct
{
    linkedlist list;
} queue;


static inline queue* init_queue()
{
    return calloc(1, sizeof(queue));
}

static inline void* dequeue(queue*q)
{
    return ls_delete_at(&q->list, 0);
}

static inline void enqueue(queue*q,void*data)
{
    ls_add(&q->list, data);
}

static inline bool q_empty(queue*q)
{
    return ls_empty(&q->list);
}

static inline void* peekq(queue*q)
{
    return q->list.head->data;
}

static inline void free_q(queue* q, bool free_data)
{
    free_nodes(q->list.head, free_data);
    free(q);
}
#endif
