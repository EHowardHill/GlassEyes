// ge_battle.h

#ifndef GE_BATTLE_H
#define GE_BATTLE_H

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
#include "ge_bullet.h"

using namespace bn;

static constexpr int MAX_PARTY_SIZE = 4;

static constexpr int JEREMY_IDLE_START = 10;
static constexpr int JEREMY_HURT_START = 11;
static constexpr int JEREMY_HURT_END = 14;
static constexpr int JEREMY_ATK_START = 15;
static constexpr int JEREMY_ATK_END = 21;

static constexpr int GINGER_IDLE_START = 8;
static constexpr int GINGER_IDLE_END = 11;
static constexpr int GINGER_HURT_START = 12;
static constexpr int GINGER_HURT_END = 14;
static constexpr int GINGER_ATK_START = 15;
static constexpr int GINGER_ATK_END = 17;

static constexpr int ACTION_NONE = -1;
static constexpr int ACTION_ATTACK = 0;
static constexpr int ACTION_ITEM = 1;
static constexpr int ACTION_SPARE = 2;

enum BATTLE_STAGE
{
    stage_heart_moving,
    stage_main,
    stage_talking,
    stage_recv,
    stage_status,
    stage_attack,
    stage_talking_then_attack,
    stage_item_dialogue,
    stage_execute_attacks,
    stage_act
};

enum BULLET_STYLE
{
    bullet_fall
};

enum STATUS_BAR_BUTTONS
{
    STATUS_BAR_NONE,
    STATUS_BAR_ATTACK,
    STATUS_BAR_ACT,
    STATUS_BAR_ITEM,
    STATUS_BAR_SPARE,
    STATUS_BAR_DEFEND,
    STATUS_BAR_SIZE
};

enum BATTLE_RESULT
{
    RESULT_FIRST,
    RESULT_UP,
    RESULT_DOWN,
    RESULT_SPARE,
    RESULT_ACT, // Add new result type for ACT actions
    RESULT_LAST_WIN,
    RESULT_LAST_LOSE,
    RESULT_SIZE
};

// Structure to hold action data
struct battle_action
{
    const char *name;
    conversation *convo;
    bool used;

    battle_action(const char *n, conversation *c) : name(n), convo(c), used(false) {}
};

struct attack_unit_dissolve
{
    optional<sprite_ptr> spr;
};

struct attack_bar
{
    optional<sprite_ptr> header;
    optional<sprite_ptr> recv_bar;
    optional<sprite_ptr> unit;
    vector<attack_unit_dissolve, 5> dissolves;
    bool is_ended = false;

    attack_bar(int y_delta, int index);
    void update();
};

struct attack
{
    vector<attack_bar, 3> attack_bars;
    bool is_ended = false;

    attack();
    void update();
};

struct status_bar_items
{
    optional<text> icon_label;
    int index = 0;

    status_bar_items();

    void update_label();
    void update();
};

struct status_bar_menu
{
    optional<sprite_ptr> battle_icons[5];
    optional<text> icon_label;
    int index = 0;

    status_bar_menu();

    void update_label();
    void update();
};

struct status_bar
{
    optional<sprite_ptr> char_img;
    optional<text> name;
    optional<text> hp;
    regular_bg_ptr action_bg = regular_bg_items::bg_battle_action.create_bg(0, 0);
    int actor_index;

    static int current_party_size;
    static int current_enemy_size;
    static int selected_menu;
    static vector<battle_action, 4> available_actions;

    optional<status_bar_menu> sb_menu;
    optional<status_bar_items> sb_items;

    status_bar(int actor_index_ = 0);
    void update();
};

struct recv
{
    int ticker = 0;
    vector<bullet, bullet_count> bullets;
    int bullet_style = bullet_fall;
    regular_bg_ptr bg_action = regular_bg_items::bg_battle_box.create_bg(0, 0);
    vector_2 eye_pos = {0, 0};
    unsigned int random_value = 32;
    sprite_ptr heart = sprite_items::hearts.create_sprite(
        0,
        0,
        1);

    recv();
    void update(int &g_defense_stacks);
    void spawn_bullets();
};

vector_2 moveTowards(vector_2 from, vector_2 towards, fixed_t<4> speed);
int battle_map();

struct battle_state
{
    const sprite_item *enemy_sprite_item;
    int party_size = 1;
    int current_actor = -1;
    int selected_menu = STATUS_BAR_NONE;
    int stage = stage_talking;
    int result = RESULT_FIRST;
    int y_delta = 0;
    int moveset = 2;
    int selected_moveset = 0;
    int speed = 1;

    items_box item_menu;
    conversation *pending_item_conv = nullptr;
    int used_item_index = -1;

    // Action tracking
    int character_actions[MAX_PARTY_SIZE] = {ACTION_NONE, ACTION_NONE, ACTION_NONE, ACTION_NONE};
    int choosing_for = 0; // Which character is currently choosing
    bool has_acted[MAX_PARTY_SIZE];

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

    // Attack bars - now arrays for multiple characters
    optional<sprite_ptr> attack_headers[MAX_PARTY_SIZE];
    optional<sprite_ptr> attack_recvs[MAX_PARTY_SIZE];
    optional<sprite_ptr> attack_units[MAX_PARTY_SIZE];
    int attack_damages[MAX_PARTY_SIZE] = {0, 0, 0, 0};
    bool attack_pressed[MAX_PARTY_SIZE] = {false, false, false, false};
    int num_attackers = 0;

    // Individual attack timing parameters
    fixed attack_speeds[MAX_PARTY_SIZE] = {0, 0, 0, 0};
    int attack_launch_delays[MAX_PARTY_SIZE] = {0, 0, 0, 0};
    int attack_launch_timers[MAX_PARTY_SIZE] = {0, 0, 0, 0};
    bool attack_launched[MAX_PARTY_SIZE] = {false, false, false, false};

    // Recv state
    optional<sprite_ptr> heart;
    vector_2 heart_pos = {0, 0};
    int recv_ticker = 0;
    vector<bullet, 16> bullets;

    // UI elements
    optional<sprite_ptr> char_img;
    optional<sprite_ptr> battle_icons[3];
    optional<text> labels[5];

    // Special Croke battle tracking
    int croke_conv_index = 0; // Which conversation (0=croke_02, 1=croke_03, 2=croke_04)
    int croke_anim_frame = 0; // Current animation frame for Croke
};

#endif