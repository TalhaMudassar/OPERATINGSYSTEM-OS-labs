#include <stdio.h>     // printf, scanf
#include <stdlib.h>    // atoi, malloc
#include <unistd.h>    // dup2, fork(), pipe
#include <sys/types.h> // Data types for system calls such as pid_t
#include <sys/file.h>  // O_CREAT, O_TRUNC, O_RDWR

int main()
{
    int fd1, fd2;      // File descriptors for input and output files
    int pipe_fd[2];    // Pipe for communication between grep and sort

    // Open input.txt for reading
    fd1 = open("input.txt", O_RDWR, 0777);

    // Open output.txt for writing (create if it doesn't exist, truncate if it does)
    fd2 = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);

    // Create the pipe
    pipe(pipe_fd);

    pid_t pid = fork();

    if (pid == 0) // Child process: grep
    {
        // Close the unused read end of the pipe
        close(pipe_fd[0]);

        // Redirect stdin to read from input.txt
        dup2(fd1, 0);

        // Redirect stdout to write to the write end of the pipe
        dup2(pipe_fd[1], 1);

        // Execute grep
        execlp("grep", "grep", "q", NULL);
    }
    else // Parent process: sort
    {
        pid_t pid2 = fork();

        if (pid2 == 0) // Second child process: sort
        {
            // Close the unused write end of the pipe
            close(pipe_fd[1]);

            // Redirect stdin to read from the read end of the pipe
             dup2(pipe_fd[0], 0);

            // Redirect stdout to write to output.txt
            dup2(fd2, 1);

            // Execute sort
            execlp("sort", "sort", NULL);
        }
        else
        {
            // Parent process: close both ends of the pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both children to finish
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
