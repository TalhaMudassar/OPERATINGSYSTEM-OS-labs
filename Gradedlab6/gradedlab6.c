#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define maximumjob 3

sem_t lock1, mainlock;
void *doingwork(void *arg)
{
    int id = *((int *)arg);

    printf("EMPLOYEE %d IS TRYING TO PRINT THE JOB \n", id);
   

    sem_wait(&lock1);
    

    sem_wait(&mainlock);

    printf("EMPLOYEE %d IS PRINTING THE JOB \n", id);
   usleep(1000);
    printf("EMPLOYEE %d FINISHED THE JOB \n", id);

    sem_post(&mainlock);

    sem_post(&lock1);
}

int main()
{

    sem_init(&lock1, 0, maximumjob);
    sem_init(&mainlock, 0, 1);
    pthread_t employees[5];
    int emplpoyeeid[5];

    for (int i = 0; i < 5; i++)
    {
        emplpoyeeid[i] = i+1;
        pthread_create(&employees[i], NULL, doingwork, &emplpoyeeid[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(employees[i], NULL);
    }

    return 0;
}