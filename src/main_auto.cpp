#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "main_auto.h"
#include "ge_globals.h"
#include "ge_map_data.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"

#include "bn_regular_bg_items_bg_cutscene_channel.h"
#include "bn_regular_bg_items_big_bg_forest_01.h"

void resolve_chapter()
{
    switch (global_data_ptr->process_stage)
    {
    case TEST_MAP:
    {
        global_data_ptr->entry_map = &map_beach_02;
        global_data_ptr->jeremy_position = {2, 5};
        global_data_ptr->ginger_position = {2, 4};
        global_data_ptr->sebellus_position = {2, 3};
        global_data_ptr->bg_track = &music_items::forest_01;
        break;
    }
    case CUTSCENE_01:
    {
        typewriter(TYPEWRITER_INTRO);

        global_data_ptr->entry_map = &map_room01;
        global_data_ptr->jeremy_position = {9, 2};
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
        global_data_ptr->jeremy_position = {9, 5};
        global_data_ptr->bg_track = &music_items::bg_garbage;
        break;
    }
    case GARBAGE_TO_BLACK:
    {
        global_data_ptr->hp[0] = 20;
        typewriter(TYPEWRITER_GARBAGE);

        global_data_ptr->entry_map = &map_lab_01;
        global_data_ptr->jeremy_position = {4, 5};
        global_data_ptr->bg_track = &music_items::bg_office;
        break;
    }
    case BLACK_TO_LAB:
    {
        global_data_ptr->entry_map = &map_lab_01;
        global_data_ptr->jeremy_position = {4, 5};
        global_data_ptr->bg_track = &music_items::bg_office;
        break;
    }
    case FOREST_01:
    {
        global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
        global_data_ptr->entry_map = &map_forest_01;
        global_data_ptr->jeremy_position = {6, 8};
        global_data_ptr->ginger_position = {5, 8};
        global_data_ptr->bg_track = &music_items::forest_01;
        break;
    }
    case PIT_01:
    {
        sound_items::sfx_wack_his_pipis.play();
        typewriter(TYPEWRITER_BUFFER);
        music::stop();

        global_data_ptr->entry_map = &map_cave_05;
        global_data_ptr->jeremy_position = {4, 12};
        global_data_ptr->ginger_position = {4, 10};
        global_data_ptr->bg_track = &music_items::cave_01;
        break;
    }
    case NEW_BERLIN:
    {
        typewriter(TYPEWRITER_NEW_BERLIN);

        // Return
        global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
        global_data_ptr->entry_map = &map_forest_02;
        global_data_ptr->jeremy_position = {15, 5};
        global_data_ptr->ginger_position = {14, 5};
        global_data_ptr->bg_track = &music_items::forest_01;
        break;
    }
    case DOG_AND_PONY:
    {
        typewriter(TYPEWRITER_DOG_AND_PONY);

        // Return
        music::stop();
        global_data_ptr->entry_map = &map_room_04;
        global_data_ptr->jeremy_position = {4, 6};
        global_data_ptr->bg_track = &music_items::theme_anata;
        break;
    }
    case WAKEY_WAKEY:
    {
        typewriter(TYPEWRITER_BUFFER);
        music::stop();

        global_data_ptr->entry_map = &map_room_05b;
        global_data_ptr->jeremy_position = {3, 3};
        global_data_ptr->bg_track = &music_items::ambient_wind;
        break;
    }
    case AVALON:
    {
        global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
        global_data_ptr->entry_map = &map_forest_03;
        global_data_ptr->jeremy_position = {15, 15};
        global_data_ptr->ginger_position = {14, 15};
        global_data_ptr->bg_track = &music_items::bg_avalon;
        break;
    }
    case DARK_TO_DARK:
    {
        typewriter(TYPEWRITER_BUFFER);
        music::stop();

        global_data_ptr->entry_map = &map_dark_04;
        global_data_ptr->jeremy_position = {3, 22};
        global_data_ptr->ginger_position = {5, 22};
        global_data_ptr->bg_track = &music_items::ambient_wind;
        break;
    }
    case CUTSCENE_CHANNEL:
    {
        global_data_ptr->bg = &regular_bg_items::bg_cutscene_channel;
        global_data_ptr->entry_map = &map_cutscene_channel;
        global_data_ptr->bg_track = &music_items::ambient_wind;
        break;
    }
    case FINAL_MSG:
    {
        typewriter(TYPEWRITER_BUFFER);
        typewriter(TYPEWRITER_MSG);
        break;
    }
    default:
    {
        global_data_ptr->entry_map = &map_garbage_01;
        global_data_ptr->jeremy_position = {9, 5};
        global_data_ptr->bg_track = &music_items::bg_garbage;
        break;
    }
    }
}