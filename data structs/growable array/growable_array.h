#ifndef CPUSCHEDULERSIMULATOR_GROWABLE_ARRAY_H
#define CPUSCHEDULERSIMULATOR_GROWABLE_ARRAY_H
#include <stdlib.h>
#include <stdbool.h>

///a simple dynamic array


//TODO make arr void* instead of void** and make 'size_t element_size' a member in the struct so the arr can take non-pointer types

typedef struct
{
    void**arr;
    int cap;
    int size;
    int growth_rate;
} array;


array* init_array(int);
void arr_add_at(array *a, void *element, int index);
void arr_add(array *a, void *element);
void* arr_delete_first(array *a);
void* arr_delete_at(array *a, int index);
void* arr_delete_last(array *a);
void* arr_get_at(array *a, int index);
void* arr_get_last(array *a);
void get_arr(array*, void**);
int arr_memsize(array *a);
void free_array(array*a, bool free_data);
void shrink_to_fit(array*a);
bool arr_empty(array*);
void msort(void*, size_t,size_t, int(*)(const void*, const void*));

//int* generate_rand_arr(int*);
//bool is_sorted(void*arr, size_t n_of_elements, size_t size_of_elements, int (*cmp)(const void *,const void *));
//void print_arr(int*, size_t);
#endif //CPUSCHEDULERSIMULATOR_GROWABLE_ARRAY_H
