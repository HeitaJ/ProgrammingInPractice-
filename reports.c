#include <stdio.h>
#include <string.h>
#include "mfms.h"

/* ---------------- Assets ---------------- */
int addAsset(Asset list[], int count)
{
    Asset a;

    if (count >= MAX_RECORDS) {
        printf("  Asset list is full (%d records).\n", MAX_RECORDS);
        return count;
    }
    a.id = readInt("  ID: ");
    readWord("  Description (one word): ", a.description, (int)sizeof a.description);
    a.value    = readDouble("  Value (N$): ");
    a.acquired = readDate("  Date acquired:");

    list[count] = a;
    printf("  Asset added.\n");
    return count + 1;
}

void displayAssets(const Asset list[], int count)
{
    int i, best = 0;
    double total = 0.0;

    if (count == 0) {
        printf("  No assets stored yet.\n");
        return;
    }
    printf("\n%-6s %-20s %14s %-12s\n", "ID", "Description", "Value (N$)", "Acquired");
    for (i = 0; i < count; i++) {
        printf("%-6d %-20s %14.2f %02d/%02d/%d\n",
               list[i].id, list[i].description, list[i].value,
               list[i].acquired.day, list[i].acquired.month, list[i].acquired.year);
        total += list[i].value;
    }
    for (i = 1; i < count; i++) {
        if (list[i].value > list[best].value) {
            best = i;
        }
    }
    printf("\nTotal value of assets: N$%.2f\n", total);
    printf("Most valuable asset: %s (N$%.2f)\n", list[best].description, list[best].value);
}

/* ---------------- Challenge / extension reports ---------------- */
void searchSuppliersByTown(const Supplier list[], int count)
{
    char town[20];
    int i, found = 0;

    readWord("  Town to search: ", town, (int)sizeof town);
    for (i = 0; i < count; i++) {
        if (strcmp(list[i].town, town) == 0) {
            if (!found) {
                printf("\n%-6s %-15s %-25s %-14s\n", "ID", "Name", "Email", "Phone");
            }
            printf("%-6d %-15s %-25s %-14s\n",
                   list[i].id, list[i].name, list[i].email, list[i].phone);
            found++;
        }
    }
    if (!found) {
        printf("  No suppliers found in %s.\n", town);
    }
}

void listAssetsAbove(const Asset list[], int count)
{
    double limit = readDouble("  Show assets worth more than (N$): ");
    int i, found = 0;

    for (i = 0; i < count; i++) {
        if (list[i].value > limit) {
            printf("  %-6d %-20s N$%.2f\n", list[i].id, list[i].description, list[i].value);
            found++;
        }
    }
    if (!found) {
        printf("  No assets worth more than N$%.2f.\n", limit);
    }
}

void projectsEndingIn(const Project list[], int count)
{
    int year = readInt("  Year to search: ");
    int i, found = 0;

    for (i = 0; i < count; i++) {
        if (list[i].endDate.year == year) {
            printf("  %-6d %-20s ends %02d/%02d/%d\n", list[i].id, list[i].title,
                   list[i].endDate.day, list[i].endDate.month, list[i].endDate.year);
            found++;
        }
    }
    if (!found) {
        printf("  No projects end in %d.\n", year);
    }
}
