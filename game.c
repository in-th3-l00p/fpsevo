/*
 * =====================================================================================
 *
 *       Filename:  game.c
 *
 *    Description:  implementation of game.h
 *
 *        Version:  1.0
 *        Created:  19.10.2023 21:44:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop,
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include "game.h"
#include "config.h"
#include <stdlib.h>

Game *createGame() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Error initializing SDL2: %s", SDL_GetError());
        return NULL;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Failed to initialize SDL_TTF: %s\n", TTF_GetError());
        return NULL;
    }

    Game *game = (Game *) malloc(sizeof(Game));
    game->window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
    );
    if (game->window == NULL) {
        fprintf(stderr, "Error creating window: %s", SDL_GetError());
        return NULL;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (game->renderer == NULL) {
        fprintf(stderr, "Error creating renderer: %s", SDL_GetError());
        return NULL;
    }

    game->running = true;
    game->currentScene = createScene(DDA_TEST_SCENE, game->window, game->renderer);

    return game;
}

void runGame(Game *game) {
    SDL_Event event; // event holding structure

    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;
    float deltaTime = 0;

    while (game->running) {
        while (SDL_PollEvent(&event))
            switch (event.type) {
                case SDL_QUIT:
                    game->running = false;
                    break;
            }

        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (float) ((now - last) * 1000 / (float) SDL_GetPerformanceFrequency());

        // clear
        SDL_SetRenderDrawColor(game->renderer, 69, 69, 69, 255);
        SDL_RenderClear(game->renderer);

        updateScene(&game->currentScene, deltaTime);

        // update
        SDL_RenderPresent(game->renderer);
    }
}

void destroyGame(Game *game) {
    destroyScene(game->currentScene);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
}

