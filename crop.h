#ifndef CROP_H_
#define CROP_H_

#include "raylib.h"
#include <stdlib.h>

typedef enum
{
    CROP_PADDY = 0,
    CROP_TOMATO,
} crop_type;

typedef enum
{
    CROP_STAGE_GERMINATE = 0,
    CROP_STAGE_GROWTH,
    CROP_STAGE_FRUITING,
    CROP_STAGE_HARVEST,
} crop_stage;

typedef struct
{
    sEntity base;
    Rectangle hitbox;
    Rectangle actionbox;
    sTimer timer;
    int type;
    int stage;
    double duration;
} sCrop;

typedef struct
{
    sCrop* array;
    int counter;
    int capacity;
} sCropList;

sCrop CreateCrop(int x, int y, crop_type type, double duration);

sCropList CreateCropList(int initialCapacity);

void AddCrop(sCrop crop, sCropList* cropList);

void FreeCropList(sCropList* cropList);

#endif