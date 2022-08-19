#ifndef CPUSCHEDULERSIMULATOR_LINKEDLIST_H
#define CPUSCHEDULERSIMULATOR_LINKEDLIST_H

#include <corecrt.h>
#include <stdbool.h>
#include "../linkedstructs.h"

typedef struct
{
    node* head;
    node* tail;
    linked_metadata metadata;
} linkedlist;

//make arg[0] NULL if you don't plan on using ls_contains, ls_delete_element, or ls_get_data.
//If you do, either initialize equals in this init function or by assigning to ls->metadata.equals afterwards
linkedlist* init_linkedlist(bool (*equals)(const void*, const void*));
void ls_add(linkedlist*, void*);
void* ls_delete_at(linkedlist*, size_t);
void* ls_delete_first(linkedlist*);
void* ls_delete_element(linkedlist* ls, void* element);
bool ls_empty(linkedlist*);
void free_ls(linkedlist*ls, bool free_data);
bool ls_contains(linkedlist*, void* data);
void* ls_get_data(linkedlist*, void* data);
void* ls_get_at(linkedlist*, size_t);
#endif
