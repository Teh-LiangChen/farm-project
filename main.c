#include "global.h"

sTimer animationTimer;
Texture2D textures[MAX_TEXTURES];
sTile world[WORLD_WIDTH][WORLD_HEIGHT];
sHitbox worldHitbox;
Camera2D camera = {0};
sSprite player;
sCropList cropList;
const sTileset TILESET_TABLE[] = 
{
    [GRASS_PLAIN]          = { 1, 1, TEXTURE_TILESET_GRASS },
    [GRASS_PLAIN2]         = { 1, 1, TEXTURE_TILESET_GRASS },
    [GRASS_LONG]           = { 0, 5, TEXTURE_TILESET_GRASS },
    [GRASS_LONG_WHTIE]     = { 0, 6, TEXTURE_TILESET_GRASS },
    [GRASS_SHORT_1]        = { 1, 5, TEXTURE_TILESET_GRASS },
    [GRASS_SHORT_2]        = { 2, 5, TEXTURE_TILESET_GRASS },
    [GRASS_SHORT_1_WHITE]  = { 1, 6, TEXTURE_TILESET_GRASS },
    [GRASS_SHORT_2_WHITE]  = { 2, 6, TEXTURE_TILESET_GRASS },
    [DIRT_FARM]            = { 0, 6, TEXTURE_TILESET_DIRT  },
};

int main()
{
    InitWindow(screenWidth, screenHeight, "learning-farm");
    SetTargetFPS(60);

    GameStartup();

    while(!WindowShouldClose())
    {
        GameUpdate();

        BeginDrawing();
        ClearBackground(WHITE);

        GameRender();

        EndDrawing();
    }

    GameShutdown();

    CloseWindow();
    return 0;
}