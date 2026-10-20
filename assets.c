/* assets.c */
#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utilities.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;

void addAsset(void)
{
    Asset *a;

    if (assetCount >= MAX_ASSETS) {
        printf("Asset list is full.\n");
        return;
    }
    a = &assets[assetCount];
    a->id = readInt("Asset ID: ", 1, 999999);
    if (assetIdExists(a->id)) {
        printf("Asset ID %d already exists.\n", a->id);
        return;
    }
    readString("Asset name: ", a->name, sizeof a->name);
    a->value = readDouble("Value: ", 0.0);
    assetCount++;
    printf("Asset added.\n");
}

void listAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("No assets recorded.\n");
        return;
    }
    printf("%-8s %-30s %12s\n", "ID", "Name", "Value");
    for (i = 0; i < assetCount; i++) {
        printf("%-8d %-30s %12.2f\n", assets[i].id, assets[i].name, assets[i].value);
    }
}

int getAssetCount(void)
{
    return assetCount;
}

const Asset *getAsset(int index)
{
    if (index < 0 || index >= assetCount) {
        return NULL;
    }
    return &assets[index];
}

int assetIdExists(int id)
{
    int i;

    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int addAssetRecord(int id, const char *name, double value)
{
    if (assetCount >= MAX_ASSETS || assetIdExists(id) ||
        strlen(name) >= ASSET_NAME_LEN) {
        return 0;
    }
    assets[assetCount].id = id;
    strcpy(assets[assetCount].name, name);
    assets[assetCount].value = value;
    assetCount++;
    return 1;
}

void clearAssets(void)
{
    assetCount = 0;
}
