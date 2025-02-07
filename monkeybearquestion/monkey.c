#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t mainlock, lock1,  lock2;
int lcount = 0, rcount = 0;

sem_t handlethree_monkeys;

void *moveleftmonkey(void *arg)
{
    sem_wait(&handlethree_monkeys);
    sem_wait(&lock1);
    lcount++;
    if (lcount == 1) // First left monkey blocks others
    {
        sem_wait(&mainlock);
    }
    sem_post(&lock1);

    printf("Left monkey crossing the stream.\n");
    sleep(1); // Simulating crossing time

    sem_wait(&lock1);
    lcount--;
    if (lcount == 0) // Last left monkey releases the lock
    {
        sem_post(&mainlock);
    }
    sem_post(&lock1);
    sem_post(&handlethree_monkeys);
    return NULL;
}

void *moverightmonkey(void *arg)
{
    sem_wait(&handlethree_monkeys);
    sem_wait(&lock2);
    rcount++;
    if (rcount == 1) // First right monkey blocks others
    {
        sem_wait(&mainlock);
    }
    sem_post(&lock2);

    printf("Right monkey crossing the stream.\n");
    sleep(1); // Simulating crossing time

    sem_wait(&lock2);
    rcount--;
    if (rcount == 0) // Last right monkey releases the lock
    {
        sem_post(&mainlock);
    }
    sem_post(&lock2);
    sem_post(&handlethree_monkeys);
    return NULL;

}

void *moveleftbear(void *arg)
{
    sem_wait(&mainlock);
    printf("Left bear crossing the stream.\n");
    sleep(2); // Bears take longer to cross
    sem_post(&mainlock);
    return NULL;
}

void *moverightbear(void *arg)
{
    sem_wait(&mainlock);
    printf("Right bear crossing the stream.\n");
    sleep(2); // Bears take longer to cross
    sem_post(&mainlock);
    return NULL;
}

int main()
{
    sem_init(&mainlock, 0, 1);
    sem_init(&lock1, 0, 1);
    sem_init(&lock2, 0, 1);
    sem_init(&handlethree_monkeys,0,3);

    pthread_t threads[40];

    for (int i = 0; i < 40; i++)
    {
        if (i % 4 == 0)
            pthread_create(&threads[i], NULL, moveleftmonkey, NULL);
        else if (i % 4 == 1)
            pthread_create(&threads[i], NULL, moverightmonkey, NULL);
        else if (i % 4 == 2)
            pthread_create(&threads[i], NULL, moveleftbear, NULL);
        else
            pthread_create(&threads[i], NULL, moverightbear, NULL);
    }

    for (int i = 0; i < 40; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mainlock);
    sem_destroy(&lock1);
    sem_destroy(&lock2);

    return 0;
}
