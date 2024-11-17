#include <stdio.h>
#include <stdlib.h>

// Define the Employee structure
struct Employee {
    char id[10];
    char name[50];
    int age;
    float pay;
};

// Function declarations
void inputEmployeeInfo(struct Employee *emp);
void displayEmployeeInfo(const struct Employee *emp);

int main() {
    struct Employee emp;

    // Input employee information
    inputEmployeeInfo(&emp);

    // Display employee information
    displayEmployeeInfo(&emp);

    return 0;
}

// Function to input employee information
void inputEmployeeInfo(struct Employee *emp) {
    printf("Enter Employee ID: ");
    scanf("%s", emp->id);
    printf("Enter Employee Name: ");
    scanf("%s", emp->name);
    printf("Enter Employee Age: ");
    scanf("%d", &emp->age);
    printf("Enter Employee Pay: ");
    scanf("%f", &emp->pay);
}

// Function to display employee information
void displayEmployeeInfo(const struct Employee *emp) {
    printf("\nEmployee Information:\n");
    printf("ID: %s\n", emp->id);
    printf("Name: %s\n", emp->name);
    printf("Age: %d\n", emp->age);
    printf("Pay: %.2f\n", emp->pay);
}
