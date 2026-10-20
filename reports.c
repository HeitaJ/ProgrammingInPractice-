/* reports.c - uses only the public interfaces of employees and budget */
#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"

void employeeReport(void)
{
    printf("=== Employee Report ===\n");
    printf("Employees : %d\n", getEmployeeCount());
    printf("Payroll   : %.2f\n", calculatePayrollTotal());
}

void budgetReport(void)
{
    int i;
    const BudgetItem *b;

    printf("=== Budget Report ===\n");
    for (i = 0; i < getBudgetCount(); i++) {
        b = getBudgetItem(i);
        printf("%-20s allocated %10.2f  spent %10.2f  left %10.2f\n",
               b->department, b->allocated, b->spent, b->allocated - b->spent);
    }
    printf("Total balance: %.2f\n", calculateBudgetBalance());
}
