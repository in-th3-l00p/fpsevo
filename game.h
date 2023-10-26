/*
 * =====================================================================================
 *
 *       Filename:  game.h
 *
 *    Description: the entry point of the game engine 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 21:41:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop,
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "scenes.h"

// fundamental game structure
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running; 

    Scene* currentScene;
} Game;

Game* createGame();
void runGame(Game* game);
void destroyGame(Game* game);
