#include "hitbox.h"
#include <stdlib.h>

sHitbox CreateHitboxRec(int initialCapacity)
{
    sHitbox hitbox =
	{
		.rectangles = NULL,
		.counter = 0,
        .capacity = initialCapacity,
	};
	
	Rectangle* temp = (Rectangle*)malloc(sizeof(Rectangle) * initialCapacity);
	if (temp == NULL)
	{
		TraceLog(LOG_FATAL, "No memory for animation");
		hitbox.capacity = 0;
		return hitbox;
	}

	hitbox.rectangles = temp;
	return hitbox;
}

void AddHitboxRec(sHitbox* hitbox, Rectangle rect)
{
    Rectangle* temp;
    if(hitbox->counter + 5 >= hitbox->capacity)
    {
        temp = (Rectangle*)realloc(hitbox->rectangles, hitbox->capacity * 2 * sizeof(Rectangle));
        if (temp == NULL)
        {
            TraceLog(LOG_FATAL, "No memory for hitbox");
            return;
        }

        hitbox->rectangles = temp;
        hitbox->capacity *= 2;
    }

    hitbox->rectangles[hitbox->counter++] = rect;
}

void FreeHitbox(sHitbox* hitbox)
{
    free(hitbox->rectangles);
}