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

#include "bn_regular_bg_items_scene_cabin01.h"
#include "bn_regular_bg_items_scene_title01.h"
#include "bn_regular_bg_items_big_bg_forest_01.h"
#include "bn_regular_bg_items_bg_gameover.h"
#include "bn_regular_bg_items_scene_berlin01.h"

using namespace bn;

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
    default:
    {
        type = TYPE_IMG;
        music::stop();
        break;
    }
    }

    if (type == TYPE_TEXT)
    {
        // Initialize with first dialogue including color
        const dialogue_line &first_line = (*current_conversation)[index];

        lines[0] = {first_line.raw_text[0], {-71 + 16, 36}};
        lines[1] = {first_line.raw_text[1], {-71 + 16, 36 + 16}};
        lines[2] = {first_line.raw_text[2], {-71 + 16, 36 + 32}};

        // Set color for each line
        lines[0].color = first_line.color;
        lines[1].color = first_line.color;
        lines[2].color = first_line.color;

        while ((*current_conversation)[index].action != ACT_END)
        {
            const dialogue_line &current_line = (*current_conversation)[index];

            if (current_line.bg_item != nullptr)
            {
                frame.reset();
                frame = current_line.bg_item->create_bg(0, 0);
            }

            if (keypad::a_pressed())
            {
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

                // Set color for new text
                lines[0].color = next_line.color;
                lines[1].color = next_line.color;
                lines[2].color = next_line.color;
            }

            // Update letters with color
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
