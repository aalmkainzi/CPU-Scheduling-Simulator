#include <stdlib.h>
#include "linkedlist.h"

linkedlist* init_linkedlist(bool (*equals)(const void*, const void*))
{
    linkedlist* ret = calloc(1, sizeof(linkedlist));
    ret->metadata.size = 0;
    ret->metadata.equals = equals;
    return ret;
}

void ls_add(linkedlist*ls, void*data)
{
    linked_add(&ls->head, &ls->tail, data, &ls->metadata.size);
    /*
    if(ls_empty(ls))
    {
        ls->head = calloc(1, sizeof(node));
        ls->head->data = data;
        ls->tail = ls->head;
    }
    else
    {
        ls->tail->next = calloc(1, sizeof(node));
        ls->tail->next->data = data;
        ls->tail = ls->tail->next;
    }
    ls->metadata.size++;
    */
}

void* ls_delete_at(linkedlist* ls, size_t index)
{
    return linked_delete_at(&ls->head, &ls->tail, index, &ls->metadata.size);
    /*
    if(ls_empty(ls))
        return NULL;
    if(index==0)
    {
        void* ret = ls->head->data;
        node* temp = ls->head->next;
        free(ls->head);
        ls->head = temp;
        ls->metadata.size--;
        return ret;
    }
    node* current = ls->head;
    index--;
    while(index--)
    {
        current = current->next;
    }
    void* ret = current->next->data;
    node* temp = current->next->next;
    free(current->next);
    current->next = temp;
    ls->metadata.size--;
    return ret;
    */
}

void* ls_delete_first(linkedlist*ls)
{
    return ls_delete_at(ls,0);
}

void* ls_delete_element(linkedlist* ls, void* element)
{
    return linked_delete_element(&(ls->head), &ls->tail, element, &(ls->metadata));
    /*
    node* current = ls->head;
    for (size_t n = ls->metadata.size; n ; n--)
    {
        if(equals(current->data, element))
        {
            ls_delete_at(ls, n);
            return true;
        }
        current = current->next;
        n--;
    }
    return false;
    */
}

bool ls_empty(linkedlist*ls)
{
    return linked_empty(&ls->metadata);
}

void free_ls(linkedlist*ls, bool free_data)
{
    free_linked(ls, ls->head, free_data);
}

bool ls_contains(linkedlist*ls, void* data)
{
    return linked_contains(ls->head, data, &ls->metadata);
}

void* ls_get_data(linkedlist*ls, void* data)
{
    return linked_get(ls->head, data, &ls->metadata);
}

void* ls_get_at(linkedlist* ls, size_t i)
{
    return linked_get_at(ls->head, i);
}