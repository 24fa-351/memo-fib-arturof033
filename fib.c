#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1024
typedef unsigned long long (*FibFunc)(unsigned long long fibIndex);


unsigned long long iter_fib(unsigned long long n) {
    
    unsigned long long result = 0;
    unsigned long long value1 = 0;
    unsigned long long value2 = 1;

    for (int i = 1; i <= n; i++)
    {
        result = value1 + value2;
        value2 = value1;
        value1 = result; 
    }

    return result;
}

unsigned long long rec_fib(unsigned long long n) {
    
    if(n < 2)
    {
        return n;
    }

    return rec_fib(n - 1) + rec_fib(n - 2);
}


unsigned long long memo_fib(
    unsigned long long (*fib)(unsigned long long fibIndex), 
    unsigned long long n) {

   static unsigned long long memo[MAX_LEN];

    FibFunc chosenFunc = fib;

    if (memo[n] != 0) {
        return memo[n];
    }

    memo[n] = chosenFunc(n);
    return memo[n];
}

int main(int argc, char * argv[]) {

    unsigned long long N = atoi(argv[1]) - 1;

    if (*argv[2] == 'r')
    {
        printf("%llu", memo_fib(rec_fib, N));
    }
    else if (*argv[2] == 'i')
    {
        printf("%llu", memo_fib(iter_fib, N));
    }
    
   return 0;
}


