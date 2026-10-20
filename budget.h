/* budget.h - budget operations */
#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 50
#define DEPT_LEN    40

typedef struct {
    char   department[DEPT_LEN];
    double allocated;
    double spent;
} BudgetItem;

void   addBudget(void);
void   recordExpense(void);
double calculateBudgetBalance(void);
int    getBudgetCount(void);
const BudgetItem *getBudgetItem(int index);
int    addBudgetRecord(const char *department, double allocated, double spent);
void   clearBudgets(void);

#endif
