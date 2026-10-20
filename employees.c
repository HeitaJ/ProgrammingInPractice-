/* employees.c */
#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utilities.h"

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

void addEmployee(void)
{
    Employee *e;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }
    e = &employees[employeeCount];
    e->id = readInt("Employee ID: ", 1, 999999);
    if (employeeIdExists(e->id)) {
        printf("Employee ID %d already exists.\n", e->id);
        return;
    }
    readString("Name: ", e->name, sizeof e->name);
    e->salary = readDouble("Monthly salary: ", 0.0);
    employeeCount++;
    printf("Employee added.\n");
}

void listEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("No employees recorded.\n");
        return;
    }
    printf("%-8s %-30s %12s\n", "ID", "Name", "Salary");
    for (i = 0; i < employeeCount; i++) {
        printf("%-8d %-30s %12.2f\n",
               employees[i].id, employees[i].name, employees[i].salary);
    }
}

void searchEmployee(void)
{
    int id = readInt("Employee ID to find: ", 1, 999999);
    int i;

    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            printf("Found: %s, salary %.2f\n", employees[i].name, employees[i].salary);
            return;
        }
    }
    printf("No employee with ID %d.\n", id);
}

double calculatePayrollTotal(void)
{
    double total = 0.0;
    int i;

    for (i = 0; i < employeeCount; i++) {
        total += employees[i].salary;
    }
    return total;
}

int getEmployeeCount(void)
{
    return employeeCount;
}

const Employee *getEmployee(int index)
{
    if (index < 0 || index >= employeeCount) {
        return NULL;
    }
    return &employees[index];
}

int employeeIdExists(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int addEmployeeRecord(int id, const char *name, double salary)
{
    if (employeeCount >= MAX_EMPLOYEES || employeeIdExists(id) ||
        strlen(name) >= NAME_LEN) {
        return 0;
    }
    employees[employeeCount].id = id;
    strcpy(employees[employeeCount].name, name);
    employees[employeeCount].salary = salary;
    employeeCount++;
    return 1;
}

void clearEmployees(void)
{
    employeeCount = 0;
}
