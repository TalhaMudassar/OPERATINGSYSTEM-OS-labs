#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    // Check if the user provided three sides as command-line arguments
    if (argc != 4) {
        printf("Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return 1;
    }

 
    int side1 = atoi(argv[1]);
    int side2 = atoi(argv[2]);
    int side3 = atoi(argv[3]);

   
    if ((side1 + side2 > side3) && (side1 + side3 > side2) && (side2 + side3 > side1))
     {
        printf("The sides form a valid triangle.\n");

        if (side1 == side2 && side2 == side3) {
            printf("The triangle is Equilateral.\n");
        } else if (side1 == side2 || side1 == side3 || side2 == side3) {
            printf("The triangle is Isosceles.\n");
        } else {
            printf("The triangle is Scalene.\n");
        }
    } 
    else 
    {
        printf("The sides do not form a valid triangle.\n");
    }

    return 0;
}
