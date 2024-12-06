#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
// $ ls / -lR 2> error.txt | grep “Nov” | sort | less 
int main() {
    int pipe1[2], pipe2[2]; // Pipes for communication
    int fd_error; // File descriptor for error.txt

    // Create error.txt to store errors
    fd_error = open("error.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);

    // Create the first pipe for communication between `ls` and `grep`
    pipe(pipe1);

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child process: `ls`
        // Redirect stderr to error.txt
        dup2(fd_error, 2);

        // Redirect stdout to the write end of pipe1
        dup2(pipe1[1], 1);

        // Close unused ends of the pipe
        close(pipe1[0]);
        close(pipe1[1]);

        // Execute `ls / -lR`
        execlp("ls", "ls", "/", "-lR", NULL);
    } else {
        // Create the second pipe for communication between `grep` and `sort`
        pipe(pipe2);

        pid_t pid2 = fork();
        if (pid2 == 0) { // Second child process: `grep`
            // Redirect stdin to the read end of pipe1
            dup2(pipe1[0], 0);

            // Redirect stdout to the write end of pipe2
            dup2(pipe2[1], 1);

            // Close unused ends of the pipes
            close(pipe1[1]);
            close(pipe1[0]);
            close(pipe2[0]);
            close(pipe2[1]);

            // Execute `grep "Nov"`
            execlp("grep", "grep", "Nov", NULL);
        } else {
            pid_t pid3 = fork();
            if (pid3 == 0) { // Third child process: `sort`
                // Redirect stdin to the read end of pipe2
                dup2(pipe2[0], 0);

                // Redirect stdout to the default stdout (for `less` to take over)
                dup2(1, 1);

                // Close unused ends of the pipes
                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[1]);
                close(pipe2[0]);

                // Execute `sort`
                execlp("sort", "sort", NULL);
            } else { // Parent process: `less`
                // Close unused ends of the pipes
                close(pipe1[0]);
                close(pipe1[1]);
                close(pipe2[0]);
                close(pipe2[1]);

                // Wait for all child processes to finish
                wait(NULL);
                wait(NULL);
                wait(NULL);

                // Execute `less`
                execlp("less", "less", NULL);
            }
        }
    }

    return 0;
}
