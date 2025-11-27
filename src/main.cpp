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

#include "main.h"
#include "main_auto.h"
#include "ge_globals.h"
#include "ge_sprites.h"
#include "ge_text.h"
#include "ge_maps.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_actions.h"
#include "ge_games.h"
#include "ge_map_data.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"
#include "ge_navigate.h"
#include "ge_game_numpad.h"

#include "bn_regular_bg_items_bg_chapter_select.h"

using namespace bn;

constexpr bool TESTING = false;

int chapter_select()
{
    auto bg = regular_bg_items::bg_chapter_select.create_bg(0, 0);
    int index = 0;

    {
        constexpr int c_w = -56 - 32;
        constexpr int c_h = -56;

        const char *ch_titles[7] = {
            "Ch. 1", "Ch. 2", "Ch. 3", "Ch. 4",
            "Ch. 5", "Ch. 6", "Ch. 7"};

        const char *ch_names[7] = {
            "Exordium", "Her", "North by North", "1000 Miles",
            "Morning Bell", "The Giantess", "Always Like This"};

        list<unique_ptr<text>, 7> ch_titles_var;
        list<unique_ptr<text>, 7> ch_names_var;

        auto heart = sprite_items::hearts.create_sprite(c_w - 20, c_h, 1);

        for (int t = 0; t < 7; t++)
        {
            ch_titles_var.push_back(unique_ptr<text>(new text{ch_titles[t], {c_w, c_h + (16 * t)}}));
            ch_names_var.push_back(unique_ptr<text>(new text{ch_names[t], {c_w + 64, c_h + (16 * t)}}));
        }

        // Helper lambda to simulate .at(index) behavior for a list
        auto get_item = [](auto &list_container, int idx) -> text *
        {
            auto it = list_container.begin();
            for (int i = 0; i < idx; ++i)
                ++it;
            return it->get();
        };

        for (auto &t : ch_titles_var)
            t->render();
        for (auto &n : ch_names_var)
            n->render();

        get_item(ch_titles_var, index)->color = COLOR_YELLOW;
        get_item(ch_names_var, index)->color = COLOR_YELLOW;
        get_item(ch_titles_var, index)->render();
        get_item(ch_names_var, index)->render();

        bool selected = false;

        int ticker = 0;
        while (selected == false)
        {
            if (ticker % 256 == 0)
            {
                sound_items::drone.play();
            }

            if (keypad::down_pressed())
            {
                get_item(ch_titles_var, index)->color = COLOR_WHITE;
                get_item(ch_names_var, index)->color = COLOR_WHITE;
                get_item(ch_titles_var, index)->render();
                get_item(ch_names_var, index)->render();

                index++;
                if (index > 6)
                    index = 0;

                sound_items::snd_select.play();
                heart.set_y(c_h + (16 * index));

                get_item(ch_titles_var, index)->color = COLOR_YELLOW;
                get_item(ch_names_var, index)->color = COLOR_YELLOW;
                get_item(ch_titles_var, index)->render();
                get_item(ch_names_var, index)->render();
            }

            if (keypad::up_pressed())
            {
                get_item(ch_titles_var, index)->color = COLOR_WHITE;
                get_item(ch_names_var, index)->color = COLOR_WHITE;
                get_item(ch_titles_var, index)->render();
                get_item(ch_names_var, index)->render();

                index--;
                if (index < 0)
                    index = 6;

                sound_items::snd_select.play();
                heart.set_y(c_h + (16 * index));

                get_item(ch_titles_var, index)->color = COLOR_YELLOW;
                get_item(ch_names_var, index)->color = COLOR_YELLOW;
                get_item(ch_titles_var, index)->render();
                get_item(ch_names_var, index)->render();
            }

            if (keypad::r_pressed() && keypad::l_pressed())
            {
                return CH_SANS;
            }

            if (keypad::a_pressed())
            {
                switch (index)
                {
                case 0:
                    return CH_CUTSCENE_01;
                case 1:
                    return CH_CUTSCENE_02;
                case 2:
                    return CH_CUTSCENE_03;
                case 3:
                    return CH_CUTSCENE_05;
                case 4:
                    return CH_CUTSCENE_06;
                case 5:
                    return CH_CUTSCENE_07;
                case 6:
                    return CH_CUTSCENE_08;
                default:
                    return CUTSCENE_01;
                }
            }

            ticker++;
            core::update();
        }
    }
}

int main()
{
    core::init();
    global_data_ptr = new global_data();
    global_data_ptr->jeremy_position = {0, 0};
    global_data_ptr->ginger_position = {0, 0};
    global_data_ptr->sebellus_position = {0, 0};

    int value = NEW_CHAPTER;

    if (TESTING == true)
    {
        global_data_ptr->process_stage = FINAL_CHAPTER;
    }
    else
    {
        {
            global_data_ptr->process_stage = CUTSCENE_01;
            resolve_chapter();
            navigate_map();
            global_data_ptr->process_stage = CH_TITLE;
            resolve_chapter();
        }

        global_data_ptr->process_stage = chapter_select();
        core::update();

        sound_items::snd_chime.play();
        for (int t = 0; t < 96; t++)
        {
            core::update();
        }
    }

    while (true)
    {
        global_data_ptr->inverted_controls = false;

        switch (value)
        {
        case GAME:
        {
            value = game_map();
            break;
        }
        case BATTLE:
        {
            value = battle_map();
            break;
        }
        case NEW_CHAPTER:
        {
            global_data_ptr->jeremy_position = {0, 0};
            global_data_ptr->ginger_position = {0, 0};
            global_data_ptr->sebellus_position = {0, 0};
            resolve_chapter();

            value = CONTINUE;
            break;
        }
        case KEYPAD:
        {
            value = game_numpad();
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
                global_data_ptr->bg_track->play(1);
            }

            value = navigate_map();
            break;
        }
        }

        core::update();
    }
}