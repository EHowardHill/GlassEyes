#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "main_auto.h"
#include "ge_globals.h"
#include "ge_map_data.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"

#include "bn_regular_bg_items_big_bg_forest_01.h"
#include "bn_regular_bg_items_bg_cutscene_channel.h"

void resolve_chapter()
{
    switch (global_data_ptr->process_stage)
    {
	case CUTSCENE_TO_GARBAGE: {
		typewriter(TYPEWRITER_INTRO2);
		typewriter(TYPEWRITER_BUFFER);
		typewriter(TYPEWRITER_INTRO3);
		typewriter(TYPEWRITER_BUFFER);
		typewriter(TYPEWRITER_TITLE);
		typewriter(TYPEWRITER_BUFFER);
		global_data_ptr->entry_map = &map_garbage_01;
		global_data_ptr->bg_track = &music_items::bg_garbage;
		global_data_ptr->jeremy_position = {9, 5};
		break;		}
	case FOREST_01: {
		global_data_ptr->entry_map = &map_forest_01;
		global_data_ptr->bg_track = &music_items::forest_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		music::stop();
		global_data_ptr->jeremy_position = {6, 8};
		global_data_ptr->ginger_position = {5, 8};
		break;		}
	case PIT_01: {
		sound_items::sfx_wack_his_pipis.play();
		typewriter(TYPEWRITER_BUFFER);
		global_data_ptr->entry_map = &map_cave_05;
		global_data_ptr->bg_track = &music_items::cave_01;
		global_data_ptr->jeremy_position = {4, 12};
		global_data_ptr->ginger_position = {4, 10};
		break;		}
	case NEW_BERLIN: {
		typewriter(TYPEWRITER_NEW_BERLIN);
		global_data_ptr->entry_map = &map_forest_02;
		global_data_ptr->bg_track = &music_items::forest_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		music::stop();
		global_data_ptr->jeremy_position = {15, 5};
		global_data_ptr->ginger_position = {14, 5};
		break;		}
	case DOG_AND_PONY: {
		typewriter(TYPEWRITER_DOG_AND_PONY);
		global_data_ptr->entry_map = &map_room_04;
		global_data_ptr->bg_track = &music_items::theme_anata;
		global_data_ptr->jeremy_position = {4, 6};
		break;		}
	case WAKEY_WAKEY: {
		typewriter(TYPEWRITER_BUFFER);
		global_data_ptr->entry_map = &map_room_05b;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		global_data_ptr->jeremy_position = {3, 3};
		break;		}
	case DARK_TO_DARK: {
		typewriter(TYPEWRITER_BUFFER);
		global_data_ptr->entry_map = &map_dark_04;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		global_data_ptr->jeremy_position = {3, 22};
		global_data_ptr->ginger_position = {5, 22};
		break;		}
	case CUTSCENE_CHANNEL: {
		global_data_ptr->entry_map = &map_cutscene_channel;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		global_data_ptr->bg = &regular_bg_items::bg_cutscene_channel;
		music::stop();
		break;		}
	case FINAL_MSG: {
		typewriter(TYPEWRITER_BUFFER);
		typewriter(TYPEWRITER_MSG);
		break;		}
	case BLACK_TO_BEACH: {
		global_data_ptr->entry_map = &map_beach_02;
		global_data_ptr->bg_track = &music_items::forest_01;
		global_data_ptr->jeremy_position = {2, 5};
		global_data_ptr->ginger_position = {2, 4};
		global_data_ptr->sebellus_position = {2, 3};
		break;		}
	case TEST_MAP: {
		global_data_ptr->entry_map = &map_to_flay_02;
		global_data_ptr->bg_track = &music_items::forest_01;
		global_data_ptr->ginger_position = {2, 3};
		break;		}
	case FLAYITHRO_AWAKE: {
		global_data_ptr->entry_map = &map_hotel_01_night;
		global_data_ptr->jeremy_position = {2, 2};
		break;		}
	case BLACK_TO_TRAIN: {
		global_data_ptr->entry_map = &map_train_room_04;
		global_data_ptr->bg_track = &music_items::bg_sorry_train;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		music::stop();
		global_data_ptr->jeremy_position = {4, 3};
		break;		}
	case BLACK_TO_CANTERBURY: {
		global_data_ptr->entry_map = &map_to_canter_01;
		global_data_ptr->jeremy_position = {6, 3};
		break;		}
	case BLACK_TO_LAB_02: {
		global_data_ptr->entry_map = &map_lab_02;
		global_data_ptr->bg_track = &music_items::bg_office;
		global_data_ptr->jeremy_position = {1, 5};
		break;		}
	case CH_CUTSCENE_04: {
		global_data_ptr->entry_map = &map_cutscene_lab_room_02;
		break;		}
	case CH_CUTSCENE_06: {
		global_data_ptr->entry_map = &map_cutscene_garbage_chute;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		break;		}
	case CH_CUTSCENE_07: {
		typewriter(TYPEWRITER_CCUTSCENE_07);
		global_data_ptr->entry_map = &map_cutscene_castle_01;
		break;		}
	case CH_CUTSCENE_08: {
		global_data_ptr->entry_map = &map_cutscene_castle_02;
		global_data_ptr->bg_track = &music_items::intro_02;
		break;		}
	case CH_CUTSCENE_08B: {
		global_data_ptr->entry_map = &map_cutscene_castle_03;
		break;		}
	case CH_CUTSCENE_08C: {
		global_data_ptr->entry_map = &map_cutscene_castle_bonus;
		break;		}
	case CUTSCENE_01: {
		typewriter(TYPEWRITER_INTRO);
		global_data_ptr->entry_map = &map_room01;
		global_data_ptr->jeremy_position = {0, 0};
		break;		}
	case CH_SANS: {
		global_data_ptr->entry_map = &map_sans;
		global_data_ptr->bg_track = &music_items::theme_sans;
		break;		}
	case CH_TITLE: {
		typewriter(TYPEWRITER_INTRO2);
		typewriter(TYPEWRITER_BUFFER);
		typewriter(TYPEWRITER_TITLE);
		typewriter(TYPEWRITER_BUFFER);
		break;		}
	case CH_CUTSCENE_05: {
		global_data_ptr->entry_map = &map_cutscene_lab_kitchen;
		global_data_ptr->bg_track = &music_items::intro;
		break;		}
	case CH_CUTSCENE_09: {
		global_data_ptr->entry_map = &map_castle_ginger;
		global_data_ptr->bg_track = &music_items::intro;
		break;		}
	case CH_CUTSCENE_03: {
		typewriter(TYPEWRITER_CCUTSCENE_03);
		global_data_ptr->entry_map = &map_forest_03;
		global_data_ptr->jeremy_position = {16, 15};
		global_data_ptr->ginger_position = {17, 15};
		break;		}
	case CH_CUTSCENE_01: {
		typewriter(TYPEWRITER_CCUTSCENE_01);
		global_data_ptr->entry_map = &map_garbage_01;
		global_data_ptr->bg_track = &music_items::bg_garbage;
		global_data_ptr->jeremy_position = {9, 5};
		break;		}
	case CH_CUTSCENE_02: {
		typewriter(TYPEWRITER_CCUTSCENE_02);
		global_data_ptr->entry_map = &map_lab_01;
		global_data_ptr->bg_track = &music_items::bg_office;
		global_data_ptr->jeremy_position = {4, 5};
		break;		}
	default: { break; }
	}
}