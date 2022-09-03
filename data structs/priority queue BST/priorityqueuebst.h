#ifndef PRIORITYTREE_PRIORITYQUEUEBST_H
#define PRIORITYTREE_PRIORITYQUEUEBST_H
#include <stdbool.h>

///this list structure is a priority queue implementation using a bst. Uses a poll_node that points to its parent for faster polling (situational);

typedef struct pq_node
{
    struct pq_node* right;
    struct pq_node* left;
    void* data;
    int p;
} pq_node;

typedef struct
{
    struct pq_node* right;
    struct pq_node* parent;
    void* data;
    int p;
} poll_node;

typedef struct
{
    pq_node*root;
    poll_node*poll_node;
} priority_queue_bst;

priority_queue_bst* init_pqbst();
void pqbst_add_p(priority_queue_bst *pqbst, void *data, int p);
void pqbst_add_int(priority_queue_bst *pqbst, void *data, size_t size);
void* pqbst_poll(priority_queue_bst *pqbst);
void* pqbst_peek(priority_queue_bst *pqbst);
void free_pqbst(priority_queue_bst *pqbst, bool free_data);
bool pqbst_empty(priority_queue_bst*);

#endif