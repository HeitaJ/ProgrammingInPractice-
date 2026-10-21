#include <stdio.h>
#include "mfms.h"

/* ---------------- Employees ---------------- */
int addEmployee(Employee list[], int count)
{
    Employee e;
    int i;

    if (count >= MAX_RECORDS) {
        printf("  Employee list is full (%d records).\n", MAX_RECORDS);
        return count;
    }
    e.id = readInt("  ID: ");
    for (i = 0; i < count; i++) {
        if (list[i].id == e.id) {
            printf("  ID %d already exists. Record not added.\n", e.id);
            return count;
        }
    }
    readWord("  First name (one word): ", e.name, (int)sizeof e.name);
    readWord("  Department (one word): ", e.department, (int)sizeof e.department);
    e.salary = readDouble("  Salary (N$): ");

    list[count] = e;
    printf("  Employee added.\n");
    return count + 1;
}

void displayEmployees(const Employee list[], int count)
{
    int i;

    if (count == 0) {
        printf("  No employees stored yet.\n");
        return;
    }
    printf("\n%-6s %-15s %-15s %12s\n", "ID", "Name", "Department", "Salary (N$)");
    for (i = 0; i < count; i++) {
        printf("%-6d %-15s %-15s %12.2f\n",
               list[i].id, list[i].name, list[i].department, list[i].salary);
    }
}

/* ---------------- Suppliers ---------------- */
int addSupplier(Supplier list[], int count)
{
    Supplier s;

    if (count >= MAX_RECORDS) {
        printf("  Supplier list is full (%d records).\n", MAX_RECORDS);
        return count;
    }
    s.id = readInt("  ID: ");
    readWord("  Name (one word): ", s.name, (int)sizeof s.name);
    readWord("  Email: ", s.email, (int)sizeof s.email);
    readWord("  Phone: ", s.phone, (int)sizeof s.phone);
    readWord("  Town (one word): ", s.town, (int)sizeof s.town);

    list[count] = s;
    printf("  Supplier added.\n");
    return count + 1;
}

void displaySuppliers(const Supplier list[], int count)
{
    int i;

    if (count == 0) {
        printf("  No suppliers stored yet.\n");
        return;
    }
    printf("\n%-6s %-15s %-25s %-14s %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    for (i = 0; i < count; i++) {
        printf("%-6d %-15s %-25s %-14s %-12s\n",
               list[i].id, list[i].name, list[i].email, list[i].phone, list[i].town);
    }
}

/* ---------------- Week 12: pointers and records ---------------- */
void updateSalary(Employee *e, double newSalary)
{
    e->salary = newSalary;                  /* arrow: change the REAL record */
}

/* Returns the address of the matching record, or NULL if the ID is not found. */
Employee *findEmployee(Employee list[], int n, int id)
{
    int i;

    for (i = 0; i < n; i++) {
        if (list[i].id == id) {
            return &list[i];
        }
    }
    return NULL;
}

void updateEmployeeSalaryMenu(Employee list[], int n)
{
    int id = readInt("  Employee ID: ");
    Employee *found = findEmployee(list, n, id);
    double newSalary;

    if (found == NULL) {
        printf("  Sorry, no employee with ID %d was found.\n", id);
        return;
    }
    printf("  Found: %s (%s), current salary N$%.2f\n",
           found->name, found->department, found->salary);
    newSalary = readDouble("  New salary (N$): ");
    if (newSalary < 0) {
        printf("  Salary cannot be negative. No change made.\n");
        return;
    }
    updateSalary(found, newSalary);
    printf("  Updated record: %d | %s | %s | N$%.2f\n",
           found->id, found->name, found->department, found->salary);
}
