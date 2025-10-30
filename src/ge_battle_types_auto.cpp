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
#include "bn_sound.h"
#include "bn_sound_items.h"
#include "bn_random.h"
#include "bn_sprite_items_hearts.h"

using namespace bn;

/*

The boundary of the game screen is -58 to 58 in x and y.

The mini game's "vars" variable is where to store all persistent data needed for the mini-game.

vars: maximum 192 elements
bits: maximum 48 elements

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

int battle_fall(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // OPTIMIZED: Move eye to (0, 48) to prevent initial collision with falling bits
        mg.eye = sprite_items::hearts.create_sprite(0, 48, 1);

        for (int t = 0; t < 48; t++)
        {
            int x = global_data_ptr->bn_random.get_int(110) - 50;
            auto new_bit = sprite_items::hearts.create_sprite(x, (-24 * t) - 48, 4);
            mg.bits.push_back(new_bit);
        }
    }

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
            sound::stop_all();
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

    handle_movement_input(*mg.eye, 2, -58, 58);
    return 0;
}

// --- BATTLE FALL FAST: Bits fall from the top of the screen to the bottom

int battle_fall_fast(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // OPTIMIZED: Move eye to (0, 48) to prevent initial collision with falling bits
        mg.eye = sprite_items::hearts.create_sprite(0, 48, 1);

        for (int t = 0; t < 48; t++)
        {
            int x = global_data_ptr->bn_random.get_int(110) - 50;
            auto new_bit = sprite_items::hearts.create_sprite(x, (-48 * t) - 48, 4);
            mg.bits.push_back(new_bit);
        }
    }

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
            sound::stop_all();
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

int battle_fall_wobble(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // OPTIMIZED: Move eye to (0, 48) to prevent initial collision with falling bits
        mg.eye = sprite_items::hearts.create_sprite(0, 48, 1);

        for (int t = 0; t < 48; t++)
        {
            mg.vars[t] = global_data_ptr->bn_random.get_int(100) - 50; // x position
            auto new_bit = sprite_items::hearts.create_sprite(mg.vars[t], (-24 * t) - 48, 4);
            mg.bits.push_back(new_bit);
        }
    }

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
            sound::stop_all();
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

    handle_movement_input(*mg.eye, 2, -58, 58);

    (*ticker) += 1;
    return 0;
}

// --- BATTLE SPIRAL: Bits spiral inward from the edges

int battle_spiral(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // No optimization needed: bits start far from (0, 0) due to initial radius
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
            sound::stop_all();
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

int battle_walls(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // OPTIMIZED: Move eye to (48, 0) to prevent initial collision with wall bits
        mg.eye = sprite_items::hearts.create_sprite(48, 0, 1);

        // Create 6 walls
        for (int wall = 0; wall < 6; wall++)
        {
            int gap_y = global_data_ptr->bn_random.get_int(80) - 40;
            mg.vars[wall] = gap_y; // Store gap position

            // Each wall has bits above and below the gap
            for (int y = -58; y < -16; y += 12)
            {
                if (y < gap_y - 20 || y > gap_y + 20)
                {
                    auto new_bit = sprite_items::hearts.create_sprite(-58 - (wall * 40), y, 4);
                    mg.bits.push_back(new_bit);
                }
            }

            for (int y = 16; y <= 58; y += 12)
            {
                if (y < gap_y - 20 || y > gap_y + 20)
                {
                    auto new_bit = sprite_items::hearts.create_sprite(-58 - (wall * 40), y, 4);
                    mg.bits.push_back(new_bit);
                }
            }
        }
    }

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
            sound::stop_all();
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit.set_position(-200, bit.y());
        }
    }

    if (max_x > 80)
    {
        return 1; // All walls passed
    }

    handle_movement_input(*mg.eye, 2, -58, 58);
    return 0;
}

// --- BATTLE ZIGZAG: Bits move in zigzag patterns down the screen

int battle_zigzag(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // No optimization needed: bits start off-screen
        mg.eye = sprite_items::hearts.create_sprite(0, 0, 1);

        for (int t = 0; t < 40; t++)
        {
            int x = (t % 5) * 30 - 60;
            int y = -58 - (t / 5) * 30;

            mg.vars[t] = 0; // Direction flag (0 = right, 1 = left)

            auto new_bit = sprite_items::hearts.create_sprite(x, y, 4);
            mg.bits.push_back(new_bit);
        }
    }

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
            sound::stop_all();
            sound_items::sfx_damage.play();
            bit->set_position(global_data_ptr->bn_random.get_int(120) - 60, -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        return 1;
    }

    handle_movement_input(*mg.eye, 2, -58, 58);
    return 0;
}

// --- BATTLE CONVERGE: Bits converge from all edges toward center

int battle_converge(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // OPTIMIZED: Move eye to (0, 40) to prevent initial collision at center
        mg.eye = sprite_items::hearts.create_sprite(0, 40, 1);

        for (int t = 0; t < 40; t++)
        {
            int side = t % 4;

            fixed_t<4> start_x = 0;
            fixed_t<4> start_y = 0;

            // Position on one of four edges
            if (side == 0) // Top
            {
                start_x = global_data_ptr->bn_random.get_int(128) - 58;
                start_y = -58;
            }
            else if (side == 1) // Right
            {
                start_x = 58;
                start_y = global_data_ptr->bn_random.get_int(128) - 58;
            }
            else if (side == 2) // Bottom
            {
                start_x = global_data_ptr->bn_random.get_int(128) - 58;
                start_y = 58;
            }
            else // Left
            {
                start_x = -58;
                start_y = global_data_ptr->bn_random.get_int(128) - 58;
            }

            mg.vars[t * 2] = start_x;
            mg.vars[t * 2 + 1] = start_y;

            auto new_bit = sprite_items::hearts.create_sprite(start_x, start_y, 4);
            mg.bits.push_back(new_bit);
        }

        mg.vars[80] = 0; // Convergence progress timer
    }

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
            sound::stop_all();
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;

            // Reset bit to edge
            int side = global_data_ptr->bn_random.get_int(4);
            if (side == 0)
            {
                bit->set_position(global_data_ptr->bn_random.get_int(128) - 58, -58);
            }
            else if (side == 1)
            {
                bit->set_position(58, global_data_ptr->bn_random.get_int(128) - 58);
            }
            else if (side == 2)
            {
                bit->set_position(global_data_ptr->bn_random.get_int(128) - 58, 58);
            }
            else
            {
                bit->set_position(-58, global_data_ptr->bn_random.get_int(128) - 58);
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

int battle_pulse(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // No optimization needed: already spawns eye away from center
        mg.eye = sprite_items::hearts.create_sprite(0, 48, 1);

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
                sound::stop_all();
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

    handle_movement_input(*mg.eye, 2, -58, 58);
    return 0;
}

// --- BATTLE CROSSFIRE: Bits move horizontally and vertically in alternating waves

int battle_crossfire(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // No optimization needed: bits start off-screen
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
            sound::stop_all();
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
            sound::stop_all();
            sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit->set_position(mg.vars[10 + i], -80);
        }
    }

    if (max_pos > 100)
    {
        return 1; // All waves passed
    }

    handle_movement_input(*mg.eye, 2, -58, 58);
    return 0;
}

// --- BATTLE BREAKOUT: Classic breakout game with paddle, ball, and blocks

int battle_breakout(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // Create paddle (eye) at bottom center
        mg.eye = sprite_items::hearts.create_sprite(0, 50, 1);

        // Create ball (first bit)
        auto ball = sprite_items::hearts.create_sprite(0, 30, 4);
        mg.bits.push_back(ball);

        // Initialize ball velocity in vars
        mg.vars[0] = 1;  // vx (horizontal velocity)
        mg.vars[1] = -2; // vy (vertical velocity, negative = moving up)

        // Create blocks in rows at the top
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                int x = (col - 3) * 12 - 7; // Spread blocks across screen
                int y = -50 + (row * 10);   // Stack rows from top

                auto block = sprite_items::hearts.create_sprite(x, y, 4);
                mg.bits.push_back(block);
            }
        }
    }

    // Handle paddle movement (horizontal only, locked at bottom)
    if (keypad::left_held() && mg.eye->x() > -56)
    {
        mg.eye->set_x(mg.eye->x() - 3);
    }
    else if (keypad::right_held() && mg.eye->x() < 56)
    {
        mg.eye->set_x(mg.eye->x() + 3);
    }
    mg.eye->set_y(50); // Lock paddle at bottom

    // Get ball reference (always first bit)
    auto ball = &mg.bits[0];

    // Get ball velocity from vars
    fixed_t<4> vx = mg.vars[0];
    fixed_t<4> vy = mg.vars[1];

    // Update ball position
    ball->set_position(ball->x() + vx, ball->y() + vy);

    // Bounce off left/right walls
    if (ball->x() <= -58 || ball->x() >= 58)
    {
        vx = -vx;
        mg.vars[0] = vx;
        ball->set_x(ball->x() + vx); // Move back inside bounds
    }

    // Bounce off top wall
    if (ball->y() <= -58)
    {
        vy = -vy;
        mg.vars[1] = vy;
        ball->set_y(ball->y() + vy);
    }

    // Paddle collision detection
    if (ball->y() >= 45 && ball->y() <= 55 &&
        abs(ball->x() - mg.eye->x()) < 14)
    {
        // Bounce ball upward
        vy = -abs(vy);
        mg.vars[1] = vy;

        // Adjust horizontal velocity based on where ball hit paddle
        fixed_t<4> hit_offset = ball->x() - mg.eye->x();
        vx = hit_offset / 4; // Further from center = sharper angle

        // Clamp velocity to reasonable range
        if (vx > 3)
            vx = 3;
        if (vx < -3)
            vx = -3;
        mg.vars[0] = vx;

        // Ensure minimum vertical speed
        if (abs(vy) < 1.5)
        {
            vy = vy < 0 ? -2 : 2;
            mg.vars[1] = vy;
        }

        sound_items::sfx_damage.play();
    }

    // Block collision detection (check all bits except ball at index 0)
    for (int i = mg.bits.size() - 1; i >= 1; i--)
    {
        auto block = &mg.bits[i];

        if (close(ball->x(), ball->y(), block->x(), block->y(), 10))
        {
            // Bounce ball
            vy = -vy;
            mg.vars[1] = vy;

            // Destroy block
            mg.bits.erase(mg.bits.begin() + i);

            sound_items::sfx_wack_his_pipis.play();
            break; // Only destroy one block per frame
        }
    }

    // Check if ball fell below paddle (lose condition)
    if (ball->y() > 58)
    {
        sound::stop_all();
        sound_items::sfx_damage.play();
        global_data_ptr->hp[0] -= 1;

        // Reset ball to starting position
        ball->set_position(0, 30);
        mg.vars[0] = 1;
        mg.vars[1] = -2;
    }

    // Win condition: all blocks destroyed (only ball remains)
    if (mg.bits.size() == 1)
    {
        return 1; // Battle complete!
    }

    return 0;
}

// --- BATTLE PLATFORMER: Simple platformer with jumping and enemies

int battle_platformer(bool init, mini_game &mg, character_manager *ch_man)
{
    if (init)
    {
        // Player starts on left side, grounded
        mg.eye = sprite_items::hearts.create_sprite(-40, 35, 1);

        // Initialize player physics vars
        mg.vars[0] = 0; // vertical velocity
        mg.vars[1] = 1; // grounded flag (1 = on ground, 0 = in air)
        mg.vars[2] = 0; // jump button was pressed last frame

        // Create 4 patrolling enemies
        for (int i = 0; i < 2; i++)
        {
            int x = -20 + (i * 30);
            auto enemy = sprite_items::hearts.create_sprite(x, 35, 4);
            mg.bits.push_back(enemy);

            // Store enemy initial position and velocity
            mg.vars[3 + i] = x;                     // enemy world position
            mg.vars[7 + i] = (i % 2 == 0) ? 1 : -1; // enemy velocity (alternating directions)
        }

        // Create platform blocks (visual representation)
        // Ground level platforms
        for (int x = -58; x <= 58; x += 12)
        {
            auto block = sprite_items::hearts.create_sprite(x, 45, 4);
            mg.bits.push_back(block);
        }

        // Mid-level platforms (bits 14-18)
        int platform_positions[] = {-40, -20, 0, 20, 40};
        for (int i = 0; i < 5; i++)
        {
            auto block = sprite_items::hearts.create_sprite(platform_positions[i], 10, 4);
            mg.bits.push_back(block);
        }

        // High platform (goal area) - bits 19-20
        auto block1 = sprite_items::hearts.create_sprite(35, -20, 4);
        auto block2 = sprite_items::hearts.create_sprite(47, -20, 4);
        mg.bits.push_back(block1);
        mg.bits.push_back(block2);

        // Goal flag (bit 21)
        auto flag = sprite_items::hearts.create_sprite(41, -35, 3);
        mg.bits.push_back(flag);
    }

    const fixed_t<4> GRAVITY = fixed_t<4>(0.3);
    const fixed_t<4> JUMP_POWER = fixed_t<4>(-4.5);
    const fixed_t<4> MOVE_SPEED = fixed_t<4>(2);
    const fixed_t<4> MAX_FALL_SPEED = fixed_t<4>(6);

    // Get player state
    fixed_t<4> vy = mg.vars[0];
    bool grounded = mg.vars[1] > 0.5;
    bool jump_was_pressed = mg.vars[2] > 0.5;

    // --- Player Movement ---
    // Horizontal movement
    if (keypad::left_held() && mg.eye->x() > -58)
    {
        mg.eye->set_x(mg.eye->x() - MOVE_SPEED);
    }
    else if (keypad::right_held() && mg.eye->x() < 58)
    {
        mg.eye->set_x(mg.eye->x() + MOVE_SPEED);
    }

    // Jump input
    bool jump_pressed = keypad::a_held() || keypad::b_held();
    if (jump_pressed && !jump_was_pressed && grounded)
    {
        vy = JUMP_POWER;
        grounded = false;
        sound_items::sfx_wack_his_pipis.play();
    }
    mg.vars[2] = jump_pressed ? 1 : 0;

    // --- Apply Gravity ---
    if (!grounded)
    {
        vy += GRAVITY;
        if (vy > MAX_FALL_SPEED)
            vy = MAX_FALL_SPEED;
    }

    // Update vertical position
    mg.eye->set_y(mg.eye->y() + vy);

    // --- Platform Collision ---
    grounded = false;

    // Check ground (y = 45)
    if (mg.eye->y() >= 35 && vy >= 0)
    {
        mg.eye->set_y(35);
        vy = 0;
        grounded = true;
    }

    // Check mid platforms (y = 10)
    if (!grounded && mg.eye->y() >= 0 && mg.eye->y() <= 10 && vy >= 0)
    {
        int px = mg.eye->x().integer();
        if ((px >= -50 && px <= -30) || (px >= -30 && px <= -10) ||
            (px >= -10 && px <= 10) || (px >= 10 && px <= 30) || (px >= 30 && px <= 50))
        {
            mg.eye->set_y(0);
            vy = 0;
            grounded = true;
        }
    }

    // Check high platform (y = -20)
    if (!grounded && mg.eye->y() >= -30 && mg.eye->y() <= -20 && vy >= 0)
    {
        int px = mg.eye->x().integer();
        if (px >= 25 && px <= 57)
        {
            mg.eye->set_y(-30);
            vy = 0;
            grounded = true;
        }
    }

    // --- Update Enemies (bits 0-3) ---
    for (int i = 0; i < 2; i++) // NOTE: Only 2 enemies are created in init, so loop limit should be 2
    {
        auto enemy = &mg.bits[i];

        // Update enemy position
        mg.vars[3 + i] += mg.vars[7 + i];

        // Bounce off boundaries
        if (mg.vars[3 + i] < -55 || mg.vars[3 + i] > 55)
        {
            mg.vars[7 + i] = -mg.vars[7 + i];
        }

        enemy->set_x(mg.vars[3 + i]);

        // Check collision with player
        if (close(enemy->x(), enemy->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // Check if player is stomping (falling onto enemy from above)
            if (vy > 0 && mg.eye->y() < enemy->y() - 5)
            {
                // Stomp enemy - move it off screen
                mg.vars[3 + i] = -200;
                enemy->set_position(-200, -200);
                vy = fixed_t<4>(-3); // Bounce
                sound_items::sfx_wack_his_pipis.play();
            }
            else if (mg.vars[3 + i] > -100) // Only damage if enemy is alive
            {
                // Take damage
                sound::stop_all();
                sound_items::sfx_damage.play();
                global_data_ptr->hp[0] -= 1;

                // Knockback
                mg.eye->set_position(-40, 35);
                vy = 0;
                grounded = true;
            }
        }
    }

    // --- Check Win Condition ---
    // Player reaches the goal flag
    if (mg.eye->y() < -25 && mg.eye->x() > 30)
    {
        sound_items::sfx_wack_his_pipis.play();
        return 1; // Level complete!
    }

    // Check if player fell off the screen
    if (mg.eye->y() > 70)
    {
        sound::stop_all();
        sound_items::sfx_damage.play();
        global_data_ptr->hp[0] -= 1;

        // Reset to start
        mg.eye->set_position(-40, 35);
        vy = 0;
        grounded = true;
    }

    // Save state
    mg.vars[0] = vy;
    mg.vars[1] = grounded ? 1 : 0;

    return 0;
}