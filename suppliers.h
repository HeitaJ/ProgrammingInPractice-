/* suppliers.h - supplier operations */
#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define SUP_NAME_LEN  50
#define SUP_CONTACT_LEN 40

typedef struct {
    int  id;
    char name[SUP_NAME_LEN];
    char contact[SUP_CONTACT_LEN];
} Supplier;

void addSupplier(void);
void listSuppliers(void);
int  getSupplierCount(void);
const Supplier *getSupplier(int index);
int  supplierIdExists(int id);
int  addSupplierRecord(int id, const char *name, const char *contact);
void clearSuppliers(void);

#endif
