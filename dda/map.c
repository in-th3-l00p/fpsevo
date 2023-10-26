/*
 * =====================================================================================
 *
 *       Filename:  map.c
 *
 *    Description:  implementation of map.h 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 21:57:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop,
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include "map.h"
#include <stdlib.h>

#define TEST_MAP_WIDTH 8
#define TEST_MAP_HEIGHT 8
#define TEST_MAP_WALLSIZE 64

static uint8_t testMap[TEST_MAP_WIDTH][TEST_MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1}, 
    {1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1}, 
};

Map* createTestMap() {
    Map* map = (Map*)malloc(sizeof(Map));
    map->width = TEST_MAP_WIDTH;
    map->height = TEST_MAP_HEIGHT;
    map->wallSize = TEST_MAP_WALLSIZE;

    map->map = (uint8_t**)malloc(sizeof(uint8_t*) * map->height);
    for (int i = 0; i < map->height; i++)
        map->map[i] = (uint8_t*)malloc(sizeof(uint8_t) * map->width);
    for (int i = 0; i < map->height; i++)
        for (int j = 0; j < map->width; j++)
            map->map[i][j] = testMap[i][j];
    return map;
}


void destroyMap(Map* map) {
    for (int i = 0; i < map->height; i++)
        free(map->map[i]);
    free(map->map);
    free(map);
}

void renderMinimap(Minimap* minimap) {
    uint32_t minimapWallSize = (uint32_t)(
            minimap->map->wallSize * minimap->ratio
    );
    for (int y = 0; y < minimap->map->height; y++)  
        for (int x = 0; x < minimap->map->width; x++) {
            if (minimap->map->map[y][x])
                SDL_SetRenderDrawColor(minimap->renderer, 255, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(minimap->renderer, 0, 0, 0, 255);
            SDL_Rect sdlRect = { 
                x * minimapWallSize, y * minimapWallSize,
                minimapWallSize, minimapWallSize
            };
            SDL_RenderFillRect(minimap->renderer, &sdlRect);
        }

    vec2i minimapPlayerPosition = { 
        (int)(minimap->player->position.x * minimap->ratio),
        (int)(minimap->player->position.y * minimap->ratio)
    };
    filledCircleRGBA(
            minimap->renderer, 
            minimapPlayerPosition.x, 
            minimapPlayerPosition.y, 
            (int)(minimap->player->radius * minimap->ratio),
            255, 0, 0, 255
    );

    const int DIRECTION_MULTIPLIER = 30;
    vec2i minimapPlayerDirection = {
        minimapPlayerPosition.x + minimap->player->direction.x * minimap->ratio * DIRECTION_MULTIPLIER, 
        minimapPlayerPosition.y + minimap->player->direction.y * minimap->ratio * DIRECTION_MULTIPLIER
    };
    printf(
            "%d %d\n%d %d\n\n", 
            minimapPlayerPosition.x, 
            minimapPlayerPosition.y, 
            minimapPlayerDirection.x, 
            minimapPlayerDirection.y
            );
    lineRGBA(
            minimap->renderer,
            minimapPlayerPosition.x, minimapPlayerPosition.y,
            minimapPlayerDirection.x, minimapPlayerDirection.y,
            255, 0, 0, 255
    );
}
