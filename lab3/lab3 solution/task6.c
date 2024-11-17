#include <stdio.h>
#include <stdlib.h>

int findSecondMin(int *arr, int size) {
    int min = -1;        
    int secondMin = -1;   

    for (int i = 0; i < size; i++) {
        if (min == -1 || arr[i] < arr[min]) {
            secondMin = min;
            min = i;
        } else if ((secondMin == -1 || arr[i] < arr[secondMin]) && arr[i] != arr[min]) {
            secondMin = i;
        }
    }

    return secondMin != -1 ? arr[secondMin] : -1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;  
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]);
    }

    int secondMin = findSecondMin(arr, size);
    
    if (secondMin == -1) {
        printf("There is no second minimum number in the array.\n");
    } else {
        printf("The second minimum number in the array is: %d\n", secondMin);
    }

    free(arr);
    return 0;
}
