#include "gameShutdown.h"

void GameShutdown()
{
    for (int i=0; i< MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
    }

    for (int i=0; i < ANIMATION_MAX; i++)
    {
        DisposeSpriteAnimation(player.animations[i]);
    }

    FreeHitbox(&worldHitbox);

    CloseAudioDevice();
}