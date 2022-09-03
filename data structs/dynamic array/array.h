#ifndef ARRAY_H
#define ARRAY_H
#include <stdbool.h>

typedef struct
{
    void *arr;
    int  cap;
    int  size;
    int  element_size;
    bool (*equals)(const void*, const void*);
} array;

array* init_array(int, int, bool (*equals)(const void*, const void*));
void set_array(array* arr, int init_cap, int element_size, bool (*equals)(const void*, const void*));
void arr_add_at(array *a, const void *element, int index);
void arr_add(array *a, const void *element);
void arr_delete_at(array *a, int index);
void arr_delete_last(array *a);
void* arr_get_at(array *a, int index);
void* arr_get_last(array *a);
int arr_memsize(array *a);
void free_array(array*a);
void shrink_to_fit(array*a);
bool arr_empty(array*);
int arr_contains(array*, void*);
void* arr_get_element(array*, void*);
void* arr_delete_element(array*, void*);
void msort(void*, size_t,size_t, int(*)(const void*, const void*));

static inline void arr_msort(array* a, int(*cmp)(const void*, const void*))
{
    msort(a->arr, a->size, a->element_size, cmp);
}

#endif
