#pragma once

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGH = 600;
const unsigned int FRAMES_PER_SECOND = 60;
const unsigned int MIN_DELTA_TIME = 1000 / FRAMES_PER_SECOND;

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
