#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t lock1, lock2, mainlock;

int arr[5];
int in = 0;
int out = 0;
int count = 1;
int maxitem = 5;

void *producer(void *arg)
{


    int id = *((int *)arg);

    for (int i = 0; i < maxitem; i++)
    {
        sem_wait(&lock1);

        sem_wait(&mainlock);
        arr[in] = count;
        printf("producer %d produces the item %d \n", id,count);
        count++;
        in = (in + 1) % 5;
        sem_post(&mainlock);

        sem_post(&lock2);
        sleep(1);
        
    }
}
void *consumer(void *arg)
{
    int id = *((int *)arg);

    for (int i = 0; i < maxitem; i++)
    {
        sem_wait(&lock2);
        sem_wait(&mainlock);

        int item = arr[out];
        printf("consumer %d consumed  the item %d \n", id,item);
        out = (out + 1) % 5;

        sem_post(&mainlock);
        sem_post(&lock1);
        usleep(300);
        
    }
}

int main()
{
    sem_init(&lock1, 0, 5);
    sem_init(&lock2, 0, 0);
    sem_init(&mainlock, 0, 1);
    pthread_t prod1, prod2, cosm1, consm2;
    int id1 = 1;
    int id2 = 2;
    pthread_create(&prod1, NULL, producer, &id1);
    pthread_create(&prod2, NULL, producer, &id2);
    pthread_create(&cosm1, NULL, consumer, &id1);
    pthread_create(&consm2, NULL, consumer, &id2);

    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(cosm1, NULL);
    pthread_join(consm2, NULL);
    return 0;
}