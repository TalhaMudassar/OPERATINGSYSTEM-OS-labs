//code first thread find the fibnonci of the number 
//second thread find the factoral of the number 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to calculate the Fibonacci series
void *fibonacci(void *ptr) {
    int n = *(int *)ptr;
    int *fib = (int *)malloc((n + 1) * sizeof(int));

    if (n >= 0) fib[0] = 0;
    if (n >= 1) fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib;
}

// Function to calculate the factorial
void *factorial(void *ptr) {
    int n = *(int *)ptr;
    int *fact = (int *)malloc(sizeof(int));

    *fact = 1;
    for (int i = 1; i <= n; i++) {
        *fact *= i;
    }

    return fact;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    pthread_t tid1, tid2;
    void *ret1, *ret2;

    pthread_create(&tid1, NULL, fibonacci, (void *)&number);
    pthread_create(&tid2, NULL, factorial, (void *)&number);

    pthread_join(tid1, &ret1);
    pthread_join(tid2, &ret2);

    int *fib = (int *)ret1;
    int *fact = (int *)ret2;

    printf("Fibonacci series up to %d: \n", number);
    for (int i = 0; i <= number; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    printf("Factorial of %d: %d\n", number, *fact);

    free(fib);
    free(fact);

    return 0;
}
