#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t lock1, lock2;
int lockvalue1 = 1, lockvalue2 = 3;
 
int count = 0;
void *rider(void *arg)
{
    sem_wait(&lock1);
    count++;
    sem_post(&lock1);
}

void *bus(void *arg)
{
  sleep(1);
    sem_wait(&lock1);
    int inbus = 0;
    for (int i = 0; count != 0 && i < lockvalue2; i++)
    {
        printf("boardbus()  \n");
        count--;
        inbus++;
    }

    printf("depart(%d)             %d \n", inbus,count);
    sem_post(&lock1);
}
int main()
{
    sem_init(&lock1, 0, lockvalue1);
    sem_init(&lock2, 0, lockvalue2);

    pthread_t bust[10], ridert[32];

    // Create rider threads
    for (int i = 0; i < 32; i++)
    {
        pthread_create(&ridert[i], NULL, rider, NULL);
    }

    // Create bus threads
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&bust[i], NULL, bus, NULL);
    }

    // Join rider threads
    for (int i = 0; i < 32; i++)
    {
        pthread_join(ridert[i], NULL);
    }

    // Join bus threads
    for (int i = 0; i < 10; i++)
    {
        pthread_join(bust[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&lock1);
    sem_destroy(&lock2);

    return 0;
}
