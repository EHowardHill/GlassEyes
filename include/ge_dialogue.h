// ge_dialogue.h
// THIS IS AN AUTO-GENERATED FILE. DO NOT EDIT.

#ifndef GE_DIALOGUE_H
#define GE_DIALOGUE_H

#include "ge_text.h"
#include "ge_sprites.h"
#include "ge_animations.h"
#include "ge_variables.h"

#include "bn_regular_bg_item.h"

using namespace bn;

typedef const dialogue_line conversation[128];

#include "bn_sprite_items_db_ch_vista.h"
#include "bn_sprite_items_db_ch_visker.h"
#include "bn_sprite_items_db_ch_visker_wife.h"
#include "bn_sprite_items_db_ch_ginger.h"
#include "bn_sprite_items_db_ch_croke.h"
#include "bn_sprite_items_db_ch_temmie.h"
#include "bn_sprite_items_db_ch_deadguy.h"
#include "bn_sprite_items_db_ch_grandma.h"
#include "bn_sprite_items_db_ch_wormguy.h"
#include "bn_sprite_items_db_ch_courier.h"
#include "bn_sprite_items_db_ch_primary.h"
#include "bn_sprite_items_db_ch_doll.h"
#include "bn_sprite_items_db_ch_greyfriar.h"
#include "bn_sprite_items_db_ch_jelly.h"
#include "bn_sprite_items_db_ch_horsey.h"
#include "bn_sprite_items_db_ch_glompy.h"
#include "bn_sprite_items_db_ch_sneaker.h"
#include "bn_sprite_items_db_ch_tollman.h"
#include "bn_sprite_items_db_ch_robin.h"
#include "bn_sprite_items_db_ch_togore.h"
#include "bn_sprite_items_db_ch_sebellus.h"
#include "bn_sprite_items_db_ch_mcwebb.h"
#include "bn_sprite_items_db_ch_naomi.h"
#include "bn_sprite_items_db_ch_ghost.h"
#include "bn_sprite_items_db_ch_pringle.h"
#include "bn_sprite_items_db_ch_kathy.h"
#include "bn_sprite_items_db_ch_dima.h"
#include "bn_sprite_items_db_ch_ack.h"
#include "bn_sprite_items_db_ch_eggplant.h"
#include "bn_sprite_items_db_ch_vista_02.h"
#include "bn_regular_bg_items_scene_cabin01.h"
#include "bn_regular_bg_items_scene_berlin01.h"
#include "bn_regular_bg_items_scene_tv_02.h"
#include "bn_regular_bg_items_scene_tv_03.h"
#include "bn_regular_bg_items_scene_tv_04.h"
#include "bn_regular_bg_items_scene_tv_05.h"
#include "bn_regular_bg_items_scene_tv_01.h"

// Forward declarations for conversations
extern const conversation ack_01;
extern const conversation avalon_courier_01;
extern const conversation avalon_courier_02;
extern const conversation avalon_courier_03;
extern const conversation avalon_courier_03_alt_01;
extern const conversation avalon_courier_04;
extern const conversation avalon_grandma_01;
extern const conversation avalon_grandma_02;
extern const conversation avalon_guy_01;
extern const conversation avalon_guy_02;
extern const conversation avalon_shop_01;
extern const conversation avalon_shop_01_alt_02;
extern const conversation avalon_shop_01_alt_03;
extern const conversation avalon_shop_02;
extern const conversation avalon_sign_01;
extern const conversation avalon_sign_02;
extern const conversation avalon_sign_03;
extern const conversation avalon_sign_03_alt_01;
extern const conversation avalon_sign_03_alt_02;
extern const conversation avalon_sign_03_alt_03;
extern const conversation avalon_sign_03_alt_04;
extern const conversation avalon_sign_04;
extern const conversation avalon_sign_05;
extern const conversation avalon_sign_06;
extern const conversation avalon_wormguy_01;
extern const conversation avalon_wormguy_01_alt_01;
extern const conversation avalon_wormguy_02;
extern const conversation beach_sign;
extern const conversation bm_fridge;
extern const conversation boutique_01;
extern const conversation boutique_02;
extern const conversation boutique_03;
extern const conversation bridge_01;
extern const conversation broken_avalon_00;
extern const conversation broken_avalon_01;
extern const conversation broken_avalon_01_alt_01;
extern const conversation broken_avalon_02;
extern const conversation captive_01;
extern const conversation cave_01;
extern const conversation cave_01_alt_01;
extern const conversation cave_sign_01;
extern const conversation cave_sign_02;
extern const conversation chat_197;
extern const conversation chat_mcwebb;
extern const conversation chat_mcwebb_02;
extern const conversation chat_mcwebb_02_alt_01;
extern const conversation chat_mcwebb_03;
extern const conversation convo_obj_clothes;
extern const conversation convo_obj_document;
extern const conversation convo_obj_flint;
extern const conversation convo_obj_lime;
extern const conversation convo_obj_photograph;
extern const conversation convo_obj_pie;
extern const conversation convo_obj_soup;
extern const conversation convo_obj_steel;
extern const conversation convo_obj_sticks;
extern const conversation convo_obj_stones;
extern const conversation convo_obj_ticket;
extern const conversation convo_obj_water_bottle;
extern const conversation croke_01;
extern const conversation croke_01_alt_01;
extern const conversation croke_01_alt_02;
extern const conversation croke_02;
extern const conversation croke_03;
extern const conversation croke_04;
extern const conversation croke_05;
extern const conversation croke_05_alt_01;
extern const conversation dark_152;
extern const conversation dark_info;
extern const conversation dark_talk;
extern const conversation dark_talk_alt_01;
extern const conversation dark_talk_alt_02;
extern const conversation dark_talk_alt_03;
extern const conversation dark_talk_alt_04;
extern const conversation dart_01;
extern const conversation dart_02;
extern const conversation dart_03;
extern const conversation dart_04;
extern const conversation dima_01;
extern const conversation dima_02;
extern const conversation dock_ginger_01;
extern const conversation dock_ginger_02;
extern const conversation dock_ginger_alt_01;
extern const conversation dock_ginger_alt_02;
extern const conversation dock_sebellus_01;
extern const conversation dock_sebellus_01_alt_01;
extern const conversation dock_sebellus_01_alt_02;
extern const conversation dog_and_pony;
extern const conversation doll_guy_01;
extern const conversation eggplant_01;
extern const conversation eggplant_01_alt_01;
extern const conversation eggplant_01_alt_02;
extern const conversation f_cutscene_01;
extern const conversation f_cutscene_02;
extern const conversation f_cutscene_03;
extern const conversation f_cutscene_04;
extern const conversation fall_down;
extern const conversation final_msg;
extern const conversation flayithro_sign;
extern const conversation flayithro_sign_01;
extern const conversation forest_dlg_01;
extern const conversation forest_dlg_01_alt_01;
extern const conversation forest_dlg_02;
extern const conversation forest_dlg_03;
extern const conversation forest_dlg_paper;
extern const conversation forest_dlg_sign_01;
extern const conversation forest_dlg_sign_02;
extern const conversation forest_dlg_sign_02_alt_01;
extern const conversation garbage_01;
extern const conversation garbage_01_alt_01;
extern const conversation garbage_02;
extern const conversation garbage_02b;
extern const conversation garbage_03;
extern const conversation garbage_03_alt_01;
extern const conversation garbage_04;
extern const conversation garbage_04_alt_01;
extern const conversation garbage_04_alt_02;
extern const conversation garbage_05;
extern const conversation garbage_05b;
extern const conversation garbage_06;
extern const conversation garbage_06_alt_01;
extern const conversation garbage_06_alt_02;
extern const conversation garbage_06b;
extern const conversation garbage_fight_01;
extern const conversation garbage_fight_02;
extern const conversation garbage_fight_03;
extern const conversation garbage_fight_04;
extern const conversation garbage_fight_05;
extern const conversation garbage_sign01;
extern const conversation garbage_sign01b;
extern const conversation garbage_sign02;
extern const conversation garbage_sign03;
extern const conversation garbage_sign04;
extern const conversation garbage_sign05;
extern const conversation garbage_spare;
extern const conversation ghost_01;
extern const conversation ghost_01_alt_01;
extern const conversation ghost_01_alt_02;
extern const conversation have_to_go;
extern const conversation have_to_go_2;
extern const conversation have_to_go_3;
extern const conversation have_to_go_3_alt_01;
extern const conversation have_to_go_4;
extern const conversation hotel_01;
extern const conversation hotel_02;
extern const conversation hotel_bed_01;
extern const conversation hotel_bed_02;
extern const conversation hotel_bed_03;
extern const conversation hotel_bed_04;
extern const conversation hotel_bed_04_alt_01;
extern const conversation hotel_fridge;
extern const conversation hotel_room_01;
extern const conversation hotel_room_02;
extern const conversation hotel_room_03;
extern const conversation intro_01;
extern const conversation intro_02;
extern const conversation intro_03;
extern const conversation item_153;
extern const conversation item_155;
extern const conversation item_155b;
extern const conversation item_156;
extern const conversation item_157;
extern const conversation item_158;
extern const conversation item_168_alt_01;
extern const conversation item_banana_hat_01;
extern const conversation item_enoki_01;
extern const conversation item_lime_01;
extern const conversation item_none;
extern const conversation item_tire_01;
extern const conversation kathy_01;
extern const conversation lab_01;
extern const conversation lab_02;
extern const conversation lab_02b;
extern const conversation lab_03;
extern const conversation lab_03_alt_01;
extern const conversation lab_03_alt_02;
extern const conversation lab_04;
extern const conversation lab_05;
extern const conversation lab_05_alt_01;
extern const conversation lab_05_alt_02;
extern const conversation lab_05_alt_03;
extern const conversation lab_06;
extern const conversation lab_07;
extern const conversation lab_08;
extern const conversation leaving_lab;
extern const conversation leaving_lab_alt_01;
extern const conversation leaving_lab_alt_02;
extern const conversation leaving_lab_alt_03;
extern const conversation naomi_fortune_01;
extern const conversation naomi_fortune_01_alt_01;
extern const conversation new_berlin_sign;
extern const conversation pringle_01;
extern const conversation scruffys_01;
extern const conversation scruffys_01_alt_01;
extern const conversation scruffys_02;
extern const conversation scruffys_02_alt_01;
extern const conversation scruffys_03;
extern const conversation scruffys_04;
extern const conversation scruffys_04b;
extern const conversation scruffys_04c;
extern const conversation scruffys_05;
extern const conversation scruffys_05_alt_01;
extern const conversation scruffys_05b;
extern const conversation scruffys_06;
extern const conversation scruffys_06b;
extern const conversation scruffys_06b_alt_01;
extern const conversation sebellus_00;
extern const conversation sebellus_01;
extern const conversation sebellus_02;
extern const conversation sign_135;
extern const conversation sign_136;
extern const conversation sign_142;
extern const conversation sleep_01;
extern const conversation sleep_01_alt_01;
extern const conversation talk_151;
extern const conversation talk_151_alt_01;
extern const conversation talk_151_alt_02;
extern const conversation talk_168;
extern const conversation talk_175;
extern const conversation talk_177;
extern const conversation talk_177_alt_01;
extern const conversation talk_177_alt_02;
extern const conversation talk_177a;
extern const conversation talk_177a_alt_01;
extern const conversation talk_184;
extern const conversation talk_189;
extern const conversation talk_190;
extern const conversation talk_190b;
extern const conversation teddy_spare01;
extern const conversation temmie_01;
extern const conversation temmie_02;
extern const conversation temmie_03;
extern const conversation temmie_04;
extern const conversation temmie_05;
extern const conversation temmie_06;
extern const conversation temmie_07;
extern const conversation temmie_sign;
extern const conversation test_convo;
extern const conversation togore_01;
extern const conversation tollhouse_01;
extern const conversation tollhouse_01b;
extern const conversation train_arrive;
extern const conversation train_ginger;
extern const conversation train_locked;
extern const conversation train_mirror;
extern const conversation train_sebellus;
extern const conversation tunnel_01;
extern const conversation vf_01;
extern const conversation vf_02;
extern const conversation vf_03;
extern const conversation vf_04;
extern const conversation visker_final;
extern const conversation visker_final_02;
extern const conversation visker_final_03;
extern const conversation visker_final_alt_01;
extern const conversation visker_h_01;
extern const conversation visker_h_02;
extern const conversation visker_h_03;
extern const conversation vista_01;
extern const conversation vista_01_alt_01;
extern const conversation vista_bar;
extern const conversation wakeup_01;
extern const conversation worm_action_01;
extern const conversation worm_action_01_alt_01;

#endif // GE_DIALOGUE_H
