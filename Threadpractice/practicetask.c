#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Function to calculate the mean of the array
void *calculate_mean(void *arg) {
    int *arr = (int *)arg;
    int size = arr[0];
    int sum = 0;
    
    for (int i = 1; i <= size; i++) {
        sum += arr[i];
    }

    double *mean = (double *)malloc(sizeof(double));
    *mean = (double)sum / size;
    return mean;
}

// Function to find the 4th maximum number
void *find_fourth_max(void *arg) {
    int *arr = (int *)arg;
    int size = arr[0];

    if (size < 4) {
        printf("Array size is less than 4, cannot find 4th maximum.\n");
        return NULL;
    }

    // Sorting the array in descending order to find the 4th maximum
    for (int i = 1; i <= size - 1; i++) {
        for (int j = i + 1; j <= size; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int *fourth_max = (int *)malloc(sizeof(int));
    *fourth_max = arr[4];  // After sorting, the 4th maximum will be at index 4
    return fourth_max;
}

// Function to find the 2nd minimum number
void *find_second_min(void *arg) {
    int *arr = (int *)arg;
    int size = arr[0];

    if (size < 2) {
        printf("Array size is less than 2, cannot find 2nd minimum.\n");
        return NULL;
    }

    // Sorting the array in ascending order to find the 2nd minimum
    for (int i = 1; i <= size - 1; i++) {
        for (int j = i + 1; j <= size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int *second_min = (int *)malloc(sizeof(int));
    *second_min = arr[1];  // After sorting, the 2nd minimum will be at index 1
    return second_min;
}

// Function to count even, odd, and prime numbers
int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void *count_even_odd_prime(void *arg) {
    int *arr = (int *)arg;
    int size = arr[0];
    
    int even_count = 0, odd_count = 0, prime_count = 0;
    
    for (int i = 1; i <= size; i++) {
        if (arr[i] % 2 == 0) even_count++;
        else odd_count++;

        if (is_prime(arr[i])) prime_count++;
    }

    printf("Even Numbers: %d\n", even_count);
    printf("Odd Numbers: %d\n", odd_count);
    printf("Prime Numbers: %d\n", prime_count);
    return NULL;
}

int main(int argc, char *argv[]) {
    int arr_size = argc - 1;
    int *arr = (int *)malloc((arr_size + 1) * sizeof(int));
    arr[0] = arr_size;

    for (int i = 1; i <= arr_size; i++) {
        arr[i] = atoi(argv[i]);
    }

    pthread_t thread1, thread2, thread3, thread4;
    void *result1, *result2, *result3, *result4;

    // Creating threads
    pthread_create(&thread1, NULL, calculate_mean, arr);
    pthread_create(&thread2, NULL, find_fourth_max, arr);
    pthread_create(&thread3, NULL, find_second_min, arr);
    pthread_create(&thread4, NULL, count_even_odd_prime, arr);

    // Joining threads
    pthread_join(thread1, &result1);
    pthread_join(thread2, &result2);
    pthread_join(thread3, &result3);
    pthread_join(thread4, &result4);

    // Retrieving results from threads
    double mean_result = *((double *)result1);
    int fourth_max_result = *((int *)result2);
    int second_min_result = *((int *)result3);

    // Displaying results
    printf("Mean: %.2f\n", mean_result);
    printf("4th Maximum: %d\n", fourth_max_result);
    printf("2nd Minimum: %d\n", second_min_result);

    // Freeing memory
    free(result1);
    free(result2);
    free(result3);
    free(arr);

    return 0;
}
