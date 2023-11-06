/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  the definitions for storing a game map 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 21:52:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: intheloop
 *   Organization: steagu enterprise
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "player.h"

typedef struct {
    uint32_t width, height, wallSize;
    uint8_t **map;
} Map;

Map *createTestMap();

void destroyMap(Map *map);

// holds the data needed for showing a minimap of the game
typedef struct {
    Map *map;
    Player *player;
    double ratio;

    SDL_Renderer *renderer;
} Minimap;

void renderMap(Minimap *minimap);

void renderMinimap(Minimap *minimap);

void renderDDARays(Minimap *minimap);

void renderPlayer(Minimap *minimap);