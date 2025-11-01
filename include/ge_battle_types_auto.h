// ge_battle_types_auto.h

#ifndef GE_BATTLE_TYPES_AUTO_H
#define GE_BATTLE_TYPES_AUTO_H

#include "bn_regular_bg_item.h"

#include "ge_battle.h"
#include "ge_sprites_auto.h"
#include "ge_dialogue.h"
#include "ge_character_manager.h"

#include "bn_regular_bg_items_bg_battle_grid.h"

using namespace bn;

int battle_fall_fast(bool init, mini_game *mg, character_manager *ch_man);
int battle_fall_wobble(bool init, mini_game *mg, character_manager *ch_man);
int battle_spiral(bool init, mini_game *mg, character_manager *ch_man);
int battle_walls(bool init, mini_game *mg, character_manager *ch_man);
int battle_zigzag(bool init, mini_game *mg, character_manager *ch_man);
int battle_crossfire(bool init, mini_game *mg, character_manager *ch_man);
int battle_breakout(bool init, mini_game *mg, character_manager *ch_man);

int attack_darts(bool init, mini_game *mg, character_manager *ch_man);

const battle_data foe01 = {
    .party = {CHAR_JEREMY_BATTLE, CHAR_GINGER_BATTLE, 0, 0},
    .enemies = {CHAR_VISKER_BATTLE, 0, 0, 0},
    .party_count = 2,
    .enemy_count = 1,
    .bg_item = &regular_bg_items::bg_battle_grid,
    .talk_init = &garbage_fight_01,
    .talk_progress_party = {&garbage_fight_02, &garbage_fight_03, nullptr},
    .talk_win = &garbage_fight_04,
    .talk_spare = {&garbage_spare, nullptr, nullptr},
    .battles = {&battle_fall_wobble, &battle_spiral, &battle_fall_fast, &battle_zigzag}, // List of pointers to battle functions to use in this fight
};

#endif // GE_BATTLE_TYPES_AUTO_H