#include <stdio.h>
int main() {
    double revenue;
    double expenses;
    double balance;
    int departments;
    double payroll;
    double procurement;
    double assets;
    printf("Enter total revenue: ");
    scanf("%lf" , &revenue);
    printf("Enter total expenses: ");
    scanf("%lf"  , &expenses);
    printf("Enter number of departments: ");
    scanf("%lf" , &departments);
    printf("Enter total payroll amount: ");
    scanf("%lf" , &payroll);
    printf("Enter total procurement amount: ");
    scanf("%lf" , &procurement);
    printf("Enter the total value of assets: ");
    scanf("%lf" , &assets);

    balance = revenue - expenses;
    printf("\nFinancial Balance: %.2f\n", balance);
    if(revenue > expenses) {
        printf("The budget is in a SURPLUS.\n");
    }
    else if (revenue < expenses) {
        printf("The budget is in a DEFICIT.\n");
    }
    else {
        printf("The budget is BALANCED.\n");
    }
    return 0;
}
