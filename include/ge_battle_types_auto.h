#ifndef GE_BATTLE_TYPES_AUTO_H
#define GE_BATTLE_TYPES_AUTO_H

#include "bn_regular_bg_item.h"

#include "ge_battle.h"
#include "ge_sprites_auto.h"
#include "ge_dialogue.h"
#include "ge_character_manager.h"

#include "bn_regular_bg_items_bg_battle_grid.h"

using namespace bn;

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
    .minigames = {true}};

int battle_fall(bool init, mini_game &mg, character_manager *ch_man);
int battle_fall_fast(bool init, mini_game &mg, character_manager *ch_man);
int battle_fall_wobble(bool init, mini_game &mg, character_manager *ch_man);
int battle_walls(bool init, mini_game &mg, character_manager *ch_man);
int battle_zigzag(bool init, mini_game &mg, character_manager *ch_man);
int battle_converge(bool init, mini_game &mg, character_manager *ch_man);
int battle_pulse(bool init, mini_game &mg, character_manager *ch_man);
int battle_crossfire(bool init, mini_game &mg, character_manager *ch_man);
int battle_breakout(bool init, mini_game &mg, character_manager *ch_man);
int battle_platformer(bool init, mini_game &mg, character_manager *ch_man);

#endif // GE_BATTLE_TYPES_AUTO_H