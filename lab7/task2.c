#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double pi = 0.0;

typedef struct
{
    int start;
    int end;
} ThreadArgc;

void *compute_pifunction(void *args)
{
    ThreadArgc *arg = (ThreadArgc *)args;
    double local_sum = 0.0;

    for (int i = arg->start; i < arg->end; i++)
    {
        double term;
        if (i % 2 == 0)
        {
            term = 1.0 / (2 * i + 1);
        }
        else
        {
            term = -1.0 / (2 * i + 1);
        }
        local_sum += term;
    }

    pi += local_sum;

    free(arg);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <number_of_threads> <number_of_terms>\n", argv[0]);
        return 1;
    }

    int number_thread = atoi(argv[1]);
    int number_term = atoi(argv[2]);

    if (number_term < 100000 || number_term % number_thread != 0)
    {
        printf("Number of terms must be greater than 100,000 and evenly divisible by the number of threads.\n");
        return 1; // Exit with an error code if validation fails
    }

    pthread_t thread[number_thread];
    int term_per_thread = number_term / number_thread;

    for (int i = 0; i < number_thread; i++)
    {
        ThreadArgc *args = (ThreadArgc *)malloc(sizeof(ThreadArgc));
        args->start = i * term_per_thread;
        args->end = args->start + term_per_thread;
        pthread_create(&thread[i], NULL, compute_pifunction, args);
    }

    for (int i = 0; i < number_thread; i++)
    {
        pthread_join(thread[i], NULL);
    }

    pi *= 4;
    printf("Estimated value of pi: %.15f\n", pi);

    return 0;
}