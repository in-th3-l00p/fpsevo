/*
 * =====================================================================================
 *
 *       Filename:  player.h
 *
 *    Description:  definition for the player structure 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 22:49:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#ifndef FPSEVO_PLAYER_H_
#define FPSEVO_PLAYER_H_

#include "../utils/mymath.h"
#include <stdint.h>
#include <SDL2/SDL_render.h>

typedef struct {
    vec2f position, direction;
    float radius;
    float fov;
} Player;

// to be run in game loop
void
updatePlayer(Player *player, float *deltaTime, uint8_t **map, uint32_t wallSize);

#endif