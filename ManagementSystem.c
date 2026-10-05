#include <stdio.h>
#include <string.h>

#define NUM_SALARIES 50
#define NUM_BUDGETS 10
#define NUM_REGISTRATIONS 20
#define REG_LENGTH 20

/* ========== PART A: Employee Salaries ========== */
void captureSalaries(float salaries[], int n) {
    printf("\n=== Capture Employee Salaries ===\n");
    for (int i = 0; i < n; i++) {
        printf("Enter salary for employee %d: ", i + 1);
        scanf("%f", &salaries[i]);
    }
}

void displaySalaries(float salaries[], int n) {
    printf("\n=== All Employee Salaries ===\n");
    for (int i = 0; i < n; i++) {
        printf("Employee %2d: %.2f\n", i + 1, salaries[i]);
    }
}

float calculateAverage(float arr[], int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

float findHighest(float arr[], int n) {
    float highest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > highest) {
            highest = arr[i];
        }
    }
    return highest;
}

float findLowest(float arr[], int n) {
    float lowest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < lowest) {
            lowest = arr[i];
        }
    }
    return lowest;
}

void searchSalary(float salaries[], int n) {
    float target;
    int found = 0;
    printf("\nEnter salary to search for: ");
    scanf("%f", &target);

    printf("Search results:\n");
    for (int i = 0; i < n; i++) {
        if (salaries[i] == target) {
            printf("  Found at employee %d (index %d)\n", i + 1, i);
            found = 1;
        }
    }
    if (!found) {
        printf("  Salary %.2f not found.\n", target);
    }
}

/* ========== PART B: Department Budgets ========== */
void captureBudgets(float budgets[], int n) {
    printf("\n=== Capture Department Budgets ===\n");
    for (int i = 0; i < n; i++) {
        printf("Enter budget for department %d: ", i + 1);
        scanf("%f", &budgets[i]);
    }
}

void displayBudgets(float budgets[], int n) {
    printf("\n=== Department Budgets ===\n");
    for (int i = 0; i < n; i++) {
        printf("Department %2d: %.2f\n", i + 1, budgets[i]);
    }
}

float calculateTotal(float arr[], int n) {
    float total = 0.0f;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

void sortBudgetsAscending(float budgets[], int n) {
    /* Simple bubble sort */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (budgets[j] > budgets[j + 1]) {
                float temp = budgets[j];
                budgets[j] = budgets[j + 1];
                budgets[j + 1] = temp;
            }
        }
    }
}

/* ========== PART C: Vehicle Registration Numbers ========== */
void captureRegistrations(char registrations[][REG_LENGTH], int n) {
    printf("\n=== Capture Vehicle Registration Numbers ===\n");
    for (int i = 0; i < n; i++) {
        printf("Enter registration number %d: ", i + 1);
        scanf("%19s", registrations[i]);  /* limit to 19 chars + null */
    }
}

void displayRegistrations(char registrations[][REG_LENGTH], int n) {
    printf("\n=== All Vehicle Registration Numbers ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d: %s\n", i + 1, registrations[i]);
    }
}

void searchRegistration(char registrations[][REG_LENGTH], int n) {
    char target[REG_LENGTH];
    int found = 0;
    printf("\nEnter registration number to search for: ");
    scanf("%19s", target);

    printf("Search results:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(registrations[i], target) == 0) {
            printf("  Found at position %d\n", i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("  Registration number '%s' not found.\n", target);
    }
}

/* ========== Main Menu ========== */
int main(void) {
    float salaries[NUM_SALARIES];
    float budgets[NUM_BUDGETS];
    char registrations[NUM_REGISTRATIONS][REG_LENGTH];

    int choice;
    int salariesCaptured = 0;
    int budgetsCaptured = 0;
    int registrationsCaptured = 0;

    do {
        printf("\n========================================\n");
        printf("  Municipal Information Management System\n");
        printf("========================================\n");
        printf("1. Employee Salaries (Part A)\n");
        printf("2. Department Budgets (Part B)\n");
        printf("3. Vehicle Registrations (Part C)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { /* Salaries menu */
                int sub;
                do {
                    printf("\n--- Employee Salaries Menu ---\n");
                    printf("1. Capture 50 salaries\n");
                    printf("2. Display all salaries\n");
                    printf("3. Calculate average salary\n");
                    printf("4. Find highest salary\n");
                    printf("5. Find lowest salary\n");
                    printf("6. Search for a salary\n");
                    printf("0. Back to main menu\n");
                    printf("Choice: ");
                    scanf("%d", &sub);

                    switch (sub) {
                        case 1:
                            captureSalaries(salaries, NUM_SALARIES);
                            salariesCaptured = 1;
                            break;
                        case 2:
                            if (salariesCaptured)
                                displaySalaries(salaries, NUM_SALARIES);
                            else
                                printf("Please capture salaries first.\n");
                            break;
                        case 3:
                            if (salariesCaptured)
                                printf("Average salary: %.2f\n",
                                       calculateAverage(salaries, NUM_SALARIES));
                            else
                                printf("Please capture salaries first.\n");
                            break;
                        case 4:
                            if (salariesCaptured)
                                printf("Highest salary: %.2f\n",
                                       findHighest(salaries, NUM_SALARIES));
                            else
                                printf("Please capture salaries first.\n");
                            break;
                        case 5:
                            if (salariesCaptured)
                                printf("Lowest salary: %.2f\n",
                                       findLowest(salaries, NUM_SALARIES));
                            else
                                printf("Please capture salaries first.\n");
                            break;
                        case 6:
                            if (salariesCaptured)
                                searchSalary(salaries, NUM_SALARIES);
                            else
                                printf("Please capture salaries first.\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while (sub != 0);
                break;
            }

            case 2: { /* Budgets menu */
                int sub;
                do {
                    printf("\n--- Department Budgets Menu ---\n");
                    printf("1. Capture 10 department budgets\n");
                    printf("2. Display budgets\n");
                    printf("3. Calculate total budget\n");
                    printf("4. Calculate average budget\n");
                    printf("5. Sort budgets (lowest to highest)\n");
                    printf("0. Back to main menu\n");
                    printf("Choice: ");
                    scanf("%d", &sub);

                    switch (sub) {
                        case 1:
                            captureBudgets(budgets, NUM_BUDGETS);
                            budgetsCaptured = 1;
                            break;
                        case 2:
                            if (budgetsCaptured)
                                displayBudgets(budgets, NUM_BUDGETS);
                            else
                                printf("Please capture budgets first.\n");
                            break;
                        case 3:
                            if (budgetsCaptured)
                                printf("Total budget: %.2f\n",
                                       calculateTotal(budgets, NUM_BUDGETS));
                            else
                                printf("Please capture budgets first.\n");
                            break;
                        case 4:
                            if (budgetsCaptured)
                                printf("Average budget: %.2f\n",
                                       calculateAverage(budgets, NUM_BUDGETS));
                            else
                                printf("Please capture budgets first.\n");
                            break;
                        case 5:
                            if (budgetsCaptured) {
                                sortBudgetsAscending(budgets, NUM_BUDGETS);
                                printf("Budgets sorted from lowest to highest:\n");
                                displayBudgets(budgets, NUM_BUDGETS);
                            } else {
                                printf("Please capture budgets first.\n");
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while (sub != 0);
                break;
            }

            case 3: { /* Registrations menu */
                int sub;
                do {
                    printf("\n--- Vehicle Registrations Menu ---\n");
                    printf("1. Capture 20 registration numbers\n");
                    printf("2. Display all registration numbers\n");
                    printf("3. Search for a registration number\n");
                    printf("0. Back to main menu\n");
                    printf("Choice: ");
                    scanf("%d", &sub);

                    switch (sub) {
                        case 1:
                            captureRegistrations(registrations, NUM_REGISTRATIONS);
                            registrationsCaptured = 1;
                            break;
                        case 2:
                            if (registrationsCaptured)
                                displayRegistrations(registrations, NUM_REGISTRATIONS);
                            else
                                printf("Please capture registrations first.\n");
                            break;
                        case 3:
                            if (registrationsCaptured)
                                searchRegistration(registrations, NUM_REGISTRATIONS);
                            else
                                printf("Please capture registrations first.\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while (sub != 0);
                break;
            }

            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}