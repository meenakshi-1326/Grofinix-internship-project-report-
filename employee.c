#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "employees.dat"
typedef struct {
    int id;
    char name[50];
    int age;
    char department[50];
    float salary;
} 
Employee;
void addEmployee();
void viewEmployees();
void searchEmployee();
void editEmployee();
void deleteEmployee();
void sortEmployees();
int isIdUnique(int id);
int main() 
{
    int choice;
    while (1) 
    {
        printf("\n--- Employee Record Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. View All Employees (Tabular)\n");
        printf("3. Search Employee (ID/Dept)\n");
        printf("4. Edit Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Sort Employees (Salary/Age)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: editEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: sortEmployees(); break;
            case 7: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
int isIdUnique(int id) 
{
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 1;
    Employee temp;
    while (fread(&temp, sizeof(Employee), 1, fp)) 
    {
        if (temp.id == id) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}
void addEmployee() 
{
    FILE *fp = fopen(FILE_NAME, "ab");
    Employee e;
    printf("Enter ID: ");
    scanf("%d", &e.id);
    if (!isIdUnique(e.id)) 
    {
        printf("Error: ID already exists!\n");
        fclose(fp);
        return;
    }
    printf("Enter Name: ");
    scanf(" %[^\n]", e.name);
    do 
    {
        printf("Enter Age (18-65): ");
        scanf("%d", &e.age);
    } 
    while (e.age < 18 || e.age > 65);
    printf("Enter Department: ");
    scanf(" %[^\n]", e.department);
    do 
    {
        printf("Enter Salary: ");
        scanf("%f", &e.salary);
    } 
    while (e.salary <= 0);
    fwrite(&e, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Record added successfully!\n");
}
void viewEmployees() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    Employee e;
    printf("\n%-10s %-20s %-5s %-15s %-10s\n", "ID", "Name", "Age", "Dept", "Salary");
    printf("--------------------------------------------------------------\n");
    while (fread(&e, sizeof(Employee), 1, fp)) {
        printf("%-10d %-20s %-5d %-15s %-10.2f\n", e.id, e.name, e.age, e.department, e.salary);
    }
    fclose(fp);
}
void searchEmployee() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return;
    int choice, searchId, found = 0;
    char searchDept[50];
    Employee e;
    printf("Search by: 1. ID  2. Department: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Enter ID: ");
        scanf("%d", &searchId);
        while (fread(&e, sizeof(Employee), 1, fp)) {
            if (e.id == searchId) {
                printf("Found: %s in %s\n", e.name, e.department);
                found = 1; break;
            }
        }
    } else {
        printf("Enter Department: ");
        scanf(" %[^\n]", searchDept);
        while (fread(&e, sizeof(Employee), 1, fp)) {
            if (strcasecmp(e.department, searchDept) == 0) {
                printf("ID: %d | Name: %s\n", e.id, e.name);
                found = 1;
            }
        }
    }
    if (!found) printf("No records matched.\n");
    fclose(fp);
}
void editEmployee() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return;
    int id, found = 0;
    Employee e;
    printf("Enter ID to edit: ");
    scanf("%d", &id);
    while (fread(&e, sizeof(Employee), 1, fp)) {
        if (e.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", e.name);
            printf("Enter New Salary: ");
            scanf("%f", &e.salary);
            fseek(fp, -(long)sizeof(Employee), SEEK_CUR);
            fwrite(&e, sizeof(Employee), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found) printf("Record updated!\n");
    else printf("ID not found.\n");
}
void deleteEmployee() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *ft = fopen("temp.dat", "wb");
    int id, found = 0;
    Employee e;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (fread(&e, sizeof(Employee), 1, fp)) {
        if (e.id == id) found = 1;
        else fwrite(&e, sizeof(Employee), 1, ft);
    }
    fclose(fp);
    fclose(ft);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    if (found) printf("Record deleted.\n");
    else printf("ID not found.\n");
}
void sortEmployees() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return;
    // Load into memory for sorting
    fseek(fp, 0, SEEK_END);
    long n = ftell(fp) / sizeof(Employee);
    rewind(fp);
    Employee *arr = malloc(n * sizeof(Employee));
    for (int i = 0; i < n; i++) fread(&arr[i], sizeof(Employee), 1, fp);
    fclose(fp);
    int choice;
    printf("Sort by: 1. Salary  2. Age: ");
    scanf("%d", &choice);
    // Simple Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int condition = (choice == 1) ? (arr[j].salary > arr[j+1].salary) : (arr[j].age > arr[j+1].age);
            if (condition) {
                Employee temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("\n--- Sorted List ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d | %s | %d | %.2f\n", arr[i].id, arr[i].name, arr[i].age, arr[i].salary);
    }
    free(arr);
}