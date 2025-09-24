#ifndef GE_SPRITES_H
#define GE_SPRITES_H

#include "bn_core.h"
#include "bn_array.h"
#include "bn_sprites.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_optional.h"
#include "bn_vector.h"
#include "bn_keypad.h"
#include "bn_list.h"

// Do NOT include ge_character_manager.h or ge_maps.h here
#include "ge_structs.h"

using namespace bn;

struct character_manager;
struct map_manager;

bool within_bounds(bound me, bound you);

struct animation
{
    array<int, 64> frames = {0};
    int size = 0;
    int speed = 1;
    bool loop = true;
};

#define MAX_V_SPRITES 32

struct v_sprite_ptr
{
    static vector<v_sprite_ptr *, MAX_V_SPRITES> manager;
    static vector_2 camera;

    const sprite_item *sprite_item_ptr;
    optional<sprite_ptr> sprite_ptr_raw[2];
    bound bounds;
    int frame;

    v_sprite_ptr();
    v_sprite_ptr(const sprite_item *sprite_item_ptr_, vector_2 position = {0, 0}, int width = 32, int height = 32, int frame_ = 0);
    ~v_sprite_ptr();

    void move(vector_2 direction);
    bound real_position() const;
    void set_frame(int frame_);
    static void update(bool character_box_ended);

    static void clear_all()
    {
        for (auto *item : manager)
        {
            if (item->sprite_ptr_raw[0].has_value())
                item->sprite_ptr_raw[0].reset();
            if (item->sprite_ptr_raw[1].has_value())
                item->sprite_ptr_raw[1].reset();
        }
        manager.clear();
    }
};

enum character_list
{
    CHAR_DEFAULT,
    CHAR_VISTA,
    CHAR_JEREMY,
    CHAR_VISKER,
    CHAR_VISKER_WIFE,
    CHAR_GINGER,
    CHAR_CROKE,
    ITEM_BUTTON,
    ITEM_SPIKE,
    ITEM_X,
    CHAR_NOODLE,
    CHAR_GRANDMA,
    CHAR_WORMDUDE,
    CHAR_COURIER,
    CHAR_PRIMARY,
    CHAR_GOAT,
    CHAR_BEAR,
    CHAR_BIRB,
    CHAR_HONSE,
    CHAR_ROBIN,
    CHAR_SNEAKER,
    CHAR_TOLLBOOTH,
    CHAR_SPAMTON,
    CHAR_SIZE,
    CHAR_TYPEWRITER
};

enum facing
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

enum character_type
{
    CH_TYPE_PLAYER,
    CH_TYPE_NPC,
    CH_TYPE_ELEMENT,
    CH_TYPE_PUSHABLE,
    CH_TYPE_ITEM,
    CH_TYPE_DECORATION,
    CH_TYPE_DECORATION_ABOVE
};

struct character
{
    v_sprite_ptr v_sprite;
    const animation *current_animation;
    const animation *idle_animation;
    character_manager *ch_man;

    int id = 0;
    int index;
    int ticker = 0;
    int frame = 0;
    int face = DIR_DOWN;

    vector_2 move_to = {0, 0};
    bool is_follow = false;
    int follow_id = CHAR_JEREMY;

    bool is_sticky = false;
    bool is_pressed = false;

    int face_lock_timer = 0;
    int last_significant_x = 0;
    int last_significant_y = 0;
    int face_change_cooldown = 0;

    character(int index_, vector_2 start_, character_manager *manager);

    void update(map_manager *current_map, bool character_box_ended); // This is also fine now

    static void add(list<character, 32> *characters, int character_id, vector_2 location);

    int type()
    {
        switch (index)
        {
        case CHAR_VISTA:
            return CH_TYPE_PLAYER;
        case CHAR_JEREMY:
            return CH_TYPE_PLAYER;
        default:
            return CH_TYPE_NPC;
        }
    }

    static void add(list<character, 32> *characters, int character_id, vector_2 location, character_manager *manager);
};

#endif // GE_SPRITES_H