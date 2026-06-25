#include "global.h"
#include "gameStartup.h"
#include "gameUpdate.h"
#include "gameRender.h"
#include "gameShutdown.h"

Rectangle hitbox[400];
Rectangle hillhitbox;
Texture2D textures[MAX_TEXTURES];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
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