#include "growable_array.h"
#include <string.h>

array* init_array(int init_cap)
{
    array* a = malloc(sizeof (array));
    a->cap = init_cap;
    a->size = 0;
    a->growth_rate = 2;
    a->arr = calloc(a->cap, sizeof(void*));
    return a;
}

void arr_add_at(array* a, void* element, int index)
{
    if(a->size == a->cap)
    {
        a->cap = a->cap*a->growth_rate;
        a->arr = realloc(a->arr, a->cap*sizeof(void*));
    }
    if(index == a->size)
    {
        a->arr[a->size] = element;
    }
    else
    {
        memmove(a->arr[index + 1], a->arr[index], (a->cap - index) * sizeof(void*));
        a->arr[index] = element;
    }
    a->size++;
}

void arr_add(array* a, void* element)
{
    arr_add_at(a, element, a->size);
}

void* arr_delete_at(array* a, int index)
{
    if(index>=a->size)
        return NULL;
    void* ret = a->arr[index];
    memmove(a->arr+index, a->arr+index+1, (a->cap - (index+1))*sizeof(void*)); //TODO maybe use size instead of cap?
    a->size--;
    return ret;
}

void* arr_delete_last(array*a)
{
    if(a->size==0)
        return NULL;
    void* ret = a->arr[a->size-1];
    a->size--;
    return ret;
}

void* arr_delete_first(array*a)
{
    if(a->size==0)
        return NULL;
    void* ret = a->arr[0];
    memmove(a->arr, a->arr+1, (a->cap-1)*sizeof(void*)); //TODO maybe use size instead of cap?
    a->size--;
    return ret;
}

void* arr_get_at(array*a, int index)
{
    if(index>=a->size || index<0)
        return NULL;
    return a->arr[index];
}

void* arr_get_last(array*a)
{
    return arr_get_at(a, a->size - 1);
}

int arr_memsize(array*a)
{
    return a->size*sizeof(void*);
}

void get_arr(array*a, void**buffer)
{
    memcpy(buffer, a->arr, arr_memsize(a));
}

void shrink_to_fit(array*a)
{
    if(a->size==a->cap)
        return;
    a->arr = realloc(a->arr, a->size*sizeof(void*));
}

void free_array(array*a, bool free_data)
{
    if(free_data)
    {
        for (int i = 0; i < a->size; ++i)
            free(a->arr[i]);
    }
    free(a->arr);
    free(a);
}

bool arr_empty(array*a)
{
    return !a->size;
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

//to sort a dynamic array pass array*->arr in argument 0, array*->size in argument 1, and sizeof(void*) in argument 2
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

/* testing functions.
int* generate_rand_arr(int*size)
{
    srand(time(NULL));
    *size = rand()%100;
    int* randArray = calloc(*size, sizeof(int));
    for(int i=0;i<*size;i++)
        randArray[i]=rand()%100;   //Generate number between 0 to 99
    return randArray;
}

bool is_sorted(void*arr, size_t n_of_elements, size_t size_of_elements, int (*cmp)(const void *,const void *))
{
    for (int i = 0; i < n_of_elements-1; ++i)
        if(cmp(arr+(i*size_of_elements), arr+((i+1)*size_of_elements)) > 0)
            return false;
    return true;
}

void print_arr(int*arr, size_t n)
{
    if(n>0)
        printf("%d", arr[0]);
    for (int i = 1; i < n; ++i)
        printf(", %d", arr[i]);
    puts("");
}

int cmpint(const int*a, const int*b)
{
    return *a-*b;
}
*/