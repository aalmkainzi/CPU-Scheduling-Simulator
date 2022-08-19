#ifndef CPUSCHEDULERSIMULATOR_LINKEDSTRUCTS_H
#define CPUSCHEDULERSIMULATOR_LINKEDSTRUCTS_H
#include <stdbool.h>

///file containing common structs and functions for singly linked lists

typedef struct
{
    size_t size;
    bool (*equals)(const void*, const void*);
} linked_metadata;

typedef struct node
{
    struct node* next;
    void* data;
} node;

///frees all the nodes of linked structure by passing the head node
///if arg[2] is true the function will free the data member of every node,
///if you call it with arg[2] being false with no other way to access the data you'll have a memory leak
///to call this with linked list and want to free data you do: free_nodes(ls->head, true)
void free_linked(void* linked_struct, node* linked_struct_head, bool free_data);

///returns 'true' if list has no elements, 'false' otherwise
static inline bool linked_empty(linked_metadata* lmd)
{
    return !lmd->size;
}

void linked_add(node**, node**, void*, size_t*);

void linked_add_at(node**, node**, void*, size_t, size_t*);

static inline size_t linked_size(linked_metadata* lmd)
{
    return lmd->size;
}

void *linked_delete_at(node**, node**, size_t , size_t*);
void* linked_delete_element(node**, node**, void*, linked_metadata*);
bool linked_contains(node*, void*, linked_metadata*);
void* linked_get(node*, void*, linked_metadata*);
void* linked_get_at(node*, size_t);

#endif
