#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mainlock, lock1, lock2;
int arr[5];
int in = 0;
int out = 0;

void *producer(void *arg)
{
    sem_wait(&lock1); // Wait if buffer is full

    sem_wait(&mainlock);
    arr[in] = (rand() % 10); // Produce a random value
    printf("\nPRODUCER produces the value %d\n", arr[in]);
    in = (in + 1) % 5; // Move to next slot
    sem_post(&mainlock);

    sem_post(&lock2); // Signal consumer
    return NULL;
}

void *consumer(void *arg)
{
    sem_wait(&lock2); // Wait if buffer is empty

    sem_wait(&mainlock);
    printf("CONSUMER consumes the value %d\n", arr[out]);
    out = (out + 1) % 5; // Move to next slot
    sem_post(&mainlock);

    sem_post(&lock1); // Signal producer
    return NULL;
}

int main()
{
    sem_init(&mainlock, 0, 1);
    sem_init(&lock1, 0, 1);
    sem_init(&lock2, 0, 0);

    pthread_t threads[10];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, producer, NULL);
        pthread_create(&threads[i + 5], NULL, consumer, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
        pthread_join(threads[i + 5], NULL);
    }

    sem_destroy(&mainlock);
    sem_destroy(&lock1);
    sem_destroy(&lock2);

    return 0;
}
