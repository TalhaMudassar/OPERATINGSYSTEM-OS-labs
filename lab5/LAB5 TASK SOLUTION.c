#include <stdio.h>  // For input-output operations (printf)
#include <stdlib.h> // For standard library functions (atoi, exit)
#include <unistd.h> // For pipe and fork functions
#include <sys/types.h> // For defining data types like pid_t

int main(int argc, char *argv[]) {
    // Check if at least one number is passed as a command-line argument
    if (argc < 2) {
        printf("Usage: %s <array elements>\n", argv[0]); // Print usage instructions
        return 1; // Exit with error code
    }

    int n = argc - 1; // Number of elements in the array (excluding the program name)
    int arr[n]; // Array to store integers passed as arguments
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);  // Convert string arguments to integers and store them in the array
    }

    // Pipes for inter-process communication
    int fd1[2], fd2[2], fd3[2], fd4[2];
    pipe(fd1); // Pipe1: Parent to Child1
    pipe(fd2); // Pipe2: Parent to Child2
    pipe(fd3); // Pipe3: Child1 to Parent
    pipe(fd4); // Pipe4: Child2 to Parent

    pid_t pid1, pid2; // Variables to store process IDs for forked children

    if ((pid1 = fork()) == 0) { // Child1 Process
        // Close all unrelated ends of the pipes in Child1
        close(fd1[1]); // Close write end of Pipe1 (only reading is needed)
        close(fd2[0]); close(fd2[1]); // Close both ends of Pipe2 (not used)
        close(fd3[0]); // Close read end of Pipe3 (only writing is needed)
        close(fd4[0]); close(fd4[1]); // Close both ends of Pipe4 (not used)

        // Read the array sent by the parent through Pipe1
        read(fd1[0], arr, sizeof(arr));
        close(fd1[0]); // Close read end of Pipe1 after reading

        // Calculate the sum of array elements
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i]; // Accumulate the sum of all elements
        }

        // Send the sum back to the parent through Pipe3
        write(fd3[1], &sum, sizeof(sum));
        close(fd3[1]); // Close write end of Pipe3 after writing
        exit(0); // Exit the child process
    }

    if ((pid2 = fork()) == 0) { // Child2 Process
        // Close all unrelated ends of the pipes in Child2
        close(fd2[1]); // Close write end of Pipe2 (only reading is needed)
        close(fd1[0]); close(fd1[1]); // Close both ends of Pipe1 (not used)
        close(fd3[0]); close(fd3[1]); // Close both ends of Pipe3 (not used)
        close(fd4[0]); // Close read end of Pipe4 (only writing is needed)

        // Read the array sent by the parent through Pipe2
        read(fd2[0], arr, sizeof(arr));
        close(fd2[0]); // Close read end of Pipe2 after reading

        // Find the minimum value in the array
        int min = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < min) {
                min = arr[i]; // Update the minimum value if a smaller value is found
            }
        }

        // Send the minimum value back to the parent through Pipe4
        write(fd4[1], &min, sizeof(min));
        close(fd4[1]); // Close write end of Pipe4 after writing
        exit(0); // Exit the child process
    }

    // Parent Process
    // Close all unrelated ends of the pipes in the parent
    close(fd1[0]); // Close read end of Pipe1 (only writing is needed)
    close(fd2[0]); // Close read end of Pipe2 (only writing is needed)
    close(fd3[1]); // Close write end of Pipe3 (only reading is needed)
    close(fd4[1]); // Close write end of Pipe4 (only reading is needed)

    // Send the array to both children through Pipe1 and Pipe2
    write(fd1[1], arr, sizeof(arr));
    write(fd2[1], arr, sizeof(arr));
    close(fd1[1]); // Close write end of Pipe1 after sending data
    close(fd2[1]); // Close write end of Pipe2 after sending data

    // Read the results from both children
    int sum, min;
    read(fd3[0], &sum, sizeof(sum)); // Read sum from Pipe3
    read(fd4[0], &min, sizeof(min)); // Read min from Pipe4
    close(fd3[0]); // Close read end of Pipe3 after reading
    close(fd4[0]); // Close read end of Pipe4 after reading

    // Display the results
    printf("Sum: %d\n", sum); // Print the sum of the array elements
    printf("Min: %d\n", min); // Print the minimum value in the array

    return 0; // Exit the parent process
}
