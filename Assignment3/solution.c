//  TALHA MUDASSAR       L1F22BSCS0379        OS-ASSIGNMENT_NO_3

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int start;
    int end;
    long par_product;
} DATA;

// Thread function to calculate partial factorial
void *calculate_partial_factorial(void *arg)
{
    DATA *data = (DATA *)arg;
    data->par_product = 1;
    for (int i = data->start; i <= data->end; i++)
    {
        data->par_product *= i;
    }
    printf("Thread processing range (%d to %d) produced partial result: %ld\n", data->start, data->end, data->par_product);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <M> <N>\n", argv[0]);
        printf("<M>: Number of threads to use (must be greater than 0).\n");
        printf("<N>: Number for which the factorial is to be calculated (must be greater than or equal to M).\n");
        return 1;
    }

    int M = atoi(argv[1]);
    int N = atoi(argv[2]);

    // Validate inputs
    if (N < M || M <= 0)
    {
        printf("Error: Ensure N >= M and M > 0.\n");
        return 1;
    }

    pthread_t tid[M];
    DATA thread_data[M];

    int each_thread_range = N / M;
    int remainder = N % M;

    int start = 1;
    for (int i = 0; i < M; i++)
    {
        thread_data[i].start = start;
        thread_data[i].end = start + each_thread_range - 1;

        if (i < remainder)
        {
            thread_data[i].end++;
        }

        thread_data[i].par_product = 1;

        if (pthread_create(&tid[i], NULL, calculate_partial_factorial, &thread_data[i]) != 0)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }

        start = thread_data[i].end + 1;
    }

    long result = 1;

    for (int i = 0; i < M; i++)
    {
        pthread_join(tid[i], NULL);
        result *= thread_data[i].par_product;
    }

    printf("Final factorial of Number %d is: %ld\n", N, result);
    return 0;
}



// TERMINAL OUTPUT

// root@DESKTOP-DC1LHIA:/mnt/c/Users/PC/Desktop/THREADPRA# gcc -pthread TALHA0379A3.c
// root@DESKTOP-DC1LHIA:/mnt/c/Users/PC/Desktop/THREADPRA# ./a.out 3 10
// Thread handling range (1, 4) Partial_result: 24
// Thread handling range (5, 7) Partial_result: 210
// Thread handling range (8, 10) Partial_result: 720
// Final factorial of Number 10 is: 3628800