#include <stdio.h>
#include <string.h>
  
#define MAX_LEN 100
int main() {
    char supplierName[100];
    char email[100];
    char phone[20];
    char town[50];
    
    char copiedName[100];
    char searchName[100];

    printf("=== Supplier Information System ===\n\n");
    
    printf("Enter Supplier Name: ");
    fgets(supplierName, sizeof(supplierName), stdin);
    supplierName[strcspn(supplierName, "\n")] = '\0';
    
    printf("Enter Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    printf("Enter Town: ");
    fgets(town, sizeof(town), stdin);
    town[strcspn(town, "\n")] = '\0';


    /* 2. Display the information */
    printf("\n--- Supplier Details ---\n");
    printf("Name  : %s\n", supplierName);
    printf("Email : %s\n", email);
    printf("Phone : %s\n", phone);
    printf("Town  : %s\n", town);

    /* 3. Display the length of the supplier name */
    printf("\nLength of supplier name: %zu characters\n", strlen(supplierName));

    /* 4. Copy the supplier name into a second variable */
    strcpy(copiedName, supplierName);
    printf("Copied name (second variable): %s\n", copiedName);

    /* 5. Search for the supplier */
    printf("\n--- Search Supplier ---\n");
    printf("Enter name to search for: ");
    fgets(searchName, MAX_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    /* 6. Display an appropriate message */
    if (strcmp(supplierName, searchName) == 0) {
        printf("Supplier FOUND!\n");
        printf("Matching record:\n");
        printf("  Name  : %s\n", supplierName);
        printf("  Email : %s\n", email);
        printf("  Phone : %s\n", phone);
        printf("  Town  : %s\n", town);
    } else {
        printf("Supplier NOT FOUND.\n");
        printf("No record matches the name \"%s\".\n", searchName);
    }

    return 0;
}