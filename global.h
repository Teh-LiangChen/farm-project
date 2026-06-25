#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "raylib.h"
#include "raymath.h"

#include "animation.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define screenWidth 800
#define screenHeight 600

typedef enum 
{
    // MAP AND TERRAIN
    TEXTURE_TILESET_GRASS = 0,
    TEXTURE_TILESET_HILL,

    // SPRITE
    TEXTURE_SPRITE_BASIC,

    //OBJECTS
    MAX_TEXTURES
} texture_asset;

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
    bool isSolid;
} sTile;

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
    Rectangle hitbox;
} sSprite;

extern Rectangle hitbox[];
extern Rectangle hillhitbox;
extern Texture2D textures[MAX_TEXTURES];
extern sTile world[WORLD_WIDTH][WORLD_HEIGHT];
extern Camera2D camera;
extern sSprite player;

#endif