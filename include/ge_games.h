#ifndef GE_GAMES_H
#define GE_GAMES_H

#include "bn_core.h"
#include "bn_log.h"
#include "bn_regular_bg_item.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_list.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"
#include "bn_sound_items.h"
#include "bn_math.h"

#include "bn_camera_ptr.h"
#include "bn_regular_bg_items_bg_battle_grid.h"
#include "bn_regular_bg_items_bg_battle_box.h"
#include "bn_regular_bg_items_bg_battle_action.h"
#include "bn_sprite_items_spr_jeremy_01.h"
#include "bn_sprite_items_spr_ginger_01.h"
#include "bn_sprite_items_spr_visker_01.h"
#include "bn_sprite_items_hearts.h"
#include "bn_sprite_items_battle_icons.h"
#include "bn_sprite_items_battle_chars.h"

#include "bn_sprite_items_jeremy_battle.h"
#include "bn_sprite_items_ginger_battle.h"
#include "bn_sprite_items_visker_battle.h"
#include "bn_sprite_items_croke_battle.h"

#include "ge_globals.h"
#include "ge_text.h"
#include "ge_battle.h"

using namespace bn;

int game_map(int game_type);

enum game_stage
{
    G_TALKING,
    G_PLAYING,
    G_FINISH
};

enum game_result
{
    G_FIRST,
    G_UP,
    G_DOWN,
    G_WIN,
    G_LOSE,
    G_SIZE
};

enum dart_state
{
    DART_INTRO,
    DART_AIMING,
    DART_POWER,
    DART_THROWING,
    DART_RESULT,
    DART_ENEMY_TURN,
    DART_GAME_OVER
};

struct dart_game
{
    // Game mechanics
    int state = DART_INTRO;
    int current_round = 0;
    int max_rounds = 12;
    bool player_turn = true;

    // Scoring
    int player_score = 0;
    int enemy_score = 0;
    int round_scores[6] = {0}; // 3 for player, 3 for enemy

    // Aiming system
    fixed aim_x = 0;
    fixed aim_y = 0;
    fixed aim_speed = 1;
    fixed aim_wobble = 0;
    int wobble_timer = 0;

    // Power meter
    fixed power = 0;
    fixed power_direction = 1;
    fixed max_power = 100;

    // Dart physics
    fixed dart_x = 0;
    fixed dart_y = 60;
    fixed dart_target_x = 0;
    fixed dart_target_y = 0;
    fixed dart_speed = 0;
    int throw_timer = 0;

    fixed random_jitter_x = 0;
    fixed random_jitter_y = 0;
    fixed wobbled_aim_x = 0;
    fixed wobbled_aim_y = 0;
    fixed dart_start_x = 0;  // Starting position for dart throw
    fixed dart_start_y = 0;

    // Visual elements
    optional<sprite_ptr> dartboard;
    optional<sprite_ptr> dart;
    optional<sprite_ptr> crosshair;
    optional<sprite_ptr> power_meter[5]; // 5 segments for power bar

    // Text displays - initialized with positions
    text player_score_text{nullptr, {-100, 70}};
    text enemy_score_text{nullptr, {60, 70}};
    text round_text{nullptr, {-20, -70}};

    // Animation timers
    int state_timer = 0;
    int result_timer = 0;

    // Enemy AI difficulty
    fixed enemy_accuracy = 0.7; // 0.0 to 1.0, higher = better
};

struct game_state
{
    const sprite_item *enemy_sprite_item = nullptr;
    int party_size = 1;
    int current_actor = -1;
    int stage = G_TALKING;
    int result = G_FIRST;
    int y_delta = 0;
    dart_game darts;

    // Reusable dialogue state
    conversation *active_conv = nullptr;
    int dlg_index = 0;
    int dlg_size = 0;
    int dlg_ticker = 0;
    text dlg_lines[3] = {{nullptr, {-40, 32}}, {nullptr, {-40, 48}}, {nullptr, {-40, 64}}};
    optional<sprite_ptr> portrait;
    optional<regular_bg_ptr> bg_ptr;

    // Combat entities
    optional<sprite_ptr> character_sprites[MAX_PARTY_SIZE];
    int character_states[MAX_PARTY_SIZE] = {0, 0, 0, 0};
    int character_tickers[MAX_PARTY_SIZE] = {0, 0, 0, 0};

    optional<sprite_ptr> enemy_sprite;
    int enemy_state = 0;
    int enemy_ticker = 0;

    // Menu state
    int menu_index = 0;

    bn::random rng;
};

#endif