//
// Created by alexdavid on 01.11.2023.
//

#ifndef FPSEVO_CONFIG_H
#define FPSEVO_CONFIG_H

#include "utils/mymath.h"

#define WINDOW_TITLE "Raycaster"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define TEST_MAP_WIDTH 8
#define TEST_MAP_HEIGHT 8
#define TEST_MAP_WALLSIZE 16
#define TEXTURE_SIZE 32

#define MINIMAP_RATIO 4

#define PLAYER_SPEED 0.05
#define ROTATE_SPEED DEG2RAD(0.10)

#define PLAYER_START_X 100
#define PLAYER_START_Y 100
#define PLAYER_DIRECTION_X 1
#define PLAYER_DIRECTION_Y 0
#define PLAYER_RADIUS 5
#define PLAYER_FOV DEG2RAD(85)

#endif //FPSEVO_CONFIG_H
