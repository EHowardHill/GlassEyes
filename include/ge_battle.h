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

struct mini_game
{
    optional<sprite_ptr> eye;
    vector<sprite_ptr, 24> bits;
    fixed_t<4> vars[64] = {0};

    void reset()
    {
        eye.reset();
        bits.clear();

        for (int i = 0; i < 64; ++i)
        {
            vars[i] = 0;
        }
    }
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

    int (*battles[8])(bool, mini_game *, character_manager *) = {nullptr};
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
    stage_talking_init,
    stage_talking,
    stage_recv_init,
    stage_recv,
    stage_menu_init,
    stage_menu,
    stage_action_init,
    stage_action,
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

struct battle_map
{
    optional<regular_bg_ptr> bg_grid;
    character_manager ch_man;
    int stage = 0;
    const battle_data *data;

    int play();

    battle_map(const battle_data *data);
};

enum battle_responses
{
    resp_attack,
    resp_damage,
    resp_act
};

struct battle_menu
{
    optional<text> title;
    vector<text, 5> options;
    optional<sprite_ptr> character_img;
    optional<sprite_ptr> selector;
    int index = 0;
    int character_index = 0;

    battle_menu(int character_index_);
    int update();

    void reset()
    {
        title.reset();
        character_img.reset();
        selector.reset();
        options.clear();

        index = 0;
        character_index = 0;
    }
};

#endif // GE_BATTLE_H