#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;  
int shared_counter = 0;  


void* increment_counter(void* arg) {

    pthread_mutex_lock(&mutex);


    for (int i = 0; i < 5; i++) {
        shared_counter++;
        printf("Thread %ld: Counter = %d\n", (long)arg, shared_counter);
    }

  
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    
    pthread_mutex_init(&mutex, NULL);

   
    pthread_create(&thread1, NULL, increment_counter, (void*)1);
    pthread_create(&thread2, NULL, increment_counter, (void*)2);

    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

   
    pthread_mutex_destroy(&mutex);

    return 0;
}
