#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <wait.h>


void *averagefun(void *arg)
{
    int *arr1 = (int *)arg;
    int size = arr1[0];
    int sum = 0;
    for (int i = 1; i <= size; i++)
    {
        sum += arr1[i];
    }
    double *average = (double *)malloc(sizeof(double));
    *average = (double)sum / size;
    return average;
}
void *minimumfun(void *arg1)
{
    int *arr = (int *)arg1;
    int size = arr[0];
    int min = arr[1];
    for (int i = 2; i <= size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    int *minimum = (int *)malloc(sizeof(int));
    *minimum = min;
    return minimum;
}

void *maximumfun(void *arg2)
{
    int *arr = (int *)arg2;
    int size = arr[0];
    int max = arr[1];
    for (int i = 2; i <= size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int *maximum = (int *)malloc(sizeof(int));
    *maximum = max;
    return maximum;
}

int main(int argc, char *argv[])
{
    int arrsize = argc - 1;
    int *arr = (int *)malloc((arrsize + 1) * sizeof(int));
    arr[0] = arrsize;
    for (int i = 1; i <= arrsize; i++)
    {
        arr[i] = atoi(argv[i]);
    }

    pthread_t pid1, pid2, pid3;
    void *ret1, *ret2, *ret3;

    pthread_create(&pid1, NULL, averagefun, arr);
    pthread_create(&pid2, NULL, minimumfun, arr);
    pthread_create(&pid3, NULL, maximumfun, arr);

    pthread_join(pid1, &ret1);
    pthread_join(pid2, &ret2);
    pthread_join(pid3, &ret3);

    double returnval1 = *((double *)ret1);
    int returnval2 = *((int *)ret2);
    int returnval3 = *((int *)ret3);

    printf("The average of the array is %.2f\n", returnval1);
    printf("The minimum integer of the array is %d\n", returnval2);
    printf("The maximum integer of the array is %d\n", returnval3);

    free(arr);
    free(ret1);
    free(ret2);
    free(ret3);

    return 0;
}