// main.cpp
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

// Face Sprites
#include "bn_sprite_items_db_ch_jeremy.h"
#include "bn_sprite_items_db_ch_vista.h"

#include "bn_sprite_items_spr_vista_01.h"

#include "bn_regular_bg_items_big_bg_forest_01.h"
#include "bn_regular_bg_items_bg_gameover.h"
#include "bn_regular_bg_items_scene_berlin01.h"

#include "main.h"
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

using namespace bn;

int navigate_map()
{
    map_manager current_map(global_data_ptr->entry_map);
    character_manager char_mgr;

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

    if (global_data_ptr->entry_map != &map_room01)
    {
        char_mgr.add_character(CHAR_JEREMY, global_data_ptr->entry_position, 0);
    }

    if (global_data_ptr->ginger_position.x != 0 && global_data_ptr->ginger_position.y != 0)
    {
        char_mgr.add_character(CHAR_GINGER, global_data_ptr->ginger_position, 0);
    }

    if (current_map.current_map == &map_forest_01 && global_data_ptr->action_iterations[CONVO_FOREST_01] > 1)
    {
        auto croke = char_mgr.find_by_index(CHAR_CROKE);
        croke->idle_animation = &croke_lay_down;
    }

    vector_2 spawn_pos = {
        global_data_ptr->entry_position.x * 32,
        global_data_ptr->entry_position.y * 32};
    int spawn_action = current_map.action(spawn_pos);

    if (spawn_action == NEW_BERLIN_SIGN)
    {
        if (current_map.bg_ptr.has_value())
        {
            current_map.bg_ptr.value().set_visible(true);
        }
    }

    int loop_value = 0;
    bool handle_frame = true;
    while (loop_value == CONTINUE && char_mgr.status == CONTINUE)
    {
        char_mgr.update(&current_map);
        loop_value = action_listener(&current_map, &char_mgr);
        current_map.update();
        bool dialogue_is_active = char_mgr.db.has_value() && !char_mgr.db.value().is_ended();
        v_sprite_ptr::update(!dialogue_is_active);

        if (current_map.bg_ptr.has_value())
        {
            current_map.bg_ptr.value().set_x(v_sprite_ptr::camera.x / -5);
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
                if (ch->index == ITEM_BUTTON)
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

    v_sprite_ptr::clear_all();
    return loop_value + char_mgr.status;
}

enum TYPEWRITER_SCENES
{
    TYPEWRITER_INTRO,
    TYPEWRITER_CREDITS,
    TYPEWRITER_INTRO2,
    TYPEWRITER_INTRO3,
    TYPEWRITER_TITLE,
    TYPEWRITER_GARBAGE,
    TYPEWRITER_MSG,
    TYPEWRITER_NEW_BERLIN,
    TYPEWRITER_GAME_OVER,
    TYPEWRITER_BUFFER,
    TYPEWRITER_YT_AD
};

enum TYPEWRITER_TYPE
{
    TYPE_TEXT,
    TYPE_IMG
};

#include "bn_regular_bg_items_scene_cabin01.h"
#include "bn_regular_bg_items_scene_title01.h"

void typewriter(int scene)
{
    optional<regular_bg_ptr> frame;
    text lines[3] = {{nullptr, {-71 + 16, 36}}, {nullptr, {-71 + 16, 36 + 16}}, {nullptr, {-71 + 16, 36 + 32}}};
    conversation *current_conversation;
    int index = 0;
    int ticker = 0;
    int type = TYPE_IMG;

    switch (scene)
    {
    case TYPEWRITER_INTRO:
    {
        frame = regular_bg_items::scene_cabin01.create_bg(0, 0);
        current_conversation = &intro_01;
        music_items::intro.play(1);
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_TITLE:
    {
        frame = regular_bg_items::scene_title01.create_bg(0, 0);
        sound_items::snd_intro.play();
        music::stop();
        break;
    }
    case TYPEWRITER_INTRO2:
    {
        music::stop();
        current_conversation = &intro_02;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_INTRO3:
    {
        current_conversation = &intro_03;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_GARBAGE:
    {
        music::stop();
        sound_items::sfx_drag.play();
        break;
    }
    case TYPEWRITER_MSG:
    {
        music_items::shop.play();
        current_conversation = &final_msg;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_NEW_BERLIN:
    {
        music::stop();
        frame = regular_bg_items::scene_berlin01.create_bg(0, 0);
        current_conversation = &new_berlin_sign;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_BUFFER:
    {
        break;
    }
    case TYPEWRITER_GAME_OVER:
    {
        frame = regular_bg_items::bg_gameover.create_bg(0, 0);
        music::stop();
        music_items::intro.play();

        while (!keypad::a_pressed())
        {
            core::update();
        }

        break;
    }
    case TYPEWRITER_YT_AD:
    {
        frame = regular_bg_items::scene_cabin01.create_bg(0, 0);
        current_conversation = &youtube_ad;
        type = TYPE_TEXT;
        break;
    }
    default:
    {
        type = TYPE_IMG;
        music::stop();
        break;
    }
    }

    if (type == TYPE_TEXT)
    {
        // Initialize with first dialogue
        lines[0] = {(*current_conversation)[index].raw_text[0], {-71 + 16, 36}};
        lines[1] = {(*current_conversation)[index].raw_text[1], {-71 + 16, 36 + 16}};
        lines[2] = {(*current_conversation)[index].raw_text[2], {-71 + 16, 36 + 32}};

        while ((*current_conversation)[index].action != ACT_END)
        {
            if (keypad::a_pressed())
            {
                index++;

                // Check if we've reached the end
                if ((*current_conversation)[index].action == ACT_END)
                    break;

                // Clear existing letters
                lines[0].letters.clear();
                lines[1].letters.clear();
                lines[2].letters.clear();

                // Reset indices for new text
                lines[0].index = 0;
                lines[1].index = 0;
                lines[2].index = 0;

                // Reinitialize with new text
                lines[0].init((*current_conversation)[index].raw_text[0]);
                lines[1].init((*current_conversation)[index].raw_text[1]);
                lines[2].init((*current_conversation)[index].raw_text[2]);
            }

            if (ticker % 5 == 0)
            {
                if (lines[0].is_ended())
                {
                    if (lines[1].is_ended())
                    {
                        lines[2].update(nullptr, true);
                    }
                    else
                    {
                        lines[1].update(nullptr, true);
                    }
                }
                else
                {
                    lines[0].update(nullptr, true);
                }
            }

            ticker++;
            core::update();
        }
    }
    else if (type == TYPE_IMG)
    {
        int wait = 96;
        if (frame.has_value())
        {
            wait = 192;
        }

        for (int t = 0; t < wait; t++)
        {
            core::update();
        }
    }
}

int main()
{
    core::init();

    int value = NEW_CHAPTER;

    // Set for debug
    global_data_ptr = new global_data();
    global_data_ptr->process_stage = AVALON; // BLACK_TO_LAB;

    // Test game
    global_data_ptr->items[OBJ_LIME] = true;
    global_data_ptr->foe = FOE_TEST;
    value = game_map();
    core::update();
    value = NEW_CHAPTER;

    // Test battle before game begins
    /*
    global_data_ptr->items[OBJ_LIME] = true;
    global_data_ptr->foe = FOE_TEST;
    value = battle_map();
    core::update();
    value = NEW_CHAPTER;
    */

    while (true)
    {
        switch (value)
        {
        case BATTLE:
        {
            value = battle_map();
            break;
        }
        case GAME:
        {
            value = game_map();
            break;
        }
        case NEW_CHAPTER:
        {
            BN_LOG("New Chapter: ", global_data_ptr->process_stage);
            switch (global_data_ptr->process_stage)
            {
            case TEST_MAP:
            {
                global_data_ptr->bg_track = &music_items::theme_visker;
                global_data_ptr->entry_map = &map_tavern_01;
                global_data_ptr->entry_position = {8, 10};
                global_data_ptr->ginger_position = {7, 10};
                break;
            }
            case CUTSCENE_01:
            {
                typewriter(TYPEWRITER_INTRO);
                global_data_ptr->entry_map = &map_room01;
                global_data_ptr->entry_position = {9, 2};
                break;
            }
            case CUTSCENE_TO_GARBAGE:
            {
                typewriter(TYPEWRITER_INTRO2);
                typewriter(TYPEWRITER_BUFFER);
                typewriter(TYPEWRITER_INTRO3);
                typewriter(TYPEWRITER_BUFFER);
                typewriter(TYPEWRITER_TITLE);
                typewriter(TYPEWRITER_BUFFER);

                global_data_ptr->entry_map = &map_garbage_01;
                global_data_ptr->entry_position = {9, 5};
                global_data_ptr->bg_track = &music_items::bg_garbage;
                break;
            }
            case GARBAGE_TO_BLACK:
            {
                global_data_ptr->hp[0] = 20;
                typewriter(TYPEWRITER_GARBAGE);
                global_data_ptr->entry_map = &map_lab_01;
                global_data_ptr->entry_position = {4, 5};
                global_data_ptr->bg_track = &music_items::bg_office;
                break;
            }
            case BLACK_TO_LAB:
            {
                global_data_ptr->entry_map = &map_lab_01;
                global_data_ptr->entry_position = {4, 5};
                global_data_ptr->bg_track = &music_items::bg_office;
                break;
            }
            case FOREST_01:
            {
                global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
                global_data_ptr->entry_map = &map_forest_01;
                global_data_ptr->entry_position = {6, 8};
                global_data_ptr->ginger_position = {5, 8};
                global_data_ptr->bg_track = &music_items::forest_01;
                break;
            }
            case NEW_BERLIN:
            {
                typewriter(TYPEWRITER_NEW_BERLIN);

                // Return
                global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
                global_data_ptr->entry_map = &map_forest_02;
                global_data_ptr->entry_position = {15, 5};
                global_data_ptr->ginger_position = {14, 5};
                global_data_ptr->bg_track = &music_items::forest_01;
                break;
            }
            case AVALON:
            {
                global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
                global_data_ptr->entry_map = &map_forest_03;
                global_data_ptr->entry_position = {15, 15};
                global_data_ptr->ginger_position = {14, 15};
                global_data_ptr->bg_track = &music_items::bg_avalon;
                break;
            }
            case FINAL_MSG:
            {
                typewriter(TYPEWRITER_BUFFER);
                typewriter(TYPEWRITER_MSG);
                while (true)
                {
                    core::update();
                }
                break;
            }
            case YOUTUBE_AD:
            {
                typewriter(TYPEWRITER_YT_AD);
                break;
            }
            default:
            {
                global_data_ptr->entry_map = &map_garbage_01;
                global_data_ptr->entry_position = {9, 5};
                global_data_ptr->bg_track = &music_items::bg_garbage;
                break;
            }
            }

            value = CONTINUE;
            break;
        }
        case GAME_OVER:
        {
            music::stop();
            music_items::intro.play(1);
            typewriter(TYPEWRITER_GAME_OVER);
            value = NEW_CHAPTER;
            global_data_ptr->hp[0] = 20;
            global_data_ptr->hp[1] = 20;
            global_data_ptr->hp[2] = 20;
            global_data_ptr->hp[3] = 20;
            for (int t = 0; t < ACTIONS_SIZE; t++)
            {
                global_data_ptr->action_iterations[t] = 0;
            }
            break;
        }
        default:
        {
            if (!music::playing())
            {
                global_data_ptr->bg_track->play(0.5);
            }

            value = navigate_map();
            break;
        }
        }

        if (global_data_ptr->hp[0] == 0 && global_data_ptr->entry_map != &map_garbage_05)
        {
            value = GAME_OVER;
        }

        core::update();
    }
}