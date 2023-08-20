#pragma once
#include <SDL2/SDL_image.h>

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGH = 600;
const unsigned int FRAMES_PER_SECOND = 60;
const unsigned int MIN_DELTA_TIME = 1000 / FRAMES_PER_SECOND;

enum CollisionType
{
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISTION,
    ENEME_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

enum LayerType
{
    TILEMAP_LAYER = 0,
    VEGETATION_LAYER,
    ENEMY_LAYER,
    PLAYER_LAYER,
    PROJECTILE_LAYER,
    UI_LAYER = 5,
};

const unsigned int NUM_LAYERS = 6;

static const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
static const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
static const SDL_Color RED_COLOR = {255, 0, 0, 255};
static const SDL_Color BLUE_COLOR = {0, 0, 255, 255};
