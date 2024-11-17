#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILENAME "task8helper.txt"

typedef struct {
    char id[10];
    char name[50];
    char gender; // 'm' or 'f'
    char jobPosition[20]; // e.g., "internee" or "developer"
    int experience; // in years
    float pay; // salary
} Employee;

void addRecord(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Cannot add more employees. Maximum limit reached.\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%s", employees[*count].id);
    printf("Enter Name: ");
    scanf("%s", employees[*count].name);
    printf("Enter Gender (m/f): ");
    scanf(" %c", &employees[*count].gender);
    printf("Enter Job Position: ");
    scanf("%s", employees[*count].jobPosition);
    printf("Enter Experience (in years): ");
    scanf("%d", &employees[*count].experience);
    printf("Enter Pay: ");
    scanf("%f", &employees[*count].pay);

    (*count)++;
    printf("Record added successfully.\n");
}

void searchRecordByID(Employee employees[], int count) {
    char id[10];
    printf("Enter Employee ID to search: ");
    scanf("%s", id);
    
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            printf("ID: %s, Name: %s, Gender: %c, Job Position: %s, Experience: %d years, Pay: %.2f\n",
                   employees[i].id, employees[i].name, employees[i].gender,
                   employees[i].jobPosition, employees[i].experience, employees[i].pay);
            return;
        }
    }
    printf("Employee with ID %s not found.\n", id);
}

void showAllRecords(Employee employees[], int count) {
    if (count == 0) {
        printf("No records to display.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        printf("ID: %s, Name: %s, Gender: %c, Job Position: %s, Experience: %d years, Pay: %.2f\n",
               employees[i].id, employees[i].name, employees[i].gender,
               employees[i].jobPosition, employees[i].experience, employees[i].pay);
    }
}

void showEmployeesWithLowPay(Employee employees[], int count, float basicPay) {
    printf("Employees with pay less than %.2f:\n", basicPay);
    int found = 0;
    
    for (int i = 0; i < count; i++) {
        if (employees[i].pay < basicPay) {
            printf("ID: %s, Name: %s, Pay: %.2f\n", employees[i].id, employees[i].name, employees[i].pay);
            found = 1;
        }
    }
    if (!found) {
        printf("No employees found with pay less than %.2f.\n", basicPay);
    }
}

void saveAndExit(Employee employees[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving data to file.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %c %s %d %.2f\n",
                employees[i].id, employees[i].name, employees[i].gender,
                employees[i].jobPosition, employees[i].experience, employees[i].pay);
    }
    
    fclose(file);
    printf("Data saved successfully. Exiting program.\n");
    exit(0);
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;
    
    while (1) {
        printf("==================== MENU ===================\n");
        printf("1. Add a record\n");
        printf("2. Search a record by ID\n");
        printf("3. Show all records\n");
        printf("4. Show employees having pay less than basic pay (20000)\n");
        printf("5. Save and exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addRecord(employees, &count);
                break;
            case 2:
                searchRecordByID(employees, count);
                break;
            case 3:
                showAllRecords(employees, count);
                break;
            case 4:
                showEmployeesWithLowPay(employees, count, 20000);
                break;
            case 5:
                saveAndExit(employees, count);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
