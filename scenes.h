//
// Created by intheloop on 25.10.2023.
//

#ifndef FPSEVO_SCENES_H
#define FPSEVO_SCENES_H

/**
 * defining the scene system
 * basically a scene is going to be a simple structure holding
 * other data and an update function that is going to run in the game loop
 */

#include <SDL2/SDL.h>

#include "dda/map.h"
#include "dda/player.h"

enum SceneType {
    DDA_TEST_SCENE // DDATestScene
};

// base structure (used for "polymorphism")
typedef struct Scene {
    enum SceneType type; // somewhat of a scene id (used for destroying)
    SDL_Window* window;
    SDL_Renderer* renderer;
} Scene;

Scene* createScene(
    enum SceneType type,
    SDL_Window* window,
    SDL_Renderer* renderer
);
void updateScene(Scene** scene, float deltaTime);
void destroyScene(Scene* scene);

typedef struct {
    enum SceneType type;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Map* map;
    Player player;
    Minimap minimap;
} DDATestScene;

#endif //FPSEVO_SCENES_H
