#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mainlock, lock1, lock2, fixhandle;
int rcount = 0;
int wcount = 0;

void *READER(void *arg)
{
    sem_wait(&fixhandle); // Limit number of readers

    sem_wait(&lock1);
    rcount++;
    if (rcount == 1)
    {
        sem_wait(&mainlock); // First reader locks main resource
    }
    sem_post(&lock1);

    printf("READER IS READING \n");
    sleep(1); // Simulate reading process
    printf("READER IS DONE READING \n");

    sem_wait(&lock1);
    rcount--;
    if (rcount == 0)
    {
        sem_post(&mainlock); // Last reader unlocks main resource
    }
    sem_post(&lock1);

    sem_post(&fixhandle); // Release slot for another reader
}

void *WRITER(void *arg)
{
    sem_wait(&lock2);
    wcount++;
    if (wcount == 1)
    {
        sem_wait(&mainlock); // First writer locks main resource
    }
    sem_post(&lock2);

    printf("WRITER IS WRITING \n");
    sleep(1); // Simulate writing process
    printf("WRITER IS DONE WRITING \n");

    sem_wait(&lock2);
    wcount--;
    if (wcount == 0)
    {
        sem_post(&mainlock); // Last writer unlocks main resource
    }
    sem_post(&lock2);
}

int main()
{
    sem_init(&mainlock, 0, 1);
    sem_init(&lock1, 0, 1);
    sem_init(&lock2, 0, 1);
    sem_init(&fixhandle, 0, 2); // Limits number of concurrent readers

    pthread_t threads[20];

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i * 2], NULL, READER, NULL);
        pthread_create(&threads[i * 2 + 1], NULL, WRITER, NULL);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i * 2], NULL);
        pthread_join(threads[i * 2 + 1], NULL);
    }

    return 0;
}