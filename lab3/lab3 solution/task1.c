#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the user provided both length and width as arguments
    if (argc != 3) {
        printf("Usage: %s <length> <width>\n", argv[0]);
        return 1;
    }

    // Convert command-line arguments to integers using atoi
    int length = atoi(argv[1]);
    int width = atoi(argv[2]);

    // Calculate the area of the rectangle
    int area = length * width;

    // Display the result
    printf("The area of rectangle with length %d and width %d is %d.\n", length, width, area);

    return 0;
}
