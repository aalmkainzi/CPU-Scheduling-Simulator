#include "hashmap.h"
#include "hashmath/hashmath.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

hashmap* init_hashmap(int s, bool (*equals)(const void*, const void*), int(*hash_val)(const void*), int key_size, int val_size)
{
    hashmap* ret = malloc(sizeof(hashmap));
    set_hashmap(ret, s, equals, hash_val, key_size, val_size);
    return ret;
}

void set_hashmap(hashmap* hm, int s, bool (*equals)(const void*, const void*), int(*hash_val)(const void*), int key_size, int val_size)
{
    hm->equals = equals;
    hm->hash_val = hash_val;
    hm->key_size = key_size;
    hm->val_size = val_size;
    s = ceil(s * 1.3);
    s = next_prime(s);
    hm->buffer_width = s;
    hm->arrays = calloc(s, sizeof(pair_soa));
}

int hm_hash(hashmap* hm, void* key)
{
    return hm->hash_val(key) % hm->buffer_width;
}

void hashmap_add(hashmap*hm, void* key, void* val)
{
    pair_soa soa = hm->arrays[hm_hash(hm, key)];
    if(soa.cap==0)
    {
        soa.cap = 8;
        soa.buffer = malloc((hm->key_size*soa.cap) + (hm->val_size*soa.cap));
        soa.v_start = soa.buffer + (hm->key_size*soa.cap);
    }
    else if(soa.cap == soa.size)
    {
        soa.cap *= 2;
        soa.buffer = realloc(soa.buffer, (soa.cap * hm->key_size) + (soa.cap * hm->val_size));
        soa.v_start = soa.buffer + (hm->key_size * soa.cap); //because we reallocated the buffer
        memmove(soa.v_start+(hm->val_size * soa.size), soa.v_start, hm->val_size*(soa.size)); //this is hacky. only works if growth rate is 2, test it though
    }
    memcpy(soa.buffer+(hm->key_size*soa.k_empty_start), key, hm->key_size);
    memcpy(soa.v_start+(hm->val_size*soa.v_empty_start), val, hm->val_size);
    soa.size++;
    soa.k_empty_start++;
    soa.v_empty_start++;
}

bool hashmap_contains_key(hashmap* hm, void* key)
{
    pair_soa soa = hm->arrays[hm_hash(hm, key)];
    for (int i = 0; i < soa.size; ++i)
    {
        if(hm->equals(soa.buffer + (i * hm->key_size), key)) return true;
    }
    return false;
}

bool hashmap_delete(hashmap* hm, void* key)
{
    pair_soa soa = hm->arrays[hm_hash(hm, key)];
    int index = -1;
    for (int i = 0; i < soa.size; ++i)
    {
        if(hm->equals(soa.buffer + (i * hm->key_size), key))
        {
            index = i;
            break;
        }
    }
    if(index==-1) return false;
    memcpy(soa.buffer + (index * hm->key_size), soa.buffer + ((soa.k_empty_start - 1) * hm->key_size), hm->key_size);
    memcpy(soa.v_start+(index*hm->val_size), soa.v_start+((soa.v_empty_start-1)*hm->val_size), hm->val_size);
    soa.v_empty_start -= 1;
    soa.k_empty_start -= 1;
    soa.size--;
    return true;
}

void* hashmap_get_val_of(hashmap* hm, void* key)
{
    pair_soa soa = hm->arrays[hm_hash(hm, key)];
    int index = -1;
    for (int i = 0; i < soa.size; ++i)
    {
        if(hm->equals(soa.buffer + (i * hm->key_size), key))
        {
            index = i;
            break;
        }
    }
    if(index==-1) return NULL;
    return soa.v_start+(index*hm->val_size);
}

bool hashmap_update(hashmap* hm, void* key, void* new_val)
{
    pair_soa soa = hm->arrays[hm_hash(hm, key)];
    int index = -1;
    for (int i = 0; i < soa.size; ++i)
    {
        if(hm->equals(key, soa.buffer + (i * hm->key_size)))
        {
            index = i;
            break;
        }
    }
    if(index!=-1)
    {
        memcpy(soa.v_start + (index * hm->val_size), new_val, hm->val_size);
        return true;
    }
    return false;
}

void free_hashmap(hashmap* hm)
{
    for (int i = 0; i < hm->buffer_width; ++i)
        free(hm->arrays[i].buffer);
    free(hm->arrays);
}

void hashmap_to_arr(hashmap* hm, void* buffer)
{
    int count = 0;
    for (int i = 0; i < hm->buffer_width; ++i)
    {
        pair_soa current_soa = hm->arrays[i];
        memcpy(buffer+(count*hm->val_size), current_soa.v_start, current_soa.size*hm->val_size);
        count+=current_soa.size;
    }
}
