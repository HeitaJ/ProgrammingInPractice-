/* utilities.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

static int readLine(char *buf, size_t size)
{
    if (fgets(buf, (int)size, stdin) == NULL) {
        return 0;
    }
    buf[strcspn(buf, "\n")] = '\0';
    return 1;
}

int readInt(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long v;

    for (;;) {
        printf("%s", prompt);
        if (!readLine(line, sizeof line)) {
            return min;            /* EOF: fall back safely */
        }
        v = strtol(line, &end, 10);
        if (end != line && *end == '\0' && v >= min && v <= max) {
            return (int)v;
        }
        printf("Invalid input. Enter a whole number from %d to %d.\n", min, max);
    }
}

double readDouble(const char *prompt, double min)
{
    char line[64];
    char *end;
    double v;

    for (;;) {
        printf("%s", prompt);
        if (!readLine(line, sizeof line)) {
            return min;
        }
        v = strtod(line, &end);
        if (end != line && *end == '\0' && v >= min) {
            return v;
        }
        printf("Invalid input. Enter a number >= %.2f.\n", min);
    }
}

void readString(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        printf("%s", prompt);
        if (!readLine(buf, size)) {
            buf[0] = '\0';
            return;
        }
        if (buf[0] != '\0') {
            return;
        }
        printf("Input cannot be empty.\n");
    }
}

void pauseScreen(void)
{
    char line[8];
    printf("\nPress Enter to continue...");
    readLine(line, sizeof line);
}
