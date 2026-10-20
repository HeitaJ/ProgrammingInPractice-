/* storage.c
 * Text format: one record per line, fields separated by '|'.
 *   employees.txt : id|name|salary
 *   suppliers.txt : id|name|contact
 *   assets.txt    : id|name|value
 *   budgets.txt   : department|allocated|spent
 * A '|' typed inside a field is replaced by '_' when saving, so a record can
 * never be split into the wrong number of fields.
 * Loading REPLACES the in-memory records of that type. Malformed lines and
 * duplicate IDs are skipped and counted.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include "storage.h"
#include "employees.h"
#include "suppliers.h"
#include "assets.h"
#include "budget.h"

#define EMP_TXT  DATA_DIR "/employees.txt"
#define SUP_TXT  DATA_DIR "/suppliers.txt"
#define AST_TXT  DATA_DIR "/assets.txt"
#define BUD_TXT  DATA_DIR "/budgets.txt"
#define EMP_BIN  DATA_DIR "/employees.dat"

#define LINE_LEN   256
#define MAX_FIELDS 4

int ensureDataDir(void)
{
    int rc;
#ifdef _WIN32
    rc = _mkdir(DATA_DIR);
#else
    rc = mkdir(DATA_DIR, 0755);
#endif
    if (rc != 0 && errno != EEXIST) {
        perror("Cannot create data directory");
        return 0;
    }
    return 1;
}

/* ---------- helpers ---------- */

static void cleanField(const char *src, char *dst, size_t size)
{
    size_t i;

    for (i = 0; i + 1 < size && src[i] != '\0'; i++) {
        dst[i] = (src[i] == '|') ? '_' : src[i];
    }
    dst[i] = '\0';
}

/* Splits line in place on '|'. Returns the number of fields found. */
static int splitFields(char *line, char *fields[], int max)
{
    int n = 0;
    char *p = line;

    fields[n++] = p;
    while ((p = strchr(p, '|')) != NULL) {
        *p++ = '\0';
        if (n >= max) {
            return max + 1;      /* too many fields */
        }
        fields[n++] = p;
    }
    return n;
}

static int toInt(const char *s, int *out)
{
    char *end;
    long v = strtol(s, &end, 10);

    if (end == s || *end != '\0' || v < 1 || v > 999999) {
        return 0;
    }
    *out = (int)v;
    return 1;
}

static int toMoney(const char *s, double *out)
{
    char *end;
    double v = strtod(s, &end);

    if (end == s || *end != '\0' || v < 0.0) {
        return 0;
    }
    *out = v;
    return 1;
}

/* ---------- per-entity line parsers: return 1 if the record was stored ---------- */

static int parseEmployee(char *f[], int n)
{
    int id;
    double salary;

    if (n != 3 || !toInt(f[0], &id) || !toMoney(f[2], &salary)) {
        return 0;
    }
    return addEmployeeRecord(id, f[1], salary);
}

static int parseSupplier(char *f[], int n)
{
    int id;

    if (n != 3 || !toInt(f[0], &id)) {
        return 0;
    }
    return addSupplierRecord(id, f[1], f[2]);
}

static int parseAsset(char *f[], int n)
{
    int id;
    double value;

    if (n != 3 || !toInt(f[0], &id) || !toMoney(f[2], &value)) {
        return 0;
    }
    return addAssetRecord(id, f[1], value);
}

static int parseBudget(char *f[], int n)
{
    double allocated, spent;

    if (n != 3 || f[0][0] == '\0' || !toMoney(f[1], &allocated) || !toMoney(f[2], &spent)) {
        return 0;
    }
    return addBudgetRecord(f[0], allocated, spent);
}

/* Generic text loader. Returns records loaded, or -1 if the file could not be opened
 * (memory is left untouched in that case). */
static int loadText(const char *path, const char *label,
                    int (*parse)(char **, int), void (*clear)(void))
{
    FILE *fp = fopen(path, "r");
    char line[LINE_LEN];
    char *fields[MAX_FIELDS + 1];
    int loaded = 0, skipped = 0, n;

    if (fp == NULL) {
        if (errno == ENOENT) {
            printf("%s: no saved file yet (%s) - skipped.\n", label, path);
        } else {
            perror(path);
        }
        return -1;
    }
    clear();
    while (fgets(line, sizeof line, fp) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') {
            continue;                     /* ignore blank lines */
        }
        n = splitFields(line, fields, MAX_FIELDS);
        if (parse(fields, n)) {
            loaded++;
        } else {
            skipped++;
        }
    }
    fclose(fp);
    printf("%s: loaded %d record(s)", label, loaded);
    if (skipped > 0) {
        printf(", skipped %d malformed/duplicate line(s)", skipped);
    }
    printf(".\n");
    return loaded;
}

/* ---------- text save ---------- */
/* "w" is used ON PURPOSE: every save writes a complete snapshot of memory, so the
 * old file must be replaced. Use Backup Data first if the old copy matters. */

static int saveEmployeesText(void)
{
    FILE *fp = fopen(EMP_TXT, "w");
    const Employee *e;
    char name[NAME_LEN];
    int i, count = getEmployeeCount();

    if (fp == NULL) { perror(EMP_TXT); return -1; }
    for (i = 0; i < count; i++) {
        e = getEmployee(i);
        cleanField(e->name, name, sizeof name);
        fprintf(fp, "%d|%s|%.2f\n", e->id, name, e->salary);
    }
    if (fclose(fp) != 0) { perror(EMP_TXT); return -1; }
    return count;
}

static int saveSuppliersText(void)
{
    FILE *fp = fopen(SUP_TXT, "w");
    const Supplier *s;
    char name[SUP_NAME_LEN], contact[SUP_CONTACT_LEN];
    int i, count = getSupplierCount();

    if (fp == NULL) { perror(SUP_TXT); return -1; }
    for (i = 0; i < count; i++) {
        s = getSupplier(i);
        cleanField(s->name, name, sizeof name);
        cleanField(s->contact, contact, sizeof contact);
        fprintf(fp, "%d|%s|%s\n", s->id, name, contact);
    }
    if (fclose(fp) != 0) { perror(SUP_TXT); return -1; }
    return count;
}

static int saveAssetsText(void)
{
    FILE *fp = fopen(AST_TXT, "w");
    const Asset *a;
    char name[ASSET_NAME_LEN];
    int i, count = getAssetCount();

    if (fp == NULL) { perror(AST_TXT); return -1; }
    for (i = 0; i < count; i++) {
        a = getAsset(i);
        cleanField(a->name, name, sizeof name);
        fprintf(fp, "%d|%s|%.2f\n", a->id, name, a->value);
    }
    if (fclose(fp) != 0) { perror(AST_TXT); return -1; }
    return count;
}

static int saveBudgetsText(void)
{
    FILE *fp = fopen(BUD_TXT, "w");
    const BudgetItem *b;
    char dept[DEPT_LEN];
    int i, count = getBudgetCount();

    if (fp == NULL) { perror(BUD_TXT); return -1; }
    for (i = 0; i < count; i++) {
        b = getBudgetItem(i);
        cleanField(b->department, dept, sizeof dept);
        fprintf(fp, "%s|%.2f|%.2f\n", dept, b->allocated, b->spent);
    }
    if (fclose(fp) != 0) { perror(BUD_TXT); return -1; }
    return count;
}

static void report(const char *label, int n)
{
    if (n >= 0) {
        printf("%s: saved %d record(s).\n", label, n);
    }
}

void saveAllText(void)
{
    if (!ensureDataDir()) {
        return;
    }
    report("Employees", saveEmployeesText());
    report("Suppliers", saveSuppliersText());
    report("Assets",    saveAssetsText());
    report("Budgets",   saveBudgetsText());
}

void loadAllText(void)
{
    loadText(EMP_TXT, "Employees", parseEmployee, clearEmployees);
    loadText(SUP_TXT, "Suppliers", parseSupplier, clearSuppliers);
    loadText(AST_TXT, "Assets",    parseAsset,    clearAssets);
    loadText(BUD_TXT, "Budgets",   parseBudget,   clearBudgets);
}

/* ---------- binary (employees only) ---------- */
/* Raw struct bytes: fast and simple, but tied to this compiler/platform's
 * sizeof(Employee), padding and byte order. Not an interchange format. */

void saveEmployeesBinary(void)
{
    FILE *fp;
    const Employee *e;
    int i, count = getEmployeeCount();

    if (!ensureDataDir()) {
        return;
    }
    fp = fopen(EMP_BIN, "wb");
    if (fp == NULL) {
        perror(EMP_BIN);
        return;
    }
    for (i = 0; i < count; i++) {
        e = getEmployee(i);
        if (fwrite(e, sizeof *e, 1, fp) != 1) {
            perror("Error writing employee");
            fclose(fp);
            return;
        }
    }
    if (fclose(fp) != 0) {
        perror(EMP_BIN);
        return;
    }
    printf("Employees (binary): saved %d record(s).\n", count);
}

void loadEmployeesBinary(void)
{
    FILE *fp = fopen(EMP_BIN, "rb");
    Employee e;
    int loaded = 0, skipped = 0;

    if (fp == NULL) {
        if (errno == ENOENT) {
            printf("Employees (binary): no saved file yet (%s) - skipped.\n", EMP_BIN);
        } else {
            perror(EMP_BIN);
        }
        return;
    }
    clearEmployees();
    while (fread(&e, sizeof e, 1, fp) == 1) {
        e.name[NAME_LEN - 1] = '\0';          /* never trust bytes from a file */
        if (addEmployeeRecord(e.id, e.name, e.salary)) {
            loaded++;
        } else {
            skipped++;
        }
    }
    fclose(fp);
    printf("Employees (binary): loaded %d record(s)", loaded);
    if (skipped > 0) {
        printf(", skipped %d invalid/duplicate record(s)", skipped);
    }
    printf(".\n");
}

/* ---------- backup ---------- */

static void backupOne(const char *path)
{
    char bakPath[128];
    FILE *in = fopen(path, "rb");
    FILE *out;
    char buf[1024];
    size_t n;

    if (in == NULL) {
        printf("Backup: %s not found - skipped.\n", path);
        return;
    }
    sprintf(bakPath, "%s.bak", path);
    out = fopen(bakPath, "wb");
    if (out == NULL) {
        perror(bakPath);
        fclose(in);
        return;
    }
    while ((n = fread(buf, 1, sizeof buf, in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            perror(bakPath);
            break;
        }
    }
    fclose(in);
    fclose(out);
    printf("Backup: %s -> %s\n", path, bakPath);
}

void backupData(void)
{
    backupOne(EMP_TXT);
    backupOne(SUP_TXT);
    backupOne(AST_TXT);
    backupOne(BUD_TXT);
    backupOne(EMP_BIN);
}
