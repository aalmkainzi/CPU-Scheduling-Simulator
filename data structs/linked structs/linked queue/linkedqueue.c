#include <stdlib.h>
#include "linkedqueue.h"

queue* init_queue(bool (*equals)(const void*, const void*))
{
    queue* q = calloc(1, sizeof(queue));
    q->metadata.equals = equals;
    return q;
}

void* dequeue(queue*q)
{
    return linked_delete_at(&q->head, &q->tail, 0, &q->metadata.size);
/*    if(q->size==0)
        return NULL;
    node* temp = q->head->next;
    free(q->head);
    q->head = temp;
    q->size--;
    return temp ? temp->data : NULL;*/
}

void enqueue(queue*q,void*data)
{
    linked_add(&q->head, &q->tail, data, &q->metadata.size);
    /*if(q->size==0)
    {
        q->head = calloc(1, sizeof(node));
        q->head->data = data;
        q->tail = q->head;
    }
    else
    {
       q->tail->next = calloc(1, sizeof(node));
       q->tail->next->data = data;
       q->tail = q->tail->next;
    }
    q->size++;*/
}

bool q_empty(queue*q)
{
    return linked_empty(&q->metadata);
}

void* peekq(queue*q)
{
    return q->head->data;
}

void free_q(queue* q, bool free_data)
{
    free_linked(q, q->head, free_data);
}