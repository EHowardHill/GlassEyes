// ge_maps.cpp

#include "bn_log.h"
#include "bn_regular_bg_ptr.h"

#include "ge_globals.h"
#include "ge_maps.h"
#include "ge_sprites.h"
#include "ge_animations.h"

map_manager::map_manager(const map *current_map_)
    : current_map(current_map_)
{
    if (global_data_ptr->bg != nullptr)
    {
        bg_ptr = global_data_ptr->bg->create_bg(0, 0);
        bg_ptr.value().set_visible(false);
    }

    collider_ptr = current_map_->bg_item_ptr->create_bg(0, 0);
}

void map_manager::update()
{
    vector_2 *cam = &v_sprite_ptr::camera;

    vector_2 offset = {
        current_map->raw_size.x / 2,
        current_map->raw_size.y / 2};

    collider_ptr.value().set_position(-cam->x + offset.x, -cam->y + offset.y);
}

int map_manager::collision(vector_2 location, character_manager *ch_man)
{
    // Get the tile coordinates
    int tile_x = location.x.integer() / 32;
    int tile_y = location.y.integer() / 32;

    // Clamp to map bounds
    if (tile_x < 0 || tile_x >= current_map->size.x.integer() ||
        tile_y < 0 || tile_y >= current_map->size.y.integer())
    {
        return 1; // Out of bounds is a collision
    }

    int tile_index = tile_x + (tile_y * current_map->size.x.integer());

    // 1. Get the collision value from the static map as a default.
    int collision_value = current_map->collisions[tile_index];

    // 2. Check for a spike to override the default.
    if (current_map->characters[tile_index] - 1 == ITEM_SPIKE)
    {
        // Find the character at this tile position
        vector_2 tile_pos = {tile_x * 32 + 16, tile_y * 32 + 16}; // Center of tile

        if (ch_man != nullptr)
        {
            // Look for a spike character at this position
            for (auto &ch : ch_man->characters)
            {
                if (ch && ch->index == ITEM_SPIKE)
                {
                    // Check if this spike is at the current tile
                    int ch_tile_x = ch->v_sprite.bounds.position.x.integer() / 32;
                    int ch_tile_y = ch->v_sprite.bounds.position.y.integer() / 32;

                    if (ch_tile_x == tile_x && ch_tile_y == tile_y)
                    {
                        if (ch->is_pressed)
                        {
                            return true;
                        }
                        break;
                    }
                }
            }
        }
    }

    // 3. Return the final collision value.
    return collision_value;
}

int map_manager::action(vector_2 location)
{
    // Get the tile coordinates
    int tile_x = location.x.integer() / 32;
    int tile_y = location.y.integer() / 32;

    // Clamp to map bounds
    if (tile_x < 0 || tile_x >= current_map->size.x.integer() ||
        tile_y < 0 || tile_y >= current_map->size.y.integer())
    {
        return 0; // Out of bounds has no action
    }

    int tile_index = tile_x + (tile_y * current_map->size.x.integer());
    return current_map->actions[tile_index];
}

bool map_manager::check_box_collision(bound box, character_manager *ch_man)
{
    // Check all four corners of the bounding box
    int left = (box.position.x.integer() - box.width.integer() / 2);
    int right = (box.position.x.integer() + box.width.integer() / 2 - 1);
    int top = (box.position.y.integer() - box.height.integer() / 2);
    int bottom = (box.position.y.integer() + box.height.integer() / 2 - 1);

    // Check corners
    if (collision({left, top}, ch_man) > 0)
        return true;
    if (collision({right, top}, ch_man) > 0)
        return true;
    if (collision({left, bottom}, ch_man) > 0)
        return true;
    if (collision({right, bottom}, ch_man) > 0)
        return true;

    // For wider sprites, also check middle points
    if (box.width.integer() > 32)
    {
        int mid_x = box.position.x.integer();
        if (collision({mid_x, top}, ch_man) > 0)
            return true;
        if (collision({mid_x, bottom}, ch_man) > 0)
            return true;
    }

    if (box.height.integer() > 32)
    {
        int mid_y = box.position.y.integer();
        if (collision({left, mid_y}, ch_man) > 0)
            return true;
        if (collision({right, mid_y}, ch_man) > 0)
            return true;
    }

    return false;
}