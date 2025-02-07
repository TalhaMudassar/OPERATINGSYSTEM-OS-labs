#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declare a binary semaphore
sem_t semaphore;

void *produce_data(void *arg)
{
    printf("Thread 1 (Producer) is producing data\n");
    
    // Simulate data production
    sleep(1);
    
    // Signal that data is ready for consumption
    sem_post(&semaphore);
    return NULL;
}

void *consume_data(void *arg)
{
    // Wait for data to be produced
    sem_wait(&semaphore);
    
    printf("Thread 2 (Consumer) is consuming data\n");
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    // Initialize the semaphore with initial value 0 (locked)
    sem_init(&semaphore, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, produce_data, NULL);
    pthread_create(&consumer_thread, NULL, consume_data, NULL);

    // Wait for threads to finish execution
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
