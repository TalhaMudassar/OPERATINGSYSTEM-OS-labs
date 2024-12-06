#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    printf("Root A created\n");

    pid_t pidA = fork(); // Create B


    if (pidA < 0) {
        perror("Fork failed");
        exit(1);
    } 

    else if (pidA == 0) 
     { // Child B
        printf("Child B created by Parent A\n");

        pid_t pidB1 = fork(); // Create E

        if (pidB1 < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pidB1 == 0) { // Child E
            printf("Child E created by Parent B\n");

            pid_t pidE = fork(); // Create I

            if (pidE < 0) {
                perror("Fork failed");
                exit(1);
            } else if (pidE == 0) { // Child I
                printf("Child I created by Parent E\n");
                exit(0);
            }

            // Wait for child of E to finish
            wait(NULL);
            exit(0);
        }

        pid_t pidB2 = fork(); // Create H
        if (pidB2 < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pidB2 == 0) { // Child H
            printf("Child H created by Parent B\n");
            exit(0);
        }

        pid_t pidB3 = fork(); // Create F
        if (pidB3 < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pidB3 == 0) { // Child F
            printf("Child F created by Parent B\n");
            exit(0);
        }

        // Wait for all children of B to finish
        wait(NULL);
        wait(NULL);
        wait(NULL);
        exit(0);
    }

    pid_t pidC = fork(); // Create C
    if (pidC < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pidC == 0) 
    { // Child C
        printf("Child C created by Parent A\n");

        pid_t pidC1 = fork(); // Create G
        if (pidC1 < 0) {
            perror("Fork failed");
            exit(1);
        }
         else if (pidC1 == 0) { // Child G
            printf("Child G created by Parent C\n");
            exit(0);
        }

        // Wait for child of C to finish
        wait(NULL);
        exit(0);
    }

    pid_t pidD = fork(); // Create D
    if (pidD < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pidD == 0) { // Child D
        printf("Child D created by Parent A\n");
        exit(0);
    }

    // Wait for all children of A to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
