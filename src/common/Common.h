#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

const int GAME_SCREEN_WIDTH = 1200;
const int GAME_SCREEN_HEIGHT = 800;
const std::string GAME_TITLE = "Sky Bird Game";
const int GAME_FPS = 60;
const int GAME_TICKS_PER_FRAME = 1000 / GAME_FPS;
const int numberOfMenuItem = 2;

struct Input {
    bool left,
         right,
         up,
         down;
};

enum CHARACTER_STATE {
    FLYING = 0,
    ATTACKING,
    DEAD,
};

enum SOUND_EFFECT {
    ATTACK = 0,
};

enum BULLET_TYPE {
    PLAYER_BULLET = 0,
    ENEMY_BULLET,
};

enum ENEMY_TYPE {
    ALIEN = 0,
    EYE = 1,
    DARK = 2,
    HORN = 3,
};

#endif // COMMON_H
