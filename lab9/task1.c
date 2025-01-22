#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBERS_TO_SEND 10

int shared_variable; // Shared variable to pass data between threads
int flag = 0;        // Flag to synchronize threads (0 = not written, 1 = written)

// Thread #1: Sends numbers to Thread #2
void* sender_thread(void* arg) {
    for (int i = 1; i <= NUMBERS_TO_SEND; i++) {
        // Wait until Thread #2 has read the previous value
        while (flag == 1) {
            // Busy wait (spinlock)
        }

        // Write the number to the shared variable
        shared_variable = i;
        printf("Thread #1 sent: %d\n", shared_variable);

        // Set the flag to indicate that the value has been written
        flag = 1;
    }
    pthread_exit(NULL);
}

// Thread #2: Receives numbers from Thread #1 and displays them
void* receiver_thread(void* arg) {
    for (int i = 1; i <= NUMBERS_TO_SEND; i++) {
        // Wait until Thread #1 has written a new value
        while (flag == 0) {
            // Busy wait (spinlock)
        }

        // Read the number from the shared variable
        int received_value = shared_variable;
        printf("Thread #2 received: %d\n", received_value);

        // Set the flag to indicate that the value has been read
        flag = 0;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2; // Thread IDs

    // Create Thread #1 (sender)
    if (pthread_create(&thread1, NULL, sender_thread, NULL) != 0) {
        perror("Failed to create Thread #1");
        return 1;
    }

    // Create Thread #2 (receiver)
    if (pthread_create(&thread2, NULL, receiver_thread, NULL) != 0) {
        perror("Failed to create Thread #2");
        return 1;
    }

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Program completed.\n");
    return 0;
}