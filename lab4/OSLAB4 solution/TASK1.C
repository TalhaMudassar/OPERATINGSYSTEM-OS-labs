#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createChildProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        // In the child process
        printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
    } else {
        // In the parent process
        wait(NULL); // Wait for the child to finish
    }
}

int main() {
    printf("Process ID: %d, Parent ID: %d (Root Parent)\n", getpid(), getppid());

    pid_t firstChild = fork();
    if (firstChild == 0) {
        // First child
        printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());

        pid_t secondChild = fork();
        if (secondChild == 0) {
            // Second child of the first child
            printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
            
            // Third child of the second child
            createChildProcess();
        } else {
            wait(NULL); // Wait for the second child to finish
        }

        pid_t thirdChild = fork();
        if (thirdChild == 0) {
            // Third child of the first child
            printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
        } else {
            wait(NULL); // Wait for the third child to finish
        }
    } else {
        wait(NULL); // Wait for the first child to finish

        pid_t secondMainChild = fork();
        if (secondMainChild == 0) {
            // Second child of the root parent
            printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());

            // Child of the second main child
            createChildProcess();
        } else {
            wait(NULL); // Wait for the second main child to finish

            pid_t thirdMainChild = fork();
            if (thirdMainChild == 0) {
                // Third child of the root parent
                printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());

                // Child of the third main child
                createChildProcess();
            } else {
                wait(NULL); // Wait for the third main child to finish
            }
        }
    }

    return 0;
}
