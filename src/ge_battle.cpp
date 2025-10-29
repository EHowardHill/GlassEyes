// ge_battle.cpp

#include "bn_core.h"
#include "bn_log.h"
#include "bn_keypad.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_random.h"

#include "bn_regular_bg_items_bg_battle_grid.h"
#include "bn_regular_bg_items_bg_dialogue_box.h"
#include "bn_sprite_items_hearts.h"
#include "bn_sprite_items_battle_icons.h"
#include "bn_sprite_items_battle_chars.h"
#include "bn_sprite_items_battle_squares.h"

#include "ge_battle_types_auto.h"

#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_battle.h"

using namespace bn;

const map default_battle_map = {
    {8, 4},
    {256, 256},
    {0}, // metadata
    {0}, // collisions
    {0}, // actions
    {0}, // characters
    &regular_bg_items::bg_battle_box};

// Main battle function
battle_map::battle_map(const battle_data *data_) : data(data_)
{
    music::stop();
    sound_items::snd_fight_start.play();
    bg_grid = data->bg_item->create_bg(0, 0);
}

int battle_map::play()
{
    map_manager current_map(&default_battle_map);

    for (int t = 0; t < data->party_count; t++)
    {
        if (data->party[t] == 0)
            continue;
        ch_man.add_character(data->party[t], {0.5, t + 4}, t);
    }

    for (int t = 0; t < data->enemy_count; t++)
    {
        if (data->enemies[t] == 0)
            continue;
        ch_man.add_character(data->enemies[t], {6.5, t + 4}, t + data->party_count);
    }

    if (data->talk_init != nullptr)
    {
        ch_man.load(data->talk_init);
    }

    // Main game loop
    while (true)
    {
        bg_grid->set_position(bg_grid->x() - 1, bg_grid->y() - 1);

        if (ch_man.db.has_value())
        {
            ch_man.db->update();

            if (keypad::a_pressed())
            {
                ch_man.db->handle_a_button_press(&ch_man);
            }

            if (ch_man.db->is_ended())
            {
                ch_man.db.reset();
            }
        }

        auto j = ch_man.find_by_index(CHAR_JEREMY);
        if (j != nullptr)
        {
            BN_LOG("X: ", j->v_sprite.real_position().position.x, " Y: ", j->v_sprite.real_position().position.y);
        }

        ch_man.update(&current_map);
        current_map.update();
        bool dialogue_is_active = ch_man.db.has_value() && !ch_man.db.value().is_ended();
        v_sprite_ptr::update(!dialogue_is_active);
        core::update();
    }
}