/* main.c - coordinates the application only */
#include <stdio.h>
#include "main.h"
#include "employees.h"
#include "suppliers.h"
#include "assets.h"
#include "budget.h"
#include "utilities.h"
#include "reports.h"
#include "storage.h"

void displayMainMenu(void)
{
    printf("\nMunicipal Financial Management System\n");
    printf(" 1. Add employee          9. Record expense\n");
    printf(" 2. List employees       10. Employee report\n");
    printf(" 3. Search employee      11. Budget report\n");
    printf(" 4. Add supplier         12. Save data (text)\n");
    printf(" 5. List suppliers       13. Load data (text)\n");
    printf(" 6. Add asset            14. Save employees (binary)\n");
    printf(" 7. List assets          15. Load employees (binary)\n");
    printf(" 8. Add budget           16. Backup data\n");
    printf(" 0. Exit\n");
}

int main(void)
{
    int choice;

    do {
        displayMainMenu();
        choice = readInt("Choice: ", 0, 16);
        switch (choice) {
        case 1:  addEmployee();            break;
        case 2:  listEmployees();          break;
        case 3:  searchEmployee();         break;
        case 4:  addSupplier();            break;
        case 5:  listSuppliers();          break;
        case 6:  addAsset();               break;
        case 7:  listAssets();             break;
        case 8:  addBudget();              break;
        case 9:  recordExpense();          break;
        case 10: employeeReport();         break;
        case 11: budgetReport();           break;
        case 12: saveAllText();            break;
        case 13: loadAllText();            break;
        case 14: saveEmployeesBinary();    break;
        case 15: loadEmployeesBinary();    break;
        case 16: backupData();             break;
        case 0:  printf("Goodbye.\n");     break;
        }
        if (choice != 0) {
            pauseScreen();
        }
    } while (choice != 0);
    return 0;
}
