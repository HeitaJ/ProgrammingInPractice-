/* lab12.c - Week 12 practical: pointers, pass by address, arrays, -> operator */
#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 5

typedef struct {
    int id;
    char name[30];
    double salary;
} Employee;

/* ---------- Part B: swap salaries ---------- */
void swapWrong(double a, double b)          /* works on COPIES - does nothing useful */
{
    double temp = a;
    a = b;
    b = temp;
}

void swapSalaries(double *a, double *b)     /* works on the ORIGINALS */
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

/* ---------- Part C: arrays passed to functions ---------- */
void displaySalaries(const double salaries[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("  Employee %d: N$%.2f\n", i + 1, salaries[i]);
    }
}

double findHighest(const double salaries[], int n)
{
    double highest = salaries[0];
    int i;

    for (i = 1; i < n; i++) {
        if (salaries[i] > highest) {
            highest = salaries[i];
        }
    }
    return highest;
}

double calculateAverage(const double salaries[], int n)
{
    double total = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        total += salaries[i];
    }
    return total / n;
}

void giveRaise(double salaries[], int n, double percent)
{
    int i;

    for (i = 0; i < n; i++) {
        salaries[i] = salaries[i] * (1 + percent / 100);
    }
}

/* ---------- Part D: modify employee records ---------- */
void updateSalary(Employee *e, double newSalary)
{
    e->salary = newSalary;
}

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

/* ---------- Challenges ---------- */
void swapEmployees(Employee *a, Employee *b)
{
    Employee temp = *a;
    *a = *b;
    *b = temp;
}

/* Selection sort, highest salary first, using swapEmployees() */
void sortBySalaryDesc(Employee list[], int n)
{
    int i, j, max;

    for (i = 0; i < n - 1; i++) {
        max = i;
        for (j = i + 1; j < n; j++) {
            if (list[j].salary > list[max].salary) {
                max = j;
            }
        }
        if (max != i) {
            swapEmployees(&list[i], &list[max]);
        }
    }
}

Employee *highestPaid(Employee list[], int n)
{
    Employee *best = &list[0];
    int i;

    for (i = 1; i < n; i++) {
        if (list[i].salary > best->salary) {
            best = &list[i];
        }
    }
    return best;
}

void printEmployee(const Employee *e)
{
    printf("  %d | %-8s | N$%.2f\n", e->id, e->name, e->salary);
}

int main(void)
{
    int age = 25;
    int *p = &age;
    double salaryA = 18500.50, salaryB = 21000.75;
    double salaries[4] = {15000.00, 18500.50, 21000.75, 17200.00};
    Employee staff[MAX_EMPLOYEES] = {
        {1001, "Maria", 18500.50},
        {1002, "Simon", 17200.00},
        {1003, "Anna",  21000.75}
    };
    int count = 3, i;
    Employee *found;

    /* Part A */
    printf("=== Part A - pointer warm-up ===\n");
    printf("age = %d | address = %p | *p = %d\n", age, (void *)p, *p);
    *p = 30;
    printf("After *p = 30: age = %d, *p = %d\n", age, *p);

    /* Part B */
    printf("\n=== Part B - swap salaries ===\n");
    printf("Before:          A = %.2f, B = %.2f\n", salaryA, salaryB);
    swapWrong(salaryA, salaryB);
    printf("After swapWrong: A = %.2f, B = %.2f   (unchanged - copies!)\n", salaryA, salaryB);
    swapSalaries(&salaryA, &salaryB);
    printf("After swapRight: A = %.2f, B = %.2f   (swapped)\n", salaryA, salaryB);

    /* Part C */
    printf("\n=== Part C - arrays and functions ===\n");
    printf("Before raise:\n");
    displaySalaries(salaries, 4);
    printf("Highest: N$%.2f | Average: N$%.2f\n",
           findHighest(salaries, 4), calculateAverage(salaries, 4));
    giveRaise(salaries, 4, 10.0);
    printf("After 10%% raise (original array changed):\n");
    displaySalaries(salaries, 4);
    printf("Highest: N$%.2f | Average: N$%.2f\n",
           findHighest(salaries, 4), calculateAverage(salaries, 4));

    /* Part D */
    printf("\n=== Part D - modify employee records ===\n");
    found = findEmployee(staff, count, 1002);              /* found */
    if (found != NULL) {
        updateSalary(found, 19000.00);
        printf("Update 1: "); printEmployee(found);
        updateSalary(found, 19500.00);                     /* updated twice */
        printf("Update 2: "); printEmployee(found);
    }
    found = findEmployee(staff, count, 9999);              /* not found */
    if (found == NULL) {
        printf("ID 9999: employee not found.\n");
    }

    /* Challenges */
    printf("\n=== Challenges ===\n");
    sortBySalaryDesc(staff, count);
    printf("Sorted by salary (highest first):\n");
    for (i = 0; i < count; i++) {
        printEmployee(&staff[i]);
    }
    printf("Highest paid: %s\n", highestPaid(staff, count)->name);
    printf("Address staff[0] = %p\n", (void *)&staff[0]);
    printf("Address staff[1] = %p\n", (void *)&staff[1]);
    printf("Address staff[2] = %p\n", (void *)&staff[2]);
    printf("Difference between neighbours = %zu bytes, sizeof(Employee) = %zu bytes\n",
           (size_t)((char *)&staff[1] - (char *)&staff[0]), sizeof(Employee));

    return 0;
}
