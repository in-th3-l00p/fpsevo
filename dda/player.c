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
#include "../config.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

void updatePlayer(Player *player, float *deltaTime, uint8_t **map,
                  uint32_t wallSize) {
    SDL_PumpEvents();

    const uint8_t *keys = SDL_GetKeyboardState(NULL);
    vec2d input = {
            (int) keys[SDL_SCANCODE_A] - (int) keys[SDL_SCANCODE_D],
            (int) keys[SDL_SCANCODE_W] - (int) keys[SDL_SCANCODE_S],
    };

    player->direction = rotateVec2f(
            player->direction, ROTATE_SPEED * input.x * (*deltaTime)
    );

    vec2f newPosition = {
            player->position.x + PLAYER_SPEED * input.y * player->direction.x * (*deltaTime),
            player->position.y + PLAYER_SPEED * input.y * player->direction.y * (*deltaTime)
    };

    if (map[(int) (newPosition.y / wallSize)][(int) (newPosition.x / wallSize)] == 0) {
        player->position = newPosition;
    } else {
        newPosition.x = player->position.x + PLAYER_SPEED * input.y * player->direction.x * (*deltaTime);
        newPosition.y = player->position.y;
        if (map[(int) (newPosition.y / wallSize)][(int) (newPosition.x / wallSize)] == 0) {
            player->position = newPosition;
        }
        newPosition.x = player->position.x;
        newPosition.y = player->position.y + PLAYER_SPEED * input.y * player->direction.y * (*deltaTime);
        if (map[(int) (newPosition.y / wallSize)][(int) (newPosition.x / wallSize)] == 0) {
            player->position = newPosition;
        }
    }
}