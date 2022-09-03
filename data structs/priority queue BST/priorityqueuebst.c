#include <stdlib.h>
#include <stdio.h>
#include "priorityqueuebst.h"

priority_queue_bst* init_pqbst()
{
    priority_queue_bst* qbst = calloc(1, sizeof(priority_queue_bst));
    return qbst;
}

void bst_add(pq_node*n, void* data, int p)
{
    if(p < n->p)
    {
        if(n->left!=NULL)
            bst_add(n->left,data,p);
        else
        {
            n->left = calloc(1, sizeof(pq_node));
            n->left->data = data;
            n->left->p = p;
        }
    }
    else if(p >= n->p)
    {
        if(n->right!=NULL)
            bst_add(n->right,data,p);
        else
        {
            n->right = calloc(1, sizeof(pq_node));
            n->right->data = data;
            n->right->p = p;
        }
    }
}

//only works with integer types __int8, __int16, and __int32; will use the list as priority (i.e. the lower the list the higher the priority)
void pqbst_add_int(priority_queue_bst*pqbst, void* data, size_t size)
{
    switch (size)
    {
        case sizeof(__int8):
        {
            pqbst_add_p(pqbst, data, *((__int8 *) data));
            break;
        }
        case sizeof(__int16):
        {
            pqbst_add_p(pqbst, data, *((__int16 *) data));
            break;
        }
        case sizeof(__int32):
        {
            pqbst_add_p(pqbst, data, *((__int32 *) data));
            break;
        }
        default:
        {
            perror("pqbst_add_int must be __int8 or __int16 or __int32");
            exit(1);
        }
    }
}

void pqbst_add_p(priority_queue_bst*pqbst, void* data, int p)
{
    if(pqbst->root == NULL)
    {
        pqbst->root = calloc(1, sizeof (pq_node));
        pqbst->root->data = data;
        pqbst->root->p = p;
        pqbst->poll_node = (poll_node *) pqbst->root;
    }
    else if(p < pqbst->poll_node->p)
    {
        poll_node* new_next = calloc(1, sizeof(poll_node));
        pq_node* old_next = (pq_node*) pqbst->poll_node;
        old_next->left = (pq_node*) new_next;
        new_next->parent = old_next;
        new_next->data = data;
        new_next->p = p;
        pqbst->poll_node = new_next;
    }
    else if(pqbst->poll_node->right && p <= pqbst->poll_node->right->p)
    {
        bst_add(pqbst->poll_node->right, data, p);
    }
    else
    {
        bst_add(pqbst->root, data, p);
    }
}

pq_node* min_node_parent_h(pq_node*n)
{
    return n->left->left!=NULL ? min_node_parent_h(n->left) : n;
}

pq_node* min_node_parent(pq_node*n)
{
    if(n==NULL || n->left==NULL)
    {
        return NULL;
    }
    else
    {
        return min_node_parent_h(n);
    }
}

void* pqbst_poll(priority_queue_bst*pqbst)
{
    if(pqbst->root == NULL)
    {
        return NULL;
    }
    if(pqbst->poll_node == (poll_node*)pqbst->root)
    {
        void* ret = pqbst->poll_node->list;
        pq_node* right = pqbst->root->right;
        free(pqbst->root);
        pqbst->root = right;
        if(pqbst->root==NULL || pqbst->root->left==NULL)
            pqbst->poll_node = (poll_node*) pqbst->root;
        else
        {
            pq_node* min_parent_left = min_node_parent(pqbst->root->left);
            if(min_parent_left==NULL)
            {
                pqbst->poll_node = (poll_node*) pqbst->root->left;
                pqbst->poll_node->parent = pqbst->root;
            }
            else
            {
                pqbst->poll_node = (poll_node*) min_parent_left->left;
                pqbst->poll_node->parent = min_parent_left;
            }
        }
        return ret;
    }
    else
    {
        void* ret = pqbst->poll_node->list;

        pq_node* old_next_rbst = pqbst->poll_node->parent->left = pqbst->poll_node->right;
        pq_node* min_parent_of_next_rbst = min_node_parent(old_next_rbst);
        pq_node* old_next_parent = pqbst->poll_node->parent;

        free(pqbst->poll_node);
        if(min_parent_of_next_rbst == NULL)
        {
            if(old_next_rbst == NULL)
            {
                if(old_next_parent == pqbst->root)
                {
                    pqbst->poll_node= (poll_node*) pqbst->root;
                    pqbst->poll_node->parent=NULL;
                }
                else
                {
                    pqbst->poll_node = (poll_node*) old_next_parent;
                    pqbst->poll_node->parent = min_node_parent(pqbst->root);
                }
            }
            else
            {
                pqbst->poll_node = (poll_node*) old_next_rbst;
                pqbst->poll_node->parent = old_next_parent;
            }
        }
        else
        {
            pqbst->poll_node = (poll_node*) min_parent_of_next_rbst->left;
            pqbst->poll_node->parent = min_parent_of_next_rbst;
        }
        return ret;
    }
}

void free_bst(pq_node*n, bool free_data, pq_node* poll_node)
{
    if(n!=NULL)
    {
        if(free_data)    free(n->data);
        if(n!=poll_node) free_bst(n->left, free_data, poll_node);
        free_bst(n->right, free_data, poll_node);
        free(n);
    }
}

void free_pqbst(priority_queue_bst* pqbst, bool free_data)
{
    free_bst(pqbst->root, free_data, (pq_node*)pqbst->poll_node);
    free(pqbst);
}


void* pqbst_peek(priority_queue_bst*pqbst)
{
    if(!pqbst->poll_node)
        return NULL;
    return pqbst->poll_node->list;
}

bool pqbst_empty(priority_queue_bst*pqbst)
{
    return !pqbst->root;
}

/*
void print_pqbst(priority_queue_bst*pqbst)
{
    char* next_data;
    bool alloced = false;
    if(pqbst->poll_node != NULL)
    {
        next_data = calloc(11,sizeof(char));
        alloced = true;
        sprintf(next_data, "%d", *((int*)pqbst->poll_node->list));
    }
    else
    {
        next_data = "None";
    }
    printf("poll_node is: %s\n\n", next_data);
    if(alloced)
        free(next_data);
    print2D(pqbst->root, (pq_node*) pqbst->poll_node);
    puts("\n");
}
*/