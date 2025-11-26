// ge_actions.cpp

#include "bn_log.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_optional.h"

#include "ge_globals.h"
#include "ge_sprites.h"
#include "ge_maps.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_map_data.h"
#include "ge_actions.h"
#include "ge_actions_auto.h"

static vector_2 previous_tile = {-1, -1};
static bool dialogue_just_closed = false;
static bool cooldown = false;

void reset_previous_tile()
{
    previous_tile = {-1, -1};
    dialogue_just_closed = false;
    cooldown = false;
}

int action_listener(map_manager *man, character_manager *ch_man)
{
    if (ch_man->player_ptr != nullptr)
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
            previous_tile = current_tile;
        }

        if (!ch_man->db.has_value())
        {
            if (dialogue_just_closed)
            {
                cooldown = true;
                dialogue_just_closed = false;
            }

            if (action != 0 && cooldown == false)
            {
                // AUTOMATIC
                if (new_tile)
                {
                    switch (action)
                    {
                    case 18:
                    {
                        if (global_data_ptr->action_iterations[23] == 0)
                        {
                            global_data_ptr->entry_map = &map_garbage_03;
                            global_data_ptr->jeremy_position = {2, 8};
                            return NEW_MAP;
                        }
                        else
                        {
                            global_data_ptr->entry_map = &map_garbage_05;
                            global_data_ptr->jeremy_position = {4, 45};
                            return NEW_MAP;
                        }
                        break;
                    }

                    case 24:
                    {
                        ch_man->music_fadeout = true;
                        break;
                    }

                    case 53:
                    {
                        auto croke = ch_man->find_by_index(CHAR_CROKE);
                        if (croke != nullptr)
                        {
                            ch_man->remove_character(croke);
                        }
                        break;
                    }

                    case CHAT_SNEAKER:
                    {
                        BN_LOG("Iterations: ", global_data_ptr->action_iterations[CHAT_SNEAKER]);
                        if (global_data_ptr->action_iterations[CHAT_SNEAKER] > 0)
                        {
                            ch_man->load(&scruffys_05b);
                        }
                        break;
                    }

                    case 163:
                    {
                        if (global_data_ptr->action_iterations[163] == 1)
                        {
                            auto seb = ch_man->find_by_index(CHAR_SEBELLUS);
                            if (seb != nullptr)
                            {
                                seb->current_animation = &sebellus_hide;
                                seb->idle_animation = &sebellus_hide;
                            }
                        }
                        break;
                    }

                    case 190:
                    {
                        auto g = ch_man->find_by_index(CHAR_GINGER);
                        g->idle_animation = &ginger_sit_chair;
                        g->current_animation = &ginger_sit_chair;
                        break;
                    }

                    case 192:
                    {
                        auto g = ch_man->find_by_index(CHAR_GINGER);
                        if (g != nullptr)
                        {
                            g->idle_animation = &ginger_hide;
                            g->current_animation = &ginger_hide;
                        }

                        auto s = ch_man->find_by_index(CHAR_SEBELLUS);
                        if (s != nullptr)
                        {
                            s->idle_animation = &sebellus_hide;
                            s->current_animation = &sebellus_hide;
                        }
                        break;
                    }

                    case 180:
                    case 193:
                    {
                        if (global_data_ptr->action_iterations[ITEM_181] < 2)
                        {
                            auto s = ch_man->find_by_index(CHAR_SEBELLUS);
                            if (s != nullptr)
                            {
                                s->idle_animation = &sebellus_sleep_01;
                                s->current_animation = &sebellus_sleep_01;
                            }
                        }
                        else
                        {
                            auto s = ch_man->find_by_index(CHAR_SEBELLUS);
                            if (s != nullptr)
                            {
                                s->idle_animation = &sebellus_sleep_03;
                                s->current_animation = &sebellus_sleep_03;
                            }
                        }
                        break;
                    }
                    case 210:
                    {
                        if (global_data_ptr->action_iterations[210] < 1)
                        {
                            for (int t = 0; t < ITEMS_SIZE; t++)
                            {
                                global_data_ptr->items[t] = 0;
                            }

                            ch_man->load(&naomi_fortune_01);
                            global_data_ptr->action_iterations[210]++;
                        }
                        break;
                    }
                    case 240:
                    {
                        if (global_data_ptr->action_iterations[238] > 0 &&
                            global_data_ptr->action_iterations[239] > 0)
                        {

                            // If spoken to both, cue Vista
                            ch_man->load(&vista_01);

                            auto v = ch_man->find_by_index(CHAR_VISTA_LIFT);
                            if (v != nullptr)
                            {
                                v->v_sprite.bounds.position.x = ch_man->player_ptr->v_sprite.bounds.position.x - 42;
                                v->v_sprite.bounds.position.y = ch_man->player_ptr->v_sprite.bounds.position.y + 16;
                            }
                        }
                        else
                        {

                            // Set up Ginger and Sebellus' sprites
                            auto g = ch_man->find_by_index(CHAR_GINGER);
                            if (g != nullptr)
                            {
                                g->idle_animation = &ginger_fancy_sit;
                                g->current_animation = &ginger_fancy_sit;
                            }

                            auto s = ch_man->find_by_index(CHAR_SEBELLUS);
                            if (s != nullptr)
                            {
                                s->idle_animation = &sebellus_fancy_stand;
                                s->current_animation = &sebellus_fancy_stand;
                            }
                        }
                        break;
                    }
                    case 243:
                    {
                        auto v = ch_man->find_by_index(CHAR_VISTA_02);
                        if (v != nullptr)
                        {
                            v->current_animation = &vista_drinking;
                            v->idle_animation = &vista_drinking;
                        }
                        break;
                    }
                    case 256:
                    {
                        // Set up Ginger and Sebellus' sprites
                        auto g = ch_man->find_by_index(CHAR_GINGER);
                        if (g != nullptr)
                        {
                            g->idle_animation = &ginger_fancy_wistful;
                            g->current_animation = &ginger_fancy_wistful;
                        }

                        auto s = ch_man->find_by_index(CHAR_SEBELLUS);
                        if (s != nullptr)
                        {
                            s->idle_animation = &sebellus_fancy_sleep;
                            s->current_animation = &sebellus_fancy_sleep;
                        }
                        break;
                    }
                    case 306:
                    {
                        if (global_data_ptr->action_iterations[306] < 1)
                        {
                            auto p = ch_man->find_by_index(CHAR_PILLS);
                            if (p != nullptr)
                            {
                                p->idle_animation = &pills_roll;
                                p->current_animation = &pills_roll;
                            }
                            p->move_to.x = 6;
                            p->move_to.y = 7;
                            sound_items::sfx_bottle.play();
                            global_data_ptr->action_iterations[306] = 1;
                        }
                        break;
                    }
                    case 318:
                    {
                        return KEYPAD;
                        break;
                    }
                    case 322:
                    {
                        if (global_data_ptr->action_iterations[322] < 1)
                        {
                            global_data_ptr->action_iterations[322]++;
                            if (global_data_ptr->items[OBJ_TURKEY] == true)
                            {
                                global_data_ptr->items[OBJ_TURKEY] = false;
                                ch_man->load(&visker_final);
                            }
                            else
                            {
                                for (int t = 0; t < ITEMS_SIZE; t++)
                                {
                                    global_data_ptr->items[t] = false;
                                }
                                ch_man->load(&visker_final_alt_01);
                            }
                        }

                        break;
                    }
                    case 346:
                    {
                        auto v = ch_man->find_by_index(CHAR_VISTA_02);
                        if (v != nullptr)
                        {
                            v->current_animation = &anim_face_right;
                            v->idle_animation = &anim_face_right;
                        }
                        break;
                    }
                    case 348:
                    {
                        if (global_data_ptr->variables[HENRY_TALK] == true)
                        {
                            ch_man->load(&henry_02);
                        }
                        break;
                    }
                    default:
                    {
                        int ret = perform_action_automatic(action, *ch_man);
                        if (ret != -1)
                            return ret;
                        break;
                    }
                    }
                }

                // INTERACTIVE
                if (keypad::a_pressed())
                {
                    global_data_ptr->action_iterations[action]++;

                    switch (action)
                    {
                    case 155:
                    {
                        bool ready = (global_data_ptr->items[OBJ_FLINT] &&
                                      global_data_ptr->items[OBJ_STEEL] &&
                                      global_data_ptr->items[OBJ_STICKS] &&
                                      global_data_ptr->items[OBJ_STONES]);

                        if (!ready && global_data_ptr->action_iterations[155] < 16)
                        {
                            global_data_ptr->action_iterations[155] = 16;
                            ch_man->load(&item_155);
                        }
                        else if (global_data_ptr->action_iterations[155] < 32)
                        {
                            global_data_ptr->action_iterations[155] = 32;
                            ch_man->load(&item_155b);
                        }
                        break;
                    }

                    case 181:
                    {
                        if (global_data_ptr->action_iterations[BUFFER_190b] == 0)
                        {
                            ch_man->load(&talk_190);

                            global_data_ptr->action_iterations[BUFFER_190b]++;
                        }
                        break;
                    }

                    case 112:
                    {
                        if (global_data_ptr->action_iterations[112] == 1)
                        {
                            global_data_ptr->jeremy_position = {13, 3};
                            global_data_ptr->ginger_position = {14, 3};
                            global_data_ptr->entry_map = &map_tavern_01;

                            ch_man->load(&scruffys_05);
                        }
                        break;
                    }
                    case 308:
                    {
                        if (global_data_ptr->items[OBJ_PILLS])
                        {
                            ch_man->load(&cutscene_09b);
                        }
                        else
                        {
                            ch_man->load(&c09_reiterate);
                        }
                        break;
                    }
                    case 319:
                    {
                        music_items::z02_the_champ.play();
                        break;
                    }
                    case 336:
                    {
                        if (global_data_ptr->variables[BEAR_DEFEAT] == false)
                        {
                            ch_man->load(&boutique_0a);
                        }
                        else if (global_data_ptr->items[OBJ_CLOTHES] == false)
                        {
                            ch_man->load(&boutique_02);
                        }
                        break;
                    }
                    case 337:
                    {
                        if (global_data_ptr->items[OBJ_CLOTHES] == true)
                        {
                            ch_man->load(&lobbybot_02);
                        }
                        else
                        {
                            ch_man->load(&lobbybot_01);
                        }
                        break;
                    }
                    case 335:
                    {
                        if (global_data_ptr->items[OBJ_SOUP] == true)
                        {
                            global_data_ptr->items[OBJ_SOUP] = false;
                            ch_man->load(&boutique_01b);
                        }
                        else if (global_data_ptr->variables[BEAR_DEFEAT] == true)
                        {
                            ch_man->load(&boutique_01);
                        }
                        break;
                    }
                    case 341:
                    {
                        if (global_data_ptr->items[OBJ_CLOTHES] == true)
                        {
                            global_data_ptr->jeremy_position = {4, 6};
                            global_data_ptr->ginger_position = {3, 6};
                            global_data_ptr->sebellus_position = {2, 6};
                            global_data_ptr->entry_map = &map_hotel_01;
                            sound_items::sfx_door.play();
                            return NEW_MAP;
                        }
                        else
                        {
                            ch_man->load(&door_locked);
                        }
                        break;
                    }
                    default:
                    {
                        int ret = perform_action_interactive(action, *ch_man);
                        if (ret != -1)
                            return ret;
                        break;
                    }
                    }
                }
            }

            if (cooldown)
                cooldown = false;
        }
        else
        {
            dialogue_just_closed = true;
        }
    }
    else
    {
        previous_tile = {-1, -1};
    }

    return NONE;
}