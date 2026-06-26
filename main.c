#include "global.h"

Texture2D textures[MAX_TEXTURES];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sHitbox worldHitbox;
Camera2D camera = {0};
sSprite player;

int main()
{
    InitWindow(screenWidth, screenHeight, "learning-farm");
    SetTargetFPS(60);

    GameStartup();

    while(!WindowShouldClose())
    {
        GameUpdate();

        BeginDrawing();
        ClearBackground(GRAY);

        GameRender();

        EndDrawing();
    }

    GameShutdown();

    CloseWindow();
    return 0;
}