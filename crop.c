#include "global.h"

sCrop CreateCrop(int x, int y, crop_type type, double duration)
{
    sCrop crop = 
    {
        .base.x = x,
        .base.y = y,
        .hitbox = (Rectangle){x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT},
        .actionbox = (Rectangle){x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT},
        .type = type,
        .stage = CROP_STAGE_GERMINATE,
        .duration = duration,
    };

    StartTimer(&crop.timer, duration);
    return crop;
}

sCropList CreateCropList(int initialCapacity)
{
    sCropList cropList = 
    {
        .array = NULL,
        .counter = 0,
        .capacity = initialCapacity,
    };

    sCrop* temp = (sCrop*)malloc(sizeof(sCrop) * initialCapacity);
    if (temp == NULL)
    {
        TraceLog(LOG_FATAL, "No memory for croplist creation");
        cropList.capacity = 0;
        return cropList;
    }

    cropList.array = temp;
    return cropList;
}

void AddCrop(sCrop crop, sCropList* cropList)
{
    if(cropList->counter + 5 >= cropList->capacity)
    {
        sCrop* temp = (sCrop*)realloc(cropList->array, sizeof(sCrop) * cropList->capacity * 2);

        if (temp == NULL)
        {
            TraceLog(LOG_FATAL, "No memory for croplist addition");
            return;
        }

        cropList->array = temp;
        cropList->capacity *= 2;
    }

    cropList->array[cropList->counter++] = crop;
}

void FreeCropList(sCropList* cropList)
{
    free(cropList->array);
}