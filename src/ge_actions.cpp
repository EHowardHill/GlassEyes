#include "bn_log.h"
#include "bn_music.h"
#include "bn_music_items.h"

#include "ge_globals.h"
#include "ge_sprites.h"
#include "ge_maps.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_map_data.h"
#include "ge_actions.h"

static vector_2 previous_tile = {-1, -1};
static bool action_triggered = false;
static bool buffer_active = false;

bool is_interactive(int action)
{
    for (int t = 0; t < 999; t++)
    {
        if (is_interactive_array[t] == -1)
        {
            return false;
        }
        else if (is_interactive_array[t] == action)
        {
            return true;
        }
    }
    return false;
}

int action_listener(map_manager *man, character_manager *ch_man)
{
    if (!ch_man->db.has_value())
    {
        auto chara_ptr = ch_man->player_ptr;
        vector_2 current_position = chara_ptr->v_sprite.bounds.position;

        // Calculate current tile coordinates
        vector_2 current_tile = {
            current_position.x / 32,
            current_position.y / 32};

        // Check if we've moved to a new tile
        bool new_tile = (previous_tile.x != current_tile.x ||
                         previous_tile.y != current_tile.y);

        // Get the action for current position
        int action = man->action(current_position);

        // Reset action_triggered flag when entering a new tile
        if (new_tile)
        {
            action_triggered = false;
            previous_tile = current_tile;

            if (action != 0 && !is_interactive(action))
            {
                global_data_ptr->action_iterations[action]++;
            }
        }

        if (is_interactive(action) && keypad::a_pressed() && !buffer_active)
        {
            global_data_ptr->action_iterations[action]++;
            buffer_active = true;

            switch (action)
            {
            case CONVO_GARBAGE_SIGN01:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_SIGN01] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_sign01);
                    ch_man->db->init(ch_man);
                }
                else if (global_data_ptr->action_iterations[CONVO_GARBAGE_SIGN01] == 2)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_sign01b);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_VISKER_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&garbage_sign02);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_GARBAGE_03_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&garbage_sign03);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_VISKER_AFTER_FIGHT:
            {
                ch_man->db.emplace();
                ch_man->db->load(&garbage_05b);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_GARBAGE_04_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&garbage_sign04);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_GARBAGE_05_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&garbage_sign05);
                ch_man->db->init(ch_man);
                break;
            }
            case LAB_COMPUTER:
            {
                ch_man->db.emplace();
                ch_man->db->load(&lab_03);
                ch_man->db->init(ch_man);
                break;
            }

            case CONVO_FOREST_01_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&forest_dlg_sign_01);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_FOREST_02_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&forest_dlg_sign_02);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_FOREST_03_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&forest_dlg_sign_02);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_COWBEMMIE_01_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_sign);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_01:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_01);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_02:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_02);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_03:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_03);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_04:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_04);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_05:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_05);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_06:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_06);
                ch_man->db->init(ch_man);
                break;
            }
            case TEMMIE_07:
            {
                ch_man->db.emplace();
                ch_man->db->load(&temmie_07);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_CAVE_02_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&cave_sign_01);
                ch_man->db->init(ch_man);
                break;
            }
            case CAVE_04_SIGN:
            {
                ch_man->db.emplace();
                ch_man->db->load(&cave_sign_02);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_01:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_01);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_02:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_02);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_VISTA:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_03);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_03:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_04);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_04:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_05);
                ch_man->db->init(ch_man);
                break;
            }
            case AVALON_SIGN_05:
            {
                ch_man->db.emplace();
                ch_man->db->load(&avalon_sign_06);
                ch_man->db->init(ch_man);
                break;
            }
            case CHAT_NOODLE:
            {
                if (global_data_ptr->action_iterations[CHAT_NOODLE] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_guy_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_guy_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_GRANDMA:
            {
                if (global_data_ptr->action_iterations[CHAT_GRANDMA] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_grandma_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_grandma_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_COURIER:
            {
                if (global_data_ptr->action_iterations[CHAT_COURIER] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_courier_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_courier_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_WORMGUY:
            {
                if (global_data_ptr->action_iterations[CHAT_WORMGUY] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_wormguy_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_wormguy_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_DOLL:
            {
                if (global_data_ptr->action_iterations[CHAT_DOLL] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&doll_guy_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case BUY_TIRE:
            {
                if (global_data_ptr->action_iterations[BUY_TIRE] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&item_tire_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case BUY_ENOKI:
            {
                if (global_data_ptr->action_iterations[BUY_ENOKI] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&item_enoki_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case BUY_LIME:
            {
                if (global_data_ptr->action_iterations[BUY_LIME] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&item_lime_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_PRIMARY:
            {
                if (global_data_ptr->action_iterations[CHAT_PRIMARY] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_shop_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&avalon_shop_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case NEW_BERLIN_SIGN:
            {
                global_data_ptr->process_stage = NEW_BERLIN;
                return NEW_CHAPTER;
            }
            case CHAT_GOAT:
            {
                if (global_data_ptr->action_iterations[CHAT_GOAT] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_BEAR:
            {
                if (global_data_ptr->action_iterations[CHAT_BEAR] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_HORSE:
            {
                if (global_data_ptr->action_iterations[CHAT_HORSE] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_03);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_BIRB:
            {
                if (global_data_ptr->action_iterations[CHAT_BIRB] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_04);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_SNEAKER:
            {
                if (global_data_ptr->action_iterations[CHAT_SNEAKER] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_05);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CHAT_ROBIN:
            {
                if (global_data_ptr->action_iterations[CHAT_ROBIN] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_06);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&scruffys_06b);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case JUKEBOX_01:
            {
                music::stop();
                music_items::shop.play();
                break;
            }
            case CHAT_TOLLHOUSE:
            {
                if (global_data_ptr->action_iterations[CHAT_TOLLHOUSE] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&tollhouse_01);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&tollhouse_01b);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else if (action != 0 && !action_triggered)
        {
            action_triggered = true; // Mark as triggered

            switch (action)
            {
            case CONVO_SCENE_1:
            {
                ch_man->db.emplace();
                ch_man->db->load(&test_convo);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_GARBAGE_1:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_1] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_GARBAGE_2:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_2] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_GARBAGE_3:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_3] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_03);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_GARBAGE_02:
            {
                global_data_ptr->entry_map = &map_garbage_02;
                global_data_ptr->entry_position = {2, 6};
                return NEW_MAP;
                break;
            }
            case TO_GARBAGE_02b:
            {
                global_data_ptr->entry_map = &map_garbage_02;
                global_data_ptr->entry_position = {13, 2};
                return NEW_MAP;
                break;
            }
            case TO_VISKERS_HOUSE:
            {
                global_data_ptr->entry_map = &map_viskers_house;
                global_data_ptr->entry_position = {3, 5};
                return NEW_MAP;
                break;
            }
            case CONVO_VISKER_BED:
            {
                if (global_data_ptr->action_iterations[CONVO_VISKER_BED] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&visker_h_03);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_VISKER_FOOD:
            {
                if (global_data_ptr->action_iterations[CONVO_VISKER_FOOD] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&visker_h_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_VISKER_NIGHTSTAND:
            {
                if (global_data_ptr->action_iterations[CONVO_VISKER_NIGHTSTAND] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&visker_h_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_GARBAGE_03:
            {
                global_data_ptr->entry_map = &map_garbage_03;
                global_data_ptr->entry_position = {1, 3};
                return NEW_MAP;
                break;
            }
            case CONVO_VISKER_FIGHT:
            {
                if (global_data_ptr->action_iterations[CONVO_VISKER_FIGHT] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_04);
                    ch_man->db->init(ch_man);
                }
                else if (global_data_ptr->action_iterations[CONVO_VISKER_FIGHT] == 2)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_05);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_GARBAGE_04:
            {
                global_data_ptr->entry_map = &map_garbage_04;
                global_data_ptr->entry_position = {29, 4};
                return NEW_MAP;
                break;
            }
            case GARBAGE_04_EXIT_01:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_04_SIGN] == 0)
                {
                    global_data_ptr->entry_map = &map_garbage_03;
                    global_data_ptr->entry_position = {2, 8};
                    return NEW_MAP;
                }
                else
                {
                    global_data_ptr->entry_map = &map_garbage_05;
                    global_data_ptr->entry_position = {4, 45};
                    return NEW_MAP;
                }
                break;
            }
            case GARBAGE_04_EXIT_02:
            {
                global_data_ptr->entry_map = &map_garbage_04;
                global_data_ptr->entry_position = {10, 12};
                return NEW_MAP;
                break;
            }
            case GARBAGE_04_EXIT_03:
            {
                global_data_ptr->entry_map = &map_garbage_04;
                global_data_ptr->entry_position = {2, 20};
                return NEW_MAP;
                break;
            }
            case GARBAGE_04_EXIT_04:
            {
                global_data_ptr->entry_map = &map_garbage_04;
                global_data_ptr->entry_position = {29, 12};
                return NEW_MAP;
                break;
            }
            case GARBAGE_04_EXIT_05:
            {
                global_data_ptr->entry_map = &map_garbage_04;
                global_data_ptr->entry_position = {29, 20};
                return NEW_MAP;
                break;
            }
            case EXIT_GARBAGE_01:
            {
                ch_man->music_fadeout = true;
                break;
            }
            case CONVO_GARBAGE_FINAL_01:
            {
                if (global_data_ptr->action_iterations[CONVO_GARBAGE_FINAL_01] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_06);
                    ch_man->db->init(ch_man);
                }
                else
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&garbage_06b);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_LAB_RUG:
            {
                if (global_data_ptr->action_iterations[CONVO_LAB_RUG] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case LAB_BED:
            {
                if (global_data_ptr->action_iterations[LAB_BED] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_02);
                    ch_man->db->init(ch_man);
                }
                else if (global_data_ptr->action_iterations[LAB_BED] == 2)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_02b);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_LAB_GINGER:
            {
                if (global_data_ptr->action_iterations[CONVO_LAB_GINGER] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_05);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case LAB_DOOR:
            {
                if (global_data_ptr->action_iterations[LAB_DOOR] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_06);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case LAB_FRIDGE:
            {
                if (global_data_ptr->action_iterations[LAB_FRIDGE] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_07);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case LAB_LOCKER:
            {
                if (global_data_ptr->action_iterations[LAB_LOCKER] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&lab_08);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_LAB_OUTSIDE:
            {
                ch_man->db.emplace();
                ch_man->db->load(&leaving_lab);
                ch_man->db->init(ch_man);
                break;
            }
            case CONVO_FOREST_01:
            {
                if (global_data_ptr->action_iterations[CONVO_FOREST_01] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&forest_dlg_02);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_FOREST_02:
            {
                if (global_data_ptr->action_iterations[CONVO_FOREST_02] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&forest_dlg_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_FOREST_03:
            {
                if (global_data_ptr->action_iterations[CONVO_FOREST_02] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&forest_dlg_03);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case CONVO_CROKE_01:
            {
                if (global_data_ptr->action_iterations[CONVO_CROKE_01] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&croke_01);
                    ch_man->db->init(ch_man);
                }
                else if (global_data_ptr->action_iterations[CONVO_CROKE_01] == 2)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&croke_05);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_CAVE_01:
            {
                global_data_ptr->entry_map = &map_cave_01;
                global_data_ptr->entry_position = {7, 12};
                global_data_ptr->ginger_position = {6, 12};
                global_data_ptr->bg_track = nullptr;
                music::stop();
                return NEW_MAP;
                break;
            }
            case FROM_CAVE_01:
            {
                global_data_ptr->entry_map = &map_forest_01;
                global_data_ptr->entry_position = {67, 3};
                global_data_ptr->ginger_position = {66, 3};
                global_data_ptr->bg_track = &music_items::forest_01;
                music::stop();
                return NEW_MAP;
                break;
            }
            case CONVO_CAVE_01:
            {
                if (global_data_ptr->action_iterations[CONVO_CAVE_01] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&cave_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case TO_CAVE_02:
            {
                global_data_ptr->entry_map = &map_cave_02;
                global_data_ptr->entry_position = {3, 30};
                global_data_ptr->ginger_position = {2, 30};
                return NEW_MAP;
                break;
            }
            case FOREST_01_SETUP:
            {
                auto croke = ch_man->find_by_index(CHAR_CROKE);
                if (croke != nullptr)
                {
                    ch_man->remove_character(croke);
                }
                break;
            }
            case CONVO_BRIDGE_02:
            {
                if (global_data_ptr->action_iterations[CONVO_BRIDGE_02] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&bridge_01);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case ENTER_BG:
            {
                if (man->bg_ptr.has_value())
                {
                    man->bg_ptr.value().set_visible(true);
                }
                break;
            }
            case EXIT_BG:
            {
                if (man->bg_ptr.has_value())
                {
                    man->bg_ptr.value().set_visible(false);
                }
                break;
            }
            case TO_FOREST_02:
            {
                global_data_ptr->entry_map = &map_forest_01;
                global_data_ptr->entry_position = {105, 3};
                global_data_ptr->ginger_position = {104, 3};
                return NEW_MAP;
                break;
            }
            case ACT_55:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {19, 30};
                global_data_ptr->ginger_position = {20, 30};
                return NEW_MAP;
                break;
            }
            case ACT_56:
            {
                global_data_ptr->entry_map = &map_cave_02;
                global_data_ptr->entry_position = {28, 3};
                global_data_ptr->ginger_position = {29, 3};
                return NEW_MAP;
                break;
            }
            case ACT_57:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {16, 4};
                global_data_ptr->ginger_position = {15, 4};
                return NEW_MAP;
                break;
            }
            case ACT_58:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {16, 16};
                global_data_ptr->ginger_position = {15, 16};
                return NEW_MAP;
                break;
            }
            case ACT_59:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {30, 19};
                global_data_ptr->ginger_position = {31, 19};
                return NEW_MAP;
                break;
            }
            case ACT_60:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {29, 3};
                global_data_ptr->ginger_position = {30, 3};
                return NEW_MAP;
                break;
            }
            case ACT_61:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {12, 11};
                global_data_ptr->ginger_position = {11, 11};
                return NEW_MAP;
                break;
            }
            case ACT_62:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {12, 21};
                global_data_ptr->ginger_position = {11, 21};
                return NEW_MAP;
                break;
            }
            case ACT_63:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {4, 3};
                global_data_ptr->ginger_position = {5, 3};
                return NEW_MAP;
                break;
            }
            case ACT_64:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {28, 11};
                global_data_ptr->ginger_position = {29, 11};
                return NEW_MAP;
                break;
            }
            case ACT_65:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {2, 24};
                global_data_ptr->ginger_position = {2, 23};
                return NEW_MAP;
                break;
            }
            case ACT_66:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {13, 8};
                global_data_ptr->ginger_position = {13, 7};
                return NEW_MAP;
                break;
            }
            case ACT_67:
            {
                global_data_ptr->entry_map = &map_cave_cowbemmie;
                global_data_ptr->entry_position = {2, 3};
                global_data_ptr->ginger_position = {1, 3};
                global_data_ptr->bg_track = &music_items::bg_dixieland;
                music::stop();
                return NEW_MAP;
                break;
            }
            case ACT_68:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {5, 23};
                global_data_ptr->ginger_position = {6, 23};
                global_data_ptr->bg_track = &music_items::forest_01;
                music::stop();
                return NEW_MAP;
                break;
            }
            case BACK_TO_CAVE_03:
            {
                global_data_ptr->entry_map = &map_cave_03;
                global_data_ptr->entry_position = {5, 15};
                global_data_ptr->ginger_position = {4, 15};
                return NEW_MAP;
                break;
            }
            case TO_FOREST_02b:
            {
                global_data_ptr->entry_map = &map_forest_02;
                global_data_ptr->entry_position = {2, 3};
                global_data_ptr->ginger_position = {1, 3};
                return NEW_MAP;
                break;
            }
            case TO_FOREST_03:
            {
                global_data_ptr->entry_map = &map_forest_03;
                global_data_ptr->entry_position = {14, 15};
                global_data_ptr->ginger_position = {15, 15};

                // New BG track
                music::stop();
                global_data_ptr->bg_track = &music_items::bg_avalon;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case TO_CAVE_04:
            {
                global_data_ptr->entry_map = &map_cave_04;
                global_data_ptr->entry_position = {16, 3};
                global_data_ptr->ginger_position = {15, 3};
                return NEW_MAP;
                break;
            }
            case BACK_TO_FOREST_02:
            {
                global_data_ptr->entry_map = &map_forest_02;
                global_data_ptr->entry_position = {27, 3};
                global_data_ptr->ginger_position = {26, 3};
                return NEW_MAP;
                break;
            }
            case TO_AVALON_SHOP_01:
            {
                global_data_ptr->entry_map = &map_shop_01;
                global_data_ptr->entry_position = {5, 8};
                global_data_ptr->ginger_position = {4, 8};

                music::stop();
                global_data_ptr->bg_track = &music_items::shop;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case OUT_AVALON_SHOP_01:
            {
                global_data_ptr->entry_map = &map_forest_03;
                global_data_ptr->entry_position = {47, 8};
                global_data_ptr->ginger_position = {46, 8};

                music::stop();
                global_data_ptr->bg_track = &music_items::bg_avalon;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case FINAL_MSG_ACTION:
            {
                if (global_data_ptr->action_iterations[FINAL_MSG_ACTION] == 1)
                {
                    ch_man->db.emplace();
                    ch_man->db->load(&final_msg);
                    ch_man->db->init(ch_man);
                }
                break;
            }
            case NEW_BERLIN_SIGN:
            {
                if (man->bg_ptr.has_value())
                {
                    man->bg_ptr.value().set_visible(true);
                }
                break;
            }
            case TO_AVALON_TAVERN:
            {
                global_data_ptr->entry_map = &map_tavern_01;
                global_data_ptr->entry_position = {8, 10};
                global_data_ptr->ginger_position = {7, 10};

                music::stop();
                global_data_ptr->bg_track = &music_items::theme_visker;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case FROM_AVALON_TAVERN:
            {
                global_data_ptr->entry_map = &map_forest_03;
                global_data_ptr->entry_position = {24, 14};
                global_data_ptr->ginger_position = {23, 14};

                music::stop();
                global_data_ptr->bg_track = &music_items::bg_avalon;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case TO_SPAMTON:
            {
                global_data_ptr->entry_map = &map_forest_04;
                global_data_ptr->entry_position = {4, 7};
                global_data_ptr->ginger_position = {3, 7};

                music::stop();
                global_data_ptr->bg_track = &music_items::bg_spamton;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case FROM_SPAMTON:
            {
                global_data_ptr->entry_map = &map_forest_03;
                global_data_ptr->entry_position = {6, 2};
                global_data_ptr->ginger_position = {6, 1};

                music::stop();
                global_data_ptr->bg_track = &music_items::bg_avalon;
                global_data_ptr->bg_track->play(0.5);
                return NEW_MAP;
                break;
            }
            case GO_SPAMTON_GO:
            {
                auto st = ch_man->find_by_index(CHAR_SPAMTON);
                if (st != nullptr)
                {
                    st->idle_animation = &spamton_anim;
                    st->current_animation = &spamton_anim;
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else
        {
            buffer_active = false;
        }
    }

    return NONE;
}