#include "bn_music.h"
#include "bn_music_items.h"

#include "bn_regular_bg_items_big_bg_city_01.h"
#include "bn_regular_bg_items_big_bg_forest_01.h"

#include "main_auto.h"
#include "ge_globals.h"
#include "ge_dialogue.h"
#include "ge_character_manager.h"
#include "ge_actions_auto.h"
#include "ge_map_data.h"

using namespace bn;

int perform_action_interactive(int index, character_manager &ch_man)
{
    switch (index)
    {	case 6:
	{
		if (global_data_ptr->action_iterations[6] == 1) { ch_man.load(&garbage_sign01); } else
		if (global_data_ptr->action_iterations[6] == 2) { ch_man.load(&garbage_sign01b); } else
		{ };
		break;
	}
	case 10:
	{
		ch_man.load(&garbage_sign02);
		break;
	}
	case 14:
	{
		ch_man.load(&garbage_sign03);
		break;
	}
	case 16:
	{
		ch_man.load(&garbage_05b);
		break;
	}
	case 23:
	{
		ch_man.load(&garbage_sign04);
		break;
	}
	case 25:
	{
		ch_man.load(&garbage_sign05);
		break;
	}
	case 29:
	{
		ch_man.load(&lab_03);
		break;
	}
	case 37:
	{
		ch_man.load(&forest_dlg_sign_01);
		break;
	}
	case 40:
	{
		ch_man.load(&forest_dlg_sign_02);
		break;
	}
	case 42:
	{
		ch_man.load(&forest_dlg_sign_02);
		break;
	}
	case 54:
	{
		ch_man.load(&cave_sign_01);
		break;
	}
	case 70:
	{
		ch_man.load(&temmie_sign);
		break;
	}
	case 72:
	{
		ch_man.load(&temmie_01);
		break;
	}
	case 73:
	{
		ch_man.load(&temmie_02);
		break;
	}
	case 74:
	{
		ch_man.load(&temmie_03);
		break;
	}
	case 75:
	{
		ch_man.load(&temmie_04);
		break;
	}
	case 76:
	{
		ch_man.load(&temmie_05);
		break;
	}
	case 77:
	{
		ch_man.load(&temmie_06);
		break;
	}
	case 78:
	{
		ch_man.load(&temmie_07);
		break;
	}
	case 80:
	{
		ch_man.load(&cave_sign_02);
		break;
	}
	case 85:
	{
		global_data_ptr->process_stage = NEW_BERLIN;
		return NEW_CHAPTER;
		break;
	}
	case 87:
	{
		ch_man.load(&avalon_sign_01);
		break;
	}
	case 88:
	{
		ch_man.load(&avalon_sign_02);
		break;
	}
	case 90:
	{
		ch_man.load(&avalon_sign_03);
		break;
	}
	case 91:
	{
		ch_man.load(&avalon_sign_04);
		break;
	}
	case 92:
	{
		ch_man.load(&avalon_sign_05);
		break;
	}
	case 94:
	{
		ch_man.load(&avalon_sign_06);
		break;
	}
	case 97:
	{
		if (global_data_ptr->action_iterations[97] == 1) { ch_man.load(&avalon_guy_01); } else
		{ ch_man.load(&avalon_guy_01); }
		break;
	}
	case 98:
	{
		if (global_data_ptr->action_iterations[98] == 1) { ch_man.load(&avalon_grandma_01); } else
		{ ch_man.load(&avalon_grandma_01); }
		break;
	}
	case 99:
	{
		if (global_data_ptr->action_iterations[99] == 1) { ch_man.load(&avalon_courier_01); } else
		{ ch_man.load(&avalon_courier_01); }
		break;
	}
	case 100:
	{
		if (global_data_ptr->action_iterations[100] == 1) { ch_man.load(&avalon_shop_01); } else
		{ ch_man.load(&avalon_shop_01); }
		break;
	}
	case 101:
	{
		if (global_data_ptr->action_iterations[101] == 1) { ch_man.load(&avalon_wormguy_01); } else
		{ ch_man.load(&avalon_wormguy_01); }
		break;
	}
	case 103:
	{
		if (global_data_ptr->action_iterations[103] == 1) { ch_man.load(&doll_guy_01); } else
		{ };
		break;
	}
	case 104:
	{
		if (global_data_ptr->action_iterations[104] == 1) { ch_man.load(&item_tire_01); } else
		{ };
		break;
	}
	case 105:
	{
		if (global_data_ptr->action_iterations[105] == 1) { ch_man.load(&item_enoki_01); } else
		{ };
		break;
	}
	case 107:
	{
		if (global_data_ptr->action_iterations[107] == 1) { ch_man.load(&item_lime_01); } else
		{ };
		break;
	}
	case 108:
	{
		if (global_data_ptr->action_iterations[108] == 1) { ch_man.load(&scruffys_01); } else
		{ };
		break;
	}
	case 109:
	{
		if (global_data_ptr->action_iterations[109] == 1) { ch_man.load(&scruffys_02); } else
		{ };
		break;
	}
	case 110:
	{
		if (global_data_ptr->action_iterations[110] == 1) { ch_man.load(&scruffys_03); } else
		{ };
		break;
	}
	case 111:
	{
		if (global_data_ptr->action_iterations[111] == 1) { ch_man.load(&scruffys_04); } else
		{ };
		break;
	}
	case 113:
	{
		music_items::shop.play();
		break;
	}
	case 114:
	{
		if (global_data_ptr->action_iterations[114] == 1) { ch_man.load(&scruffys_06); } else
		{ ch_man.load(&scruffys_06); }
		break;
	}
	case 115:
	{
		if (global_data_ptr->action_iterations[115] == 1) { ch_man.load(&tollhouse_01); } else
		{ ch_man.load(&tollhouse_01); }
		break;
	}
	case 132:
	{
		if (global_data_ptr->action_iterations[132] == 1) { ch_man.load(&broken_avalon_01); } else
		{ };
		break;
	}
	case 133:
	{
		if (global_data_ptr->action_iterations[133] == 1) { ch_man.load(&broken_avalon_02); } else
		{ };
		break;
	}
	case 134:
	{
		if (global_data_ptr->action_iterations[134] == 1) { ch_man.load(&broken_avalon_02); } else
		{ };
		break;
	}
	case 153:
	{
		if (global_data_ptr->action_iterations[153] == 1) { ch_man.load(&item_153); } else
		{ };
		break;
	}
	case 154:
	{
		if (global_data_ptr->action_iterations[154] == 1) { ch_man.load(&item_none); } else
		{ };
		break;
	}
	case 156:
	{
		if (global_data_ptr->action_iterations[156] == 1) { ch_man.load(&item_156); } else
		{ };
		break;
	}
	case 157:
	{
		if (global_data_ptr->action_iterations[157] == 1) { ch_man.load(&item_157); } else
		{ };
		break;
	}
	case 158:
	{
		if (global_data_ptr->action_iterations[158] == 1) { ch_man.load(&item_158); } else
		{ };
		break;
	}
	case 175:
	{
		if (global_data_ptr->action_iterations[175] == 1) { ch_man.load(&talk_175); } else
		{ };
		break;
	}
	case 180:
	{
		global_data_ptr->process_stage = DOG_AND_PONY;
		return NEW_CHAPTER;
		break;
	}
	case 182:
	{
		ch_man.load(&sleep_01);
		break;
	}
	case 184:
	{
		if (global_data_ptr->action_iterations[184] == 1) { ch_man.load(&talk_184); } else
		{ };
		break;
	}
	case 197:
	{
		if (global_data_ptr->action_iterations[197] == 1) { ch_man.load(&chat_197); } else
		{ };
		break;
	}
	case 206:
	{
		ch_man.load(&chat_mcwebb);
		break;
	}
	case 207:
	{
		ch_man.load(&beach_sign);
		break;
	}
	case 214:
	{
		if (global_data_ptr->action_iterations[214] == 1) { ch_man.load(&chat_mcwebb_03); } else
		{ };
		break;
	}
	case 217:
	{
		ch_man.load(&flayithro_sign);
		break;
	}
	case 225:
	{
		if (global_data_ptr->action_iterations[225] == 1) { ch_man.load(&pringle_01); } else
		{ };
		break;
	}
	case 226:
	{
		ch_man.load(&flayithro_sign_01);
		break;
	}
	case 227:
	{
		if (global_data_ptr->action_iterations[227] == 1) { ch_man.load(&kathy_01); } else
		{ };
		break;
	}
	case 231:
	{
		ch_man.load(&hotel_room_01);
		break;
	}
	case 232:
	{
		ch_man.load(&hotel_room_02);
		break;
	}
	case 234:
	{
		if (global_data_ptr->action_iterations[234] == 1) { ch_man.load(&eggplant_01); } else
		{ };
		break;
	}
	case 235:
	{
		ch_man.load(&hotel_fridge);
		break;
	}
	case 251:
	{
		if (global_data_ptr->action_iterations[251] == 1) { ch_man.load(&train_locked); } else
		{ };
		break;
	}
	case 255:
	{
		ch_man.load(&train_mirror);
		break;
	}
	case 257:
	{
		ch_man.load(&train_sebellus);
		break;
	}
	case 260:
	{
		global_data_ptr->entry_map = &map_canter_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_city_01;
		global_data_ptr->jeremy_position = {3, 11};
		return NEW_MAP;
		break;
	}
	case 264:
	{
		global_data_ptr->entry_map = &map_lab_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 11};
		global_data_ptr->kiara_position = {2, 11};
		return NEW_MAP;
		break;
	}
	case 266:
	{
		global_data_ptr->entry_map = &map_lab_04;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {11, 2};
		global_data_ptr->kiara_position = {12, 2};
		return NEW_MAP;
		break;
	}
	case 268:
	{
		if (global_data_ptr->action_iterations[268] == 1) { ch_man.load(&kiara_toaster); } else
		{ };
		break;
	}
	case 272:
	{
		if (global_data_ptr->action_iterations[272] == 1) { ch_man.load(&kiara_dog); } else
		{ };
		break;
	}
	case 273:
	{
		if (global_data_ptr->action_iterations[273] == 1) { ch_man.load(&kiara_gest); } else
		{ };
		break;
	}
	case 274:
	{
		if (global_data_ptr->action_iterations[274] == 1) { ch_man.load(&kiara_matt); } else
		{ };
		break;
	}
	case 275:
	{
		if (global_data_ptr->action_iterations[275] == 1) { ch_man.load(&kiara_note); } else
		{ };
		break;
	}
	case 276:
	{
		if (global_data_ptr->action_iterations[276] == 1) { ch_man.load(&kiara_bed); } else
		{ };
		break;
	}
	case 286:
	{
		if (global_data_ptr->action_iterations[286] == 1) { ch_man.load(&c09_mirror); } else
		{ };
		break;
	}
	case 287:
	{
		if (global_data_ptr->action_iterations[287] == 1) { ch_man.load(&c09_books); } else
		{ };
		break;
	}
	case 289:
	{
		global_data_ptr->entry_map = &map_castle_ginger;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {1, 2};
		return NEW_MAP;
		break;
	}
	case 290:
	{
		if (global_data_ptr->action_iterations[290] == 1) { ch_man.load(&c09_door_sebellus); } else
		{ };
		break;
	}
	case 291:
	{
		global_data_ptr->entry_map = &map_castle_vista;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {2, 3};
		return NEW_MAP;
		break;
	}
	case 292:
	{
		global_data_ptr->entry_map = &map_castle_02b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {17, 2};
		return NEW_MAP;
		break;
	}
	case 288:
	{
		global_data_ptr->entry_map = &map_castle_vista;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {2, 3};
		return NEW_MAP;
		break;
	}
	case 294:
	{
		global_data_ptr->entry_map = &map_castle_bonus;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {13, 2};
		return NEW_MAP;
		break;
	}
	case 295:
	{
		if (global_data_ptr->action_iterations[295] == 1) { ch_man.load(&c09_tv); } else
		{ };
		break;
	}
	case 296:
	{
		if (global_data_ptr->action_iterations[296] == 1) { ch_man.load(&c09_bed); } else
		{ };
		break;
	}
	case 297:
	{
		if (global_data_ptr->action_iterations[297] == 1) { ch_man.load(&c09_fridge); } else
		{ };
		break;
	}
	case 298:
	{
		global_data_ptr->entry_map = &map_castle_02b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {14, 22};
		return NEW_MAP;
		break;
	}
	case 299:
	{
		global_data_ptr->entry_map = &map_castle_02b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {5, 2};
		return NEW_MAP;
		break;
	}
	case 300:
	{
		if (global_data_ptr->action_iterations[300] == 1) { ch_man.load(&c09_desk); } else
		{ };
		break;
	}
	case 301:
	{
		global_data_ptr->entry_map = &map_castle_secret_garden;
		global_data_ptr->bg_track = &music_items::ambient_birds;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {6, 46};
		return NEW_MAP;
		break;
	}
	case 303:
	{
		if (global_data_ptr->action_iterations[303] == 1) { ch_man.load(&c09_graves); } else
		{ };
		break;
	}
	case 304:
	{
		global_data_ptr->entry_map = &map_castle_secret_tunnel;
		global_data_ptr->bg_track = &music_items::ambient_heartbeat;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {5, 22};
		return NEW_MAP;
		break;
	}
	case 307:
	{
		if (global_data_ptr->action_iterations[307] == 1) { ch_man.load(&c09_pills); } else
		{ };
		break;
	}
	case 315:
	{
		if (global_data_ptr->action_iterations[315] == 1) { ch_man.load(&sans_06); } else
		{ };
		break;
	}
	case 169:
	{
		global_data_ptr->entry_map = &map_room_02;
		global_data_ptr->bg_track = &music_items::theme_anata;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {9, 11};
		global_data_ptr->ginger_position = {0, 0};
		global_data_ptr->sebellus_position = {0, 0};
		return NEW_MAP;
		break;
	}
	case 316:
	{
		if (global_data_ptr->action_iterations[316] == 1) { ch_man.load(&naomi_garbage_01); } else
		if (global_data_ptr->action_iterations[316] == 2) { ch_man.load(&naomi_garbage_02); } else
		{ };
		break;
	}
	case 317:
	{
		ch_man.load(&pipis_man);
		break;
	}
	case 320:
	{
		if (global_data_ptr->action_iterations[320] == 1) { ch_man.load(&desmond_01); } else
		{ };
		break;
	}
	case 325:
	{
		if (global_data_ptr->action_iterations[325] == 1) { ch_man.load(&naomi_shop_01); } else
		if (global_data_ptr->action_iterations[325] == 2) { ch_man.load(&naomi_shop_02); } else
		{ };
		break;
	}
	case 326:
	{
		global_data_ptr->entry_map = &map_shop_02;
		global_data_ptr->bg_track = &music_items::shop;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 5};
		return NEW_MAP;
		break;
	}
	case 327:
	{
		global_data_ptr->entry_map = &map_canter_01;
		global_data_ptr->bg_track = &music_items::bg_canter_02;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {30, 13};
		return NEW_MAP;
		break;
	}
	case 328:
	{
		ch_man.load(&naomi_shop_03);
		break;
	}
	case 329:
	{
		ch_man.load(&naomi_shop_04);
		break;
	}
	case 330:
	{
		ch_man.load(&canter_shop);
		break;
	}
	case 333:
	{
		if (global_data_ptr->action_iterations[333] == 1) { ch_man.load(&canter_people); } else
		{ };
		break;
	}
	case 334:
	{
		ch_man.load(&cathedral_door);
		break;
	}
	case 338:
	{
		if (global_data_ptr->action_iterations[338] == 1) { ch_man.load(&lobbybot_03); } else
		if (global_data_ptr->action_iterations[338] == 2) { ch_man.load(&lobbybot_04); } else
		{ };
		break;
	}
	case 342:
	{
		ch_man.load(&door_locked);
		break;
	}
	case 343:
	{
		ch_man.load(&hotel_bed);
		break;
	}
	case 357:
	{
		ch_man.load(&airport_closed);
		break;
	}
	case 277:
	{
		global_data_ptr->entry_map = &map_castle_ginger;
		global_data_ptr->bg_track = &music_items::theme_anata;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {0, 0};
		global_data_ptr->kiara_position = {0, 0};
		return NEW_MAP;
		break;
	}
	case 355:
	{
		if (global_data_ptr->action_iterations[355] == 1) { ch_man.load(&train_ginger); } else
		{ };
		break;
	}
	case 363:
	{
		ch_man.load(&constance_castle);
		break;
	}
	case 366:
	{
		global_data_ptr->entry_map = &map_castle_garden;
		global_data_ptr->bg_track = &music_items::ambient_birds;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {3, 8};
		return NEW_MAP;
		break;
	}
	case 331:
	{
		global_data_ptr->entry_map = &map_church_02;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 12};
		return NEW_MAP;
		break;
	}
	case 369:
	{
		if (global_data_ptr->action_iterations[369] == 1) { ch_man.load(&sebellus_gun); } else
		if (global_data_ptr->action_iterations[369] == 2) { ch_man.load(&sebellus_gun_02); } else
		{ };
		break;
	}
	}
	return -1;
}

int perform_action_automatic(int index, character_manager &ch_man)
{
    switch (index)
    {	case 1:
	{
		ch_man.load(&test_convo);
		break;
	}
	case 2:
	{
		if (global_data_ptr->action_iterations[2] == 0) { ch_man.load(&garbage_01); global_data_ptr->action_iterations[2] += 1; } else
		{ };
		break;
	}
	case 3:
	{
		if (global_data_ptr->action_iterations[3] == 0) { ch_man.load(&garbage_02); global_data_ptr->action_iterations[3] += 1; } else
		{ };
		break;
	}
	case 4:
	{
		if (global_data_ptr->action_iterations[4] == 0) { ch_man.load(&garbage_03); global_data_ptr->action_iterations[4] += 1; } else
		{ };
		break;
	}
	case 5:
	{
		global_data_ptr->entry_map = &map_garbage_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 6};
		return NEW_MAP;
		break;
	}
	case 7:
	{
		global_data_ptr->entry_map = &map_viskers_house;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 5};
		return NEW_MAP;
		break;
	}
	case 8:
	{
		global_data_ptr->entry_map = &map_garbage_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 3};
		return NEW_MAP;
		break;
	}
	case 9:
	{
		global_data_ptr->entry_map = &map_garbage_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {13, 2};
		return NEW_MAP;
		break;
	}
	case 11:
	{
		if (global_data_ptr->action_iterations[11] == 0) { ch_man.load(&visker_h_03); global_data_ptr->action_iterations[11] += 1; } else
		{ };
		break;
	}
	case 12:
	{
		if (global_data_ptr->action_iterations[12] == 0) { ch_man.load(&visker_h_02); global_data_ptr->action_iterations[12] += 1; } else
		{ };
		break;
	}
	case 13:
	{
		if (global_data_ptr->action_iterations[13] == 0) { ch_man.load(&visker_h_01); global_data_ptr->action_iterations[13] += 1; } else
		{ };
		break;
	}
	case 15:
	{
		if (global_data_ptr->action_iterations[15] == 0) { ch_man.load(&garbage_04); global_data_ptr->action_iterations[15] += 1; } else
		if (global_data_ptr->action_iterations[15] == 1) { ch_man.load(&garbage_05); global_data_ptr->action_iterations[15] += 1; } else
		{ };
		break;
	}
	case 17:
	{
		global_data_ptr->entry_map = &map_garbage_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {29, 4};
		return NEW_MAP;
		break;
	}
	case 19:
	{
		global_data_ptr->entry_map = &map_garbage_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {10, 12};
		return NEW_MAP;
		break;
	}
	case 20:
	{
		global_data_ptr->entry_map = &map_garbage_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 20};
		return NEW_MAP;
		break;
	}
	case 21:
	{
		global_data_ptr->entry_map = &map_garbage_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {29, 12};
		return NEW_MAP;
		break;
	}
	case 22:
	{
		global_data_ptr->entry_map = &map_garbage_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {29, 20};
		return NEW_MAP;
		break;
	}
	case 27:
	{
		if (global_data_ptr->action_iterations[27] == 0) { ch_man.load(&lab_01); global_data_ptr->action_iterations[27] += 1; } else
		{ };
		break;
	}
	case 28:
	{
		if (global_data_ptr->action_iterations[28] == 0) { ch_man.load(&lab_02); global_data_ptr->action_iterations[28] += 1; } else
		if (global_data_ptr->action_iterations[28] == 1) { ch_man.load(&lab_02b); global_data_ptr->action_iterations[28] += 1; } else
		{ };
		break;
	}
	case 31:
	{
		if (global_data_ptr->action_iterations[31] == 0) { ch_man.load(&lab_05); global_data_ptr->action_iterations[31] += 1; } else
		{ };
		break;
	}
	case 32:
	{
		if (global_data_ptr->action_iterations[32] == 0) { ch_man.load(&lab_06); global_data_ptr->action_iterations[32] += 1; } else
		{ };
		break;
	}
	case 33:
	{
		if (global_data_ptr->action_iterations[33] == 0) { ch_man.load(&lab_07); global_data_ptr->action_iterations[33] += 1; } else
		{ };
		break;
	}
	case 34:
	{
		if (global_data_ptr->action_iterations[34] == 0) { ch_man.load(&lab_08); global_data_ptr->action_iterations[34] += 1; } else
		{ };
		break;
	}
	case 35:
	{
		ch_man.load(&leaving_lab);
		break;
	}
	case 36:
	{
		if (global_data_ptr->action_iterations[36] == 0) { ch_man.load(&forest_dlg_02); global_data_ptr->action_iterations[36] += 1; } else
		{ };
		break;
	}
	case 38:
	{
		if (global_data_ptr->action_iterations[38] == 0) { ch_man.load(&forest_dlg_01); global_data_ptr->action_iterations[38] += 1; } else
		{ };
		break;
	}
	case 39:
	{
		if (global_data_ptr->action_iterations[39] == 0) { ch_man.load(&croke_01); global_data_ptr->action_iterations[39] += 1; } else
		if (global_data_ptr->action_iterations[39] == 1) { ch_man.load(&croke_05); global_data_ptr->action_iterations[39] += 1; } else
		{ };
		break;
	}
	case 41:
	{
		global_data_ptr->entry_map = &map_cave_01;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {7, 12};
		global_data_ptr->ginger_position = {6, 12};
		return NEW_MAP;
		break;
	}
	case 43:
	{
		if (global_data_ptr->action_iterations[43] == 0) { ch_man.load(&forest_dlg_03); global_data_ptr->action_iterations[43] += 1; } else
		{ };
		break;
	}
	case 46:
	{
		if (global_data_ptr->action_iterations[46] == 0) { ch_man.load(&bridge_01); global_data_ptr->action_iterations[46] += 1; } else
		{ };
		break;
	}
	case 51:
	{
		global_data_ptr->entry_map = &map_forest_01;
		global_data_ptr->bg_track = &music_items::forest_01;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {67, 3};
		global_data_ptr->ginger_position = {66, 3};
		return NEW_MAP;
		break;
	}
	case 52:
	{
		if (global_data_ptr->action_iterations[52] == 0) { ch_man.load(&cave_01); global_data_ptr->action_iterations[52] += 1; } else
		{ };
		break;
	}
	case 55:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {19, 30};
		global_data_ptr->ginger_position = {20, 30};
		return NEW_MAP;
		break;
	}
	case 56:
	{
		global_data_ptr->entry_map = &map_cave_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {28, 3};
		global_data_ptr->ginger_position = {29, 3};
		return NEW_MAP;
		break;
	}
	case 57:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {16, 4};
		global_data_ptr->ginger_position = {15, 4};
		return NEW_MAP;
		break;
	}
	case 58:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {16, 16};
		global_data_ptr->ginger_position = {15, 16};
		return NEW_MAP;
		break;
	}
	case 59:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {30, 19};
		global_data_ptr->ginger_position = {31, 19};
		return NEW_MAP;
		break;
	}
	case 60:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {29, 3};
		global_data_ptr->ginger_position = {30, 3};
		return NEW_MAP;
		break;
	}
	case 61:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {12, 11};
		global_data_ptr->ginger_position = {11, 11};
		return NEW_MAP;
		break;
	}
	case 62:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {12, 21};
		global_data_ptr->ginger_position = {11, 21};
		return NEW_MAP;
		break;
	}
	case 63:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 3};
		global_data_ptr->ginger_position = {5, 3};
		return NEW_MAP;
		break;
	}
	case 64:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {28, 11};
		global_data_ptr->ginger_position = {29, 11};
		return NEW_MAP;
		break;
	}
	case 65:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 24};
		global_data_ptr->ginger_position = {2, 23};
		return NEW_MAP;
		break;
	}
	case 66:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {13, 8};
		global_data_ptr->ginger_position = {13, 7};
		return NEW_MAP;
		break;
	}
	case 67:
	{
		global_data_ptr->entry_map = &map_cave_cowbemmie;
		global_data_ptr->bg_track = &music_items::bg_dixieland;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 3};
		global_data_ptr->ginger_position = {1, 3};
		return NEW_MAP;
		break;
	}
	case 71:
	{
		global_data_ptr->entry_map = &map_forest_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {105, 3};
		global_data_ptr->ginger_position = {104, 3};
		return NEW_MAP;
		break;
	}
	case 79:
	{
		global_data_ptr->entry_map = &map_forest_02;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {27, 3};
		global_data_ptr->ginger_position = {26, 3};
		return NEW_MAP;
		break;
	}
	case 82:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 15};
		global_data_ptr->ginger_position = {4, 15};
		return NEW_MAP;
		break;
	}
	case 89:
	{
		global_data_ptr->entry_map = &map_tavern_01;
		global_data_ptr->bg_track = &music_items::theme_visker;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {8, 10};
		global_data_ptr->ginger_position = {7, 10};
		return NEW_MAP;
		break;
	}
	case 95:
	{
		global_data_ptr->entry_map = &map_shop_01;
		global_data_ptr->bg_track = &music_items::shop;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 8};
		global_data_ptr->ginger_position = {4, 8};
		return NEW_MAP;
		break;
	}
	case 102:
	{
		global_data_ptr->entry_map = &map_forest_03;
		global_data_ptr->bg_track = &music_items::bg_avalon;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {47, 8};
		global_data_ptr->ginger_position = {46, 8};
		return NEW_MAP;
		break;
	}
	case 117:
	{
		global_data_ptr->entry_map = &map_forest_03;
		global_data_ptr->bg_track = &music_items::bg_avalon;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {24, 14};
		global_data_ptr->ginger_position = {23, 14};
		return NEW_MAP;
		break;
	}
	case 118:
	{
		global_data_ptr->entry_map = &map_forest_04;
		global_data_ptr->bg_track = &music_items::bg_spamton;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 7};
		global_data_ptr->ginger_position = {3, 7};
		return NEW_MAP;
		break;
	}
	case 119:
	{
		global_data_ptr->entry_map = &map_forest_03;
		global_data_ptr->bg_track = &music_items::bg_avalon;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {6, 2};
		global_data_ptr->ginger_position = {6, 1};
		return NEW_MAP;
		break;
	}
	case 122:
	{
		if (global_data_ptr->action_iterations[122] == 0) { ch_man.load(&final_msg); global_data_ptr->action_iterations[122] += 1; } else
		{ };
		break;
	}
	case 125:
	{
		if (global_data_ptr->action_iterations[125] == 0) { ch_man.load(&captive_01); global_data_ptr->action_iterations[125] += 1; } else
		{ };
		break;
	}
	case 126:
	{
		if (global_data_ptr->action_iterations[126] == 0) { ch_man.load(&togore_01); global_data_ptr->action_iterations[126] += 1; } else
		{ };
		break;
	}
	case 127:
	{
		global_data_ptr->entry_map = &map_cave_05;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {14, 14};
		global_data_ptr->ginger_position = {15, 14};
		return NEW_MAP;
		break;
	}
	case 128:
	{
		global_data_ptr->entry_map = &map_cave_05;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 9};
		global_data_ptr->ginger_position = {5, 9};
		return NEW_MAP;
		break;
	}
	case 129:
	{
		global_data_ptr->entry_map = &map_forest_03_attack;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {25, 16};
		global_data_ptr->ginger_position = {26, 16};
		return NEW_MAP;
		break;
	}
	case 130:
	{
		if (global_data_ptr->action_iterations[130] == 0) { ch_man.load(&broken_avalon_00); global_data_ptr->action_iterations[130] += 1; } else
		{ };
		break;
	}
	case 139:
	{
		global_data_ptr->entry_map = &map_dark_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 1};
		global_data_ptr->ginger_position = {6, 1};
		return NEW_MAP;
		break;
	}
	case 140:
	{
		global_data_ptr->entry_map = &map_dark_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {14, 1};
		global_data_ptr->ginger_position = {13, 1};
		return NEW_MAP;
		break;
	}
	case 141:
	{
		global_data_ptr->entry_map = &map_dark_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {20, 1};
		global_data_ptr->ginger_position = {19, 1};
		return NEW_MAP;
		break;
	}
	case 143:
	{
		global_data_ptr->entry_map = &map_dark_01;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 22};
		global_data_ptr->ginger_position = {6, 22};
		return NEW_MAP;
		break;
	}
	case 144:
	{
		global_data_ptr->entry_map = &map_dark_01;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {14, 22};
		global_data_ptr->ginger_position = {13, 22};
		return NEW_MAP;
		break;
	}
	case 145:
	{
		global_data_ptr->entry_map = &map_dark_01;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {20, 22};
		global_data_ptr->ginger_position = {19, 22};
		return NEW_MAP;
		break;
	}
	case 146:
	{
		global_data_ptr->entry_map = &map_dark_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {17, 13};
		global_data_ptr->ginger_position = {16, 13};
		return NEW_MAP;
		break;
	}
	case 147:
	{
		global_data_ptr->entry_map = &map_dark_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {12, 3};
		global_data_ptr->ginger_position = {11, 3};
		return NEW_MAP;
		break;
	}
	case 152:
	{
		if (global_data_ptr->action_iterations[152] == 0) { ch_man.load(&dark_152); global_data_ptr->action_iterations[152] += 1; } else
		{ };
		break;
	}
	case 161:
	{
		if (global_data_ptr->action_iterations[161] == 0) { ch_man.load(&dark_talk); global_data_ptr->action_iterations[161] += 1; } else
		{ };
		break;
	}
	case 162:
	{
		global_data_ptr->entry_map = &map_dark_05;
		global_data_ptr->bg_track = &music_items::ambient_heartbeat;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 30};
		global_data_ptr->ginger_position = {1, 29};
		return NEW_MAP;
		break;
	}
	case 164:
	{
		if (global_data_ptr->action_iterations[164] == 0) { ch_man.load(&sebellus_01); global_data_ptr->action_iterations[164] += 1; } else
		{ };
		break;
	}
	case 166:
	{
		if (global_data_ptr->action_iterations[166] == 0) { ch_man.load(&sebellus_02); global_data_ptr->action_iterations[166] += 1; } else
		{ };
		break;
	}
	case 171:
	{
		global_data_ptr->entry_map = &map_room_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 6};
		return NEW_MAP;
		break;
	}
	case 172:
	{
		global_data_ptr->entry_map = &map_room_05;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 8};
		return NEW_MAP;
		break;
	}
	case 173:
	{
		global_data_ptr->entry_map = &map_room_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 4};
		return NEW_MAP;
		break;
	}
	case 176:
	{
		global_data_ptr->entry_map = &map_room_garden;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {6, 10};
		return NEW_MAP;
		break;
	}
	case 177:
	{
		if (global_data_ptr->action_iterations[177] == 0) { ch_man.load(&talk_177); global_data_ptr->action_iterations[177] += 1; } else
		{ };
		break;
	}
	case 178:
	{
		global_data_ptr->entry_map = &map_room_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {16, 6};
		return NEW_MAP;
		break;
	}
	case 179:
	{
		global_data_ptr->entry_map = &map_room_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {7, 4};
		return NEW_MAP;
		break;
	}
	case 183:
	{
		global_data_ptr->entry_map = &map_room_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {12, 4};
		return NEW_MAP;
		break;
	}
	case 185:
	{
		global_data_ptr->entry_map = &map_room_05;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 2};
		return NEW_MAP;
		break;
	}
	case 186:
	{
		global_data_ptr->entry_map = &map_room_03;
		global_data_ptr->bg_track = &music_items::theme_anata;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {15, 4};
		return NEW_MAP;
		break;
	}
	case 189:
	{
		if (global_data_ptr->action_iterations[189] == 0) { ch_man.load(&talk_189); global_data_ptr->action_iterations[189] += 1; } else
		{ };
		break;
	}
	case 195:
	{
		global_data_ptr->entry_map = &map_room_06;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 5};
		return NEW_MAP;
		break;
	}
	case 196:
	{
		if (global_data_ptr->action_iterations[196] == 0) { ch_man.load(&wakeup_01); global_data_ptr->action_iterations[196] += 1; } else
		{ };
		break;
	}
	case 198:
	{
		global_data_ptr->entry_map = &map_room_02b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {13, 4};
		global_data_ptr->ginger_position = {15, 4};
		global_data_ptr->sebellus_position = {14, 6};
		return NEW_MAP;
		break;
	}
	case 199:
	{
		if (global_data_ptr->action_iterations[199] == 0) { ch_man.load(&have_to_go); global_data_ptr->action_iterations[199] += 1; } else
		{ };
		break;
	}
	case 200:
	{
		global_data_ptr->entry_map = &map_room_03b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 5};
		global_data_ptr->ginger_position = {2, 5};
		global_data_ptr->sebellus_position = {1, 4};
		return NEW_MAP;
		break;
	}
	case 201:
	{
		global_data_ptr->entry_map = &map_room_garden_b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {6, 10};
		global_data_ptr->ginger_position = {5, 10};
		global_data_ptr->sebellus_position = {4, 10};
		return NEW_MAP;
		break;
	}
	case 202:
	{
		global_data_ptr->entry_map = &map_room_hallway;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 9};
		global_data_ptr->ginger_position = {2, 10};
		global_data_ptr->sebellus_position = {1, 10};
		return NEW_MAP;
		break;
	}
	case 203:
	{
		if (global_data_ptr->action_iterations[203] == 0) { ch_man.load(&have_to_go_2); global_data_ptr->action_iterations[203] += 1; } else
		{ };
		break;
	}
	case 204:
	{
		global_data_ptr->entry_map = &map_room_basement;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {12, 9};
		global_data_ptr->ginger_position = {12, 10};
		global_data_ptr->sebellus_position = {11, 10};
		return NEW_MAP;
		break;
	}
	case 205:
	{
		if (global_data_ptr->action_iterations[205] == 0) { ch_man.load(&have_to_go_3); global_data_ptr->action_iterations[205] += 1; } else
		{ };
		break;
	}
	case 208:
	{
		global_data_ptr->entry_map = &map_beach_cave;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {6, 3};
		global_data_ptr->ginger_position = {6, 4};
		global_data_ptr->sebellus_position = {5, 5};
		return NEW_MAP;
		break;
	}
	case 209:
	{
		global_data_ptr->entry_map = &map_beach_02b;
		global_data_ptr->bg_track = &music_items::forest_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {20, 2};
		global_data_ptr->ginger_position = {20, 3};
		global_data_ptr->sebellus_position = {20, 4};
		return NEW_MAP;
		break;
	}
	case 211:
	{
		global_data_ptr->entry_map = &map_to_flay_01;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {28, 21};
		global_data_ptr->ginger_position = {28, 22};
		global_data_ptr->sebellus_position = {27, 22};
		return NEW_MAP;
		break;
	}
	case 212:
	{
		global_data_ptr->entry_map = &map_to_flay_01b;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 13};
		global_data_ptr->ginger_position = {3, 13};
		global_data_ptr->sebellus_position = {2, 13};
		return NEW_MAP;
		break;
	}
	case 213:
	{
		global_data_ptr->entry_map = &map_to_flay_01;
		global_data_ptr->bg_track = &music_items::forest_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {11, 18};
		global_data_ptr->ginger_position = {12, 18};
		global_data_ptr->sebellus_position = {13, 18};
		return NEW_MAP;
		break;
	}
	case 215:
	{
		global_data_ptr->entry_map = &map_to_flay_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 3};
		global_data_ptr->ginger_position = {1, 3};
		global_data_ptr->sebellus_position = {1, 3};
		return NEW_MAP;
		break;
	}
	case 216:
	{
		if (global_data_ptr->action_iterations[216] == 0) { ch_man.load(&ghost_01); global_data_ptr->action_iterations[216] += 1; } else
		{ };
		break;
	}
	case 218:
	{
		global_data_ptr->entry_map = &map_flayithro_01;
		global_data_ptr->bg_track = &music_items::bg_flayithro;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 4};
		global_data_ptr->ginger_position = {2, 4};
		global_data_ptr->sebellus_position = {1, 4};
		return NEW_MAP;
		break;
	}
	case 219:
	{
		global_data_ptr->entry_map = &map_flayithro_02;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {8, 14};
		global_data_ptr->ginger_position = {7, 14};
		global_data_ptr->sebellus_position = {6, 14};
		return NEW_MAP;
		break;
	}
	case 220:
	{
		global_data_ptr->entry_map = &map_flayithro_01;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {19, 2};
		global_data_ptr->ginger_position = {18, 2};
		global_data_ptr->sebellus_position = {17, 2};
		return NEW_MAP;
		break;
	}
	case 221:
	{
		global_data_ptr->entry_map = &map_flayithro_shop;
		global_data_ptr->bg_track = &music_items::shop;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 22};
		global_data_ptr->ginger_position = {1, 22};
		global_data_ptr->sebellus_position = {1, 21};
		return NEW_MAP;
		break;
	}
	case 222:
	{
		global_data_ptr->entry_map = &map_flayithro_01;
		global_data_ptr->bg_track = &music_items::bg_flayithro;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {11, 21};
		global_data_ptr->ginger_position = {10, 21};
		global_data_ptr->sebellus_position = {9, 21};
		return NEW_MAP;
		break;
	}
	case 223:
	{
		global_data_ptr->entry_map = &map_flayithro_soup;
		global_data_ptr->bg_track = &music_items::z02_the_champ;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 6};
		global_data_ptr->ginger_position = {4, 6};
		global_data_ptr->sebellus_position = {5, 6};
		return NEW_MAP;
		break;
	}
	case 228:
	{
		if (global_data_ptr->action_iterations[228] == 0) { ch_man.load(&boutique_01); global_data_ptr->action_iterations[228] += 1; } else
		{ };
		break;
	}
	case 229:
	{
		global_data_ptr->entry_map = &map_flayithro_hotel;
		global_data_ptr->bg_track = &music_items::bg_hotel;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 22};
		global_data_ptr->ginger_position = {3, 22};
		global_data_ptr->sebellus_position = {2, 22};
		return NEW_MAP;
		break;
	}
	case 230:
	{
		global_data_ptr->entry_map = &map_flayithro_01;
		global_data_ptr->bg_track = &music_items::bg_flayithro;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {30, 20};
		global_data_ptr->ginger_position = {31, 20};
		global_data_ptr->sebellus_position = {31, 21};
		return NEW_MAP;
		break;
	}
	case 224:
	{
		global_data_ptr->entry_map = &map_flayithro_01;
		global_data_ptr->bg_track = &music_items::bg_flayithro;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {24, 14};
		global_data_ptr->ginger_position = {25, 14};
		global_data_ptr->sebellus_position = {26, 14};
		return NEW_MAP;
		break;
	}
	case 233:
	{
		if (global_data_ptr->action_iterations[233] == 0) { ch_man.load(&ack_01); global_data_ptr->action_iterations[233] += 1; } else
		{ };
		break;
	}
	case 236:
	{
		global_data_ptr->entry_map = &map_flayithro_hotel_night;
		global_data_ptr->bg_track = &music_items::bg_hotel;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 5};
		return NEW_MAP;
		break;
	}
	case 238:
	{
		if (global_data_ptr->action_iterations[238] == 0) { ch_man.load(&dock_ginger_01); global_data_ptr->action_iterations[238] += 1; } else
		{ };
		break;
	}
	case 239:
	{
		if (global_data_ptr->action_iterations[239] == 0) { ch_man.load(&dock_sebellus_01); global_data_ptr->action_iterations[239] += 1; } else
		{ };
		break;
	}
	case 237:
	{
		global_data_ptr->entry_map = &map_flayithro_01_night;
		global_data_ptr->bg_track = &music_items::bg_sorry;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {30, 20};
		return NEW_MAP;
		break;
	}
	case 244:
	{
		if (global_data_ptr->action_iterations[244] == 0) { ch_man.load(&vista_bar); global_data_ptr->action_iterations[244] += 1; } else
		{ };
		break;
	}
	case 241:
	{
		global_data_ptr->entry_map = &map_train_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {52, 2};
		return NEW_MAP;
		break;
	}
	case 245:
	{
		global_data_ptr->entry_map = &map_train_room_03;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 6};
		return NEW_MAP;
		break;
	}
	case 248:
	{
		global_data_ptr->entry_map = &map_train_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {46, 2};
		return NEW_MAP;
		break;
	}
	case 249:
	{
		global_data_ptr->entry_map = &map_train_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {40, 2};
		return NEW_MAP;
		break;
	}
	case 250:
	{
		global_data_ptr->entry_map = &map_train_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {34, 2};
		return NEW_MAP;
		break;
	}
	case 253:
	{
		global_data_ptr->entry_map = &map_train_01;
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {58, 2};
		return NEW_MAP;
		break;
	}
	case 254:
	{
		ch_man.load(&train_arrive);
		break;
	}
	case 259:
	{
		global_data_ptr->entry_map = &map_to_canter_02;
		global_data_ptr->bg_track = &music_items::bg_canter_02;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 3};
		return NEW_MAP;
		break;
	}
	case 261:
	{
		global_data_ptr->entry_map = &map_canter_cathedral;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 4};
		return NEW_MAP;
		break;
	}
	case 262:
	{
		music_items::bg_hotel.play();
		if (global_data_ptr->action_iterations[262] == 0) { ch_man.load(&matt_01); global_data_ptr->action_iterations[262] += 1; } else
		{ };
		break;
	}
	case 264:
	{
		if (global_data_ptr->action_iterations[264] == 0) { ch_man.load(&k_door_01); global_data_ptr->action_iterations[264] += 1; } else
		{ };
		break;
	}
	case 263:
	{
		if (global_data_ptr->action_iterations[263] == 0) { ch_man.load(&kiara_01); global_data_ptr->action_iterations[263] += 1; } else
		{ };
		break;
	}
	case 267:
	{
		global_data_ptr->entry_map = &map_lab_06;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 8};
		global_data_ptr->kiara_position = {4, 8};
		return NEW_MAP;
		break;
	}
	case 269:
	{
		global_data_ptr->entry_map = &map_lab_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 2};
		global_data_ptr->kiara_position = {2, 2};
		return NEW_MAP;
		break;
	}
	case 270:
	{
		global_data_ptr->entry_map = &map_lab_05;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 8};
		global_data_ptr->kiara_position = {4, 8};
		return NEW_MAP;
		break;
	}
	case 271:
	{
		global_data_ptr->entry_map = &map_lab_04;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {21, 2};
		global_data_ptr->kiara_position = {22, 2};
		return NEW_MAP;
		break;
	}
	case 277:
	{
		if (global_data_ptr->action_iterations[277] == 0) { ch_man.load(&kiara_door); global_data_ptr->action_iterations[277] += 1; } else
		{ };
		break;
	}
	case 278:
	{
		if (global_data_ptr->action_iterations[278] == 0) { ch_man.load(&cutscene_04); global_data_ptr->action_iterations[278] += 1; } else
		{ };
		break;
	}
	case 279:
	{
		if (global_data_ptr->action_iterations[279] == 0) { ch_man.load(&cutscene_05); global_data_ptr->action_iterations[279] += 1; } else
		{ };
		break;
	}
	case 280:
	{
		if (global_data_ptr->action_iterations[280] == 0) { ch_man.load(&cutscene_06); global_data_ptr->action_iterations[280] += 1; } else
		{ };
		break;
	}
	case 281:
	{
		if (global_data_ptr->action_iterations[281] == 0) { ch_man.load(&cutscene_07b); global_data_ptr->action_iterations[281] += 1; } else
		{ };
		break;
	}
	case 282:
	{
		if (global_data_ptr->action_iterations[282] == 0) { ch_man.load(&cutscene_08); global_data_ptr->action_iterations[282] += 1; } else
		{ };
		break;
	}
	case 283:
	{
		if (global_data_ptr->action_iterations[283] == 0) { ch_man.load(&cutscene_08b); global_data_ptr->action_iterations[283] += 1; } else
		{ };
		break;
	}
	case 284:
	{
		if (global_data_ptr->action_iterations[284] == 0) { ch_man.load(&cutscene_08c); global_data_ptr->action_iterations[284] += 1; } else
		{ };
		break;
	}
	case 285:
	{
		if (global_data_ptr->action_iterations[285] == 0) { ch_man.load(&c09_init); global_data_ptr->action_iterations[285] += 1; } else
		{ };
		break;
	}
	case 293:
	{
		if (global_data_ptr->action_iterations[293] == 0) { ch_man.load(&cutscene_09); global_data_ptr->action_iterations[293] += 1; } else
		{ };
		break;
	}
	case 302:
	{
		global_data_ptr->entry_map = &map_castle_bonus;
		global_data_ptr->bg_track = &music_items::bg_sorry;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {2, 2};
		return NEW_MAP;
		break;
	}
	case 305:
	{
		global_data_ptr->entry_map = &map_castle_secret_garden;
		global_data_ptr->bg_track = &music_items::ambient_birds;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {6, 2};
		return NEW_MAP;
		break;
	}
	case 310:
	{
		if (global_data_ptr->action_iterations[310] == 0) { ch_man.load(&sans_01); global_data_ptr->action_iterations[310] += 1; } else
		{ };
		break;
	}
	case 311:
	{
		if (global_data_ptr->action_iterations[311] == 0) { ch_man.load(&sans_02); global_data_ptr->action_iterations[311] += 1; } else
		{ };
		break;
	}
	case 312:
	{
		if (global_data_ptr->action_iterations[312] == 0) { ch_man.load(&sans_03); global_data_ptr->action_iterations[312] += 1; } else
		{ };
		break;
	}
	case 313:
	{
		if (global_data_ptr->action_iterations[313] == 0) { ch_man.load(&sans_04); global_data_ptr->action_iterations[313] += 1; } else
		{ };
		break;
	}
	case 314:
	{
		if (global_data_ptr->action_iterations[314] == 0) { ch_man.load(&sans_05); global_data_ptr->action_iterations[314] += 1; } else
		{ };
		break;
	}
	case 258:
	{
		music_items::intro.play();
		if (global_data_ptr->action_iterations[258] == 0) { ch_man.load(&canter_01); global_data_ptr->action_iterations[258] += 1; } else
		{ };
		break;
	}
	case 26:
	{
		if (global_data_ptr->action_iterations[26] == 0) { ch_man.load(&garbage_06); global_data_ptr->action_iterations[26] += 1; } else
		if (global_data_ptr->action_iterations[26] == 1) { ch_man.load(&garbage_06b); global_data_ptr->action_iterations[26] += 1; } else
		{ };
		break;
	}
	case 167:
	{
		global_data_ptr->entry_map = &map_dark_07;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 13};
		global_data_ptr->ginger_position = {1, 12};
		global_data_ptr->sebellus_position = {1, 11};
		return NEW_MAP;
		break;
	}
	case 321:
	{
		global_data_ptr->entry_map = &map_dark_05b;
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {14, 3};
		global_data_ptr->ginger_position = {14, 4};
		global_data_ptr->sebellus_position = {14, 5};
		return NEW_MAP;
		break;
	}
	case 323:
	{
		global_data_ptr->entry_map = &map_beach_01;
		global_data_ptr->bg_track = &music_items::intro_guitar;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {27, 4};
		global_data_ptr->ginger_position = {26, 4};
		global_data_ptr->sebellus_position = {25, 4};
		return NEW_MAP;
		break;
	}
	case 324:
	{
		global_data_ptr->entry_map = &map_tunnel_01;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 14};
		global_data_ptr->ginger_position = {2, 15};
		global_data_ptr->sebellus_position = {1, 15};
		return NEW_MAP;
		break;
	}
	case 81:
	{
		if (global_data_ptr->action_iterations[81] == 0) { ch_man.load(&avalon_01); global_data_ptr->action_iterations[81] += 1; } else
		{ };
		break;
	}
	case 332:
	{
		global_data_ptr->entry_map = &map_canter_01;
		global_data_ptr->bg_track = &music_items::bg_canter_02;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 20};
		return NEW_MAP;
		break;
	}
	case 48:
	{
		global_data_ptr->entry_map = &map_cave_02;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {3, 30};
		global_data_ptr->ginger_position = {2, 30};
		return NEW_MAP;
		break;
	}
	case 68:
	{
		global_data_ptr->entry_map = &map_cave_03;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {5, 23};
		global_data_ptr->ginger_position = {6, 23};
		return NEW_MAP;
		break;
	}
	case 83:
	{
		global_data_ptr->entry_map = &map_cave_04;
		global_data_ptr->bg_track = &music_items::cave_01;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {16, 3};
		global_data_ptr->ginger_position = {15, 3};
		return NEW_MAP;
		break;
	}
	case 84:
	{
		global_data_ptr->entry_map = &map_forest_02;
		global_data_ptr->bg_track = &music_items::ambient_wind;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_forest_01;
		global_data_ptr->jeremy_position = {2, 3};
		global_data_ptr->ginger_position = {1, 3};
		return NEW_MAP;
		break;
	}
	case 340:
	{
		if (global_data_ptr->action_iterations[340] == 0) { ch_man.load(&test_convo); global_data_ptr->action_iterations[340] += 1; } else
		{ };
		break;
	}
	case 339:
	{
		music_items::bg_channel.play();
		if (global_data_ptr->action_iterations[339] == 0) { ch_man.load(&chat_mcwebb_02); global_data_ptr->action_iterations[339] += 1; } else
		{ };
		break;
	}
	case 344:
	{
		if (global_data_ptr->action_iterations[344] == 0) { ch_man.load(&boutique_0); global_data_ptr->action_iterations[344] += 1; } else
		{ };
		break;
	}
	case 345:
	{
		global_data_ptr->entry_map = &map_canter_01;
		global_data_ptr->bg_track = &music_items::bg_canter_02;
		music::stop();
		global_data_ptr->bg = &regular_bg_items::big_bg_city_01;
		global_data_ptr->jeremy_position = {43, 3};
		return NEW_MAP;
		break;
	}
	case 347:
	{
		if (global_data_ptr->action_iterations[347] == 0) { ch_man.load(&henry_01); global_data_ptr->action_iterations[347] += 1; } else
		{ };
		break;
	}
	case 349:
	{
		if (global_data_ptr->action_iterations[349] == 0) { ch_man.load(&ending_lab_01); global_data_ptr->action_iterations[349] += 1; } else
		{ };
		break;
	}
	case 350:
	{
		if (global_data_ptr->action_iterations[350] == 0) { ch_man.load(&final_01c); global_data_ptr->action_iterations[350] += 1; } else
		{ };
		break;
	}
	case 351:
	{
		if (global_data_ptr->action_iterations[351] == 0) { ch_man.load(&final_01b); global_data_ptr->action_iterations[351] += 1; } else
		{ };
		break;
	}
	case 352:
	{
		if (global_data_ptr->action_iterations[352] == 0) { ch_man.load(&final_01d); global_data_ptr->action_iterations[352] += 1; } else
		{ };
		break;
	}
	case 353:
	{
		if (global_data_ptr->action_iterations[353] == 0) { ch_man.load(&ending_lab_01); global_data_ptr->action_iterations[353] += 1; } else
		{ };
		break;
	}
	case 354:
	{
		if (global_data_ptr->action_iterations[354] == 0) { ch_man.load(&death_01); global_data_ptr->action_iterations[354] += 1; } else
		{ };
		break;
	}
	case 356:
	{
		if (global_data_ptr->action_iterations[356] == 0) { ch_man.load(&final_03); global_data_ptr->action_iterations[356] += 1; } else
		{ };
		break;
	}
	case 131:
	{
		global_data_ptr->entry_map = &map_dark_01;
		global_data_ptr->bg_track = &music_items::bg_sorry;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {1, 11};
		global_data_ptr->ginger_position = {1, 10};
		return NEW_MAP;
		break;
	}
	case 252:
	{
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 4};
		if (global_data_ptr->action_iterations[252] == 0) { ch_man.load(&door_locked); global_data_ptr->action_iterations[252] += 1; } else
		{ };
		return NEW_MAP;
		break;
	}
	case 246:
	{
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 6};
		if (global_data_ptr->action_iterations[246] == 0) { ch_man.load(&door_locked); global_data_ptr->action_iterations[246] += 1; } else
		{ };
		return NEW_MAP;
		break;
	}
	case 247:
	{
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 6};
		if (global_data_ptr->action_iterations[247] == 0) { ch_man.load(&door_locked); global_data_ptr->action_iterations[247] += 1; } else
		{ };
		return NEW_MAP;
		break;
	}
	case 165:
	{
		global_data_ptr->entry_map = &map_dark_06;
		global_data_ptr->bg_track = &music_items::bg_sorry;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {2, 18};
		global_data_ptr->ginger_position = {1, 18};
		global_data_ptr->sebellus_position = {1, 19};
		return NEW_MAP;
		break;
	}
	case 358:
	{
		if (global_data_ptr->action_iterations[358] == 0) { ch_man.load(&convo_friend); global_data_ptr->action_iterations[358] += 1; } else
		{ };
		break;
	}
	case 359:
	{
		global_data_ptr->entry_map = &map_forest_05;
		global_data_ptr->bg_track = &music_items::bg_friend;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->jeremy_position = {4, 7};
		global_data_ptr->ginger_position = {5, 7};
		return NEW_MAP;
		break;
	}
	case 360:
	{
		if (global_data_ptr->action_iterations[360] == 0) { ch_man.load(&convo_friend_leave); global_data_ptr->action_iterations[360] += 1; } else
		{ };
		break;
	}
	case 361:
	{
		if (global_data_ptr->action_iterations[361] == 0) { ch_man.load(&skelly_01); global_data_ptr->action_iterations[361] += 1; } else
		{ };
		break;
	}
	case 362:
	{
		if (global_data_ptr->action_iterations[362] == 0) { ch_man.load(&homeless_01); global_data_ptr->action_iterations[362] += 1; } else
		{ };
		break;
	}
	case 367:
	{
		global_data_ptr->entry_map = &map_castle_02b;
		global_data_ptr->bg_track = &music_items::bg_sorry;
		music::stop();
		global_data_ptr->bg = nullptr;
		global_data_ptr->ginger_position = {41, 8};
		return NEW_MAP;
		break;
	}
	case 368:
	{
		if (global_data_ptr->action_iterations[368] == 0) { ch_man.load(&angel_01); global_data_ptr->action_iterations[368] += 1; } else
		{ };
		break;
	}
	}
	return -1;
}