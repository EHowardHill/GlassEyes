#ifndef GE_BATTLE_TYPES_AUTO_H
#define GE_BATTLE_TYPES_AUTO_H

#include "bn_regular_bg_item.h"

#include "ge_battle.h"
#include "ge_sprites_auto.h"
#include "ge_dialogue.h"

#include "bn_regular_bg_items_bg_battle_grid.h"

using namespace bn;

const battle_data foe01 = {
    .party = {CHAR_JEREMY, CHAR_GINGER, 0, 0},
    .enemies = {CHAR_VISKER, 0, 0, 0},
    .party_count = 2,
    .enemy_count = 1,
    .bg_item = &regular_bg_items::bg_battle_grid,
    .talk_init = &garbage_fight_01,
    .talk_progress_party = {&garbage_fight_02, &garbage_fight_03, nullptr},
    .talk_win = &garbage_fight_04,
    .talk_spare = {&garbage_spare, nullptr, nullptr},
    .minigames = {true}};

#endif // GE_BATTLE_TYPES_AUTO_H