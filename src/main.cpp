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
#include "ge_battle.h"
#include "ge_games.h"
#include "ge_map_data.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"
#include "ge_navigate.h"

using namespace bn;

int main()
{
    core::init();

    int value = NEW_CHAPTER;

    // Set for debug
    global_data_ptr = new global_data();
    global_data_ptr->process_stage = FLAYITHRO_AWAKE;

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