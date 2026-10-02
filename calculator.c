#include <stdio.h>
int main (){
    //Declaring variables
    double salary=0.00;
    double housingAllowance=0.00;
    double transportAllowance=0.00;
    double taxAmount=0.00;
    double grossSalary=0.00;
    double netSalary=0.00;

    //1. Ask user for salary
    printf("Enter the Salary: ");
    scanf("%lf", &salary);

    //2. Ask user for housing allowance
    printf("Enter the housingAllowance: ");
    scanf("%lf", &housingAllowance);

    //3. Ask user for transport allowance
    printf("Enter the transportAllowance: ");
    scanf("%lf", &transportAllowance);

    //4. Ask user for Tax amount
    printf("Enter your tax amount: ");
    scanf("%lf", &taxAmount);

    //5. Calculate the Gross
    grossSalary = salary + housingAllowance + transportAllowance;
    
    //6. Display the Gross
    printf("Gross: %.2f\n", grossSalary);

    //7. Calculate the Net
    netSalary = grossSalary - taxAmount;

    //8. Display the Net
    printf("Net: %.2lf\n", netSalary);

    return 0;
}