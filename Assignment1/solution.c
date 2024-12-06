#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

// Function to display files and directories in the current directory
void display_files() {
    // execlp is used to execute the "ls -lah" command to list the files
    execlp("ls", "ls", "-lah", NULL);
    perror("execlp failed");  // If execlp fails, print the error message
    exit(1);  // Exit the program if execlp fails
}

int main() {
    int a = 0;  // Variable to store user choice (delete or rename)
    char filename[256];  // Array to store the filename for operations
    char newfilename[256];  // Array to store the new filename (for renaming)
    pid_t pid1, pid2, pid3;  // PIDs for child processes

    // Print a message to the user about displaying files
    printf("Displaying the files and directories in the current working directory:\n");
    
    // Fork a new process to execute the file listing operation
    pid1 = fork();
    if (pid1 == 0) {  // In the child process
        display_files();  // Call the display_files function to list the files
    } else if (pid1 > 0) {  // In the parent process
        wait(NULL);  // Parent waits for the child process to complete
        // After listing files, show the options for user to choose
        printf("1: Delete File\n");
        printf("2: Rename File\n");

        printf("Enter Option: ");  // Prompt user to enter their choice
        scanf("%d", &a);  // Store the user's choice in 'a'

        if (a == 1) {  // If user chose to delete a file
            printf("Enter File Name with Extension: ");  // Ask for filename to delete
            scanf("%s", filename);  // Store the filename to delete

            // Fork a child process to delete the file
            pid2 = fork();
            if (pid2 == 0) {  // In the child process
                execlp("rm", "rm", "-r", filename, NULL);  // Execute the "rm" command to delete the file
                perror("execlp failed");  // If execlp fails, print the error message
                exit(1);  // Exit the program if execlp fails
            } else if (pid2 > 0) {  // In the parent process
                wait(NULL);  // Wait for the delete operation to finish
                printf("File is deleted. Displaying the files and directories again:\n");
                display_files();  // List the files again after deletion
            }
        }
        else if (a == 2) {  // If user chose to rename a file
            printf("Enter Old File Name with Extension: ");  // Ask for the old filename
            scanf("%s", filename);  // Store the old filename

            printf("Enter New File Name with Extension: ");  // Ask for the new filename
            scanf("%s", newfilename);  // Store the new filename

            // Fork a child process to rename the file
            pid3 = fork();
            if (pid3 == 0) {  // In the child process
                execlp("mv", "mv", filename, newfilename, NULL);  // Execute the "mv" command to rename the file
                perror("execlp failed");  // If execlp fails, print the error message
                exit(1);  // Exit the program if execlp fails
            } else if (pid3 > 0) {  // In the parent process
                wait(NULL);  // Wait for the rename operation to finish
                printf("File name is updated. Displaying the files and directories again:\n");
                display_files();  // List the files again after renaming
            }
        } else {  // If user entered an invalid choice
            printf("Invalid option selected!\n");  // Print an error message for invalid choice
        }
    } else {  // If fork fails for the first child process
        perror("fork failed");  // Print error message if fork fails
        exit(1);  // Exit the program if fork fails
    }

    return 0;  // Return 0 to indicate successful program termination
}
