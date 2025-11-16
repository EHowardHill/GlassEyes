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

int chapter_select()
{
    auto bg = regular_bg_items::bg_chapter_select.create_bg(0, 0);

    int index = 0;

    {
        constexpr int c_w = -56 - 32;
        constexpr int c_h = -56;

        const char *ch_titles[7] = {
            "Ch. 1",
            "Ch. 2",
            "Ch. 3",
            "Ch. 4",
            "Ch. 5",
            "Ch. 6",
            "Ch. 7"};

        const char *ch_names[7] = {
            "Exordium",
            "Her",
            "North by North",
            "1000 Miles",
            "Morning Bell",
            "The Giantess",
            "Always Like This"};

        text titles[7] = {
            {"Ch. 1", {c_w, c_h + (16 * 0)}},
            {"Ch. 2", {c_w, c_h + (16 * 1)}},
            {"Ch. 3", {c_w, c_h + (16 * 2)}},
            {"Ch. 4", {c_w, c_h + (16 * 3)}},
            {"Ch. 5", {c_w, c_h + (16 * 4)}},
            {"Ch. 6", {c_w, c_h + (16 * 5)}},
            {"Ch. 7", {c_w, c_h + (16 * 6)}}};

        vector<text, 7> ch_titles_var;
        vector<text, 7> ch_names_var;

        auto heart = sprite_items::hearts.create_sprite(c_w - 20, c_h, 1);

        for (int t = 0; t < 7; t++)
        {
            text ch_t = {ch_titles[t], {c_w, c_h + (16 * t)}};
            ch_titles_var.push_back(ch_t);

            text ch_n = {ch_names[t], {c_w + 64, c_h + (16 * t)}};
            ch_names_var.push_back(ch_n);
        }

        for (int t = 0; t < 7; t++)
        {
            ch_titles_var.at(t).render();
            ch_names_var.at(t).render();
        }

        ch_titles_var.at(index).color = COLOR_YELLOW;
        ch_names_var.at(index).color = COLOR_YELLOW;
        ch_titles_var.at(index).render();
        ch_names_var.at(index).render();

        bool selected = false;

        while (selected == false)
        {
            if (keypad::down_pressed())
            {
                ch_titles_var.at(index).color = COLOR_WHITE;
                ch_names_var.at(index).color = COLOR_WHITE;
                ch_titles_var.at(index).render();
                ch_names_var.at(index).render();

                index++;
                if (index > 6)
                    index = 0;
                sound_items::snd_select.play();
                heart.set_y(c_h + (16 * index));

                ch_titles_var.at(index).color = COLOR_YELLOW;
                ch_names_var.at(index).color = COLOR_YELLOW;
                ch_titles_var.at(index).render();
                ch_names_var.at(index).render();
            }

            if (keypad::up_pressed())
            {
                ch_titles_var.at(index).color = COLOR_WHITE;
                ch_names_var.at(index).color = COLOR_WHITE;
                ch_titles_var.at(index).render();
                ch_names_var.at(index).render();

                index--;
                if (index < 0)
                    index = 6;
                sound_items::snd_select.play();
                heart.set_y(c_h + (16 * index));

                ch_titles_var.at(index).color = COLOR_YELLOW;
                ch_names_var.at(index).color = COLOR_YELLOW;
                ch_titles_var.at(index).render();
                ch_names_var.at(index).render();
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
                {
                    return CUTSCENE_01;
                    break;
                }
                case 1:
                {
                    return BLACK_TO_LAB;
                    break;
                }
                case 2:
                {
                    return AVALON;
                    break;
                }
                case 3:
                {
                    return DARK_TO_DARK;
                    break;
                }
                case 4:
                {
                    return WAKEY_WAKEY;
                    break;
                }
                case 5:
                {
                    return FLAYITHRO_AWAKE;
                    break;
                }
                case 6:
                {
                    return BLACK_TO_LAB_02;
                    break;
                }
                default:
                {
                    return CUTSCENE_01;
                    break;
                }
                }
            }

            core::update();
        }
    }
}

int main()
{
    core::init();
    global_data_ptr = new global_data();

    //global_data_ptr->foe = FOE_VISKERS_01;
    //battle_map();

    // game_numpad();

    int value = NEW_CHAPTER;
    {
        global_data_ptr->process_stage = CUTSCENE_01;
        resolve_chapter();
        navigate_map();
        global_data_ptr->process_stage = CH_TITLE;
        resolve_chapter();
    }

    global_data_ptr->process_stage = chapter_select();
    global_data_ptr->jeremy_position = {0, 0};
    global_data_ptr->ginger_position = {0, 0};
    global_data_ptr->sebellus_position = {0, 0};
    core::update();

    while (true)
    {
        global_data_ptr->bg = nullptr;

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
            resolve_chapter();

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