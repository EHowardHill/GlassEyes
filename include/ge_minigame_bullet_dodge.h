// ge_minigame_bullet_dodge.h
#ifndef GE_MINIGAME_BULLET_DODGE_H
#define GE_MINIGAME_BULLET_DODGE_H

#include "ge_minigame.h"
#include "ge_bullet.h"

// Custom data specific to bullet dodge
struct bullet_dodge_data {
    vector<bullet, 16> bullets;
    int moveset_index = 0;
    int speed = 100;
};

void bullet_dodge_init(minigame_state* mg);
void bullet_dodge_update(minigame_state* mg);
void bullet_dodge_cleanup(minigame_state* mg);

#endif