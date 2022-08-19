#ifndef CPUSCHEDULERSIMULATOR_HASHMATH_H
#define CPUSCHEDULERSIMULATOR_HASHMATH_H

#include <corecrt.h>
#include <stdbool.h>

bool is_prime(size_t);
size_t next_prime(size_t);
size_t hash_str(const char*);
#endif
