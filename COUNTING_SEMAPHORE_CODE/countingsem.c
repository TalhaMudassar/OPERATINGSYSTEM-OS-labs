#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RESOURCES 3
#define NUM_THREADS 5

sem_t semaphore;

void *thread_function(void *arg)
{
    int thread_id = *((int *)arg);
    free(arg);

    printf("Thread %d is trying to access the resource...\n", thread_id);

    sem_wait(&semaphore);

    printf("Thread %d is using the resource...\n", thread_id);
    sleep(2);

    sem_post(&semaphore);
    printf("Thread %d has finished using the resource.\n", thread_id);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    sem_init(&semaphore, 0, MAX_RESOURCES);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        pthread_create(&threads[i], NULL, thread_function, thread_id);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);

    return 0;
}
