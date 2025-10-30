#ifndef GE_BATTLE_TYPES_AUTO_H
#define GE_BATTLE_TYPES_AUTO_H

#include "bn_regular_bg_item.h"

#include "ge_sprites_auto.h"
#include "ge_dialogue.h"
#include "ge_character_manager.h"

#include "bn_regular_bg_items_bg_battle_grid.h"

using namespace bn;

struct mini_game
{
    optional<sprite_ptr> eye;
    vector<sprite_ptr, 48> bits;
    fixed_t<4> vars[48 * 4];
};

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

struct battle_data
{
    int party[4] = {0, 0, 0, 0};
    int enemies[4] = {0, 0, 0, 0};
    int party_count = 0;
    int enemy_count = 0;

    const music_item *bg_music = &music_items::boss;
    const regular_bg_item *bg_item = &regular_bg_items::bg_battle_grid;
    conversation *talk_init = nullptr;
    conversation *talk_progress_party[3] = {nullptr, nullptr, nullptr};
    conversation *talk_progress_enemy[3] = {nullptr, nullptr, nullptr};
    conversation *talk_win = nullptr;
    conversation *talk_lose = nullptr;
    conversation *talk_spare[3] = {nullptr, nullptr, nullptr};
    int minigames[16] = {0};
};

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
    .minigames = {0}};

#endif // GE_BATTLE_TYPES_AUTO_H