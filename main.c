#include "raylib.h"
#include "raymath.h"

#include "animation.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

const int screenWidth = 800;
const int screenHeight = 600;

typedef enum 
{
    // MAP AND TERRAIN
    TEXTURE_TILESET_GRASS = 0,

    // SPRITE
    TEXTURE_SPRITE_BASIC,

    //OBJECTS
    MAX_TEXTURES
} texture_asset;

Texture2D textures[MAX_TEXTURES];

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 20

typedef enum 
{
    GRASS_PLAIN = 0,
    GRASS_LONG,
    GRASS_LONG_WHTIE,
    GRASS_SHORT_1,
    GRASS_SHORT_2,
    GRASS_SHORT_1_WHITE,
    GRASS_SHORT_2_WHITE,
    GRASS_MAX,
}grass_tile_type;

typedef struct
{
    int x;
    int y;
    int type;
} sTile;

sTile world[WORLD_WIDTH][WORLD_HEIGHT];

Camera2D camera = {0};

typedef struct
{
    int x;
    int y;
} sEntity;

typedef enum
{
    ANIMATION_IDLE_DOWN = 0,
    ANIMATION_IDLE_UP,
    ANIMATION_IDLE_LEFT,
    ANIMATION_IDLE_RIGHT,
    ANIMATION_WALK_UP,
    ANIMATION_WALK_DOWN,
    ANIMATION_WALK_LEFT,
    ANIMATION_WALK_RIGHT,
    ANIMATION_MAX,
} AnimationType;

typedef struct
{
    sEntity base;
    sAnimation animations[ANIMATION_MAX];
    AnimationType currentAnimation;
} sSprite;

sSprite player;

void GameStartup();
void GameUpdate();
void GameRender();
void GameShutdown();
void DrawTile (int pos_x, int pos_y, int texture_index_x, int texture_index_y, Texture2D texture);
void UpdateDrawFrame(void);

void GameStartup()
{
    InitAudioDevice();

    Image image = LoadImage("assets/sprout-lands-sprites-basic-pack/Tilesets/Grass.png");
    textures[TEXTURE_TILESET_GRASS] = LoadTextureFromImage(image);
    UnloadImage(image);

    image = LoadImage("assets/sprout-lands-sprites-basic-pack/Characters/basic-character-spritesheet.png");
    textures[TEXTURE_SPRITE_BASIC] = LoadTextureFromImage(image);
    UnloadImage(image);  

    for (int i=0; i < WORLD_WIDTH; i++)
    {
        for (int j=0; j< WORLD_HEIGHT; j++)
        {
            world[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .type = GetRandomValue(GRASS_PLAIN, GRASS_MAX)
            };
        }
    }

    //starting position of player
    player = (sSprite)
    {
        .base = {.x = TILE_WIDTH * 3,
                 .y = TILE_HEIGHT * 3},
        .currentAnimation = ANIMATION_IDLE_DOWN,
    };

    player.animations[ANIMATION_IDLE_DOWN].isPlaying = true;

    player.animations[ANIMATION_IDLE_DOWN] = CreateSpriteAnimation( 4, 
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){1*TILE_WIDTH, 1*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){4*TILE_WIDTH, 1*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);

    player.animations[ANIMATION_IDLE_UP] = CreateSpriteAnimation(   4, 
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){1*TILE_WIDTH, 4*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){4*TILE_WIDTH, 4*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);
    
    player.animations[ANIMATION_IDLE_LEFT] = CreateSpriteAnimation( 4, 
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){1*TILE_WIDTH, 7*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){4*TILE_WIDTH, 7*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);
    
    player.animations[ANIMATION_IDLE_RIGHT] = CreateSpriteAnimation(4, 
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){1*TILE_WIDTH, 10*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){4*TILE_WIDTH, 10*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);

    player.animations[ANIMATION_WALK_DOWN] = CreateSpriteAnimation( 4,
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){7*TILE_WIDTH, 1*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){10*TILE_WIDTH, 1*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);   

    player.animations[ANIMATION_WALK_UP] = CreateSpriteAnimation(   4,
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){7*TILE_WIDTH, 4*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){10*TILE_WIDTH, 4*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);
    
    player.animations[ANIMATION_WALK_LEFT] = CreateSpriteAnimation( 4,
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){7*TILE_WIDTH, 7*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){10*TILE_WIDTH, 7*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);                                                                
    
    player.animations[ANIMATION_WALK_RIGHT] = CreateSpriteAnimation( 4,
                                                                    true,
                                                                    (Rectangle[]){  (Rectangle){7*TILE_WIDTH, 10*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT},
                                                                                    (Rectangle){10*TILE_WIDTH, 10*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT}},
                                                                    2);

    camera.target = (Vector2) {player.base.x,player.base.y};
    camera.offset = (Vector2) { (float) screenWidth / 2, (float) screenHeight /2};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
}

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

void GameRender()
{
    BeginMode2D(camera);

    sTile tile;
    int texture_index_x = 0;
    int texture_index_y = 0;

    // render world
    for (int i=0; i < WORLD_WIDTH; i++)
    {
        for (int j=0; j< WORLD_HEIGHT; j++)
        {

            tile = world[i][j];

            //border tile
            //top left corner
            if (i == 0 && j == 0)
            {
                texture_index_x = 0;
                texture_index_y = 0;
            }
            //top right corner
            else if (i == WORLD_WIDTH-1 && j == 0)
            {
                texture_index_x = 2;
                texture_index_y = 0;
            }
            //bottom left corner
            else if (i == 0 && j == WORLD_HEIGHT-1)
            {
                texture_index_x = 0;
                texture_index_y = 2;
            }
            //bottom right corner
            else if (i == WORLD_WIDTH-1 && j == WORLD_HEIGHT-1)
            {
                texture_index_x = 2;
                texture_index_y = 2;
            }
            //top tile
            else if (i == 0)
            {
                texture_index_x = 0;
                texture_index_y = 1;
            }
            //left tile
            else if (j == 0)
            {
                texture_index_x = 1;
                texture_index_y = 0;
            }
            //right tile
            else if (i == WORLD_WIDTH-1)
            {
                texture_index_x = 2;
                texture_index_y = 1;
            }
            //bottom tile
            else if (j == WORLD_HEIGHT-1)
            {
                texture_index_x = 1;
                texture_index_y = 2;
            }
            //center tile with random grass tile
            else
            {
                switch (tile.type)
                {
                    case GRASS_LONG:
                        texture_index_x = 0;
                        texture_index_y = 5;
                        break;
                    case GRASS_LONG_WHTIE:
                        texture_index_x = 0;
                        texture_index_y = 6;
                        break;
                    //MAX also plain grass so that more plan grass
                    case GRASS_MAX:
                        texture_index_x = 1;
                        texture_index_y = 1;
                        break;
                    case GRASS_PLAIN:
                        texture_index_x = 1;
                        texture_index_y = 1;
                        break;
                    case GRASS_SHORT_1:
                        texture_index_x = 1;
                        texture_index_y = 5;
                        break;
                    case GRASS_SHORT_1_WHITE:
                        texture_index_x = 1;
                        texture_index_y = 6;
                        break;
                    case GRASS_SHORT_2:
                        texture_index_x = 2;
                        texture_index_y = 5;
                        break;
                    case GRASS_SHORT_2_WHITE:
                        texture_index_x = 2;
                        texture_index_y = 6;
                        break;
                } 
            }

            DrawTile (tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y, textures[TEXTURE_TILESET_GRASS]);
        }
    }

    // render player
    //DrawTile(camera.target.x, camera.target.y, 1, 1,textures[TEXTURE_SPRITE_BASIC]);
    Rectangle dest = {  (int)player.base.x,
                        (int)player.base.y,
                        TILE_WIDTH,
                        TILE_HEIGHT};
    
    Vector2 origin = {0,0};
    
    sAnimation* currentAnimation = &player.animations[player.currentAnimation];

    DrawSpriteAnimationPro(currentAnimation, textures[TEXTURE_SPRITE_BASIC], dest, origin, 0.0f, WHITE);
    EndMode2D();
}

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

    CloseAudioDevice();
}

void DrawTile (int pos_x, int pos_y, int texture_index_x, int texture_index_y, Texture2D texture)
{
    Rectangle source = {(float) texture_index_x * TILE_WIDTH, 
                        (float) texture_index_y * TILE_HEIGHT, 
                        (float)TILE_WIDTH, 
                        (float)TILE_HEIGHT};
    Rectangle dest = {  (float)(pos_x), 
                        (float)(pos_y), 
                        (float)TILE_WIDTH, 
                        (float)TILE_HEIGHT};
    Vector2 origin = {0,0};
    DrawTexturePro (texture, source, dest, origin, 0.0f, WHITE);
}

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