#include <stdio.h>
#include <stdlib.h>

/*
./fib N METHOD

N = positive integer index
METHOD = 'i' for iterative, 'r' for recursive

Outputs the first N Fibonacci numbers using a memoized version
of the specified method.
*/

#define MAX_LEN 1024
typedef unsigned long long (*FibFunc)(unsigned long long);
FibFunc fib_provider;

unsigned long long iter_fib(unsigned long long fibIndex) {
    
    unsigned long long previous = 0;
    unsigned long long result = 1;

    for (int ix = 0; ix <= fibIndex - 2; ix++) {
        unsigned long long temp = previous + result;
        previous = result;
        result = temp;   
    }

    return result;
}

unsigned long long rec_fib(unsigned long long fibIndex) {

    if(fibIndex < 2) {
        return fibIndex;
    }

    return (*fib_provider)(fibIndex - 1) + (*fib_provider)(fibIndex - 2);
}


FibFunc chosenFunc;

unsigned long long memo_fib(unsigned long long fibIndex) {
    
   static unsigned long long memo[MAX_LEN];


    if (memo[fibIndex] != 0) {
        return memo[fibIndex];
    }

    memo[fibIndex] = (*chosenFunc)(fibIndex);
    return memo[fibIndex];
}


int main(int argc, char * argv[]) {

    unsigned long long fibIndex = atoi(argv[1]) - 1;

    if (*argv[2] == 'r') {
        chosenFunc = rec_fib;
        fib_provider = memo_fib;
        printf("%llu\n", memo_fib(fibIndex));
    }
    else if (*argv[2] == 'i') {
        chosenFunc = iter_fib;
        fib_provider = memo_fib;
        printf("%llu\n", memo_fib(fibIndex));
    }
    
   return 0;
}


