// ge_sprites.cpp
#include "bn_log.h"
#include "bn_sprites.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_blending.h"

#include "ge_globals.h"
#include "ge_structs.h"
#include "ge_text.h"
#include "ge_sprites.h"
#include "ge_sprites_auto.h"
#include "ge_maps.h"
#include "ge_animations.h"

#include "bn_sprite_items_spr_button.h"
#include "bn_sprite_items_spr_spike.h"

#include "bn_sprite_items_spr_jeremy_fancy.h"
#include "bn_sprite_items_spr_ginger_fancy.h"
#include "bn_sprite_items_spr_sebellus_fancy.h"

#include "bn_sprite_items_spr_ginger_casual.h"
#include "bn_sprite_items_spr_sebellus_casual.h"

using namespace bn;

// Static member definitions
vector<v_sprite_ptr *, MAX_V_SPRITES> v_sprite_ptr::manager;
vector_2 v_sprite_ptr::camera = {0, 0};

bool within_bounds(bound me, bound you)
{
    int me_x = me.position.x.integer();
    int me_y = me.position.y.integer();
    int you_x = you.position.x.integer();
    int you_y = you.position.y.integer();
    int width = you.width.integer() / 2;
    int height = you.height.integer() / 2;

    return (me_x > you_x - width && me_x < you_x + width) && (me_y > you_y - height && me_y < you_y + height);
}

v_sprite_ptr::v_sprite_ptr()
    : sprite_item_ptr(nullptr), frame(0)
{
    bounds.position = {0, 0};
    bounds.width = 0;
    bounds.height = 0;
    manager.push_back(this);
}

v_sprite_ptr::v_sprite_ptr(const sprite_item *sprite_item_ptr_, vector_2 position, int width, int height, int frame_)
    : sprite_item_ptr(sprite_item_ptr_), frame(frame_)
{
    bounds.position = position;
    bounds.width = width;
    bounds.height = height;
    manager.push_back(this);
}

v_sprite_ptr::~v_sprite_ptr()
{
    // Clear sprites before removing from manager
    sprite_ptr_raw[0].reset();
    sprite_ptr_raw[1].reset();

    // Remove this instance from the manager
    for (auto it = manager.begin(); it != manager.end(); ++it)
    {
        if (*it == this)
        {
            manager.erase(it);
            break;
        }
    }
}

void v_sprite_ptr::move(vector_2 direction)
{
    bounds.position.x = bounds.position.x + direction.x;
    bounds.position.y = bounds.position.y + direction.y;
}

bound v_sprite_ptr::real_position() const
{
    return {
        {bounds.position.x - camera.x, bounds.position.y - camera.y},
        bounds.width,
        bounds.height};
}

void v_sprite_ptr::set_frame(int frame_)
{
    frame = frame_;

    if (sprite_ptr_raw[0].has_value())
    {
        // Always use tall sprite logic
        // Top sprite uses frame * 2
        sprite_ptr_raw[0].value().set_tiles(sprite_item_ptr->tiles_item(), frame * 2);

        // Bottom sprite uses (frame * 2) + 1
        if (sprite_ptr_raw[1].has_value())
        {
            sprite_ptr_raw[1].value().set_tiles(sprite_item_ptr->tiles_item(), (frame * 2) + 1);
        }
    }
}

void v_sprite_ptr::update(bool dialogue_box_ended)
{
    for (auto *item : manager)
    {
        bound bounds = item->real_position();
        bound acceptable = {screen.position, screen.width + 72, screen.height + 72};

        if (!dialogue_box_ended)
        {
            acceptable.position.y = 0 - (screen_height / 2) + 12;
        }

        if (item->sprite_ptr_raw[0].has_value() && item->sprite_ptr_raw[1].has_value())
        {
            // Sprite exists - check if it should be removed or updated
            if (!within_bounds(bounds, acceptable))
            {
                // Out of bounds - remove sprites
                item->sprite_ptr_raw[0].reset();
                item->sprite_ptr_raw[1].reset();
            }
            else
            {
                // Update z-order for both sprites
                if (item->sprite_item_ptr != &sprite_items::spr_spike && item->sprite_item_ptr != &sprite_items::spr_button)
                {
                    item->sprite_ptr_raw[0].value().set_z_order(10 - item->sprite_ptr_raw[1].value().y().integer() / 2);
                    item->sprite_ptr_raw[1].value().set_z_order(10 - item->sprite_ptr_raw[1].value().y().integer() / 2);
                }
                else
                {
                    item->sprite_ptr_raw[1].value().set_z_order(999);
                }

                // Always update both sprites (tall sprites)
                item->sprite_ptr_raw[0].value().set_position(bounds.position.x, bounds.position.y - item->sprite_item_ptr->shape_size().width());
                item->sprite_ptr_raw[0].value().set_tiles(item->sprite_item_ptr->tiles_item(), item->frame * 2);

                if (item->sprite_ptr_raw[1].has_value())
                {
                    item->sprite_ptr_raw[1].value().set_position(bounds.position.x, bounds.position.y);
                    item->sprite_ptr_raw[1].value().set_tiles(item->sprite_item_ptr->tiles_item(), (item->frame * 2) + 1);
                }
            }
        }
        else if (within_bounds(bounds, acceptable))
        {
            // Sprite doesn't exist but is in bounds - create it
            if (item->sprite_item_ptr != nullptr) // Safety check
            {
                // Always create both sprites for tall characters
                item->sprite_ptr_raw[0] = item->sprite_item_ptr->create_sprite(bounds.position.x, bounds.position.y - 32, item->frame * 2);
                item->sprite_ptr_raw[1] = item->sprite_item_ptr->create_sprite(bounds.position.x, bounds.position.y, (item->frame * 2) + 1);
            }
        }
    }
}

character::character(int index_, vector_2 start_, character_manager *manager) : index(index_), ch_man(manager)
{
    v_sprite.bounds.position = {(start_.x * 32) + 16, (start_.y * 32) + 14};
    v_sprite.bounds.width = 28;
    v_sprite.bounds.height = 28;
    idle_animation = nullptr;
    current_animation = &anim_stand;
    follow_id = resolve_sprite_id(index_);
    idle_animation = resolve_sprite_idle_animation(index_);

    // Costume support
    int costume = global_data_ptr->costumes[index_];
    if (costume > 0)
    {
        switch (index_)
        {
        case CHAR_GINGER:
        {
            if (costume == COSTUME_GINGER_FANCY)
            {
                v_sprite.sprite_item_ptr = &sprite_items::spr_ginger_fancy;
            }
            if (costume == COSTUME_GINGER_CASUAL)
            {
                v_sprite.sprite_item_ptr = &sprite_items::spr_ginger_casual;
            }
            break;
        }
        case CHAR_JEREMY:
        {
            if (costume == COSTUME_JEREMY_FANCY)
            {
                v_sprite.sprite_item_ptr = &sprite_items::spr_jeremy_fancy;
            }
            break;
        }
        case CHAR_SEBELLUS:
        {
            if (costume == COSTUME_SEBELLUS_FANCY)
            {
                v_sprite.sprite_item_ptr = &sprite_items::spr_sebellus_fancy;
            }
            if (costume == COSTUME_SEBELLUS_CASUAL)
            {
                v_sprite.sprite_item_ptr = &sprite_items::spr_sebellus_casual;
            }
            break;
        }
        }
    }
    else
    {
        v_sprite.sprite_item_ptr = resolve_sprite_item(index_);
    }

    // Reset sprites
    v_sprite.sprite_ptr_raw[0].reset();
    v_sprite.sprite_ptr_raw[1].reset();

    if ((this == ch_man->player_ptr) || (v_sprite_ptr::camera.x == 0 && v_sprite_ptr::camera.y == 0))
    {
        v_sprite_ptr::camera.x = start_.x;
        v_sprite_ptr::camera.y = start_.y;
    }
}

bound character::get_collision_bounds() const
{
    bound collision_bounds = v_sprite.bounds;
    collision_bounds.height = 24;
    collision_bounds.position.y = collision_bounds.position.y + 6;
    collision_bounds.width = 24;

    return collision_bounds;
}

void character::update(map_manager *current_map, bool db_inactive)
{
    vector_2 delta = {0, 0};
    bool custom_anim = false;

    if (keypad::r_pressed())
    {
        if (index == CHAR_JEREMY)
        {
            toggle_falling(true);
        }
    }

    if (is_falling)
    {
        blending::set_transparency_alpha(0.5);
        v_sprite.move({0, 2});
    }

    // Not falling
    else
    {
        if (this == ch_man->player_ptr)
        {
            if (db_inactive)
            {
                move_to.x = 0;
                move_to.y = 0;
                idle_animation = nullptr;
            }

            vector_2 bound_1 = {
                (screen_width / 2),
                (screen_height / 2)};

            vector_2 bound_2 = {
                (current_map->current_map->size.x * 32) - bound_1.x,
                (current_map->current_map->size.y * 32) - bound_1.y};

            if (db_inactive)
            {
                if (bn::keypad::up_held())
                {
                    delta.y = -1;
                }

                if (bn::keypad::down_held())
                {
                    delta.y = 1;
                }

                if (bn::keypad::left_held())
                {
                    delta.x = -1;
                }

                if (bn::keypad::right_held())
                {
                    delta.x = 1;
                }

                if (global_data_ptr->inverted_controls)
                {
                    delta.x = delta.x * -1;
                    delta.y = delta.y * -1;
                }
            }

            v_sprite_ptr::camera.x = v_sprite.bounds.position.x;

            if (!db_inactive && index != CHAR_VISTA)
            {
                if (v_sprite.bounds.position.y > v_sprite_ptr::camera.y)
                {
                    v_sprite_ptr::camera.y = v_sprite.bounds.position.y;
                }
            }
            else
            {
                v_sprite_ptr::camera.y = v_sprite.bounds.position.y;
            }

            if (v_sprite_ptr::camera.x < bound_1.x)
                v_sprite_ptr::camera.x = bound_1.x;

            if (v_sprite_ptr::camera.x > bound_2.x)
                v_sprite_ptr::camera.x = bound_2.x;
        }
        else
        {
            if (!db_inactive)
            {
                if (v_sprite.sprite_ptr_raw[0].has_value())
                {
                    // Calculate where this sprite appears on screen
                    bound screen_pos = v_sprite.real_position();

                    // Keep sprites at y=0 or above for ~80 pixels of buffer from dialogue box
                    if (screen_pos.position.y > 0)
                    {
                        // Move camera down just enough to keep sprite above this threshold
                        fixed adjustment = screen_pos.position.y - 0;
                        v_sprite_ptr::camera.y += adjustment;
                    }
                }
            }
        }

        bool is_move_to_active = false;

        if (move_to.x != 0 && move_to.y != 0)
        {
            is_move_to_active = true;

            vector_2 move_to_exp = {
                (move_to.x * 32) + 16,
                (move_to.y * 32) + 16};

            int tolerance = keypad::b_held() ? 3 : 1;

            int dist_x = (move_to_exp.x - v_sprite.bounds.position.x).integer();
            int dist_y = (move_to_exp.y - v_sprite.bounds.position.y).integer();

            // Only move if we're outside the tolerance zone
            if (abs(dist_x) > tolerance)
            {
                if (dist_x > 0)
                {
                    delta.x = 1;
                }
                else
                {
                    delta.x = -1;
                }
            }

            if (abs(dist_y) > tolerance)
            {
                if (dist_y > 0)
                {
                    delta.y = 1;
                }
                else
                {
                    delta.y = -1;
                }
            }

            if (abs(dist_x) <= tolerance && abs(dist_y) <= tolerance)
            {
                move_to.x = 0;
                move_to.y = 0;
            }
        }

        // Apply speed boost if B is held
        if (keypad::b_held())
        {
            delta.x = delta.x * 2;
            delta.y = delta.y * 2;
        }

        // Decrement cooldown if active
        if (face_change_cooldown > 0)
        {
            face_change_cooldown--;
        }

        // Simplified facing direction logic
        int old_face = face;

        // Get integer values for comparison
        int dx = delta.x.integer();
        int dy = delta.y.integer();

        if (dx != 0 || dy != 0) // If we're moving at all
        {
            if (is_follow && !ch_man->db.has_value())
            {
                if (face_change_cooldown == 0)
                {
                    // Only change if movement is clear in one direction
                    if (abs(dy) > abs(dx))
                    {
                        if (dy > 0)
                            face = DIR_DOWN;
                        else if (dy < 0)
                            face = DIR_UP;
                    }
                    else if (abs(dx) > abs(dy))
                    {
                        if (dx > 0)
                            face = DIR_RIGHT;
                        else if (dx < 0)
                            face = DIR_LEFT;
                    }

                    // If we changed direction, add a small cooldown
                    if (old_face != face)
                    {
                        face_change_cooldown = 4; // 4 frames of cooldown for followers
                    }
                }
            }
            else
            {
                // Player character - more responsive but with tiny cooldown to prevent flickering
                if (face_change_cooldown == 0)
                {
                    // Update based on strongest movement direction
                    if (abs(dy) > abs(dx))
                    {
                        if (dy > 0)
                            face = DIR_DOWN;
                        else if (dy < 0)
                            face = DIR_UP;
                    }
                    else if (dx != 0) // Prioritize horizontal if equal or only horizontal movement
                    {
                        if (dx > 0)
                            face = DIR_RIGHT;
                        else if (dx < 0)
                            face = DIR_LEFT;
                    }

                    // Minimal cooldown for player to prevent rapid flickering
                    if (old_face != face)
                    {
                        face_change_cooldown = 2; // Just 2 frames for player
                    }
                }
            }
        }

        if (!is_move_to_active)
        {
            if (delta.x != 0 || delta.y != 0)
            {
                // 1. DEFINE SPIKE CHECK LAMBDA
                // This helper checks if a potential position hits an active spike
                auto check_spike_collision = [&](bound target_bounds) -> bool
                {
                    for (auto &other : ch_man->characters)
                    {
                        if (other && other.get() != this)
                        {
                            if (other->index == CHAR_SPIKE && other->is_pressed)
                            {
                                bound spike_bounds = other->get_collision_bounds();

                                // Proper box-to-box collision check
                                int target_left = (target_bounds.position.x - target_bounds.width / 2).integer();
                                int target_right = (target_bounds.position.x + target_bounds.width / 2).integer();
                                int target_top = (target_bounds.position.y - target_bounds.height / 2).integer();
                                int target_bottom = (target_bounds.position.y + target_bounds.height / 2).integer();

                                int spike_left = (spike_bounds.position.x - spike_bounds.width / 2).integer();
                                int spike_right = (spike_bounds.position.x + spike_bounds.width / 2).integer();
                                int spike_top = (spike_bounds.position.y - spike_bounds.height / 2).integer();
                                int spike_bottom = (spike_bounds.position.y + spike_bounds.height / 2).integer();

                                // Check if boxes overlap
                                if (target_right > spike_left && target_left < spike_right &&
                                    target_bottom > spike_top && target_top < spike_bottom)
                                {
                                    return true;
                                }
                            }
                        }
                    }
                    return false;
                };

                bound future_bounds_x = get_collision_bounds();
                future_bounds_x.position.x = future_bounds_x.position.x + delta.x;

                bound future_bounds_y = get_collision_bounds();
                future_bounds_y.position.y = future_bounds_y.position.y + delta.y;

                // Check X movement (Map OR Spike)
                if (current_map->check_box_collision(future_bounds_x, ch_man) || check_spike_collision(future_bounds_x))
                {
                    delta.x = 0;
                }

                // Check Y movement (Map OR Spike)
                if (current_map->check_box_collision(future_bounds_y, ch_man) || check_spike_collision(future_bounds_y))
                {
                    delta.y = 0;
                }

                // For diagonal movement
                if (delta.x != 0 && delta.y != 0)
                {
                    bound future_bounds_both = get_collision_bounds();
                    future_bounds_both.position.x = future_bounds_both.position.x + delta.x;
                    future_bounds_both.position.y = future_bounds_both.position.y + delta.y;

                    if (check_spike_collision(future_bounds_both))
                    {
                        // Try to slide along walls
                        // Check X sliding
                        if (delta.x != 0 &&
                            !current_map->check_box_collision(future_bounds_x, ch_man) &&
                            !check_spike_collision(future_bounds_x))
                        {
                            delta.y = 0; // Can move X but not Y
                        }
                        // Check Y sliding
                        else if (delta.y != 0 &&
                                 !current_map->check_box_collision(future_bounds_y, ch_man) &&
                                 !check_spike_collision(future_bounds_y))
                        {
                            delta.x = 0; // Can move Y but not X
                        }
                        else
                        {
                            // Can't move in either direction
                            delta.x = 0;
                            delta.y = 0;
                        }
                    }
                }
            }
        }

        // Apply movement with fixed direction (always do this, even if delta is 0)
        v_sprite.bounds.position.x = v_sprite.bounds.position.x + delta.x;
        v_sprite.bounds.position.y = v_sprite.bounds.position.y + delta.y;

        bool moving = (delta.x != 0 || delta.y != 0);

        // Animation and sprite update code
        custom_anim = false;
        if (moving)
        {
            if (index != CHAR_VISTA_LIFT)
            {
                current_animation = &anim_walk;
            }
        }
        else if (idle_animation == nullptr)
        {
            current_animation = &anim_stand;
        }
        else
        {
            if (current_animation != idle_animation)
            {
                frame = 0;
            }
            current_animation = idle_animation;
            custom_anim = true;
        }
    }

    // Update animations
    if (v_sprite.sprite_ptr_raw[0].has_value())
    {
        int ticker_speed;

        switch (current_animation->speed)
        {
        case SP_SLOW:
        {
            ticker_speed = 12;
            break;
        }
        case SP_FAST:
        {
            ticker_speed = 3;
            break;
        }
        default:
        {
            ticker_speed = 6;
            break;
        }
        }

        if (current_animation->loop)
        {
            if (ticker % ticker_speed == 0)
            {
                frame = (frame + 1) % current_animation->size;
            }
        }
        else
        {
            if (ticker % ticker_speed == 0 && frame < current_animation->size - 1)
            {
                frame++;
            }
        }

        int new_frame = current_animation->frames[frame];

        // Always set horizontal flip for both sprites
        v_sprite.sprite_ptr_raw[0].value().set_horizontal_flip(false);
        v_sprite.sprite_ptr_raw[1].value().set_horizontal_flip(false);

        if (is_falling)
        {
            int frame = (ticker / 8) % 4;

            custom_anim = false;
            face = frame;
        }

        if (!custom_anim)
        {
            switch (face)
            {
            case DIR_UP:
                v_sprite.set_frame(new_frame + 6);
                break;
            case DIR_DOWN:
                v_sprite.set_frame(new_frame);
                break;
            case DIR_LEFT:
                v_sprite.set_frame(new_frame + 3);
                v_sprite.sprite_ptr_raw[0].value().set_horizontal_flip(true);
                v_sprite.sprite_ptr_raw[1].value().set_horizontal_flip(true);
                break;
            case DIR_RIGHT:
                v_sprite.set_frame(new_frame + 3);
                break;
            default:
            {
                break;
            }
            }
        }
        else
        {
            v_sprite.set_frame(new_frame);
        }
    }

    if (is_falling)
    {
        if (v_sprite.sprite_ptr_raw[0].has_value())
        {
            v_sprite.sprite_ptr_raw[0].value().set_blending_enabled(true);
        }
        if (v_sprite.sprite_ptr_raw[1].has_value())
        {
            v_sprite.sprite_ptr_raw[1].value().set_blending_enabled(true);
        }
    }

    ticker++;
}

void character::add(list<character, 32> *characters, int character_id, vector_2 location, character_manager *manager)
{
    characters->emplace_back(character_id, location, manager);
};

void character::toggle_falling(bool should_be_falling){
    {is_falling = should_be_falling;

for (auto &ch : ch_man->characters)
{
    if (ch->follow_id == index)
    {
        ch->is_follow = false;
    }
}
}
}
;