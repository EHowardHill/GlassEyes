// ge_battle_types_auto.cpp

#include "ge_battle.h"
#include "ge_battle_types_auto.h"

#include "bn_core.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_random.h"
#include "bn_keypad.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_random.h"
#include "bn_sprite_items_hearts.h"

using namespace bn;

/*

The boundary of the game screen is -64 to 64 in x and y.

The mini game's "vars" variable is where to store all persistent data needed for the mini-game.

*/

// Helper functions:
bool close(fixed_t<4> x1, fixed_t<4> y1, fixed_t<4> x2, fixed_t<4> y2, int threshold)
{
    fixed_t<4> dx = x1 - x2;
    fixed_t<4> dy = y1 - y2;
    fixed_t<4> dist_squared = dx * dx + dy * dy;
    return dist_squared <= threshold * threshold;
}

void handle_movement_input(sprite_ptr &movable_sprite, int movement_speed, int boundary_min, int boundary_max)
{
    // Horizontal Movement
    if (keypad::left_held() && movable_sprite.x() > boundary_min)
    {
        movable_sprite.set_x(movable_sprite.x() - movement_speed);
    }
    else if (keypad::right_held() && movable_sprite.x() < boundary_max)
    {
        movable_sprite.set_x(movable_sprite.x() + movement_speed);
    }

    // Vertical Movement
    if (keypad::up_held() && movable_sprite.y() > boundary_min)
    {
        movable_sprite.set_y(movable_sprite.y() - movement_speed);
    }
    else if (keypad::down_held() && movable_sprite.y() < boundary_max)
    {
        movable_sprite.set_y(movable_sprite.y() + movement_speed);
    }
}

// --- BATTLE FALL: Bits fall from the top of the screen to the bottom

void battle_fall_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 48; t++)
    {

        int x = global_data_ptr->bn_random.get_int(110) - 50;

        auto new_bit = sprite_items::hearts.create_sprite(x, (-24 * t) - 48, 4);
        mg.bits.push_back(new_bit);
    }
}

int battle_fall(mini_game &mg, character_manager *ch_man)
{
    int min_y = 0;

    for (auto &bit : mg.bits)
    {
        int vy = 1;
        bit.set_position(bit.x(), bit.y() + vy);

        if (bit.y() < min_y)
        {
            min_y = bit.y().integer();
        }

        // Collision
        if (close(bit.x(), bit.y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            bit.set_position(global_data_ptr->bn_random.get_int(120), -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        // All bits have fallen
        return 1;
    }

    handle_movement_input(*mg.eye, 2, -64, 64);
    return 0;
}

// --- BATTLE FALL FAST: Bits fall from the top of the screen to the bottom

void battle_fall_fast_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 48; t++)
    {

        int x = global_data_ptr->bn_random.get_int(110) - 50;

        auto new_bit = sprite_items::hearts.create_sprite(x, (-48 * t) - 48, 4);
        mg.bits.push_back(new_bit);
    }
}

int battle_fall_fast(mini_game &mg, character_manager *ch_man)
{
    int min_y = 0;

    for (auto &bit : mg.bits)
    {
        int vy = 2;
        bit.set_position(bit.x(), bit.y() + vy);

        if (bit.y() < min_y)
        {
            min_y = bit.y().integer();
        }

        // Collision
        if (close(bit.x(), bit.y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            bit.set_position(global_data_ptr->bn_random.get_int(120), -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        // All bits have fallen
        return 1;
    }

    handle_movement_input(*mg.eye, 2, -56, 56);
    return 0;
}

// --- BATTLE FALL WOBBLE: Bits fall from the top of the screen to the bottom

#define BATTLE_FALL_WOBBLE_TICKER 48

void battle_fall_wobble_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 48; t++)
    {
        mg.vars[t] = global_data_ptr->bn_random.get_int(100) - 50; // x position

        auto new_bit = sprite_items::hearts.create_sprite(mg.vars[t], (-24 * t) - 48, 4);
        mg.bits.push_back(new_bit);
    }
}

int battle_fall_wobble(mini_game &mg, character_manager *ch_man)
{
    int min_y = 0;
    fixed_t<4> *ticker = &mg.vars[48]; // ticker stored after x positions

    for (int t = 0; t < 48; t++)
    {
        auto bit = &mg.bits.at(t);

        int vy = 1;
        bit->set_position(mg.vars[t] + (degrees_sin(ticker->integer() % 360) * 32), bit->y() + vy);

        if (bit->y() < min_y)
        {
            min_y = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            bit->set_position(global_data_ptr->bn_random.get_int(120), -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        // All bits have fallen
        return 1;
    }

    handle_movement_input(*mg.eye, 2, -64, 64);

    (*ticker) += 1;
    return 0;
}

// --- BATTLE SPIRAL: Bits spiral inward from the edges

void battle_spiral_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 32; t++)
    {
        // Store initial angle for each bit
        mg.vars[t] = t * 11; // angle in degrees

        auto new_bit = sprite_items::hearts.create_sprite(0, 0, 4);
        mg.bits.push_back(new_bit);
    }

    mg.vars[32] = 60; // radius (stored separately)
}

int battle_spiral(mini_game &mg, character_manager *ch_man)
{
    fixed_t<4> *radius = &mg.vars[32];

    for (int t = 0; t < 32; t++)
    {
        auto bit = &mg.bits.at(t);

        // Update angle
        mg.vars[t] += 3;
        int angle = mg.vars[t].integer() % 360;

        // Position bit in spiral
        fixed_t<4> x = degrees_sin(angle) * (*radius);
        fixed_t<4> y = degrees_cos(angle) * (*radius);
        bit->set_position(x, y);

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            // Reset bit to outer edge
            mg.vars[t] = global_data_ptr->bn_random.get_int(360);
            *radius = 60;
        }
    }

    // Spiral contracts inward
    (*radius) -= fixed_t<4>(0.5);

    if (*radius < 5)
    {
        return 1; // Battle complete
    }

    handle_movement_input(*mg.eye, 2, -60, 60);
    return 0;
}

// --- BATTLE WALLS: Vertical walls sweep across screen with gaps

void battle_walls_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    // Create 6 walls
    for (int wall = 0; wall < 6; wall++)
    {
        int gap_y = global_data_ptr->bn_random.get_int(80) - 40;
        mg.vars[wall] = gap_y; // Store gap position

        // Each wall has bits above and below the gap
        for (int y = -64; y < -16; y += 12)
        {
            if (y < gap_y - 20 || y > gap_y + 20)
            {
                auto new_bit = sprite_items::hearts.create_sprite(-64 - (wall * 40), y, 4);
                mg.bits.push_back(new_bit);
            }
        }

        for (int y = 16; y <= 64; y += 12)
        {
            if (y < gap_y - 20 || y > gap_y + 20)
            {
                auto new_bit = sprite_items::hearts.create_sprite(-64 - (wall * 40), y, 4);
                mg.bits.push_back(new_bit);
            }
        }
    }
}

int battle_walls(mini_game &mg, character_manager *ch_man)
{
    int max_x = -200;

    for (auto &bit : mg.bits)
    {
        bit.set_position(bit.x() + 1, bit.y());

        if (bit.x() > max_x)
        {
            max_x = bit.x().integer();
        }

        // Collision
        if (close(bit.x(), bit.y(), mg.eye->x(), mg.eye->y(), 10))
        {
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit.set_position(-200, bit.y());
        }
    }

    if (max_x > 80)
    {
        return 1; // All walls passed
    }

    handle_movement_input(*mg.eye, 2, -64, 64);
    return 0;
}

// --- BATTLE ZIGZAG: Bits move in zigzag patterns down the screen

void battle_zigzag_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 40; t++)
    {
        int x = (t % 5) * 30 - 60;
        int y = -64 - (t / 5) * 30;

        mg.vars[t] = 0; // Direction flag (0 = right, 1 = left)

        auto new_bit = sprite_items::hearts.create_sprite(x, y, 4);
        mg.bits.push_back(new_bit);
    }
}

int battle_zigzag(mini_game &mg, character_manager *ch_man)
{
    int min_y = 0;

    for (int t = 0; t < 40; t++)
    {
        auto bit = &mg.bits.at(t);

        // Move down
        bit->set_y(bit->y() + 1);

        // Zigzag horizontally
        if (mg.vars[t] < 0.5) // Moving right
        {
            bit->set_x(bit->x() + 1);
            if (bit->x() > 60)
            {
                mg.vars[t] = 1; // Switch to left
            }
        }
        else // Moving left
        {
            bit->set_x(bit->x() - 1);
            if (bit->x() < -60)
            {
                mg.vars[t] = 0; // Switch to right
            }
        }

        if (bit->y() < min_y)
        {
            min_y = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            bit->set_position(global_data_ptr->bn_random.get_int(120) - 60, -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        return 1;
    }

    handle_movement_input(*mg.eye, 2, -64, 64);
    return 0;
}

// --- BATTLE CONVERGE: Bits converge from all edges toward center

void battle_converge_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    for (int t = 0; t < 40; t++)
    {
        int side = t % 4;

        fixed_t<4> start_x = 0;
        fixed_t<4> start_y = 0;

        // Position on one of four edges
        if (side == 0) // Top
        {
            start_x = global_data_ptr->bn_random.get_int(128) - 64;
            start_y = -64;
        }
        else if (side == 1) // Right
        {
            start_x = 64;
            start_y = global_data_ptr->bn_random.get_int(128) - 64;
        }
        else if (side == 2) // Bottom
        {
            start_x = global_data_ptr->bn_random.get_int(128) - 64;
            start_y = 64;
        }
        else // Left
        {
            start_x = -64;
            start_y = global_data_ptr->bn_random.get_int(128) - 64;
        }

        mg.vars[t * 2] = start_x;
        mg.vars[t * 2 + 1] = start_y;

        auto new_bit = sprite_items::hearts.create_sprite(start_x, start_y, 4);
        mg.bits.push_back(new_bit);
    }

    mg.vars[80] = 0; // Convergence progress timer
}

int battle_converge(mini_game &mg, character_manager *ch_man)
{
    fixed_t<4> *timer = &mg.vars[80];
    (*timer) += 1;

    for (int t = 0; t < 40; t++)
    {
        auto bit = &mg.bits.at(t);

        fixed_t<4> start_x = mg.vars[t * 2];
        fixed_t<4> start_y = mg.vars[t * 2 + 1];

        // Interpolate toward center
        fixed_t<4> progress = (*timer) / 120;
        if (progress > 1)
            progress = 1;

        fixed_t<4> target_x = start_x * (1 - progress);
        fixed_t<4> target_y = start_y * (1 - progress);

        bit->set_position(target_x, target_y);

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;

            // Reset bit to edge
            int side = global_data_ptr->bn_random.get_int(4);
            if (side == 0)
            {
                bit->set_position(global_data_ptr->bn_random.get_int(128) - 64, -64);
            }
            else if (side == 1)
            {
                bit->set_position(64, global_data_ptr->bn_random.get_int(128) - 64);
            }
            else if (side == 2)
            {
                bit->set_position(global_data_ptr->bn_random.get_int(128) - 64, 64);
            }
            else
            {
                bit->set_position(-64, global_data_ptr->bn_random.get_int(128) - 64);
            }

            mg.vars[t * 2] = bit->x();
            mg.vars[t * 2 + 1] = bit->y();
        }
    }

    if (*timer > 150)
    {
        return 1; // Convergence complete
    }

    handle_movement_input(*mg.eye, 2, -50, 50);
    return 0;
}

// --- BATTLE PULSE: Expanding rings of bits pulse from center

void battle_pulse_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    // 8 bits per ring, 5 rings
    for (int ring = 0; ring < 5; ring++)
    {
        for (int i = 0; i < 8; i++)
        {
            int angle = i * 45;
            mg.vars[ring * 8 + i] = angle;

            auto new_bit = sprite_items::hearts.create_sprite(0, 0, 4);
            mg.bits.push_back(new_bit);
        }
    }

    mg.vars[40] = 0; // Pulse timer
}

int battle_pulse(mini_game &mg, character_manager *ch_man)
{
    fixed_t<4> *timer = &mg.vars[40];
    (*timer) += 1;

    for (int ring = 0; ring < 5; ring++)
    {
        // Each ring expands at different times
        fixed_t<4> ring_radius = (*timer) - (ring * 30);

        if (ring_radius < 0)
            ring_radius = 0;
        if (ring_radius > 80)
            ring_radius = 80;

        for (int i = 0; i < 8; i++)
        {
            auto bit = &mg.bits.at(ring * 8 + i);
            int angle = mg.vars[ring * 8 + i].integer();

            fixed_t<4> x = degrees_sin(angle) * ring_radius;
            fixed_t<4> y = degrees_cos(angle) * ring_radius;

            bit->set_position(x, y);

            // Collision
            if (ring_radius > 5 && ring_radius < 75 &&
                close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
            {
                sound_items::sfx_damage.play();
                global_data_ptr->hp[0] -= 1;
                ring_radius = 80; // Push bit to outer edge
            }
        }
    }

    if (*timer > 200)
    {
        return 1; // All pulses complete
    }

    handle_movement_input(*mg.eye, 2, -64, 64);
    return 0;
}

// --- BATTLE CROSSFIRE: Bits move horizontally and vertically in alternating waves

void battle_crossfire_init(mini_game &mg)
{
    mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

    // Horizontal movers
    for (int i = 0; i < 10; i++)
    {
        int y = (i - 5) * 13;
        mg.vars[i] = y; // Store y position

        auto new_bit = sprite_items::hearts.create_sprite(-80, y, 4);
        mg.bits.push_back(new_bit);
    }

    // Vertical movers
    for (int i = 0; i < 10; i++)
    {
        int x = (i - 5) * 13;
        mg.vars[10 + i] = x; // Store x position

        auto new_bit = sprite_items::hearts.create_sprite(x, -80, 4);
        mg.bits.push_back(new_bit);
    }

    mg.vars[20] = 0; // Timer for wave control
}

int battle_crossfire(mini_game &mg, character_manager *ch_man)
{
    fixed_t<4> *timer = &mg.vars[20];
    (*timer) += 1;

    int max_pos = -200;

    // Update horizontal bits
    for (int i = 0; i < 10; i++)
    {
        auto bit = &mg.bits.at(i);
        bit->set_position(bit->x() + 2, mg.vars[i]);

        if (bit->x() > max_pos)
        {
            max_pos = bit->x().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit->set_position(-80, mg.vars[i]);
        }
    }

    // Update vertical bits
    for (int i = 0; i < 10; i++)
    {
        auto bit = &mg.bits.at(10 + i);
        bit->set_position(mg.vars[10 + i], bit->y() + 2);

        if (bit->y() > max_pos)
        {
            max_pos = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit->set_position(mg.vars[10 + i], -80);
        }
    }

    if (max_pos > 100)
    {
        return 1; // All waves passed
    }

    handle_movement_input(*mg.eye, 2, -64, 64);
    return 0;
}