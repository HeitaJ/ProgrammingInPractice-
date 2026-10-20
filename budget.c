/* budget.c */
#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utilities.h"

static BudgetItem budgets[MAX_BUDGETS];
static int budgetCount = 0;

void addBudget(void)
{
    BudgetItem *b;

    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget list is full.\n");
        return;
    }
    b = &budgets[budgetCount];
    readString("Department: ", b->department, sizeof b->department);
    b->allocated = readDouble("Allocated amount: ", 0.0);
    b->spent = 0.0;
    budgetCount++;
    printf("Budget added.\n");
}

void recordExpense(void)
{
    int i;
    double amount;

    if (budgetCount == 0) {
        printf("No budgets yet. Add one first.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++) {
        printf("%d) %s\n", i + 1, budgets[i].department);
    }
    i = readInt("Choose budget: ", 1, budgetCount) - 1;
    amount = readDouble("Expense amount: ", 0.0);
    budgets[i].spent += amount;
    printf("Expense recorded.\n");
}

double calculateBudgetBalance(void)
{
    double balance = 0.0;
    int i;

    for (i = 0; i < budgetCount; i++) {
        balance += budgets[i].allocated - budgets[i].spent;
    }
    return balance;
}

int getBudgetCount(void)
{
    return budgetCount;
}

const BudgetItem *getBudgetItem(int index)
{
    if (index < 0 || index >= budgetCount) {
        return NULL;
    }
    return &budgets[index];
}

int addBudgetRecord(const char *department, double allocated, double spent)
{
    if (budgetCount >= MAX_BUDGETS || strlen(department) >= DEPT_LEN) {
        return 0;
    }
    strcpy(budgets[budgetCount].department, department);
    budgets[budgetCount].allocated = allocated;
    budgets[budgetCount].spent = spent;
    budgetCount++;
    return 1;
}

void clearBudgets(void)
{
    budgetCount = 0;
}
