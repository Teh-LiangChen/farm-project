#include "gameRender.h"

void DrawTile (int pos_x, int pos_y, int texture_index_x, int texture_index_y, Texture2D texture);

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
            if (i == 0 || i == WORLD_WIDTH - 1 || j == 0 || j == WORLD_HEIGHT - 1)
            {
                texture_index_x = 1;
                texture_index_y = 1;

                if (i == 0) texture_index_x = 0;
                if (i == WORLD_WIDTH - 1) texture_index_x = 2;

                if (j == 0) texture_index_y = 0;
                if (j == WORLD_HEIGHT - 1) texture_index_y = 2;
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

    
    // render hill
    // TO-DO make into function if keep use
    for (int i = 5; i < 8; i++)
    {
        for (int j = 5; j < 8; j++)
        {
            DrawTile (  world[i][j].x * TILE_WIDTH, 
                        world[i][j].y * TILE_HEIGHT, 
                        i-5, j-5, textures[TEXTURE_TILESET_HILL]);
        }
    }
    

    // render hill hit box
    // DrawRectangle ( world[5][5].x * TILE_WIDTH, 
    //                 world[5][5].y * TILE_HEIGHT, 
    //                 TILE_WIDTH,
    //                 TILE_HEIGHT,
    //                 Fade(GRAY, 0.5f));
    
    // render player hitbox                
    // DrawRectangle(player.hitbox.x, player.hitbox.y, TILE_WIDTH/2, TILE_HEIGHT, Fade(GRAY, 0.5f));


    // render player
    //DrawTile(camera.target.x, camera.target.y, 1, 1,textures[TEXTURE_SPRITE_BASIC]);
    // 1x1 animation destination
    Rectangle dest = {  (int)player.base.x,
                        (int)player.base.y,
                        TILE_WIDTH,
                        TILE_HEIGHT};

    // 1x3 animation destination
    Rectangle dest2 = {  (int)player.base.x,
                        (int)player.base.y - 16,
                        TILE_WIDTH,
                        TILE_HEIGHT*3};
    
    Vector2 origin = {0,0};
    
    sAnimation* currentAnimation = &player.animations[player.currentAnimation];

    if (player.currentAnimation == ANIMATION_DIG_FRONT)
    {
        DrawSpriteAnimationPro(currentAnimation, textures[TEXTURE_SPRITE_ACTION], dest2, origin, 0.0f, WHITE);
    }
    else
    {
        DrawSpriteAnimationPro(currentAnimation, textures[TEXTURE_SPRITE_BASIC], dest, origin, 0.0f, WHITE);
    }
    
    EndMode2D();

    //display player coordinate for checking
    DrawRectangle(5, 5, 500, 50, Fade(GRAY, 0.5f));
    DrawText(TextFormat("Coor: (%2.2f, %2.2f)", camera.target.x, camera.target.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("Tile: (%d, %d)", player.base.x / TILE_WIDTH, player.base.y /TILE_HEIGHT), 10, 35, 20, BLACK);
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