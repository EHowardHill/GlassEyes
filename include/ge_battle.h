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
#include "bn_sprite_items_spr_jeremy.h"
#include "bn_sprite_items_spr_ginger.h"
#include "bn_sprite_items_spr_visker.h"
#include "bn_sprite_items_hearts.h"
#include "bn_sprite_items_battle_icons.h"
#include "bn_sprite_items_battle_chars.h"

#include "bn_sprite_items_jeremy_battle.h"
#include "bn_sprite_items_ginger_battle.h"
#include "bn_sprite_items_visker_battle.h"
#include "bn_sprite_items_croke_battle.h"

#include "ge_character_manager.h"

#include "ge_globals.h"
#include "ge_text.h"

using namespace bn;

constexpr int MAX_PARTY_SIZE = 4;

enum dialogue_type
{
    DIALOGUE_INIT,
    DIALOGUE_PROGESS_PARTY,
    DIALOGUE_PROGRESS_ENEMY,
    DIALOGUE_WIN,
    DIALOGUE_LOSE,
    DIALOGUE_SPARE,
    DIALOGUE_TYPE_SIZE
};

enum minigame_types
{
    MINIGAME_BULLET_FALL,
    MINIGAME_SIZE
};

struct battle_data
{
    int party[4] = {0, 0, 0, 0};
    int enemies[4] = {0, 0, 0, 0};
    int party_count = 0;
    int enemy_count = 0;

    const regular_bg_item *bg_item = &regular_bg_items::bg_battle_grid;
    conversation *talk_init = nullptr;
    conversation *talk_progress_party[3] = {nullptr, nullptr, nullptr};
    conversation *talk_progress_enemy[3] = {nullptr, nullptr, nullptr};
    conversation *talk_win = nullptr;
    conversation *talk_lose = nullptr;
    conversation *talk_spare[3] = {nullptr, nullptr, nullptr};
    bool minigames[MINIGAME_SIZE] = {0};
};

constexpr int JEREMY_IDLE_START = 10;
constexpr int JEREMY_HURT_START = 11;
constexpr int JEREMY_HURT_END = 14;
constexpr int JEREMY_ATK_START = 15;
constexpr int JEREMY_ATK_END = 21;

constexpr int GINGER_IDLE_START = 8;
constexpr int GINGER_IDLE_END = 11;
constexpr int GINGER_HURT_START = 12;
constexpr int GINGER_HURT_END = 14;
constexpr int GINGER_ATK_START = 15;
constexpr int GINGER_ATK_END = 17;

constexpr int ACTION_NONE = -1;
constexpr int ACTION_ATTACK = 0;
constexpr int ACTION_ITEM = 1;
constexpr int ACTION_SPARE = 2;

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
    RESULT_ACT,
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

struct status_bar_items
{
    optional<sprite_ptr> icon_label; // Changed from optional<text> to optional<sprite_ptr> assuming it's a visual element
    int index = 0;

    status_bar_items();

    void update_label();
    void update();
};

struct status_bar_menu
{
    optional<sprite_ptr> battle_icons[5];
    optional<sprite_ptr> icon_label; // Changed from optional<text> to optional<sprite_ptr> assuming it's a visual element
    int index = 0;

    status_bar_menu();

    void update_label();
    void update();
};

struct status_bar
{
    optional<sprite_ptr> char_img;
    optional<sprite_ptr> name; // Changed from optional<text>
    optional<sprite_ptr> hp;   // Changed from optional<text>
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

struct battle_map
{
    optional<regular_bg_ptr> bg_grid;
    character_manager ch_man;
    int stage = 0;
    const battle_data * data;

    int play();

    battle_map(const battle_data * data);
};

#endif // GE_BATTLE_H