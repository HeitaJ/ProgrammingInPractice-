#include <stdio.h>
#include "mfms.h"

#define EMP_FILE "employees.dat"

static void showMenu(int e, int s, int a, int b, int p)
{
    printf("\n=========== MFMS - Municipal Financial Management System ===========\n");
    printf("Employees: %d, Suppliers: %d, Assets: %d, Budgets: %d, Projects: %d\n", e, s, a, b, p);
    printf(" 1. Add Employee          2. Display Employees\n");
    printf(" 3. Add Supplier          4. Display Suppliers\n");
    printf(" 5. Add Asset             6. Display Assets\n");
    printf(" 7. Add Budget            8. Display Budgets\n");
    printf(" 9. Add Project          10. Display Projects\n");
    printf("11. Save Employees       12. Load Employees\n");
    printf("13. Search Suppliers by Town\n");
    printf("14. List Assets Above a Value\n");
    printf("15. Projects Ending in a Year\n");
    printf("16. Update Employee Salary\n");
    printf("17. Increase a Department Budget\n");
    printf(" 0. Exit\n");
}

int main(void)
{
    Employee employees[MAX_RECORDS];
    Supplier suppliers[MAX_RECORDS];
    Asset    assets[MAX_RECORDS];
    Budget   budgets[MAX_RECORDS];
    Project  projects[MAX_RECORDS];
    int employeeCount = 0, supplierCount = 0, assetCount = 0;
    int budgetCount = 0, projectCount = 0;
    int choice;

    do {
        showMenu(employeeCount, supplierCount, assetCount, budgetCount, projectCount);
        choice = readInt("Choose an option: ");

        switch (choice) {
        case 1:  employeeCount = addEmployee(employees, employeeCount); break;
        case 2:  displayEmployees(employees, employeeCount);            break;
        case 3:  supplierCount = addSupplier(suppliers, supplierCount); break;
        case 4:  displaySuppliers(suppliers, supplierCount);            break;
        case 5:  assetCount = addAsset(assets, assetCount);             break;
        case 6:  displayAssets(assets, assetCount);                     break;
        case 7:  budgetCount = addBudget(budgets, budgetCount);         break;
        case 8:  displayBudgets(budgets, budgetCount);                  break;
        case 9:  projectCount = addProject(projects, projectCount);     break;
        case 10: displayProjects(projects, projectCount);               break;
        case 11:
            if (saveArray(EMP_FILE, employees, sizeof employees[0], employeeCount)) {
                printf("  Saved %d employee(s) to %s.\n", employeeCount, EMP_FILE);
            }
            break;
        case 12:
            employeeCount = loadArray(EMP_FILE, employees, sizeof employees[0], MAX_RECORDS);
            printf("  Loaded %d employee(s) from %s.\n", employeeCount, EMP_FILE);
            break;
        case 13: searchSuppliersByTown(suppliers, supplierCount);       break;
        case 14: listAssetsAbove(assets, assetCount);                   break;
        case 15: projectsEndingIn(projects, projectCount);              break;
        case 16: updateEmployeeSalaryMenu(employees, employeeCount);    break;
        case 17: increaseBudgetMenu(budgets, budgetCount);              break;
        case 0:  printf("Goodbye.\n");                                  break;
        default: printf("  Invalid option. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
