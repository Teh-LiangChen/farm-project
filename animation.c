#include "animation.h"

#include <stdlib.h>

sAnimation CreateSpriteAnimation(int framesPerSecond, bool isLooping, Rectangle rectangles[], int length)
{
	sAnimation animation =
	{
		.framesPerSecond = framesPerSecond,
		.timeStarted = GetTime(),
        .isPlaying = false,
        .isLooping = isLooping,
		.rectangles = NULL,
		.rectanglesLength = length
	};
	
	Rectangle* mem = (Rectangle*)malloc(sizeof(Rectangle) * length);
	if (mem == NULL)
	{
		TraceLog(LOG_FATAL, "No memory for animation");
		animation.rectanglesLength = 0;
		return animation;
	}

	animation.rectangles = mem;

	for (int i = 0; i < length; i++)
	{
		animation.rectangles[i] = rectangles[i];		
	}

	return animation;
}

void DisposeSpriteAnimation(sAnimation animation)
{
	free(animation.rectangles);
}

void DrawSpriteAnimationPro(sAnimation* animation, Texture2D texture, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    if (!animation->isPlaying) return;

	int index = (int)((GetTime() - animation->timeStarted) * animation->framesPerSecond) % animation->rectanglesLength;

    if (!animation->isLooping && index == animation->rectanglesLength - 1)
    {
        animation->isPlaying = false;
    }
    
	Rectangle source = animation->rectangles[index];
	DrawTexturePro(texture, source, dest, origin, rotation, tint);
}