#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 10
#define ELEMENTS_PER_THREAD (ARRAY_SIZE / NUM_THREADS)

int array[ARRAY_SIZE]; // Array of 1000 elements
long sum = 0;          // Shared variable to store the total sum

// Peterson's solution variables for 10 threads
int flag[NUM_THREADS] = {0}; // Indicates if a thread wants to enter the critical section
int turn = 0;                // Indicates whose turn it is to enter the critical section

// Thread function to compute partial sum
void* compute_sum(void* arg) 
{
    int thread_id = *(int*)arg;
    int start = thread_id * ELEMENTS_PER_THREAD;
    int end = start + ELEMENTS_PER_THREAD;
    long partial_sum = 0;

    // Compute partial sum for this thread
    for (int i = start; i < end; i++) 
    {
        partial_sum += array[i];
    }

    // Peterson's algorithm to enter the critical section
    flag[thread_id] = 1; // Indicate that this thread wants to enter the critical section
    turn = thread_id;    // Give the turn to this thread

    // Wait until it's this thread's turn and no other thread is in the critical section
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        if (i == thread_id) continue;
        while (flag[i] == 1 && turn == thread_id) {} // Busy wait
    }

    // Critical Section: Update the shared sum variable
    sum += partial_sum;

    // Exit the critical section
    flag[thread_id] = 0; // Indicate that this thread has exited the critical section

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the array with values 0 to 999
    for (int i = 0; i < ARRAY_SIZE; i++) 
    {
        array[i] = i;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, compute_sum, &thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    } 

    // Print the final sum
    printf("Final sum of the array: %ld\n", sum);

    return 0;
}