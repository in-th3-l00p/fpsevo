/*
 * =====================================================================================
 *
 *       Filename:  map.c
 *
 *    Description:  implementation of map.h 
 *
 *        Version:  1.0
 *        Created:  19.10.2023 21:57:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  intheloop,
 *   Organization:  steagu enterprise
 *
 * =====================================================================================
 */

#include "map.h"
#include "../config.h"
#include "data.h"
#include "../ui/color.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

Map *createTestMap() {
    Map *map = (Map *) malloc(sizeof(Map));
    map->width = TEST_MAP_WIDTH;
    map->height = TEST_MAP_HEIGHT;
    map->wallSize = TEST_MAP_WALLSIZE;

    map->map = (uint8_t **) malloc(sizeof(uint8_t *) * map->height);
    for (int i = 0; i < map->height; i++)
        map->map[i] = (uint8_t *) malloc(sizeof(uint8_t) * map->width);
    for (int i = 0; i < map->height; i++)
        for (int j = 0; j < map->width; j++)
            map->map[i][j] = testMap[i][j];
    return map;
}


void destroyMap(Map *map) {
    for (int i = 0; i < map->height; i++)
        free(map->map[i]);
    free(map->map);
    free(map);
}

void renderMinimap(Minimap *minimap) {
    uint32_t minimapWallSize = (uint32_t) (
            minimap->map->wallSize * minimap->ratio
    );
    for (int y = 0; y < minimap->map->height; y++)
        for (int x = 0; x < minimap->map->width; x++) {
            if (minimap->map->map[y][x])
                SDL_SetRenderDrawColor(minimap->renderer, 255, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(minimap->renderer, 0, 0, 0, 255);
            SDL_Rect sdlRect = {
                    x * minimapWallSize, y * minimapWallSize,
                    minimapWallSize - 2, minimapWallSize - 2
            };
            SDL_RenderFillRect(minimap->renderer, &sdlRect);
        }

    renderPlayer(minimap);
}

void renderPlayer(Minimap *minimap) {
    filledCircleRGBA(
            minimap->renderer,
            (int) (minimap->player->position.x * minimap->ratio),
            (int) (minimap->player->position.y * minimap->ratio),
            (int) (minimap->player->radius * minimap->ratio),
            255, 0, 0, 255
    );

    SDL_SetRenderDrawColor(minimap->renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(
            minimap->renderer,
            (int) (minimap->player->position.x * minimap->ratio),
            (int) (minimap->player->position.y * minimap->ratio),
            (int) ((minimap->player->position.x + minimap->player->direction.x * 2 * minimap->player->radius) *
                   minimap->ratio),
            (int) ((minimap->player->position.y + minimap->player->direction.y * 2 * minimap->player->radius) *
                   minimap->ratio)
    );
}

void renderMap(Minimap *minimap) {
    int raysCount = RAD2DEG(minimap->player->fov) + 1;

    for (int i = 0; i < raysCount; i++) {
        vec2f rayDirection = rotateVec2f(
                minimap->player->direction,
                minimap->player->fov - DEG2RAD(i) - minimap->player->fov / 2
        );

        vec2f rayUnitStepSize = {
                rayDirection.x == 0 ? 1e30 : fabs(1 / rayDirection.x),
                rayDirection.y == 0 ? 1e30 : fabs(1 / rayDirection.y)
        };

        vec2d mapCell = {
                (int) minimap->player->position.x / minimap->map->wallSize,
                (int) minimap->player->position.y / minimap->map->wallSize
        };
        vec2f rayLength = {
                rayDirection.x < 0 ?
                (minimap->player->position.x - mapCell.x * minimap->map->wallSize) * rayUnitStepSize.x
                                   :
                ((mapCell.x + 1) * minimap->map->wallSize - minimap->player->position.x) *
                rayUnitStepSize.x,
                rayDirection.y < 0 ? (minimap->player->position.y - mapCell.y * minimap->map->wallSize) *
                                     rayUnitStepSize.y
                                   :
                ((mapCell.y + 1) * minimap->map->wallSize - minimap->player->position.y) *
                rayUnitStepSize.y
        };
        vec2d step = {
                rayDirection.x < 0 ? -1 : 1,
                rayDirection.y < 0 ? -1 : 1
        };

        bool hit = false;
        float distance;
        uint8_t wallType;

        while (!hit) {
            if (rayLength.x < rayLength.y) {
                mapCell.x += step.x;
                distance = rayLength.x;
                rayLength.x += rayUnitStepSize.x * minimap->map->wallSize;
            } else {
                mapCell.y += step.y;
                distance = rayLength.y;
                rayLength.y += rayUnitStepSize.y * minimap->map->wallSize;
            }

            if (mapCell.x >= minimap->map->width || mapCell.y >= minimap->map->height
                || mapCell.x < 0 || mapCell.y < 0)
                break;
            if (minimap->map->map[mapCell.y][mapCell.x]) {
                hit = true;
                wallType = minimap->map->map[mapCell.y][mapCell.x];
            }
        }

        rayLength.x = rayLength.x - rayUnitStepSize.x * minimap->map->wallSize;
        rayLength.y = rayLength.y - rayUnitStepSize.y * minimap->map->wallSize;

        bool isShaded = rayLength.x > rayLength.y;

        const uint8_t *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_M]) {
            vec2f rayEnd = {
                    minimap->player->position.x + rayDirection.x * distance,
                    minimap->player->position.y + rayDirection.y * distance
            };

            if (isShaded)
                SDL_SetRenderDrawColor(minimap->renderer, 255, 0, 0, 255);
            else
                SDL_SetRenderDrawColor(minimap->renderer, 200, 0, 0, 255);

            SDL_RenderDrawLine(
                    minimap->renderer,
                    (int) (minimap->player->position.x * minimap->ratio),
                    (int) (minimap->player->position.y * minimap->ratio),
                    (int) (rayEnd.x * minimap->ratio),
                    (int) (rayEnd.y * minimap->ratio)
            );
        } else {
            distance = distance * cos(minimap->player->fov / 2 - DEG2RAD(i));

            float wallHeight = (int) minimap->map->wallSize * WINDOW_HEIGHT / distance;
            int pitch = 0;

            int start = -wallHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
            if (start < 0) start = 0;
            int end = wallHeight / 2 + WINDOW_HEIGHT / 2 + pitch;
            if (end > WINDOW_HEIGHT) end = WINDOW_HEIGHT - 1;

            uint8_t(*texture)[TEXTURE_SIZE];
            switch (wallType) {
                case 1:
                    texture = checkBoardTexture;
                    break;
                case 2:
                    texture = wallTexture;
                    break;
                default:
                    texture = checkBoardTexture;
                    break;
            }

            float wallX;
            if (isShaded)
                wallX = minimap->player->position.y + distance * rayDirection.y;
            else wallX = minimap->player->position.x + distance * rayDirection.x;
            wallX -= floor(wallX);

            int textureX = (int) (wallX * (float) TEXTURE_SIZE / 2);
            if ((!isShaded && rayDirection.x > 0) || (isShaded && rayDirection.y < 0))
                textureX = TEXTURE_SIZE - textureX - 1;

            float textureStep = (float) TEXTURE_SIZE / wallHeight;
            float texturePosition = (start - pitch - WINDOW_HEIGHT / 2 + wallHeight / 2) * textureStep;

            for (int y = start; y < end; y++) {
                int textureY = ((int) texturePosition) & (TEXTURE_SIZE - 1);
                texturePosition += textureStep;

                SDL_Color color = getColor(texture[textureY][textureX], isShaded);
                SDL_SetRenderDrawColor(minimap->renderer, color.r, color.g, color.b, color.a);
                SDL_Rect sdlRect = {
                        minimap->map->wallSize * i, y,
                        minimap->map->wallSize, 1
                };
                SDL_RenderFillRect(minimap->renderer, &sdlRect);
            }
        }
    }
}