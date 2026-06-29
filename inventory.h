#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "global.h"

typedef enum
{
    ITEM_CANGKUL = 0,
    ITEM_PADDY_SEED,
    ITEM_TOMATO_SEED,
    ITEM_PADDY,
    ITEM_TOMATO,
    MAX_ITEM,
} item_name;

typedef struct
{
    int name;
    int texture_index_x;
    int texture_index_y;
    int texture_asset;
} sItem;

typedef struct
{
    sItem* item;
    int count;
} sInventory;

void InitialiseItem();

extern sItem ITEM_LIST[MAX_ITEM];
extern sInventory inventoryList[10];
extern int currentSelectedSlot;

#endif