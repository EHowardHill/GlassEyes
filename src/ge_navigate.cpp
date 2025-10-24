// ge_navigate.cpp

#include "bn_log.h"
#include "bn_core.h"
#include "bn_regular_bg_item.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_list.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"
#include "bn_sound_items.h"
#include "bn_math.h"
#include "bn_blending.h"

// Face Sprites
#include "bn_sprite_items_db_ch_jeremy.h"
#include "bn_sprite_items_db_ch_vista.h"

#include "bn_sprite_items_spr_vista_01.h"

#include "main.h"
#include "main_auto.h"
#include "ge_globals.h"
#include "ge_sprites.h"
#include "ge_text.h"
#include "ge_maps.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_actions.h"
#include "ge_battle.h"
#include "ge_games.h"
#include "ge_map_data.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"

using namespace bn;

int navigate_map()
{
    map_manager current_map(global_data_ptr->entry_map);
    character_manager char_mgr;

    switch (global_data_ptr->process_stage)
    {
    case BLACK_TO_TRAIN:
    case FLAYITHRO_AWAKE:
    {
        global_data_ptr->costumes[CHAR_JEREMY] = COSTUME_JEREMY_FANCY;
        global_data_ptr->costumes[CHAR_GINGER] = COSTUME_GINGER_FANCY;
        global_data_ptr->costumes[CHAR_SEBELLUS] = COSTUME_SEBELLUS_FANCY;
        break;
    }
    }

    for (int y = 0; y < current_map.current_map->size.y.integer(); y++)
    {
        for (int x = 0; x < current_map.current_map->size.x.integer(); x++)
        {
            int tile = x + (y * current_map.current_map->size.x.integer());

            if (current_map.current_map->characters[tile] != 0)
            {
                int id = current_map.current_map->metadata[tile];
                int index = current_map.current_map->characters[tile] - 1;

                char_mgr.add_character(index, {x, y}, id);
            }
        }
    }

    if (global_data_ptr->jeremy_position.x != 0 && global_data_ptr->jeremy_position.y != 0)
    {
        char_mgr.add_character(CHAR_JEREMY, global_data_ptr->jeremy_position, 0);
    }

    if (global_data_ptr->ginger_position.x != 0 && global_data_ptr->ginger_position.y != 0)
    {
        char_mgr.add_character(CHAR_GINGER, global_data_ptr->ginger_position, 0);
    }

    if (global_data_ptr->sebellus_position.x != 0 && global_data_ptr->sebellus_position.y != 0)
    {
        char_mgr.add_character(CHAR_SEBELLUS, global_data_ptr->sebellus_position, 0);
    }

    if (current_map.current_map == &map_forest_01 && global_data_ptr->action_iterations[CONVO_FOREST_01] > 1)
    {
        auto croke = char_mgr.find_by_index(CHAR_CROKE);
        croke->idle_animation = &croke_lay_down;
    }
    else if (current_map.current_map == &map_dark_06)
    {
        auto btn = char_mgr.find_by_id(6);
        btn->is_pressed = true;
        btn->idle_animation = &elem_button_down;
    }

    vector_2 spawn_pos = {
        global_data_ptr->jeremy_position.x * 32,
        global_data_ptr->jeremy_position.y * 32};
    int spawn_action = current_map.action(spawn_pos);

    // Auto-loaded conversations
    if (global_data_ptr->entry_map == &map_room01)
    {
        char_mgr.load(&test_convo);
    }
    else if (global_data_ptr->entry_map == &map_cutscene_channel)
    {
        char_mgr.load(&chat_mcwebb_02);
        v_sprite_ptr::camera.x = global_data_ptr->entry_map->raw_size.x / 2;
        v_sprite_ptr::camera.y = global_data_ptr->entry_map->raw_size.y / 4;
        global_data_ptr->shake = true;
    }

    if (current_map.bg_ptr.has_value())
    {
        current_map.bg_ptr.value().set_visible(true);
    }

    // SETUP FADE IN
    blending::set_transparency_alpha(0);

    if (current_map.collider_ptr.has_value())
        current_map.collider_ptr->set_blending_enabled(true);

    if (current_map.bg_ptr.has_value())
        current_map.bg_ptr->set_blending_enabled(true);

    for (auto &spr : v_sprite_ptr::manager)
    {
        if (spr->sprite_ptr_raw[0].has_value())
            spr->sprite_ptr_raw[0]->set_blending_enabled(true);

        if (spr->sprite_ptr_raw[1].has_value())
            spr->sprite_ptr_raw[1]->set_blending_enabled(true);
    }

    // Main loop
    int loop_value = 0;
    bool handle_frame = true;
    int fade_ticker = 0;

    while (loop_value == CONTINUE && char_mgr.status == CONTINUE)
    {
        // FADE IN using ticker
        if (fade_ticker < 48)
        {
            auto new_alpha = blending::transparency_alpha() + 0.05;

            if (new_alpha < 1)
            {
                blending::set_transparency_alpha(new_alpha);
            }
            else
            {
                blending::set_transparency_alpha(1);
            }

            fade_ticker++;

            // Disable blending after fade-in completes
            if (fade_ticker >= 48)
            {
                if (current_map.collider_ptr.has_value())
                    current_map.collider_ptr->set_blending_enabled(false);

                if (current_map.bg_ptr.has_value())
                    current_map.bg_ptr->set_blending_enabled(false);

                for (auto &spr : v_sprite_ptr::manager)
                {
                    if (spr->sprite_ptr_raw[0].has_value())
                        spr->sprite_ptr_raw[0]->set_blending_enabled(false);

                    if (spr->sprite_ptr_raw[1].has_value())
                        spr->sprite_ptr_raw[1]->set_blending_enabled(false);
                }
            }
        }

        char_mgr.update(&current_map);
        loop_value = action_listener(&current_map, &char_mgr);
        current_map.update();
        bool dialogue_is_active = char_mgr.db.has_value() && !char_mgr.db.value().is_ended();
        v_sprite_ptr::update(!dialogue_is_active);

        if (current_map.bg_ptr.has_value())
        {
            if (global_data_ptr->entry_map == &map_cutscene_channel ||
                global_data_ptr->entry_map == &map_train_room_01 ||
                global_data_ptr->entry_map == &map_train_room_02 ||
                global_data_ptr->entry_map == &map_train_room_03 ||
                global_data_ptr->entry_map == &map_train_room_04)
            {
                current_map.bg_ptr.value().set_x(current_map.bg_ptr.value().x() - 5);
            }
            else
            {
                current_map.bg_ptr.value().set_x(v_sprite_ptr::camera.x / -5);
            }
        }

        // Handle map-specific puzzle logic
        if (current_map.current_map == &map_cave_02)
        {
            auto button_01 = char_mgr.find_by_id(1);

            if (button_01 != nullptr)
            {
                if (button_01->is_pressed)
                {
                    for (auto &ch : char_mgr.characters)
                    {
                        if (ch->id == 2)
                        {
                            ch->is_pressed = false;
                            ch->idle_animation = &elem_spike_down;
                        }
                    }
                }
            }
        }

        else if (current_map.current_map == &map_cave_04)
        {
            bool correct_up = true;
            bool incorrect_down = true;

            for (auto &ch : char_mgr.characters)
            {
                if (ch->index == CHAR_BUTTON)
                {
                    if (ch->id == 1 && !ch->is_pressed)
                    {
                        correct_up = false;
                    }
                    else if (ch->id == 2 && ch->is_pressed)
                    {
                        incorrect_down = false;
                    }
                }
            }

            if (correct_up && incorrect_down)
            {
                auto spike = char_mgr.find_by_id(3);
                spike->is_pressed = false;
                spike->idle_animation = &elem_spike_down;
            }
        }

        else if (current_map.current_map == &map_cave_05)
        {
            auto spk1 = char_mgr.find_by_id(1);
            auto spk2 = char_mgr.find_by_id(2);
            auto btn3 = char_mgr.find_by_id(3);
            if (btn3 != nullptr && btn3->is_pressed)
            {
                spk1->is_pressed = false;
                spk1->idle_animation = &elem_spike_down;

                spk2->is_pressed = false;
                spk2->idle_animation = &elem_spike_down;
            }
        }

        else if (current_map.current_map == &map_dark_01)
        {
            //
            auto spk1 = char_mgr.find_by_id(1);
            auto btn2 = char_mgr.find_by_id(2);
            if (btn2 != nullptr && btn2->is_pressed)
            {
                spk1->is_pressed = false;
                spk1->idle_animation = &elem_spike_down;
            }

            //
            auto spk3 = char_mgr.find_by_id(3);
            auto btn4 = char_mgr.find_by_id(4);
            if (btn4 != nullptr && btn4->is_pressed)
            {
                spk3->is_pressed = false;
                spk3->idle_animation = &elem_spike_down;
            }
        }

        else if (current_map.current_map == &map_dark_02)
        {
            // Handle the standard spike/button pairs (IDs 1-12)
            for (int i = 1; i <= 11; i += 2)
            {
                auto spike = char_mgr.find_by_id(i);
                auto button = char_mgr.find_by_id(i + 1);

                if (spike != nullptr && button != nullptr)
                {
                    if (button->is_pressed)
                    {
                        spike->is_pressed = true;
                        spike->idle_animation = &elem_spike_up;
                    }
                    else
                    {
                        spike->is_pressed = false;
                        spike->idle_animation = &elem_spike_down;
                    }
                }
            }

            // Handle the special case pair with inverted logic (IDs 13-14)
            auto spk13 = char_mgr.find_by_id(13);
            auto btn14 = char_mgr.find_by_id(14);
            if (spk13 != nullptr && btn14 != nullptr)
            {
                if (btn14->is_pressed)
                {
                    spk13->is_pressed = false;
                    spk13->idle_animation = &elem_spike_down;
                }
                else
                {
                    spk13->is_pressed = true;
                    spk13->idle_animation = &elem_spike_up;
                }
            }
        }

        else if (current_map.current_map == &map_dark_06)
        {
            // Iterate through button IDs 1 through 9
            for (int t = 1; t <= 9; t++)
            {
                auto btn = char_mgr.find_by_id(t);
                // The corresponding spike ID is the button ID + 9
                auto spk = char_mgr.find_by_id(t + 9);

                // Ensure the spike exists before trying to change it
                if (spk != nullptr)
                {
                    if (btn != nullptr && btn->is_pressed)
                    {
                        // Spike is UP if its button is pressed
                        spk->is_pressed = true;
                        spk->idle_animation = &elem_spike_up;
                    }
                    else
                    {
                        // Spike is DOWN if its button is not pressed (or doesn't exist)
                        spk->is_pressed = false;
                        spk->idle_animation = &elem_spike_down;
                    }
                }
            }
        }

        // If fallen off-map
        if (char_mgr.player_ptr->is_falling && !char_mgr.player_ptr->v_sprite.sprite_ptr_raw[0].has_value())
        {
            loop_value = NEW_MAP;
            char_mgr.status = NEW_MAP;
        }

        // Frame handling
        if (handle_frame)
        {
            handle_frame = false;
        }
        else
        {
            core::update();
        }
    }

    // FADE OUT BACKGROUNDS AND SPRITES

    blending::set_transparency_alpha(1);

    if (current_map.collider_ptr.has_value())
        current_map.collider_ptr->set_blending_enabled(true);

    if (current_map.bg_ptr.has_value())
        current_map.bg_ptr->set_blending_enabled(true);

    for (auto &spr : v_sprite_ptr::manager)
    {
        if (spr->sprite_ptr_raw[0].has_value())
            spr->sprite_ptr_raw[0]->set_blending_enabled(true);

        if (spr->sprite_ptr_raw[1].has_value())
            spr->sprite_ptr_raw[1]->set_blending_enabled(true);
    }

    for (int t = 0; t < 48; t++)
    {
        auto new_alpha = blending::transparency_alpha() - 0.05;

        if (new_alpha > 0)
        {
            blending::set_transparency_alpha(new_alpha);
        }
        else
        {
            blending::set_transparency_alpha(0);
        }

        core::update();
    }

    // RETURN

    v_sprite_ptr::clear_all();
    return (loop_value != CONTINUE) ? loop_value : char_mgr.status;
}