#include <stdlib.h>
#include <stdio.h>
#include "linkedstructs.h"

void free_nodes(node*linked_struct_head, bool free_data)
{
    node* current = linked_struct_head;
    if(free_data)
    {
        while(current)
        {
            node* temp = current->next;
            free(current->data);
            free(current);
            current = temp;
        }
    }
    else
    {
        while(current)
        {
            node* temp = current->next;
            free(current);
            current = temp;
        }
    }
}

void free_linked(void* linked_struct, node*head, bool free_data)
{
    free_nodes(head, free_data);
    free(linked_struct);
}


void linked_add(node**head_ptr, node**tail_ptr, void*data, size_t* size)
{
    node* tail = *tail_ptr;
    if(!tail)
    {
        *tail_ptr = calloc(1, sizeof(node));
        (*tail_ptr)->data = data;
        (*head_ptr) = *tail_ptr;
    }
    else
    {
        tail->next = calloc(1, sizeof(node));
        tail->next->data = data;
        (*tail_ptr) = tail->next;
    }
    (*size)++;
}

void linked_add_at(node** head_ptr, node** tail_ptr, void *data, size_t i, size_t* size)
{
    if(!i)
    {
        node* new_head = malloc(sizeof(node));
        new_head->data = data;
        new_head->next = *head_ptr;
        *head_ptr = new_head;
        if(!size)
        {
            (*tail_ptr) = new_head;
        }
    }
    else
    {
        node* current = *head_ptr;
        i--;
        while(i--)
        {
            current = current->next;
        }
        node* new_node = calloc(1, sizeof(node));
        new_node->data = data;
        new_node->next = current->next;
        current->next = new_node;
    }
    (*size)++;
}

void* linked_delete_at(node** head_ptr, node** tail_ptr, size_t i, size_t *size)
{
    void* ret;
    (*size)--;
    if(!i)
    {
        ret = (*head_ptr)->data;
        node* temp = (*head_ptr)->next;
        free(*head_ptr);
        (*head_ptr) = temp;
        if(!*size)
        {
            *tail_ptr = *head_ptr;
        }
    }
    else
    {
        node* current = *head_ptr;
        i--;
        while(i--)
        {
            current = current->next;
        }
        node* temp = current->next->next;
        ret = current->next->data;
        free(current->next);
        current->next = temp;
    }
    return ret;
}

void* linked_delete_element(node** head_ptr, node** tail_ptr, void* element, linked_metadata* lmd)
{
    node* head = *head_ptr;
    if(!head)
        return NULL;
    bool (*equals)(const void*, const void*) = lmd->equals;
    if(equals(head->data, element))
    {
        node* temp = head->next;
        void* ret = head->data;
        free(head);
        (*head_ptr) = temp;
        lmd->size--;
        if(!lmd->size)
        {
            (*tail_ptr) = temp;
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
            lmd->size--;
            return ret;
        }
        return NULL;
    }
}

bool linked_contains(node* head, void* data, linked_metadata* lmd)
{
    for(node* n = head; n; n=n->next)
        if(lmd->equals(data, n->data))
            return true;
    return false;
}

void* linked_get_at(node* head, size_t i)
{
    node* current = head;
    while(i--)
        current = current->next;
    return current->data;
}

void* linked_get(node* head, void* data, linked_metadata* lmd)
{
    node* current = head;
    while(!lmd->equals(data, current->data))
        current = current->next;
    return current->data;
}