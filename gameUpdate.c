#include "gameUpdate.h"

void GameUpdate()
{
    const float playerSpeed = 10 * TILE_HEIGHT; // pixel per second
    float moveDistance = playerSpeed * GetFrameTime(); // pixel per frame

    float x = player.base.x;
    float y = player.base.y;
    bool hasKeyBeenPressed = false;
    bool moving = false;

    if (IsKeyDown(KEY_LEFT))
    {
        x -= moveDistance;
        hasKeyBeenPressed = true;
        moving = true;
        player.currentAnimation = ANIMATION_WALK_LEFT;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        x += moveDistance;
        hasKeyBeenPressed = true;
        moving = true;
        player.currentAnimation = ANIMATION_WALK_RIGHT;
    }
    else if (IsKeyDown(KEY_UP))
    {
        y -= moveDistance;
        hasKeyBeenPressed = true;
        moving = true;
        player.currentAnimation = ANIMATION_WALK_UP;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        y += moveDistance;
        hasKeyBeenPressed = true;
        moving = true;
        player.currentAnimation = ANIMATION_WALK_DOWN;
    }
    
    if (!moving)
    {
        if (player.currentAnimation == ANIMATION_WALK_LEFT) player.currentAnimation = ANIMATION_IDLE_LEFT;
        else if (player.currentAnimation == ANIMATION_WALK_RIGHT) player.currentAnimation = ANIMATION_IDLE_RIGHT;
        else if (player.currentAnimation == ANIMATION_WALK_UP) player.currentAnimation = ANIMATION_IDLE_UP;
        else if (player.currentAnimation == ANIMATION_WALK_DOWN) player.currentAnimation = ANIMATION_IDLE_DOWN;
    }

    player.base.x = x;
    player.base.y = y;
    camera.target = (Vector2) {player.base.x, player.base.y};

    player.animations[player.currentAnimation].isPlaying = true;
    
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        const float zoomIncrement = 0.125f;
        camera.zoom += (wheel * zoomIncrement);
        //if (camera.zoom < 3.0f) camera.zoom = 3.0f;
        //if (camera.zoom > 8.0f) camera.zoom = 8.0f;
    }
}