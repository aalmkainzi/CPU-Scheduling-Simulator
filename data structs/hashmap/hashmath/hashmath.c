#include <math.h>
#include <string.h>
#include <limits.h>
#include "hashmath.h"

bool is_prime(int n)
{
    if(!(n%2))
        return false;
    int end = floor(sqrt(n));
    for (int i = 2; i <= end; ++i)
        if(!(n%i))
            return false;
    return true;
}

int next_prime(int n)
{
    while(!is_prime(n++));
    return n-1;
}

int prev_prime(int n)
{
    while(!is_prime(n--));
    return n+1;
}

int hash_str(const char*str)
{
    int len = strlen(str);
    int p = next_prime(len);
    int m = 1000000009; //large prime number
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum + (str[i]*((int)pow(p,i)));
    }
    return sum % m;
}

int hash_int(int n)
{
    const ssize_t sqrt_max = floor(sqrt(ULLONG_MAX));
    if(n > sqrt_max)
        n = floor(sqrt(n));
    return n*n;
}