#include "hashmap.h"
#include "../../hashmath/hashmath.h"
#include <stdlib.h>
#include <math.h>

hashmap* init_hashmap(size_t s, bool (*equals)(const void*, const void**), size_t(*hash_val)(const void*))
{
    hashmap* ret = calloc(1,sizeof(hashmap));
    ret->equals = equals;
    ret->hash_val = hash_val;
    s = ceil(s * 1.3);
    s = next_prime(s);
    ret->buffer_width = s;
    ret->arr = calloc(s, sizeof(linkedlist));
    return ret;
}

size_t hm_hash(hashmap* hm, void* key)
{
    return hm->hash_val(key) % hm->buffer_width;
}

void hashmap_add(hashmap*hm, void* key, void* val)
{
    pair* p = malloc(sizeof(pair));
    p->key = key;
    p->val = val;

    linkedlist* ls = &hm->arr[hm_hash(hm, key)];
    if(!ls->metadata.equals)
        ls->metadata.equals = hm->equals;
    if(!ls_contains(ls, key))
    {
        ls_add(ls, p);
        hm->size++;
    }
}

bool hashmap_contains_key(hashmap* hm, void* key)
{
    return ls_contains(&hm->arr[hm_hash(hm, key)], key);
}

bool hashmap_delete(hashmap* hm, void* key)
{
    void* deleted_elm = ls_delete_element(&hm->arr[hm_hash(hm, key)], key);
    if(deleted_elm)
        hm->size--;
    return deleted_elm;
}

void* hashmap_get_val_of(hashmap* hm, void* key)
{
    return ((pair*)ls_get_data(&hm->arr[hm_hash(hm, key)], key))->val;
}

void* hashmap_update(hashmap* hm, void* key, void* new_val)
{
    pair *p = (pair*) ls_get_data(&hm->arr[hm_hash(hm, key)], key);
    void* ret = p->val;
    p->val = new_val;
    return ret;
}

void free_hashmap(hashmap* hm, bool free_keys, bool free_vals)
{
    for (int i = 0; i < hm->buffer_width; ++i)
    {
        node* current = hm->arr[i].head;
        while(current)
        {
            node* temp = current->next;
            pair* p = current->data;
            if(free_keys) free(p->key);
            if(free_vals) free(p->val);
            free(p);
            free(current);
            current = temp;
        }
    }
    free(hm->arr);
    free(hm);
}

void hashmap_to_arr(hashmap* hm, void** buffer)
{
    size_t count = 0;
    for (int i = 0; i < hm->buffer_width; ++i) // && count < hm->size
    {
        node* current = hm->arr[i].head;
        while(current)
        {
            buffer[count++] = ((pair*)current->data)->val;
            current = current->next;
        }
    }
}