#ifndef CPUSCHEDULERSIMULATOR_HASHMAP_H
#define CPUSCHEDULERSIMULATOR_HASHMAP_H
#include "../linked structs/linked list/linkedlist.h"

///a hashmap implementation using external chaining for collisions

typedef struct
{
    void* key;
    void* val;
} pair;

typedef struct
{
    linkedlist* arr;
    bool (*equals)(const void*, const void**);
    size_t (*hash_val)(const void*);
    size_t size;
    size_t buffer_width;
} hashmap;

///arg[0] should be the number of element to insert into the hashmap, if unknown make it sufficiently large
///always make arg[1] be in (data*, data**) form
hashmap* init_hashmap(size_t, bool (*)(const void*, const void**), size_t(*)(const void*));
void hashmap_add(hashmap*, void*, void*);
bool hashmap_contains_key(hashmap*, void*);
bool hashmap_delete(hashmap*, void*);
void* hashmap_get_val_of(hashmap*, void*);
///returns old val so you can free it
void* hashmap_update(hashmap*, void*, void*);
void free_hashmap(hashmap*, bool, bool);
void hashmap_to_arr(hashmap*, void**buffer);
#endif

