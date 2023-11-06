//
// Created by intheloop on 26.10.2023.
//

#ifndef FPSEVO_LABEL_H
#define FPSEVO_LABEL_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "fonts.h"
#include "../utils/mymath.h"

typedef struct {
    vec2f position;
    char *text;
    int fontSize;
    SDL_Color color;

    vec2f size;
    SDL_Renderer *renderer;
    TTF_Font *currentFont;
    SDL_Texture *currentTexture; // graphics accelerated
} Label;

Label *createLabel(
        SDL_Renderer *renderer,
        vec2f position,
        const char *text,
        int fontSize,
        SDL_Color color
);

void destoryLabel(Label *label);

void renderLabel(Label *label);

void labelSetPosition(Label *label, vec2f position);

void labelSetText(Label *label, const char *text);

void labelSetFontSize(Label *label, int fontSize);

void labelSetColor(Label *label, SDL_Color color);

#endif //FPSEVO_LABEL_H
