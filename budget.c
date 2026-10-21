#include <stdio.h>
#include <string.h>
#include "mfms.h"

/* ---------------- Budgets ---------------- */
int addBudget(Budget list[], int count)
{
    Budget b;

    if (count >= MAX_RECORDS) {
        printf("  Budget list is full (%d records).\n", MAX_RECORDS);
        return count;
    }
    readWord("  Department (one word): ", b.department, (int)sizeof b.department);
    b.allocated = readDouble("  Allocated (N$): ");
    b.spent     = readDouble("  Spent so far (N$): ");

    list[count] = b;
    printf("  Budget added.\n");
    return count + 1;
}

void displayBudgets(const Budget list[], int count)
{
    int i;
    double balance;

    if (count == 0) {
        printf("  No budgets stored yet.\n");
        return;
    }
    printf("\n%-15s %14s %14s %14s\n", "Department", "Allocated", "Spent", "Balance");
    for (i = 0; i < count; i++) {
        balance = list[i].allocated - list[i].spent;
        printf("%-15s %14.2f %14.2f %14.2f", list[i].department,
               list[i].allocated, list[i].spent, balance);
        if (list[i].spent > list[i].allocated) {
            printf("  ** OVER BUDGET **");
        }
        printf("\n");
    }
}

/* ---------------- Projects ---------------- */
int addProject(Project list[], int count)
{
    Project p;

    if (count >= MAX_RECORDS) {
        printf("  Project list is full (%d records).\n", MAX_RECORDS);
        return count;
    }
    p.id = readInt("  ID: ");
    readWord("  Title (one word): ", p.title, (int)sizeof p.title);
    p.budget    = readDouble("  Budget (N$): ");
    p.startDate = readDate("  Start date:");
    p.endDate   = readDate("  End date:");

    list[count] = p;
    printf("  Project added.\n");
    return count + 1;
}

void displayProjects(const Project list[], int count)
{
    int i;

    if (count == 0) {
        printf("  No projects stored yet.\n");
        return;
    }
    printf("\n%-6s %-20s %14s %-12s %-12s\n", "ID", "Title", "Budget (N$)", "Start", "End");
    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %14.2f %02d/%02d/%-6d %02d/%02d/%-6d\n",
               list[i].id, list[i].title, list[i].budget,
               list[i].startDate.day, list[i].startDate.month, list[i].startDate.year,
               list[i].endDate.day, list[i].endDate.month, list[i].endDate.year);
    }
}

/* ---------------- Week 12: pointers and budgets ---------------- */
void increaseBudget(Budget *b, double amount)
{
    b->allocated += amount;
}

void increaseBudgetMenu(Budget list[], int n)
{
    char dept[20];
    double amount;
    int i;

    if (n == 0) {
        printf("  No budgets stored yet.\n");
        return;
    }
    readWord("  Department: ", dept, (int)sizeof dept);
    for (i = 0; i < n; i++) {
        if (strcmp(list[i].department, dept) == 0) {
            amount = readDouble("  Amount to add (N$): ");
            if (amount <= 0) {
                printf("  Amount must be positive. No change made.\n");
                return;
            }
            increaseBudget(&list[i], amount);
            printf("  %s allocated is now N$%.2f (balance N$%.2f)\n", list[i].department,
                   list[i].allocated, list[i].allocated - list[i].spent);
            return;
        }
    }
    printf("  No budget found for department '%s'.\n", dept);
}
