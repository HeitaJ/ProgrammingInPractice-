#!/bin/sh
# Compile each source separately, then link
set -e
F="-std=c99 -Wall -Wextra -pedantic"
for m in main employees suppliers assets budget utilities reports storage; do
    gcc $F -c $m.c
done
gcc main.o employees.o suppliers.o assets.o budget.o utilities.o reports.o storage.o -o mfms
echo "Build OK -> ./mfms"
