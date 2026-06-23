#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "raylib.h"

typedef struct
{
	int framesPerSecond;
	float timeStarted;
    bool isPlaying;
    bool isLooping;
	Rectangle* rectangles;
	int rectanglesLength;
} sAnimation;

sAnimation CreateSpriteAnimation(int framesPerSecond, bool isLooping, Rectangle rectangles[], int length);
void DisposeSpriteAnimation(sAnimation animation);
void DrawSpriteAnimationPro(sAnimation* animation, Texture2D texture, Rectangle dest, Vector2 origin, float rotation, Color tint);

#endif