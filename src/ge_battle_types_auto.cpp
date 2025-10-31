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
#include "bn_sprite_items_dartboard.h"
#include "bn_sprite_items_darts.h"
#include "bn_sprite_items_battle_squares.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_string.h"
#include "bn_blending.h"

#include "ge_text.h"

using namespace bn;

// Enumerations for Darts game state (Assuming these are defined in ge_battle_types_auto.h)
enum dart_states
{
    DART_INTRO = 0,
    DART_AIMING = 1,
    DART_POWER = 2,
    DART_THROWING = 3,
    DART_RESULT = 4
};

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
    return dist_squared <= fixed_t<4>(threshold * threshold);
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
            // sound::stop_all();
            // sound_items::sfx_damage.play();
            bit.set_position(global_data_ptr->bn_random.get_int(120), -128);
            global_data_ptr->hp[0] -= 1;
        }
    }

    if (min_y > 96)
    {
        // All bits have fallen
        return 1;
    }

    if (mg.eye.has_value())
    {
        handle_movement_input(mg.eye, 2, -58, 58);
    }

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
            // sound::stop_all();
            // sound_items::sfx_damage.play();
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
        mg.vars[48] = fixed_t<4>(0); // Initialize ticker
    }

    int min_y = 0;
    fixed_t<4> *ticker = &mg.vars[48]; // ticker stored after x positions

    for (int t = 0; t < 48; t++)
    {
        auto bit = &mg.bits.at(t);

        int vy = 1;
        fixed_t<4> base_x = mg.vars[t];
        fixed_t<4> wobble_x = degrees_sin(ticker->integer() % 360) * 32;

        bit->set_position(base_x + wobble_x, bit->y() + vy);

        if (bit->y() < min_y)
        {
            min_y = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
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

    (*ticker) += fixed_t<4>(1);
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
        mg.vars[t] += fixed_t<4>(3);
        int angle = mg.vars[t].integer() % 360;

        // Position bit in spiral
        fixed_t<4> x = degrees_sin(angle) * (*radius);
        fixed_t<4> y = degrees_cos(angle) * (*radius);
        bit->set_position(x, y);

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            // Reset bit to outer edge
            mg.vars[t] = global_data_ptr->bn_random.get_int(360);
            *radius = fixed_t<4>(60);
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
            // sound::stop_all();
            // sound_items::sfx_damage.play();
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
        if (mg.vars[t] < 0.5) // Moving right {
            bit->set_x(bit->x() + 1);
        if (bit->x() > 60)

        {
            mg.vars[t] = 1; // Switch to left
        }
        else // Moving left {
            bit->set_x(bit->x() - 1);
        if (bit->x() < -60)

        {
            mg.vars[t] = 0; // Switch to right
        }

        if (bit->y() < min_y)
        {
            min_y = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
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
                start_x = global_data_ptr->bn_random.get_fixed(-58, 58);
                start_y = fixed_t<4>(-58);
            }
            else if (side == 1) // Right

            {
                start_x = fixed_t<4>(58);
                start_y = global_data_ptr->bn_random.get_fixed(-58, 58);
            }
            else if (side == 2) // Bottom

            {
                start_x = global_data_ptr->bn_random.get_fixed(-58, 58);
                start_y = fixed_t<4>(58);
            }
            else // Left

            {
                start_x = fixed_t<4>(-58);
                start_y = global_data_ptr->bn_random.get_fixed(-58, 58);
            }

            mg.vars[t * 2] = start_x;
            mg.vars[t * 2 + 1] = start_y;

            auto new_bit = sprite_items::hearts.create_sprite(start_x, start_y, 4);
            mg.bits.push_back(new_bit);
        }

        mg.vars[80] = 0; // Convergence progress timer
    }

    fixed_t<4> *timer = &mg.vars[80];
    (*timer) += fixed_t<4>(1);

    for (int t = 0; t < 40; t++)
    {
        auto bit = &mg.bits.at(t);

        fixed_t<4> start_x = mg.vars[t * 2];
        fixed_t<4> start_y = mg.vars[t * 2 + 1];

        // Interpolate toward center
        fixed_t<4> progress = (*timer) / fixed_t<4>(120);
        if (progress > 1)
            progress = 1;

        fixed_t<4> target_x = start_x * (fixed_t<4>(1) - progress);
        fixed_t<4> target_y = start_y * (fixed_t<4>(1) - progress);

        bit->set_position(target_x, target_y);

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;

            // Reset bit to edge
            int side = global_data_ptr->bn_random.get_int(4);
            if (side == 0)

            {
                bit->set_position(global_data_ptr->bn_random.get_fixed(-58, 58), fixed_t<4>(-58));
            }
            else if (side == 1)

            {
                bit->set_position(fixed_t<4>(58), global_data_ptr->bn_random.get_fixed(-58, 58));
            }
            else if (side == 2)

            {
                bit->set_position(global_data_ptr->bn_random.get_fixed(-58, 58), fixed_t<4>(58));
            }
            else

            {
                bit->set_position(fixed_t<4>(-58), global_data_ptr->bn_random.get_fixed(-58, 58));
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
                mg.vars[ring * 8 + i] = fixed_t<4>(angle);

                auto new_bit = sprite_items::hearts.create_sprite(0, 0, 4);
                mg.bits.push_back(new_bit);
            }
        }

        mg.vars[40] = 0; // Pulse timer
    }

    fixed_t<4> *timer = &mg.vars[40];
    (*timer) += fixed_t<4>(1);

    for (int ring = 0; ring < 5; ring++)
    {
        // Each ring expands at different times
        fixed_t<4> ring_radius = (*timer) - fixed_t<4>(ring * 30);

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
                // sound::stop_all();
                // sound_items::sfx_damage.play();
                global_data_ptr->hp[0] -= 1;
                // Reset ring radius to push bit out of collision range
                (*timer) = fixed_t<4>(ring * 30 + 80);
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
            mg.vars[i] = fixed_t<4>(y); // Store y position

            auto new_bit = sprite_items::hearts.create_sprite(-80, y, 4);
            mg.bits.push_back(new_bit);
        }

        // Vertical movers
        for (int i = 0; i < 10; i++)
        {
            int x = (i - 5) * 13;
            mg.vars[10 + i] = fixed_t<4>(x); // Store x position

            auto new_bit = sprite_items::hearts.create_sprite(x, -80, 4);
            mg.bits.push_back(new_bit);
        }

        mg.vars[20] = 0; // Timer for wave control
    }

    fixed_t<4> *timer = &mg.vars[20];
    (*timer) += fixed_t<4>(1);

    int max_pos = -200;

    // Update horizontal bits
    for (int i = 0; i < 10; i++)
    {
        auto bit = &mg.bits.at(i);
        bit->set_position(bit->x() + fixed_t<4>(2), mg.vars[i]);

        if (bit->x() > max_pos)
        {
            max_pos = bit->x().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit->set_position(fixed_t<4>(-80), mg.vars[i]);
        }
    }

    // Update vertical bits
    for (int i = 0; i < 10; i++)
    {
        auto bit = &mg.bits.at(10 + i);
        bit->set_position(mg.vars[10 + i], bit->y() + fixed_t<4>(2));

        if (bit->y() > max_pos)
        {
            max_pos = bit->y().integer();
        }

        // Collision
        if (close(bit->x(), bit->y(), mg.eye->x(), mg.eye->y(), 12))
        {
            // sound::stop_all();
            // sound_items::sfx_damage.play();
            global_data_ptr->hp[0] -= 1;
            bit->set_position(mg.vars[10 + i], fixed_t<4>(-80));
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
        mg.vars[0] = fixed_t<4>(1);
        // vx (horizontal velocity)
        mg.vars[1] = fixed_t<4>(-2); // vy (vertical velocity, negative = moving up)

        // Create blocks in rows at the top
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 8; col++)

            {
                int x = (col - 3) * 12 - 7; // Spread blocks across screen
                int y = -50 + (row * 10);
                // Stack rows from top

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
        bn::abs(ball->x() - mg.eye->x()) < 14)
    {
        // Bounce ball upward
        vy = -bn::abs(vy);
        mg.vars[1] = vy;

        // Adjust horizontal velocity based on where ball hit paddle
        fixed_t<4> hit_offset = ball->x() - mg.eye->x();
        vx = hit_offset / fixed_t<4>(4); // Further from center = sharper angle

        // Clamp velocity to reasonable range
        if (vx > 3)
            vx = 3;
        if (vx < -3)
            vx = -3;
        mg.vars[0] = vx;

        // Ensure minimum vertical speed
        if (bn::abs(vy) < 1.5)
        {
            vy = vy < 0 ? fixed_t<4>(-2) : fixed_t<4>(2);
            mg.vars[1] = vy;
        }

        sound_items::sfx_wack_his_pipis.play();
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
        // sound::stop_all();
        // sound_items::sfx_damage.play();
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