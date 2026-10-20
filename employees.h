/* employees.h - employee operations */
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN      50

typedef struct {
    int    id;
    char   name[NAME_LEN];
    double salary;
} Employee;

void   addEmployee(void);
void   listEmployees(void);
void   searchEmployee(void);
double calculatePayrollTotal(void);
int    getEmployeeCount(void);
const Employee *getEmployee(int index);
int    employeeIdExists(int id);
int    addEmployeeRecord(int id, const char *name, double salary); /* 1 = ok, 0 = rejected */
void   clearEmployees(void);

#endif
