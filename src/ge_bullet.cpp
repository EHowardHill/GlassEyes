// ge_bullet.cpp - Enhanced implementation with more patterns
#include "ge_bullet.h"
#include "ge_globals.h"
#include "bn_sprite_items_hearts.h"
#include "bn_math.h"

using namespace bn;

const bullet_pattern PATTERNS[BULLET_SIZE] = {
    // vx    vy   amp  per  acc  flags
    {0, 2, 0, 0, 0, 0x00},        // BULLET_FALL
    {0, -2, 0, 0, 0, 0x00},       // BULLET_RISE
    {0, 2, 2, 2, 0, FLAG_WAVE},   // BULLET_WAVE
    {0, 2, 0, 0, 3, FLAG_ACCEL},  // BULLET_ACCEL
    {2, 2, 0, 0, 0, FLAG_BOUNCE}, // BULLET_BOUNCE
    {2, 2, 0, 0, 0, FLAG_HOMING}, // BULLET_HOMING

    // New patterns
    {0, 1, 40, 32, 0, FLAG_ORBIT},            // BULLET_ORBIT - circular motion
    {0, 1, 80, 48, -2, FLAG_SPIRAL},          // BULLET_SPIRAL - spiral inward
    {3, 2, 30, 16, 0, FLAG_ZIGZAG},           // BULLET_ZIGZAG - sharp turns
    {0, 2, 3, 3, 0, FLAG_WAVE | 0x4000},      // BULLET_DOUBLE_WAVE - compound wave
    {1, 1, 0, 0, 4, FLAG_SCATTER},            // BULLET_SCATTER - explode outward
    {0, 2, 0, 0, -3, FLAG_CONVERGE},          // BULLET_CONVERGE - converge to center
    {0, 1, 2, 2, 2, FLAG_WAVE | FLAG_ACCEL},  // BULLET_SINE_ACCEL
    {2, 2, 1, 4, 0, FLAG_BOUNCE | FLAG_WAVE}, // BULLET_BOUNCE_WAVE
    {1, 1, 20, 0, 0, FLAG_RANDOM},            // BULLET_RANDOM_WALK
    {0, 2, 30, 24, 0, FLAG_PULSE},            // BULLET_PULSE - pulsing motion
    {0, 2, 25, 16, 0, FLAG_HELIX},            // BULLET_HELIX - 3D-like spiral
    {0, 1, 45, 40, 0, FLAG_PENDULUM},         // BULLET_PENDULUM - swing motion
};

const int SINE_TABLE[64] = {
    0, 6, 12, 18, 24, 30, 35, 40, 45, 49, 53, 56, 59, 61, 63, 64,
    64, 64, 63, 61, 59, 56, 53, 49, 45, 40, 35, 30, 24, 18, 12, 6,
    0, -6, -12, -18, -24, -30, -35, -40, -45, -49, -53, -56, -59, -61, -63, -64,
    -64, -64, -63, -61, -59, -56, -53, -49, -45, -40, -35, -30, -24, -18, -12, -6};

bullet::bullet(int16_t x_pos, int16_t y_pos, int anim_type, int speed_multiplier)
{
    compact.x = x_pos;
    compact.y = y_pos;
    compact.ticker = 0;
    compact.type = anim_type;
    compact.state1 = 0;
    compact.state2 = 0;
    compact.state3 = 0;
    compact.init_x = x_pos;
    compact.speed = speed_multiplier;

    item = sprite_items::hearts.create_sprite(
        fixed(x_pos) / 4,
        fixed(y_pos) / 4,
        4);

    // Initialize type-specific state
    switch (anim_type)
    {
    case BULLET_BOUNCE:
    case BULLET_BOUNCE_WAVE:
        compact.state1 = (global_data_ptr->bn_random.get_int(2) ? 1 : -1);
        break;

    case BULLET_HOMING:
        compact.state1 = global_data_ptr->bn_random.get_int(-50, 50);
        compact.state2 = 0;
        break;

    case BULLET_ORBIT:
        compact.state1 = global_data_ptr->bn_random.get_int(64);    // Starting angle
        compact.state2 = 4 + global_data_ptr->bn_random.get_int(4); // Radius 25-45 (smaller)
        break;

    case BULLET_SPIRAL:
        compact.state1 = global_data_ptr->bn_random.get_int(64); // Starting angle
        compact.state2 = 120;                                    // Starting radius (large)
        break;

    case BULLET_ZIGZAG:
        compact.state1 = 1; // Direction
        compact.state2 = 0; // Zigzag counter
        break;

    case BULLET_SCATTER:
        // Random angle for scatter direction
        compact.state1 = global_data_ptr->bn_random.get_int(64);
        compact.state2 = 0; // Speed multiplier
        break;

    case BULLET_CONVERGE:
        // Target point (center of screen)
        compact.state1 = 0; // Target x
        compact.state2 = 0; // Target y
        break;

    case BULLET_RANDOM_WALK:
        compact.state1 = global_data_ptr->bn_random.get_int(-2, 3); // Random vx
        compact.state2 = global_data_ptr->bn_random.get_int(-1, 2); // Random vy
        compact.state3 = 0;                                         // Change counter
        break;

    case BULLET_HELIX:
        compact.state1 = global_data_ptr->bn_random.get_int(64); // Angle
        compact.state2 = 30;                                     // Radius
        compact.state3 = global_data_ptr->bn_random.get_int(2);  // Direction
        break;

    case BULLET_PENDULUM:
        compact.state1 = 32; // Start at middle of swing
        compact.state2 = 1;  // Swing direction
        break;
    }
}

void bullet::update()
{
    if (!item.has_value())
        return;

    const bullet_pattern &pattern = PATTERNS[compact.type];
    int x = compact.x;
    int y = compact.y;
    int speed = compact.speed;
    int flags = pattern.flags;

    // Apply speed multiplier to base velocities (speed = 100 means 100% normal speed)
    int vx_modified = (pattern.vx_base * speed) / 100;
    int vy_modified = (pattern.vy_base * speed) / 100;

    // Apply speed to acceleration as well
    int accel_modified = (pattern.accel * speed) / 100;

    // Handle complex movement patterns
    if (flags & FLAG_ZIGZAG)
    {
        // Sharp zigzag movement
        compact.state2++;
        if (compact.state2 >= (12 * 100 / speed)) // Adjust zigzag frequency with speed
        {
            compact.state2 = 0;
            compact.state1 = -compact.state1;
        }
        x += vx_modified * compact.state1;
        y += vy_modified;
    }
    else if (flags & FLAG_SCATTER)
    {
        // Scatter outward from initial position
        int cos_val = SINE_TABLE[(compact.state1 + 16) & 63];
        int sin_val = SINE_TABLE[compact.state1 & 63];

        compact.state2 = bn::min(compact.state2 + accel_modified, 255);

        x += (cos_val * compact.state2 * speed) / (512 * 100);
        y += (sin_val * compact.state2 * speed) / (512 * 100) + vy_modified;
    }
    else if (flags & FLAG_CONVERGE)
    {
        // Converge toward center
        int16_t target_x = compact.state1;
        int16_t target_y = compact.state2 * 4;

        int16_t dx = ((target_x - x) * speed) / (32 * 100);
        int16_t dy = ((target_y - y) * speed) / (32 * 100) + vy_modified;

        x += dx;
        y += dy;
    }
    else if (flags & FLAG_RANDOM)
    {
        // Random walk pattern
        compact.state3++;
        if (compact.state3 >= (20 * 100 / speed)) // Change direction based on speed
        {
            compact.state3 = 0;
            compact.state1 = global_data_ptr->bn_random.get_int(-3, 4);
            compact.state2 = global_data_ptr->bn_random.get_int(-2, 3);
        }

        x += (compact.state1 * speed) / 100 + vx_modified;
        y += (compact.state2 * speed) / 100 + vy_modified;
    }
    else if (flags & FLAG_PULSE)
    {
        // Pulsing movement (expand/contract)
        int phase = (compact.ticker * 64 * speed) / (pattern.period * 100);
        int pulse = SINE_TABLE[phase & 63];

        // Pulse affects speed
        int speed_mod = 64 + (pulse / 2);
        y += (vy_modified * speed_mod) / 64;

        // Also pulse horizontally for visual effect
        x = compact.init_x + (pulse * pattern.amplitude) / 64;
    }
    else if (flags & FLAG_HELIX)
    {
        // 3D helix pattern
        compact.state1 = (compact.state1 + (4 * speed / 100)) & 63;

        int cos_val = SINE_TABLE[(compact.state1 + 16) & 63];
        int sin_val = SINE_TABLE[compact.state1 & 63];

        // Create helix by combining circular motion with forward movement
        x = compact.init_x + (cos_val * pattern.amplitude) / 64;

        // Use sine for depth illusion (affects y slightly)
        int depth = (sin_val + 64) / 4; // 0 to 32 range
        y += vy_modified + (depth * speed) / (16 * 100);
    }
    else if (flags & FLAG_PENDULUM)
    {
        // Pendulum swing
        compact.state1 += (compact.state2 * 2 * speed) / 100;

        // Reverse at ends of swing
        if (compact.state1 <= 0 || compact.state1 >= 63)
        {
            compact.state2 = -compact.state2;
            compact.state1 = (compact.state1 <= 0) ? 0 : 63;
        }

        int swing = SINE_TABLE[compact.state1 & 63];
        x = compact.init_x + (swing * pattern.amplitude) / 32;
        y += vy_modified;
    }
    else if (flags & FLAG_ORBIT)
    {
        // Circular orbit
        compact.state1 = (compact.state1 + (2 * speed / 100)) & 63;

        int cos_val = SINE_TABLE[(compact.state1 + 16) & 63];
        int sin_val = SINE_TABLE[compact.state1 & 63];

        x = compact.init_x + (cos_val * compact.state2) / 64;
        y += vy_modified;

        // Add vertical component for full circle
        y += (sin_val * pattern.amplitude * speed) / (128 * 100);
    }
    else if (flags & FLAG_SPIRAL)
    {
        // Spiral pattern
        compact.state1 = (compact.state1 + (3 * speed / 100)) & 63;
        compact.state2 = bn::max(12, compact.state2 + accel_modified);

        int cos_val = SINE_TABLE[(compact.state1 + 16) & 63];
        int sin_val = SINE_TABLE[compact.state1 & 63];

        x = compact.init_x + (cos_val * compact.state2) / 64;
        y += vy_modified + (sin_val * compact.state2 * speed) / (256 * 100);
    }
    else if ((flags & FLAG_WAVE) && (flags & FLAG_ACCEL))
    {
        // Sine wave with acceleration
        int phase = (compact.ticker * 64 * speed) / (pattern.period * 100);
        int sine = SINE_TABLE[phase & 63];
        x = compact.x + (sine * pattern.amplitude) / 32;

        int16_t current_vy = vy_modified + (compact.ticker * accel_modified) / 128;
        if (current_vy > (56 * speed / 100))
            current_vy = (56 * speed / 100);
        y += current_vy;
    }
    else if ((flags & FLAG_BOUNCE) && (flags & FLAG_WAVE))
    {
        // Bouncing with wave overlay
        x += vx_modified * compact.state1;

        // Add wave to y movement
        int phase = (compact.ticker * 64 * speed) / (pattern.period * 100);
        int sine = SINE_TABLE[phase & 63];
        y += vy_modified + (sine * pattern.amplitude * speed) / (64 * 100);

        // Bounce off walls
        if (x < -240 || x > 240)
        {
            compact.state1 = -compact.state1;
            x = (x < 0) ? -240 : 240;
        }
    }
    else if (flags & 0x4000) // DOUBLE_WAVE special flag
    {
        // Two sine waves combined for complex motion
        int phase1 = (compact.ticker * 64 * speed) / (pattern.period * 100);
        int phase2 = (compact.ticker * 32 * speed) / (pattern.period * 100);

        int sine1 = SINE_TABLE[phase1 & 63];
        int sine2 = SINE_TABLE[phase2 & 63];

        x = compact.x + (sine1 * pattern.amplitude) / 32 + (sine2 * pattern.amplitude) / 64;
        y += vy_modified;
    }
    else if (flags & FLAG_WAVE)
    {
        // Original wave implementation
        int phase = (compact.ticker * 64 * speed) / (pattern.period * 100);
        int sine = SINE_TABLE[phase & 63];
        x = compact.x + (sine * pattern.amplitude) / 32;
        y += vy_modified;
    }
    else if (flags & FLAG_ACCEL)
    {
        // Original acceleration
        int16_t current_vy = vy_modified + (compact.ticker * accel_modified) / 128;
        if (current_vy > (56 * speed / 100))
            current_vy = (56 * speed / 100);
        y += current_vy;
    }
    else if (flags & FLAG_BOUNCE)
    {
        // Original bounce
        x += vx_modified * compact.state1;
        y += vy_modified;

        if (x < -240 || x > 240)
        {
            compact.state1 = -compact.state1;
            x = (x < 0) ? -240 : 240;
        }
    }
    else if (flags & FLAG_HOMING)
    {
        // Original homing implementation
        compact.state2++;

        if (compact.state2 >= (48 * 100 / speed)) // Adjust homing retarget frequency
        {
            compact.state2 = 0;
            compact.state1 = global_data_ptr->bn_random.get_int(-50, 50);
        }

        int16_t target_x = compact.state1 * 4;
        int16_t dx = ((target_x - x) * speed) / (20 * 100);
        int16_t dy = vy_modified;

        if (dx > (8 * speed / 100))
            dx = (8 * speed / 100);
        if (dx < -(8 * speed / 100))
            dx = -(8 * speed / 100);

        x += dx;
        y += dy;
    }
    else
    {
        // Simple linear movement (FALL, RISE)
        x += vx_modified;
        y += vy_modified;
    }

    compact.x = x;
    compact.y = y;
    compact.ticker++;

    item.value().set_position(fixed(x) / 4, fixed(y) + 64);
}

void bullet::populate(bn::vector<bullet, bullet_count> *bullets, int anim_type, int speed_multiplier)
{
    bullets->clear();

    for (int b = 0; b < bullet_count; b++)
    {
        int16_t x, y;

        // Type-specific starting positions
        switch (anim_type)
        {
        case BULLET_RISE:
            x = (-50 + global_data_ptr->bn_random.get_int(100)) * 4;
            y = (70 + (b * 6)) * 4;
            break;

        case BULLET_HOMING:
            if (b < 4)
            {
                x = -240;
                y = (-60 + (b * 30)) * 4;
            }
            else if (b < 8)
            {
                x = 240;
                y = (-60 + ((b - 4) * 30)) * 4;
            }
            else if (b < 12)
            {
                x = (-30 + ((b - 8) * 15)) * 4;
                y = -280;
            }
            else
            {
                x = (-30 + ((b - 12) * 15)) * 4;
                y = (-70 - ((b - 12) * 20)) * 4;
            }
            break;

        case BULLET_ORBIT:
            // Start in a circle formation
            {
                int angle = (b * 64) / bullet_count;
                int cos_val = SINE_TABLE[(angle + 16) & 63];
                int sin_val = SINE_TABLE[angle & 63];
                x = (cos_val * 40) / 64 * 4;
                y = (-40 + (sin_val / 2) / 64) - 64;
            }
            break;

        case BULLET_SPIRAL:
            // Start from center
            x = global_data_ptr->bn_random.get_int(-10, 10) * 4;
            y = (-60 - (b * 3)) * 4;
            break;

        case BULLET_ZIGZAG:
            // Line formation
            x = (-60 + (b * 6)) * 4;
            y = -280;
            break;

        case BULLET_SCATTER:
            // Start clustered in center
            x = global_data_ptr->bn_random.get_int(-5, 5) * 4;
            y = (-60 + global_data_ptr->bn_random.get_int(-5, 5)) * 4;
            break;

        case BULLET_CONVERGE:
            // Start from edges
            if (b % 2 == 0)
                x = -240 + global_data_ptr->bn_random.get_int(20);
            else
                x = 240 - global_data_ptr->bn_random.get_int(20);
            y = (-70 - (b * 6)) * 4;
            break;

        case BULLET_HELIX:
            // Staggered start for helix effect
            x = (-30 + ((b % 4) * 20)) * 4;
            y = (-70 - (b * 10)) * 4;
            break;

        case BULLET_PENDULUM:
            // Horizontal line
            x = (-50 + (b * 6)) * 4;
            y = (-70 - (b * 5)) * 4;
            break;

        case BULLET_PULSE:
            // Random spread
            x = global_data_ptr->bn_random.get_int(-50, 50) * 4;
            y = (-70 - (b * 10)) * 4;
            break;

        case BULLET_WAVE:
        case BULLET_DOUBLE_WAVE:
        case BULLET_SINE_ACCEL:
            x = (-50 + global_data_ptr->bn_random.get_int(100)) * 4;
            y = (-70 - (b * 12)) * 4;
            break;

        case BULLET_BOUNCE:
        case BULLET_BOUNCE_WAVE:
            x = (-50 + global_data_ptr->bn_random.get_int(100)) * 4;
            y = (-70 - (b * 10)) * 4;
            break;

        case BULLET_RANDOM_WALK:
            // Grid formation
            x = (-40 + ((b % 4) * 20)) * 4;
            y = (-60 - ((b / 4) * 15)) * 4;
            break;

        default:
            x = (global_data_ptr->bn_random.get_int(-55, 55)) * 4;
            y = (-70 - (b * 15)) * 4;
            break;
        }

        bullet nb(x, y, anim_type, speed_multiplier);

        // Add type-specific variations
        if (anim_type == BULLET_WAVE || anim_type == BULLET_DOUBLE_WAVE)
        {
            nb.compact.ticker = global_data_ptr->bn_random.get_int(16);
            nb.compact.state2 = 35 + global_data_ptr->bn_random.get_int(45);
        }
        else if (anim_type == BULLET_ORBIT)
        {
            // Vary starting angles for interesting patterns
            nb.compact.state1 = (b * 64) / bullet_count;
        }
        else if (anim_type == BULLET_SPIRAL)
        {
            // Vary starting angle for spiral arms
            nb.compact.state1 = (b * 32) / bullet_count;
        }
        else if (anim_type == BULLET_PENDULUM)
        {
            // Offset phase for wave effect
            nb.compact.state1 = 32 + (b * 4);
        }

        bullets->push_back(nb);
    }
}