#include <stdio.h>
int main(){
 char supplierName[50];
 float price;
 float budget;
 int registered;
 int documentsComplete;

 //1. Ask user for supplier
 printf("Enter supplier name: ");
 scanf("%49s", supplierName);

 //2. Ask user for tender
 printf("Enter tender price: ");
 scanf("%f", &price);

 //3. Ask user for available budget 
 printf("Enter available budget: ");
 scanf("%f", &budget);

 //4. Ask if supplier is registered
 printf("Is supplier registered? (1=Yes, 0=No): ");
 scanf("%d", &registered);

 //5. Ask if documents are completed
 printf("Are all documents complete? (1=Yes, 0=No): ");
 scanf("%d", &documentsComplete);

 //6. Check if supplier is qualified based on registration, documents, and price
 if (registered == 1 || documentsComplete == 1 && price <= budget)
 {
 printf("\nSupplier is Qualified.\n");
 }
 else
 {
     printf("\nSupplier is Disqualified.\n");
 }  
   return 0; 
}
