#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <corecrt.h>
#include <stdbool.h>

typedef struct
{
    int size;
    bool (*equals)(const void*, const void*);
    int element_size; //TODO implement this
} linked_metadata;

typedef struct node
{
    struct node* next;
    void* data;
} node;

typedef struct
{
    node* head;
    node* tail;
    linked_metadata metadata;
} linkedlist;

//make arg[0] NULL if you won't use ls_contains, ls_delete_element, or ls_get_data.
//If you will, either initialize equals in this init function or by assigning to ls->metadata.equals afterwards
linkedlist* init_linkedlist(bool (*equals)(const void*, const void*));
void ls_add(linkedlist*, void*);
void* ls_delete_at(linkedlist*, int);
void* ls_delete_first(linkedlist*);
void* ls_delete_element(linkedlist* ls, void* element);
bool ls_empty(linkedlist*);
void free_nodes(node*linked_struct_head, bool free_data);
void free_ls(linkedlist*ls, bool free_data);
bool ls_contains(linkedlist*, void* data);
void* ls_get_data(linkedlist*, void* data);
void* ls_get_at(linkedlist*, int);
#endif
