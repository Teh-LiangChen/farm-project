#include "gameRender.h"

void DrawTile (int pos_x, int pos_y, int texture_index_x, int texture_index_y, Texture2D texture);

void GameRender()
{
    BeginMode2D(camera);

    sTile tile;

    // render world
    for (int i=0; i < WORLD_WIDTH; i++)
    {
        for (int j=0; j< WORLD_HEIGHT; j++)
        {

            tile = world[i][j];

            //border tile
            if (i == 0 || i == WORLD_WIDTH - 1 || j == 0 || j == WORLD_HEIGHT - 1)
            {
                int texture_index_x = 1;
                int texture_index_y = 1;

                if (i == 0) texture_index_x = 0;
                if (i == WORLD_WIDTH - 1) texture_index_x = 2;

                if (j == 0) texture_index_y = 0;
                if (j == WORLD_HEIGHT - 1) texture_index_y = 2;

                DrawTile (tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, texture_index_x, texture_index_y, textures[TEXTURE_TILESET_GRASS]);
            }
            //center tile with random grass tile
            else
            {
                sTileset tileTexture = TILESET_TABLE[tile.type];
                DrawTile (tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, tileTexture.x, tileTexture.y, textures[tileTexture.source]);
            }
            
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
    
    //render crop
    for (int i = 0; i < cropList.counter; i++)
    {
        sCrop crop = cropList.array[i];
        int texture_index_x;
        int texture_index_y;

        switch (crop.type)
        {
            case CROP_PADDY:
                texture_index_y = 0;
                break;
            case CROP_TOMATO:
                texture_index_y = 1;
                break;
        }

        switch (crop.stage)
        {
            case CROP_STAGE_GERMINATE:
                texture_index_x = 1;
                break;
            case CROP_STAGE_GROWTH:
                texture_index_x = 2;
                break;
            case CROP_STAGE_FRUITING:
                texture_index_x = 3;
                break;
            case CROP_STAGE_HARVEST:
                texture_index_x = 4;
                break;
        }

        DrawTile(   cropList.array[i].base.x * TILE_WIDTH,
                    cropList.array[i].base.y * TILE_HEIGHT,
                    texture_index_x, 
                    texture_index_y, 
                    textures[TEXTURE_OBJECT_CROP]);
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

    // visualise actionbox
    DrawRectangleRec(player.actionbox, Fade(GRAY, 0.5f));
    
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

    //render inventory box
    Rectangle inventoryBox = (Rectangle) {156, 521, 515, 56};
    DrawRectangleRec(inventoryBox, Fade(LIGHTGRAY, 0.5f));
    DrawRectangleLinesEx(inventoryBox, 3.0f, Fade(DARKBROWN, 0.7f));
      

    //render item box
    for (int i = 0; i < 10; i++)
    {
        sInventory inventory = inventoryList[i];
        Rectangle itemBox = (Rectangle){160 + i * (48+3), 525, 48, 48};

        if(i == currentSelectedSlot)
        {
            DrawRectangleRec(itemBox, Fade(WHITE, 0.65f));
        }
        
        if(inventory.item != NULL)
        {            
            Rectangle source = {(float) inventory.item->texture_index_x * TILE_WIDTH, 
                                (float) inventory.item->texture_index_y * TILE_HEIGHT, 
                                (float)TILE_WIDTH, 
                                (float)TILE_HEIGHT};
            
            DrawTexturePro (textures[inventory.item->texture_asset], 
                            source, 
                            itemBox, 
                            (Vector2){0,0}, 
                            0.0f, 
                            WHITE);
        }
        
        DrawRectangleLinesEx(itemBox, 3.0f, Fade(BROWN, 0.7f));
    }
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