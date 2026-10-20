/* assets.h - municipal asset operations */
#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS     100
#define ASSET_NAME_LEN 50

typedef struct {
    int    id;
    char   name[ASSET_NAME_LEN];
    double value;
} Asset;

void addAsset(void);
void listAssets(void);
int  getAssetCount(void);
const Asset *getAsset(int index);
int  assetIdExists(int id);
int  addAssetRecord(int id, const char *name, double value);
void clearAssets(void);

#endif
