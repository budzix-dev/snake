#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "include/raylib.h"

const int WINDOW_SIZE = 800;

const int TILES_NUM = 16;
const int TILE_SIZE = WINDOW_SIZE / TILES_NUM;

const int FRAMES_BETWEEN_MOVEMENT = 6;

const auto COLOR_LIGHTGRAY = Color{220, 220, 220, 255};

const auto PLAYER_COLOR = GREEN;
const auto BG_COLOR1 = WHITE;
const auto BG_COLOR2 = COLOR_LIGHTGRAY;
const auto FOOD_COLOR = RED;

#endif