//
// Created by intheloop on 26.10.2023.
//

#include "label.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Label* createLabel(
        SDL_Renderer* renderer,
        Scene** scene_ptr,
        vec2f position,
        const char* text,
        int fontSize,
        SDL_Color color
) {
    Label* label = (Label*)malloc(sizeof(Label));
    label->scene_ptr = scene_ptr;
    label->position = position;
    size_t textSize = strlen(text);
    label->text = (char*)malloc(sizeof(char) * textSize);
    strncpy(label->text, text, textSize * sizeof(char));
    label->fontSize = fontSize;
    label->color = color;
    label->renderer = renderer;

    label->currentFont = TTF_OpenFont(DEFAULT_FONT, label->fontSize);
    if (label->currentFont == NULL) {
        fprintf(stderr, "Failed to open default font: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(label->currentFont, label->text, label->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to create text surface: %s\n", TTF_GetError());
        return NULL;
    }

    label->size.x = (float) textSurface->w;
    label->size.y = (float) textSurface->h;
    label->currentTexture = SDL_CreateTextureFromSurface(label->renderer, textSurface);
    if (label->currentTexture == NULL) {
        fprintf(stderr, "Failed to create texture: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_FreeSurface(textSurface);

    return label;
}

void destoryLabel(Label* label) {
    free(label->text);
    TTF_CloseFont(label->currentFont);
    SDL_DestroyTexture(label->currentTexture);
    free(label);
}

void renderLabel(Label* label) {
    SDL_FRect rectangle = {
        label->position.x, label->position.y,
        label->size.x, label->size.y
    };
    SDL_RenderCopyF(label->renderer, label->currentTexture, NULL, &rectangle);
}

void labelSetPosition(Label* label, vec2f position) {
    label->position = position;
}

void labelSetText(Label* label, const char* text) {
    size_t textSize = strlen(text);
    label->text = (char*)malloc(sizeof(char) * textSize);
    strncpy(label->text, text, textSize * sizeof(char));

    SDL_Surface* textSurface = TTF_RenderText_Solid(label->currentFont, label->text, label->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    label->size.x = (float) textSurface->w;
    label->size.y = (float) textSurface->h;
    label->currentTexture = SDL_CreateTextureFromSurface(label->renderer, textSurface);
    if (label->currentTexture == NULL)
        fprintf(stderr, "Failed to create texture: %s\n", TTF_GetError());

    SDL_FreeSurface(textSurface);
}

void labelSetFontSize(Label* label, int fontSize) {
    label->fontSize = fontSize;
    label->currentFont = TTF_OpenFont(DEFAULT_FONT, label->fontSize);
    if (label->currentFont == NULL) {
        fprintf(stderr, "Failed to open default font: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(label->currentFont, label->text, label->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    label->size.x = (float) textSurface->w;
    label->size.y = (float) textSurface->h;
    label->currentTexture = SDL_CreateTextureFromSurface(label->renderer, textSurface);
    if (label->currentTexture == NULL)
        fprintf(stderr, "Failed to create texture: %s\n", TTF_GetError());

    SDL_FreeSurface(textSurface);
}

void labelSetColor(Label* label, SDL_Color color) {
    label->color = color;
    SDL_Surface* textSurface = TTF_RenderText_Solid(label->currentFont, label->text, label->color);
    if (textSurface == NULL) {
        fprintf(stderr, "Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    label->size.x = (float) textSurface->w;
    label->size.y = (float) textSurface->h;
    label->currentTexture = SDL_CreateTextureFromSurface(label->renderer, textSurface);
    if (label->currentTexture == NULL)
        fprintf(stderr, "Failed to create texture: %s\n", TTF_GetError());

    SDL_FreeSurface(textSurface);
}
