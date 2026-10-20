/* utilities.h - reusable input/helper functions */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>

int  readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min);
void readString(const char *prompt, char *buf, size_t size);
void pauseScreen(void);

#endif
