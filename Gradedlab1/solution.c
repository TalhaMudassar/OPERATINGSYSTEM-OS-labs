#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MIN and INT_MAX

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Please provide at least one integer as input.\n");
        return 1;
    }

    // Convert command-line arguments to integers and store them in an array
    int n = argc - 1;  // The number of integers (arguments excluding the program name)
    int arr[n];

    // Populate the array with integers from command-line arguments
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);  // Convert each argument to an integer
    }

    // Calculate sum
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Calculate average
    double average = (double)sum / n;

    // Find minimum
    int min = INT_MAX;  // Initialize min to maximum possible value
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    // Find maximum
    int max = INT_MIN;  // Initialize max to minimum possible value
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Print the results
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", average);
    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);

    return 0;
}
