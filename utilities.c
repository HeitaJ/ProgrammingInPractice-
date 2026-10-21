#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mfms.h"

#define LINE_SIZE 128

/* Read one line safely; quit cleanly if the input ends. */
static void readLine(char line[], int size)
{
    if (fgets(line, size, stdin) == NULL) {
        printf("\nInput ended. Goodbye.\n");
        exit(0);
    }
}

int readInt(const char *prompt)
{
    char line[LINE_SIZE];
    int value;

    for (;;) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);
        if (sscanf(line, "%d", &value) == 1) {
            return value;
        }
        printf("  Please enter a whole number.\n");
    }
}

double readDouble(const char *prompt)
{
    char line[LINE_SIZE];
    double value;

    for (;;) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);
        if (sscanf(line, "%lf", &value) == 1) {
            return value;
        }
        printf("  Please enter a number.\n");
    }
}

/* Reads the first word typed and copies at most size-1 characters. */
void readWord(const char *prompt, char dest[], int size)
{
    char line[LINE_SIZE];
    char word[LINE_SIZE];

    for (;;) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);
        if (sscanf(line, "%127s", word) == 1) {
            strncpy(dest, word, (size_t)size - 1);
            dest[size - 1] = '\0';
            return;
        }
        printf("  Please type at least one word (no spaces).\n");
    }
}

Date readDate(const char *label)
{
    Date d;

    printf("%s\n", label);
    do {
        d.day = readInt("  Day (1-31): ");
    } while (d.day < 1 || d.day > 31);
    do {
        d.month = readInt("  Month (1-12): ");
    } while (d.month < 1 || d.month > 12);
    do {
        d.year = readInt("  Year (1900-2100): ");
    } while (d.year < 1900 || d.year > 2100);
    return d;
}

/* Binary save: first the record count, then all the records in one fwrite. */
int saveArray(const char *filename, const void *arr, size_t size, int count)
{
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    fwrite(&count, sizeof count, 1, fp);
    if (count > 0) {
        fwrite(arr, size, (size_t)count, fp);
    }
    fclose(fp);
    return 1;
}

/* Binary load: returns the number of records loaded (0 if none/failed). */
int loadArray(const char *filename, void *arr, size_t size, int max)
{
    FILE *fp = fopen(filename, "rb");
    int count = 0;
    size_t got;

    if (fp == NULL) {
        printf("  No saved file '%s' found yet.\n", filename);
        return 0;
    }
    if (fread(&count, sizeof count, 1, fp) != 1 || count < 0 || count > max) {
        printf("  File '%s' is empty or damaged.\n", filename);
        fclose(fp);
        return 0;
    }
    got = fread(arr, size, (size_t)count, fp);
    fclose(fp);
    return (int)got;
}
