#ifndef HITBOX_H_
#define HITBOX_H_

#include "raylib.h"

typedef struct
{
    Rectangle* rectangles;
    int counter;
    int capacity;
}sHitbox;

//TO-DO other type of collision shape
sHitbox CreateHitboxRec(int initialCapacity);
void AddHitboxRec(sHitbox* hitbox, Rectangle rect);
void FreeHitbox(sHitbox* hitbox);

#endif