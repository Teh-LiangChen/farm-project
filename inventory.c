#include "global.h"

sItem ITEM_LIST[MAX_ITEM];
sInventory inventoryList[10];

int currentSelectedSlot = 0;

void InitialiseItem()
{
    ITEM_LIST[ITEM_CANGKUL]     = (sItem){ITEM_CANGKUL, 2, 0, TEXTURE_OBJECT_TOOL};
    ITEM_LIST[ITEM_PADDY_SEED]  = (sItem){ITEM_PADDY_SEED, 0, 0, TEXTURE_OBJECT_CROP};
    ITEM_LIST[ITEM_TOMATO_SEED] = (sItem){ITEM_TOMATO_SEED, 0, 1, TEXTURE_OBJECT_CROP};
}