#include "gameStartup.h"

void GameStartup()
{
    InitAudioDevice();

    Image image = LoadImage("assets/sprout-lands-sprites-basic-pack/Tilesets/Grass.png");
    textures[TEXTURE_TILESET_GRASS] = LoadTextureFromImage(image);
    UnloadImage(image);

    image = LoadImage("assets/sprout-lands-sprites-basic-pack/Characters/basic-character-spritesheet.png");
    textures[TEXTURE_SPRITE_BASIC] = LoadTextureFromImage(image);
    UnloadImage(image);

    image = LoadImage("assets/sprout-lands-sprites-basic-pack/Tilesets/Hills.png");
    textures[TEXTURE_TILESET_HILL] = LoadTextureFromImage(image);
    UnloadImage(image); 

    for (int i=0; i < WORLD_WIDTH; i++)
    {
        for (int j=0; j< WORLD_HEIGHT; j++)
        {
            world[i][j] = (sTile)
            {
                .x = i,
                .y = j,
                .type = GetRandomValue(GRASS_PLAIN, GRASS_MAX),
                .isSolid = false,
            };
        }
    }

    //starting position of player
    player = (sSprite)
    {
        .base = {.x = 3 * TILE_WIDTH,
                 .y = 3 * TILE_HEIGHT},
        .currentAnimation = ANIMATION_IDLE_DOWN,
        .hitbox = (Rectangle){3 * TILE_WIDTH+4, 3 * TILE_HEIGHT, TILE_WIDTH/2, TILE_HEIGHT},
    };

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

    player.animations[ANIMATION_IDLE_DOWN].isPlaying = true;

    camera.target = (Vector2) {player.base.x,player.base.y};
    camera.offset = (Vector2) { (float) screenWidth / 2, (float) screenHeight /2};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
}
