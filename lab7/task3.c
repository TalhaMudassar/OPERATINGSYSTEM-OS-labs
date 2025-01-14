#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

// Shared variables
char *search_string;
int found = 0;
pthread_mutex_t mutex;

// Structure to pass arguments to threads
typedef struct {
    FILE *file;
    int thread_id;
    int total_threads;
} ThreadArgs;

void *search_in_file(void *args) {
    ThreadArgs *arg = (ThreadArgs *)args;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, MAX_LINE_LENGTH, arg->file) != NULL) {
        pthread_mutex_lock(&mutex);
        if (found) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        line_number++;
        if (strstr(line, search_string) != NULL) {
            pthread_mutex_lock(&mutex);
            found = 1;
            pthread_mutex_unlock(&mutex);
            printf("Thread %d found the string '%s' at line %d\n", arg->thread_id, search_string, line_number);
            break;
        }
    }

    fclose(arg->file);
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename> <number_of_threads> <string_to_search>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_threads = atoi(argv[2]);
    search_string = argv[3];

    pthread_t threads[num_threads];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_threads; i++) {
        ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs));
        args->file = fopen(filename, "r");
        if (args->file == NULL) {
            perror("Error opening file");
            return 1;
        }

        // Divide the file into approximately equal parts for each thread
        fseek(args->file, i * (ftell(args->file) / num_threads), SEEK_SET);
        args->thread_id = i + 1;
        args->total_threads = num_threads;
        pthread_create(&threads[i], NULL, search_in_file, args);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    if (!found) {
        printf("String '%s' not found in the file.\n", search_string);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
