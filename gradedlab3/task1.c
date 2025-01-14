#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to calculate the third maximum in an array
void *third_maximum_func(void *arg) {
    int *arr = (int *)arg;
    int arrsize = arr[0];
    int max1, max2, max3;
    max1 = max2 = max3 = arr[1];

    for (int i = 2; i <= arrsize; i++) {
        if (arr[i] > max1) {
            max3 = max2;
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max3 = max2;
            max2 = arr[i];
        } else if (arr[i] > max3) {
            max3 = arr[i];
        }
    }

    int *thirdmax = (int *)malloc(sizeof(int));
    *thirdmax = max3;
    return thirdmax;
}

// Thread function to calculate mean, median, and mode
void *stats(void *ptr) {
    int *arr = (int *)ptr;
    int size = arr[0]; // First element contains size

    // Calculate mean
    int sum = 0;
    for (int i = 1; i <= size; i++) {
        sum += arr[i];
    }
    double mean = (double)sum / size;

    // Calculate median (sorting required)
    for (int i = 1; i <= size - 1; i++) {
        for (int j = i + 1; j <= size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    double median = (size % 2 == 0) 
        ? (arr[size / 2] + arr[size / 2 + 1]) / 2.0 
        : arr[size / 2 + 1];

    // Calculate mode
    int max_count = 0;
    int mode = arr[1];
    for (int i = 1; i <= size; i++) {
        int count = 0;
        for (int j = 1; j <= size; j++) {
            if (arr[j] == arr[i])
                count++;
        }
        if (count > max_count) {
            max_count = count;
            mode = arr[i];
        }
    }

    // Allocate memory to store results
    double *results = (double *)malloc(3 * sizeof(double));
    results[0] = mean;
    results[1] = median;
    results[2] = mode;
    return results;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    int N = argc - 1;
    int *arr = (int *)malloc((N + 1) * sizeof(int));
    arr[0] = N / 2;

    int *sechalfarr = (int *)malloc((N / 2 + 1) * sizeof(int));
    sechalfarr[0] = N - (N / 2);

    for (int i = 1; i <= N; i++) {
        if (i <= N / 2) {
            arr[i] = atoi(argv[i]);
        } else {
            sechalfarr[i - N / 2] = atoi(argv[i]);
        }
    }

    pthread_t pid1, pid2;
    void *ret1;
    void *ret2;

    pthread_create(&pid1, NULL, third_maximum_func, arr);
    pthread_create(&pid2, NULL, stats, sechalfarr);

    pthread_join(pid1, &ret1);
    pthread_join(pid2, &ret2);

    int thirdmax = *((int *)ret1);
    printf("The third max in the array is: %d\n", thirdmax);

    double *stats_results = (double *)ret2;
    printf("Mean: %.2f\n", stats_results[0]);
    printf("Median: %.2f\n", stats_results[1]);
    printf("Mode: %.2f\n", stats_results[2]);

    free(arr);
    free(sechalfarr);
    free(ret1);
    free(ret2);

    return 0;
}
