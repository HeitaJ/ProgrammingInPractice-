/* storage.h - persistence (text and binary files) for the MFMS */
#ifndef STORAGE_H
#define STORAGE_H

#define DATA_DIR "data"

int  ensureDataDir(void);
void saveAllText(void);          /* employees, suppliers, assets, budgets -> data/ text files */
void loadAllText(void);          /* data folder -> memory (replaces what is in memory)   */
void saveEmployeesBinary(void);  /* data/employees.dat */
void loadEmployeesBinary(void);
void backupData(void);           /* copies each existing data file to <name>.bak */

#endif
