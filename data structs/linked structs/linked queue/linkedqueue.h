#ifndef CPUSCHEDULERSIMULATOR_LINKEDQUEUE_H
#define CPUSCHEDULERSIMULATOR_LINKEDQUEUE_H

#include <stdbool.h>
#include "../linkedstructs.h"

typedef struct
{
    node* head;
    node* tail;
    linked_metadata metadata;
} queue;

///pass NULL if you don't want a equals function
queue* init_queue(bool (*equals)(const void*, const void*));
void* dequeue(queue*);
void enqueue(queue*,void*);
bool q_empty(queue *q);
void* peekq(queue *q);
void free_q(queue*, bool);
#endif //CPUSCHEDULERSIMULATOR_LINKEDQUEUE_H
