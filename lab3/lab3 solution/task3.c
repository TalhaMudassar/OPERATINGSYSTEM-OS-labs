#include <stdio.h>
#include <stdlib.h>

void bubblesort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char** argv) {
    int arrsize = argc - 1;
    int *arr = (int *)malloc(arrsize * sizeof(int)); 
    int count = 0;

   
    for (int i = 1; i < argc; i++) { 
        int input = atoi(argv[i]);
        if (input == -99) {
            break; 
        }
        arr[count] = input; 
        count++;
    }

    // Original sequence
    printf("Original sequence is:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]); 
    }
    printf("\n");

    // Sort the array
    bubblesort(arr, count);


    printf("Updated sequence is:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]); 
    }
    printf("\n");

    free(arr);

    return 0;
}
