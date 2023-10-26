/*
 * =====================================================================================
 *
 *       Filename:  player.c
 *
 *    Description:  the implementation of player.h 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 23:09:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include "player.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

const float PLAYER_SPEED = 0.5;
const float ROTATE_SPEED = DEG2RAD(5);

void updatePlayer(Player* player, float* deltaTime) {
    SDL_PumpEvents();
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    vec2i input = {
        (int)keys[SDL_SCANCODE_D] - (int)keys[SDL_SCANCODE_A],
        (int)keys[SDL_SCANCODE_W] - (int)keys[SDL_SCANCODE_S],
    };

    player->direction = rotateVec2f(
            player->direction, ROTATE_SPEED * input.x * (*deltaTime)
    );
    player->position.x += PLAYER_SPEED * input.y * player->direction.x;
    player->position.y += PLAYER_SPEED * input.y * player->direction.y;
}
