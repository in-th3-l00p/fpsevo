//
// Created by intheloop on 25.10.2023.
//

#include "scenes.h"

// definitions for each scene
static DDATestScene* createDDATestScene(
    SDL_Window* window,
    SDL_Renderer* renderer
);
static void destroyDDATestScene(DDATestScene* scene);
void updateDDATestScene(Scene** scene_ptr, float deltaTime);

Scene* createScene(
    enum SceneType type,
    SDL_Window* window,
    SDL_Renderer* renderer
) {
    switch (type) {
        case DDA_TEST_SCENE:
            return (Scene *) createDDATestScene(window, renderer);
    }

    return NULL;
}

void updateScene(Scene** scene, float deltaTime) {
    switch ((*scene)->type) {
        case DDA_TEST_SCENE:
            updateDDATestScene(scene, deltaTime);
            break;
    }
}

void destroyScene(Scene* scene) {
    switch (scene->type) {
        case DDA_TEST_SCENE:
            destroyDDATestScene((DDATestScene*) scene);
            break;
    }
}


// dda test scene
DDATestScene* createDDATestScene(
        SDL_Window* window,
        SDL_Renderer* renderer
) {
    DDATestScene* scene = (DDATestScene*) malloc(sizeof(DDATestScene));
    scene->type = DDA_TEST_SCENE;
    scene->window = window;
    scene->renderer = renderer;

    scene->map = createTestMap();

    // hard codeee
    scene->player.position.x = 98;
    scene->player.position.y = 98;

    scene->player.direction.x = 1;
    scene->player.direction.y = 0;

    scene->player.radius = 15;

    scene->minimap.map = scene->map;
    scene->minimap.ratio = 1;
    scene->minimap.renderer = scene->renderer;
    scene->minimap.player = &scene->player;

    return scene;
}

void destroyDDATestScene(DDATestScene* scene) {
    destroyMap(scene->map);
    free(scene);
}

void updateDDATestScene(Scene** scene_ptr, float deltaTime) {
    DDATestScene* scene = (DDATestScene*)(*scene_ptr);

    // printing the minimap if key 'm' is pressed
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_M])
        renderMinimap(&scene->minimap);
    updatePlayer(&scene->player, &deltaTime);
}

