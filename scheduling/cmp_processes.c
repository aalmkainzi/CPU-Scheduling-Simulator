#include <string.h>
#include "scheduling.h"
#include "../data structs/hashmap/hashmath/hashmath.h"

int cmp_processes_at(const process**a, const process**b)
{
    return a[0]->AT - b[0]->AT;
}

bool pmd_equals(const char*p1_name, const char**p2_name)
{
    return !strcmp(p1_name,*p2_name);
}

size_t hash_pmd(const char*p_name)
{
    return hash_str(p_name);
}
