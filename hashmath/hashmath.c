#include <math.h>
#include <string.h>
#include <limits.h>
#include "hashmath.h"

bool is_prime(size_t n)
{
    if(!(n%2))
        return false;
    int end = floor(sqrt(n));
    for (int i = 2; i <= end; ++i)
        if(!(n%i))
            return false;
    return true;
}

size_t next_prime(size_t n)
{
    while(!is_prime(n))
        n++;
    return n;
}

size_t hash_str(const char*str)
{
    size_t len = strlen(str);
    size_t p = next_prime(len);
    size_t m = pow(10,9)+9;//ULLONG_MAX;
    size_t sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum + (str[i]*((size_t)pow(p,i)));
    }
    return sum % m;
}

size_t hash_ints(ssize_t n)
{
    const ssize_t sqrt_max = floor(sqrt(ULLONG_MAX));//4294967296;
    if(n > sqrt_max)
        n = floor(sqrt(n));
    return ((size_t)n)*((size_t)n);
}