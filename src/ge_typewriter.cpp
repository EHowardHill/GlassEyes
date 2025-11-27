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
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"

#include "bn_regular_bg_items_scene_cabin01.h"
#include "bn_regular_bg_items_scene_title01.h"
#include "bn_regular_bg_items_big_bg_forest_01.h"
#include "bn_regular_bg_items_bg_gameover.h"
#include "bn_regular_bg_items_scene_berlin01.h"

using namespace bn;

#define x_center (-(temp.size() * 8) / 2) + 8

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
        current_conversation = &new_berlin_sign;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_DOG_AND_PONY:
    {
        music_items::z02_the_champ.play();
        current_conversation = &dog_and_pony;
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
    case TYPEWRITER_CCUTSCENE_01:
    {
        music::stop();
        music_items::cave_01.play();

        current_conversation = &cutscene_01;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_CCUTSCENE_02:
    {
        music::stop();
        music_items::cave_01.play();

        current_conversation = &cutscene_02;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_CCUTSCENE_03:
    {
        current_conversation = &cutscene_03;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_CCUTSCENE_07:
    {
        current_conversation = &cutscene_07;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_ENDING_01_CUTSCENE_01:
    {
        current_conversation = &final_01;
        type = TYPE_TEXT;
        break;
    }
    case TYPEWRITER_ENDING_02_CUTSCENE_01:
    {
        current_conversation = &final_02;
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
        // Initialize with first dialogue including color and centered position
        const dialogue_line &first_line = (*current_conversation)[index];

        // Calculate centered X positions using bn::string to avoid strlen optimization
        int x0 = 0, x1 = 0, x2 = 0;
        if (first_line.raw_text[0] != nullptr)
        {
            string<128> temp(first_line.raw_text[0]);
            x0 = x_center;
        }
        if (first_line.raw_text[1] != nullptr)
        {
            string<128> temp(first_line.raw_text[1]);
            x1 = x_center;
        }
        if (first_line.raw_text[2] != nullptr)
        {
            string<128> temp(first_line.raw_text[2]);
            x2 = x_center;
        }

        lines[0] = {first_line.raw_text[0], {x0, 34}};
        lines[1] = {first_line.raw_text[1], {x1, 34 + 16}};
        lines[2] = {first_line.raw_text[2], {x2, 34 + 32}};

        // Set color for each line
        lines[0].color = first_line.color;
        lines[1].color = first_line.color;
        lines[2].color = first_line.color;

        while ((*current_conversation)[index].action != ACT_END)
        {
            if ((*current_conversation)[index].action == ACT_HARD_RESET)
            {
                core::reset();
            }

            const dialogue_line &current_line = (*current_conversation)[index];

            if (current_line.bg_item != nullptr)
            {
                frame.reset();
                frame = current_line.bg_item->create_bg(0, 0);
            }

            // Check if all lines are done typing
            bool all_lines_finished = lines[0].is_ended() && lines[1].is_ended() && lines[2].is_ended();

            if (keypad::a_pressed())
            {
                if (all_lines_finished)
                {
                    // 1. If lines ARE finished, advance to the next dialogue
                    index++;

                    // Check if we've reached the end
                    if ((*current_conversation)[index].action == ACT_END)
                        break;

                    const dialogue_line &next_line = (*current_conversation)[index];

                    // Clear existing letters
                    lines[0].letters.clear();
                    lines[1].letters.clear();
                    lines[2].letters.clear();

                    // Reset indices for new text
                    lines[0].index = 0;
                    lines[1].index = 0;
                    lines[2].index = 0;

                    // Reinitialize with new text
                    lines[0].init(next_line.raw_text[0]);
                    lines[1].init(next_line.raw_text[1]);
                    lines[2].init(next_line.raw_text[2]);

                    // Update positions to center the text using bn::string
                    if (next_line.raw_text[0] != nullptr)
                    {
                        string<128> temp(next_line.raw_text[0]);
                        lines[0].start.x = x_center;
                    }
                    if (next_line.raw_text[1] != nullptr)
                    {
                        string<128> temp(next_line.raw_text[1]);
                        lines[1].start.x = x_center;
                    }
                    if (next_line.raw_text[2] != nullptr)
                    {
                        string<128> temp(next_line.raw_text[2]);
                        lines[2].start.x = x_center;
                    }

                    // Reset current_x for each line
                    lines[0].current_x = 0;
                    lines[1].current_x = 0;
                    lines[2].current_x = 0;

                    // Set color for new text
                    lines[0].color = next_line.color;
                    lines[1].color = next_line.color;
                    lines[2].color = next_line.color;
                }
                else
                {
                    // 2. If lines are NOT finished, "fast forward" them
                    while (!lines[0].is_ended())
                    {
                        lines[0].update(nullptr, true, EM_DEFAULT, true);
                    }
                    while (!lines[1].is_ended())
                    {
                        lines[1].update(nullptr, true, EM_DEFAULT, true);
                    }
                    while (!lines[2].is_ended())
                    {
                        lines[2].update(nullptr, true, EM_DEFAULT, true);
                    }
                }
            }

            // Update letters (typewriter effect)
            if (ticker % 5 == 0)
            {
                // 3. Only run the ticker update if the lines aren't already finished
                if (!all_lines_finished)
                {
                    if (lines[0].is_ended())
                    {
                        if (lines[1].is_ended())
                        {
                            lines[2].update(nullptr, true, EM_DEFAULT);
                        }
                        else
                        {
                            lines[1].update(nullptr, true, EM_DEFAULT);
                        }
                    }
                    else
                    {
                        lines[0].update(nullptr, true, EM_DEFAULT);
                    }
                }
            }

            // Apply color to all displayed letters
            for (int t = 0; t < 3; t++)
            {
                for (auto &letter_ : lines[t].letters)
                {
                    letter_.update(current_line.color, current_line.size);
                }
            }

            ticker++;
            core::update();
        }

        music::stop();
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