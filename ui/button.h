//
// Created by intheloop on 27.10.2023.
//

#ifndef FPSEVO_BUTTON_H
#define FPSEVO_BUTTON_H

#include <SDL2/SDL.h>
#include "label.h"
#include "../scenes.h"

typedef struct Button {
    Scene** scene_ptr;
    Label* label;
    vec2f padding;
    SDL_Color backgroundColor;

    void (*onClick)(struct Button* button);
} Button;

Button* createButton(
        SDL_Renderer* renderer,
        Scene** scene_ptr,
        vec2f position,
        const char* text,
        int fontSize,
        vec2f padding,
        SDL_Color color,
        SDL_Color backgroundColor,

);

#endif //FPSEVO_BUTTON_H
