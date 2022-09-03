#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "array.h"

void validate_index_in_range(int, int);

array* init_array(int init_cap, int element_size, bool (*equals)(const void*, const void*))
{
    array* arr = malloc(sizeof(array));
    arr->cap = init_cap;
    arr->size = 0;
    arr->element_size = element_size;
    arr->arr = calloc(arr->cap, element_size);
    arr->equals = equals;
    return arr;
}

void set_array(array* arr, int init_cap, int element_size, bool (*equals)(const void*, const void*))
{
    arr->cap = init_cap;
    arr->size = 0;
    arr->element_size = element_size;
    arr->arr = calloc(arr->cap, element_size);
    arr->equals = equals;
}

void arr_add_at(array *a, const void *element, int index)
{
    if(index>a->size || index < 0)
    {
        fprintf(stderr, "invalid index of %d on an array of size %d\n", index, a->size);
        exit(1);
    }
    if(a->size == a->cap)
    {
        a->cap = a->cap*2;
        a->arr = realloc(a->arr, a->cap*a->element_size);
    }
    if(index == a->size)
    {
        memcpy(a->arr+(a->element_size*a->size), element, a->element_size);
    }
    else
    {
        memmove(a->arr+(a->element_size*index+a->element_size), a->arr+(a->element_size*index), (a->size - index) * a->element_size);
        memcpy(a->arr+(a->element_size*index), element, a->element_size);
    }
    a->size++;
}
void arr_add(array *a, const void *element)
{
    arr_add_at(a, element, a->size);
}

void arr_delete_at(array *a, int index)
{
    validate_index_in_range(a->size, index);
    if(index != a->size-1)
    {
        memmove(a->arr+(index * a->element_size), a->arr+(index * a->element_size + a->element_size), (a->size - index) * a->element_size - a->element_size);
    }
    a->size--;
}

void arr_delete_last(array *a)
{
    arr_delete_at(a, a->size-1);
}

void* arr_delete_element(array*a, void* elm)
{
    for (int i = 0; i < a->size; ++i)
    {
        if (a->equals(a->arr + i, elm))
        {
            void* ret_val = a->arr+i;
            arr_delete_at(a, i);
            return ret_val;
        }
    }
    return NULL;

}

void* arr_get_at(array *a, int index)
{
    validate_index_in_range(a->size, index);
    return a->arr+(index * a->element_size);
}

void validate_index_in_range(int size, int index)
{
    if(index >= size || index < 0)
    {
        fprintf(stderr, "invalid index of %d on an array of size %d\n", index, size);
        exit(1);
    }
}

void* arr_get_last(array *a)
{
    return arr_get_at(a, a->size-1);
}

void free_array(array*a)
{
    free(a->arr);
    free(a);
}

void shrink_to_fit(array*a)
{
    if(a->size == a->cap)
        return;
    a->arr = realloc(a->arr, a->size*a->element_size);
}

bool arr_empty(array*a)
{
    return !a->size;
}

int arr_memsize(array *a)
{
    return a->element_size*a->cap;
}

int arr_contains(array* a, void* elm)
{
    for (int i = 0; i < a->size; ++i)
        if(a->equals(a->arr+i, elm))
            return i;
    return -1;
}

void* arr_get_element(array* a, void* elm)
{
    int index = arr_contains(a, elm);
    if(index!=-1)
        return arr_get_at(a, index);
    return NULL;
}

void merge(void* left, size_t n_of_elements_left, void* right, size_t n_of_elements_right, size_t size_of_elements, int (*cmp)(const void *, const void *), void* merged_buffer)
{
    size_t merged_size = n_of_elements_left + n_of_elements_right;
    for (int i = 0, left_counter = 0, right_counter = 0; i < merged_size; ++i)
    {
        if(left_counter < n_of_elements_left && (
                right_counter >= n_of_elements_right ||
                cmp(left + left_counter * size_of_elements, right + right_counter * size_of_elements) <= 0))
        {
            memcpy(merged_buffer+(i*size_of_elements), left+(left_counter*size_of_elements), size_of_elements);
            left_counter++;
        }
        else
        {
            memcpy(merged_buffer+(i*size_of_elements), right+(right_counter*size_of_elements), size_of_elements);
            right_counter++;
        }
    }
}

void msort(void* base, size_t num_of_elements, size_t size_of_elements, int (*cmp)(const void *,const void *))
{
    if(num_of_elements <= 1)
        return;

    size_t right_start = num_of_elements/2;

    msort(base, right_start, size_of_elements, cmp);
    msort(base+(right_start*size_of_elements), num_of_elements-right_start, size_of_elements, cmp);

    size_t n_of_elements_right = num_of_elements - right_start;

    void* merged = calloc(num_of_elements, size_of_elements);
    merge(base, right_start, base + (right_start * size_of_elements), n_of_elements_right, size_of_elements, cmp, merged);
    memcpy(base, merged, size_of_elements*(right_start + n_of_elements_right));
    free(merged);
}

