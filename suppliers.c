/* suppliers.c */
#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utilities.h"

static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

void addSupplier(void)
{
    Supplier *s;

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }
    s = &suppliers[supplierCount];
    s->id = readInt("Supplier ID: ", 1, 999999);
    if (supplierIdExists(s->id)) {
        printf("Supplier ID %d already exists.\n", s->id);
        return;
    }
    readString("Name: ", s->name, sizeof s->name);
    readString("Contact: ", s->contact, sizeof s->contact);
    supplierCount++;
    printf("Supplier added.\n");
}

void listSuppliers(void)
{
    int i;

    if (supplierCount == 0) {
        printf("No suppliers recorded.\n");
        return;
    }
    printf("%-8s %-25s %-20s\n", "ID", "Name", "Contact");
    for (i = 0; i < supplierCount; i++) {
        printf("%-8d %-25s %-20s\n",
               suppliers[i].id, suppliers[i].name, suppliers[i].contact);
    }
}

int getSupplierCount(void)
{
    return supplierCount;
}

const Supplier *getSupplier(int index)
{
    if (index < 0 || index >= supplierCount) {
        return NULL;
    }
    return &suppliers[index];
}

int supplierIdExists(int id)
{
    int i;

    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int addSupplierRecord(int id, const char *name, const char *contact)
{
    if (supplierCount >= MAX_SUPPLIERS || supplierIdExists(id) ||
        strlen(name) >= SUP_NAME_LEN || strlen(contact) >= SUP_CONTACT_LEN) {
        return 0;
    }
    suppliers[supplierCount].id = id;
    strcpy(suppliers[supplierCount].name, name);
    strcpy(suppliers[supplierCount].contact, contact);
    supplierCount++;
    return 1;
}

void clearSuppliers(void)
{
    supplierCount = 0;
}
