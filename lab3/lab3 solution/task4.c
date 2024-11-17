#include<stdio.h>
#include<stdlib.h>
void checkprimenumber(int number) {
   
    if (number <= 1) {
        printf("Output: Not Prime\n");
        return;
    }
    if (number == 2) {
        printf("Output: Prime\n");
        return;
    }
    
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            printf("Output: Not Prime\n");
            return;
        }
    }
    printf("Output: Prime\n");
}


int main(int argc, char** argv)
{
    int input = atoi(argv[1]);
    checkprimenumber(input);
    return 0;
}