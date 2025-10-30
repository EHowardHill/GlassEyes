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
#include "ge_sprites.h"

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
        ch_man.add_character(data->party[t], {-3.5, -t - 1}, t);
    }

    for (int t = 0; t < data->enemy_count; t++)
    {
        if (data->enemies[t] == 0)
            continue;
        ch_man.add_character(data->enemies[t], {2.5, -t - 1}, t + data->party_count);
    }

    for (auto &ch : ch_man.characters)
    {
        switch (ch->index)
        {
        case CHAR_JEREMY_BATTLE:
        {
            ch->current_animation = &jeremy_battle_init;
            break;
        }
        case CHAR_GINGER_BATTLE:
        {
            ch->current_animation = &ginger_battle_init;
            break;
        }
        case CHAR_VISKER_BATTLE:
        {
            ch->current_animation = &visker_battle_init;
            break;
        }
        case CHAR_CROKE_BATTLE:
        {
            ch->current_animation = &croke_battle_init;
            break;
        }
        }
    }

    data->bg_music->play(0.8);

    int stage = stage_talking_init;

    optional<mini_game> current_minigame;

    // Main game loop
    while (true)
    {
        bg_grid->set_position(bg_grid->x() - 1, bg_grid->y() - 1);

        switch (stage)
        {
        case stage_talking_init:
        {
            ch_man.load(data->talk_init);
            stage = stage_talking;
            break;
        }
        case stage_talking:
        {
            if (ch_man.db.has_value())
            {
                if (ch_man.db->is_ended())
                {
                    ch_man.db.reset();
                }
            }
            else
            {
                stage = stage_recv_init;
            }
            break;
        }
        case stage_recv_init:
        {
            current_minigame.emplace();
            //int result = data->minigames[0](true, current_minigame.value(), &ch_man);
            stage = stage_recv;
            break;
        }
        case stage_recv:
        {
            //int result = data->minigames[0](false, current_minigame.value(), &ch_man);
            break;
        }
        }

        ch_man.update(&current_map);
        current_map.update();
        bool dialogue_is_active = ch_man.db.has_value() && !ch_man.db.value().is_ended();
        v_sprite_ptr::update(!dialogue_is_active);

        if (current_map.collider_ptr.has_value())
        {
            current_map.collider_ptr->set_position(0, 0);
        }

        core::update();
    }
}