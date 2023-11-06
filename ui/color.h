//
// Created by intheloop on 26.10.2023.
//

#ifndef FPSEVO_COLOR_H
#define FPSEVO_COLOR_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// hard coded valuess
static const SDL_Color RED = {255, 0, 0, 255};
static const SDL_Color BLUE = {0, 255, 0, 255};
static const SDL_Color GREEN = {0, 0, 255, 255};
static const SDL_Color WHITE = {255, 255, 255, 255};
static const SDL_Color BLACK = {0, 0, 0, 255};

static const SDL_Color DARK_RED = {200, 0, 0, 255};
static const SDL_Color DARK_BLUE = {0, 200, 0, 255};
static const SDL_Color DARK_GREEN = {0, 0, 200, 255};
static const SDL_Color DARK_WHITE = {200, 200, 200, 255};

static SDL_Color getColor(uint8_t texture, bool isShaded) {
    switch (texture) {
        case 0:
            return isShaded ? DARK_WHITE : WHITE;
        case 1:
            return isShaded ? DARK_RED : RED;
        case 2:
            return isShaded ? DARK_GREEN : GREEN;
        case 3:
            return isShaded ? DARK_BLUE : BLUE;
        case 4:
            return BLACK;
        default:
            return BLACK;
    }
}

#endif //FPSEVO_COLOR_H
