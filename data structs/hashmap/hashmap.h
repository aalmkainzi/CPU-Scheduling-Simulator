#ifndef HASHMAP_H
#define HASHMAP_H

#include <corecrt.h>
#include <stdbool.h>

///a cache aware hashmap implementation. using external chaining for collisions

typedef struct
{
    void* buffer;
    void* v_start;

    int k_empty_start; //indexed by key_size
    int v_empty_start; //indexed by val_size

    int cap;
    int size;
} pair_soa;

typedef struct
{
    bool (*equals)(const void*, const void*);
    int (*hash_val)(const void*);
    pair_soa* arrays;
    int size;
    int buffer_width;
    int key_size; //these are here and not in pair_soa because we don't want to duplicate the same thing for all indexes, since they all will have the same key and val sizes
    int val_size;
} hashmap;

//initializes a heap allocated hashmap. Need to provide the equals function for key comparing and a hash_val function that returns the hash code of your keys
hashmap* init_hashmap(int s, bool (*equals)(const void*, const void*), int(*hash_val)(const void*), int key_size, int val_size);
//you can use this if you don't want to heap allocate your hashmap struct, used like this: hashmap hm; set_hashmap(&hm,...)
void set_hashmap(hashmap* hm, int s, bool (*equals)(const void*, const void*), int(*hash_val)(const void*), int key_size, int val_size);
//adds a new entry to the hashmap. If you want to store pointers, do: hashmap_add(hm, &key_ptr, &val_ptr)
void hashmap_add(hashmap*hm, void* key, void* val);
//a regular contains function, returns true if element in hashmap (using the provided equals function at initialization), false if not
bool hashmap_contains_key(hashmap* hm, void* key);
//deletes the given key and its paired value from the hashmap using the equals function. returns true if element was in hashmap and was deleted, false if not in hashmap.
bool hashmap_delete(hashmap* hm, void* key);
//returns a pointer to the val paired with the given key, overflowing the val by putting in its address something bigger than val_size might corrector other vals or cause SEGFAULT;
// don't do: set_hashmap(hm,..., 2, 1); *hashmap_get_val_of(hm, "a") = 2; => writing an int (4 bytes) into the val address when you initialized tha hashmap with val_size of 1
void* hashmap_get_val_of(hashmap* hm, void* key);
//changes the old value corresponding to the given key with new_val. Returns true key is in hm and old val of key was replaced with new_val, false if key isn't in hm
bool hashmap_update(hashmap* hm, void* key, void* new_val);
//frees the hashmap, but not the hm pointer. If hm is heap allocated, and you want to free it, do: free_hashmap(hm); free(hm); => don't call free(hm) if your hashmap is not heap allocated
void free_hashmap(hashmap* hm);
//puts all the vals in hm into the given buffer, won't be in sorted order.
void hashmap_to_arr(hashmap* hm, void* buffer);
#endif

