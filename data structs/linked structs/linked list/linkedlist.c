#include <stdlib.h>
#include <stdio.h>
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
    node* tail = ls->tail;
    if (!tail)
    {
        ls->tail = calloc(1, sizeof(node));
        ls->tail->data = data;
        ls->head =ls->tail;
    } 
    else
    {
        tail->next = calloc(1, sizeof(node));
        tail->next->data = data;
        ls->tail = tail->next;
    }
    ls->metadata.size++;
}

void* ls_delete_at(linkedlist* ls, int index)
{
    int i = index;
    void *ret;
    ls->metadata.size--;
    if(!i)
    {
        ret = (*&ls->head)->data;
        node *temp = (*&ls->head)->next;
        free(*&ls->head);
        (*&ls->head) = temp;
        if (!*&ls->metadata.size)
        {
            *&ls->tail = *&ls->head;
        }
    } 
    else
    {
        node *current = ls->head;
        i--;
        while (i--)
        {
            current = current->next;
        }
        node *temp = current->next->next;
        ret = current->next->data;
        free(current->next);
        current->next = temp;
    }
    return ret;
}

void* ls_delete_first(linkedlist*ls)
{
    return ls_delete_at(ls,0);
}

void* ls_delete_element(linkedlist* ls, void* element)
{
    node* head = ls->head;
    if(!head)
        return NULL;
    bool (*equals)(const void*, const void*) = ls->metadata.equals;
    if(equals(head->data, element))
    {
        node* temp = head->next;
        void* ret = head->data;
        free(head);
        ls->head = temp;
        ls->metadata.size--;
        if(!ls->metadata.size)
        {
            ls->tail = temp;
        }
        return ret;
    }
    else
    {
        node* prev_node = NULL;
        for(node* current = head; current->next; current = current->next)
        {
            if (equals(current->next->data, element))
            {
                prev_node = current;
                break;
            }
        }
        if(prev_node)
        {
            node* temp = prev_node->next->next;
            void* ret = prev_node->next->data;
            free(prev_node->next);
            prev_node->next = temp;
            ls->metadata.size--;
            return ret;
        }
        return NULL;
    }
}

bool ls_empty(linkedlist*ls)
{
    return !ls->metadata.size;
}

void free_nodes(node*linked_struct_head, bool free_data)
{
    node* current = linked_struct_head;
    if(free_data)
        while(current)
        {
            node* temp = current->next;
            free(current->data);
            free(current);
            current = temp;
        }
    else
        while(current)
        {
            node* temp = current->next;
            free(current);
            current = temp;
        }
}

void free_ls(linkedlist*ls, bool free_data)
{
    free_nodes(ls->head, free_data);
    free(ls);
}

bool ls_contains(linkedlist*ls, void* data)
{
    bool (*equals)(const void *, const void *) = ls->metadata.equals;
    for(node* n = ls->head; n; n=n->next)
        if(equals(data, n->data))
            return true;
    return false;
}

void* ls_get_data(linkedlist*ls, void* data)
{
    node *current = ls->head;
    while (!(&ls->metadata)->equals(data, current->data))
        current = current->next;
    return current->data;
}

void* ls_get_at(linkedlist* ls, int i)
{
    if(ls->metadata.size < i)
    {
        fprintf(stderr, "invalid index of %d for linked list of size %d\n", i, ls->metadata.size);
        exit(1);
    }
    node* current = ls->head;
    while(i--)
        current = current->next;
    return current->data;
}