// Write a program which will take an integer array from the terminal
// and pass it to two child’s. One child will find the avg of the array and
// the other child will find the second maximum value of the array.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc,char** argv)
{
    int arrsize = argc -1 ;
    int *arr = (int*)malloc(arrsize * sizeof(int));

    pid_t pid1,pid2;
    int fd[2];
    int fd1[2];
    pipe(fd);
    pipe(fd1);

    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd[1]);
         close(fd1[0]);
         close(fd1[1]);
        int newarr[100];
        read(fd[0],newarr,arrsize * sizeof(int));
        close(fd[0]);
        int sum = 0;
        for(int i= 0;  i<arrsize;  i++)
        {
            sum = sum + newarr[i]; 
        }
        printf("\n");
        printf(" the sum of the array are %d",sum);
        printf("\n");

        double average = (double)sum / arrsize;
        printf("the average of the array are %.2f",average);
        exit(0);
    }
    

    else
    {
         pid2 = fork();
        if( pid2 == 0)
        {
            close(fd1[1]);
            close(fd[0]);
            close(fd[1]);
            int nwarr[100];
            read(fd1[0],nwarr,arrsize * 4);
            close(fd1[0]);
            int max1, max2;       
            max1 = max2 = nwarr[0];
               // Find the first maximum
            for (int i = 1; i < arrsize; i++) 
            {
            if (nwarr[i] > max1) 
            {
            max1 = nwarr[i];
            }
            }

            // Find the second maximum
            int found = 0; // Flag to check if a second maximum exists
            for (int i = 0; i < arrsize; i++) 
            {
                if (nwarr[i] < max1 && (found == 0 || nwarr[i] > max2)) 
                {
                max2 = nwarr[i];
                found = 1;
                }
            }
            printf("the second maximum element in the array are %d",max2);
            exit(0);
        }

       

    close(fd[0]);
    close(fd1[0]);
    printf("\n");
    printf("orginal array are :");
    for(int i=0;  i<arrsize;  i++)
    {
        arr[i]= atoi(argv[i+1]);
        printf("%d", arr[i]);
        printf("  ");
    }
    printf("\n");
     write(fd[1],arr,arrsize*4);
     write(fd1[1],arr,arrsize*4);
     close(fd[1]);
     close(fd1[1]);
     wait(NULL);
     wait(NULL);
    }
    return 0;
}