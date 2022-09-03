#ifndef HASHMATH_H
#define HASHMATH_H

#include <corecrt.h>
#include <stdbool.h>

bool is_prime(int);
int next_prime(int);
int hash_str(const char*);
int hash_int(int n);
int prev_prime(int n);

#endif
