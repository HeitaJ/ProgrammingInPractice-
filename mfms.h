/* mfms.h - function prototypes for the MFMS */
#ifndef MFMS_H
#define MFMS_H

#include <stddef.h>
#include "records.h"

/* utilities.c */
int    readInt(const char *prompt);
double readDouble(const char *prompt);
void   readWord(const char *prompt, char dest[], int size);
Date   readDate(const char *label);
int    saveArray(const char *filename, const void *arr, size_t size, int count);
int    loadArray(const char *filename, void *arr, size_t size, int max);

/* employees.c */
int  addEmployee(Employee list[], int count);
void displayEmployees(const Employee list[], int count);
int  addSupplier(Supplier list[], int count);
void displaySuppliers(const Supplier list[], int count);

/* Week 12 - pointers */
void      updateSalary(Employee *e, double newSalary);
Employee *findEmployee(Employee list[], int n, int id);
void      updateEmployeeSalaryMenu(Employee list[], int n);
void      increaseBudget(Budget *b, double amount);
void      increaseBudgetMenu(Budget list[], int n);

/* budget.c */
int  addBudget(Budget list[], int count);
void displayBudgets(const Budget list[], int count);
int  addProject(Project list[], int count);
void displayProjects(const Project list[], int count);

/* reports.c */
int  addAsset(Asset list[], int count);
void displayAssets(const Asset list[], int count);
void searchSuppliersByTown(const Supplier list[], int count);
void listAssetsAbove(const Asset list[], int count);
void projectsEndingIn(const Project list[], int count);

#endif
