// Write a program that will find partial factorial of any given number N from command line and pass it two
// threads each thread should calculate partial factorial and return it in main fucntion.
// Note: The code should be synchronized meeting all three conditions.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
pthread_mutex_t mutex;

int result1, result2; 
// result1 = 1;
// result2 = 1;
int finalreult = 1;

void *findfirstfactorial(void *arg)
{
    int numb = *((int *)arg);

    int localsum = 1;
    for (int i = 1; i <=(numb / 2); i++)
    {
        localsum *= i;
    }
    pthread_mutex_lock(&mutex);
    result1 = localsum;
    pthread_mutex_unlock(&mutex);
}

void *findsecondfactorial(void *arg)
{
    int numb = *((int *)arg);

    int localsum2 = 1;
    for (int i = ((numb / 2) + 1); i <=numb; i++)
    {
        localsum2 *= i;
    }
    pthread_mutex_lock(&mutex);
    result2 = localsum2;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, NULL);

    int number = atoi(argv[1]);

    if (number < 0)
    {
        printf("please enter the number greater than zero \n");
        return 0;
    }
    if (number > 12)
    {
        printf("please enter the small number than 12 beuuse we cannot store  greater number  in int \n");
        return 0;
    }

    pthread_t tid1, tid2;

    // void *ret1, ret2;
    pthread_create(&tid1, NULL, findfirstfactorial, &number);
    pthread_create(&tid2, NULL, findsecondfactorial, &number);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    finalreult = result1 * result2;
    printf("the fatorial are %d \n" , finalreult);

    return 0;
}