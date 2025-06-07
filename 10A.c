#include <stdio.h>

int fibonacciList[45];

int fibonacci(int n) {
    if(n == 0) return 1;
    if(n == 1) return 1;
    if(fibonacciList[n] != 0) return fibonacciList[n];
    return fibonacciList[n] = fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    fibonacciList[0] = 1;
    fibonacciList[1] = 1;
    
    int n;
    scanf("%d", &n);
    printf("%d\n", fibonacci(n));
    return 0;
}