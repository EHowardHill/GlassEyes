// ge_character_manager.cpp

#include "bn_log.h"
#include "bn_list.h"
#include "bn_unique_ptr.h"
#include "bn_optional.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"

#include "ge_sprites.h"
#include "ge_text.h"
#include "ge_character_manager.h"
#include "ge_maps.h"
#include "ge_globals.h"
#include "ge_animations.h"
#include "ge_map_data.h"

#include "bn_sprite_items_hearts.h"

using namespace bn;

character_manager::character_manager() : player_ptr(nullptr)
{
}

void character_manager::load(conversation *convo)
{
    db.emplace();
    db->load(convo);
    db->init(this);
}

void character_manager::toggle_button(int id)
{
    auto btn = find_by_id(id);
    if (btn != nullptr)
    {
        btn->is_pressed = !btn->is_pressed;
        if (btn->is_pressed)
        {
            btn->idle_animation = &elem_button_down;
        }
        else
        {
            btn->idle_animation = &elem_button_up;
        }
    }
}

character *character_manager::add_character(int index, vector_2 position, int id)
{
    if (characters.size() >= 64 || index < 1 || index > CHAR_SIZE)
        return nullptr;

    // Create new character
    characters.push_back(make_unique<character>(index, position, this));
    character *new_char = characters.back().get();
    new_char->id = id;

    if (index == CHAR_GINGER && global_data_ptr->ginger_position.x != 0 && global_data_ptr->ginger_position.y != 0)
    {
        new_char->is_follow = true;
    }

    if (index == CHAR_SEBELLUS && global_data_ptr->sebellus_position.x != 0 && global_data_ptr->sebellus_position.y != 0)
    {
        new_char->is_follow = true;
    }

    return new_char;
}

bool character_manager::remove_character(character *ch)
{
    if (!ch || ch == player_ptr)
        return false; // Don't remove player

    for (auto it = characters.begin(); it != characters.end(); ++it)
    {
        if (it->get() == ch)
        {
            characters.erase(it);
            return true;
        }
    }
    return false;
}

void character_manager::clear_npcs()
{
    auto it = characters.begin();
    while (it != characters.end())
    {
        if ((*it)->type() == CH_TYPE_NPC)
        {
            it = characters.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

character *character_manager::find_at_position(vector_2 pos, int tolerance)
{
    for (auto &ch : characters)
    {
        if (ch)
        {
            int dx = abs(ch->v_sprite.bounds.position.x.integer() - pos.x.integer());
            int dy = abs(ch->v_sprite.bounds.position.y.integer() - pos.y.integer());

            if (dx <= tolerance && dy <= tolerance)
            {
                return ch.get();
            }
        }
    }
    return nullptr;
}

character *character_manager::find_by_index(int index)
{
    for (auto &ch : characters)
    {
        if (ch && ch->index == index)
        {
            return ch.get();
        }
    }
    return nullptr;
}

character *character_manager::find_by_id(int id)
{
    for (auto &ch : characters)
    {
        if (ch && ch->id == id)
        {
            return ch.get();
        }
    }
    return nullptr;
}

void character_manager::alert(int new_status = BATTLE)
{
    vector_2 player_pos = player_ptr->v_sprite.real_position().position;

    sprite_ptr alert_box = sprite_items::hearts.create_sprite(player_pos.x, player_pos.y - 48, 0);
    music::stop();
    sound_items::snd_alert.play();

    for (int t = 0; t < 64; t++)
    {
        core::update();
    }

    global_data_ptr->entry_direction = player_ptr->face;
    status = new_status;
}

// Modified character_manager::update method to handle branching dialogue
void character_manager::update(map_manager *current_map = nullptr)
{
    bool db_inactive = true;
    bool ib_inactive = true;

    // Track player
    if (!player_ptr)
    {
        for (auto char_id : {CHAR_JEREMY, CHAR_VISTA_02, CHAR_VISTA, CHAR_VISTA_YOUNG})
        {
            if (auto j = find_by_index(char_id); j != nullptr)
            {
                player_ptr = j;
                break;
            }
        }
    }

    if (music::playing())
    {
        if (!music_fadeout)
        {

            music::set_volume(0.5);
        }
        else
        {
            fixed volume = music::volume() - 0.005;
            if (volume > 0)
            {
                music::set_volume(volume);
            }
            else
            {
                music::set_volume(0);
            }
        }
    }

    // Handle items box first (takes priority over dialogue)
    if (ib.has_value() && ib.value().is_active())
    {
        ib_inactive = false;
        ib.value().update();
        ib.value().handle_input(this);

        // If items box closed and opened a dialogue, don't process other input
        if (!ib.value().is_active() || keypad::b_pressed() || keypad::start_pressed())
        {
            ib.reset();
        }
    }

    // Handle dialogue box
    else if (db.has_value())
    {
        db_inactive = db.value().is_ended();

        // Check if we're in branching mode
        if (db.value().is_branching)
        {
            // Only handle branching input, no normal update
            db.value().handle_branching_input(this);
        }
        else
        {
            // Normal dialogue handling
            db.value().update();

            if (keypad::a_pressed())
            {
                db.value().handle_a_button_press(this);
            }
            else if (keypad::b_pressed())
            {
                db.value().index++;
                db.value().init(this);
                // Only render lines that have been properly initialized
                if (!db.value().lines[0].reference.empty())
                    db.value().lines[0].render();
                if (!db.value().lines[1].reference.empty())
                    db.value().lines[1].render();
                if (!db.value().lines[2].reference.empty())
                    db.value().lines[2].render();
            }
        }

        if (db.value().is_ended())
        {
            db.reset();
        }
    }

    // Only allow opening items menu when no dialogue or items box is active
    else if (db_inactive && ib_inactive)
    {
        // Example: Open items with START button
        if (keypad::start_pressed())
        {
            ib = items_box();
            ib.value().init();
        }
    }

    bool allow_movement = db_inactive && ib_inactive;

    // Handle characters
    for (auto &ch : characters)
    {
        if (ch)
        {
            ch->update(current_map, allow_movement);

            if (ch->index == CHAR_BUTTON)
            {
                if (ch->idle_animation != &elem_button_down)
                {
                    vector_2 f_pos = {player_ptr->v_sprite.bounds.position.x / 32, player_ptr->v_sprite.bounds.position.y / 32};
                    vector_2 m_pos = {ch->v_sprite.bounds.position.x / 32, ch->v_sprite.bounds.position.y / 32};

                    if (current_map->current_map == &map_cave_05)
                    {
                        auto togore = find_by_index(CHAR_TOGORE);
                        if (togore != nullptr)
                        {
                            vector_2 t_pos = {togore->v_sprite.bounds.position.x / 32, togore->v_sprite.bounds.position.y / 32};

                            if (t_pos.x.integer() == m_pos.x.integer() && t_pos.y.integer() == m_pos.y.integer())
                            {
                                sound_items::snd_alert.play(0.5);
                                ch->idle_animation = &elem_button_down;
                                ch->is_pressed = true;
                            }
                        }
                    }

                    // Puzzle Room
                    else if (current_map->current_map == &map_dark_06)
                    {
                        if (f_pos.x.integer() == m_pos.x.integer() && f_pos.y.integer() == m_pos.y.integer())
                        {
                            sound_items::snd_alert.play(0.5);
                            ch->idle_animation = &elem_button_down;
                            ch->is_pressed = true;

                            int pressed_id = ch->id;

                            if (pressed_id > 3)
                            {
                                toggle_button(pressed_id - 3);
                            }

                            if (pressed_id < 7)
                            {
                                toggle_button(pressed_id + 3);
                            }

                            if (pressed_id % 3 != 1)
                            {
                                toggle_button(pressed_id - 1);
                            }

                            if (pressed_id % 3 != 0)
                            {
                                toggle_button(pressed_id + 1);
                            }
                        }
                    }

                    // Otherwise
                    else if (f_pos.x.integer() == m_pos.x.integer() && f_pos.y.integer() == m_pos.y.integer())
                    {
                        sound_items::snd_alert.play(0.5);
                        ch->idle_animation = &elem_button_down;
                        ch->is_pressed = true;
                    }
                }
            }
            else if (ch->index == CHAR_LEAVES)
            {
                if (ch->idle_animation != &elem_leaves_stepped)
                {
                    vector_2 f_pos = {player_ptr->v_sprite.bounds.position.x / 32, player_ptr->v_sprite.bounds.position.y / 32};
                    vector_2 m_pos = {ch->v_sprite.bounds.position.x / 32, ch->v_sprite.bounds.position.y / 32};

                    if (f_pos.x.integer() == m_pos.x.integer() && f_pos.y.integer() == m_pos.y.integer())
                    {
                        sound_items::sfx_fall.play(0.5);
                        ch->idle_animation = &elem_leaves_stepped;
                        player_ptr->toggle_falling(true);
                        player_ptr->idle_animation = &anim_stand;
                        player_ptr->current_animation = &anim_stand;

                        global_data_ptr->bg_track = &music_items::cave_01;
                        global_data_ptr->entry_map = &map_to_flay_01b;
                        global_data_ptr->jeremy_position = {19, 4};
                        global_data_ptr->ginger_position = {0, 0};
                        global_data_ptr->sebellus_position = {0, 0};
                    }
                }
            }

            if (ch->is_follow)
            {
                auto f_ch = find_by_index(ch->follow_id);

                if (f_ch != nullptr)
                {
                    vector_2 f_pos = {f_ch->v_sprite.bounds.position.x / 32, f_ch->v_sprite.bounds.position.y / 32};
                    vector_2 m_pos = {ch->v_sprite.bounds.position.x / 32, ch->v_sprite.bounds.position.y / 32};

                    if (abs((m_pos.x - f_pos.x) * 32) + abs((m_pos.y - f_pos.y) * 32) > 32)
                    {
                        switch (f_ch->face)
                        {
                        case DIR_UP:
                        {
                            ch->move_to = {f_pos.x.integer(), f_pos.y.integer() + 1};
                            break;
                        }
                        case DIR_DOWN:
                        {
                            ch->move_to = {f_pos.x.integer(), f_pos.y.integer() - 1};
                            break;
                        }
                        case DIR_LEFT:
                        {
                            ch->move_to = {f_pos.x.integer() + 1, f_pos.y.integer()};
                            break;
                        }
                        case DIR_RIGHT:
                        {
                            ch->move_to = {f_pos.x.integer() - 1, f_pos.y.integer()};
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }
                    }
                }
            }
        }
    }
}