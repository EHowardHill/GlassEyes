// ge_bullet.h - Enhanced version with more pattern variations
#ifndef GE_BULLET_H
#define GE_BULLET_H

#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"

#define bullet_count 16

enum BULLET_ANIM_TYPES
{
    BULLET_FALL,         // 0 - Simple fall
    BULLET_RISE,         // 1 - Simple rise
    BULLET_WAVE,         // 2 - Sine wave
    BULLET_ACCEL,        // 3 - Accelerating fall
    BULLET_BOUNCE,       // 4 - Bounce off walls
    BULLET_HOMING,       // 5 - Home to targets
    
    // New pattern variations
    BULLET_ORBIT,        // 6 - Circular orbit
    BULLET_SPIRAL,       // 7 - Spiral inward/outward
    BULLET_ZIGZAG,       // 8 - Sharp zigzag
    BULLET_DOUBLE_WAVE,  // 9 - Two waves combined
    BULLET_SCATTER,      // 10 - Explode outward
    BULLET_CONVERGE,     // 11 - Converge to center
    BULLET_SINE_ACCEL,   // 12 - Wave with acceleration
    BULLET_BOUNCE_WAVE,  // 13 - Bounce with wave
    BULLET_RANDOM_WALK,  // 14 - Random movement
    BULLET_PULSE,        // 15 - Pulsing movement
    BULLET_HELIX,        // 16 - 3D-like helix
    BULLET_PENDULUM,     // 17 - Pendulum swing
    
    BULLET_SIZE
};

// Pattern flags
#define FLAG_WAVE     0x02
#define FLAG_ACCEL    0x04
#define FLAG_BOUNCE   0x08
#define FLAG_HOMING   0x10
#define FLAG_ORBIT    0x20
#define FLAG_SPIRAL   0x40
#define FLAG_ZIGZAG   0x80
#define FLAG_SCATTER  0x100
#define FLAG_CONVERGE 0x200
#define FLAG_RANDOM   0x400
#define FLAG_PULSE    0x800
#define FLAG_HELIX    0x1000
#define FLAG_PENDULUM 0x2000

// Shared pattern data
struct bullet_pattern
{
    int vx_base;   // Base velocity * 16
    int vy_base;   // Base velocity * 16
    int amplitude; // 0-255 range
    int period;    // 0-255 frames
    int accel;     // Acceleration * 128
    int flags;     // Bit flags for behavior
};

// Pre-computed patterns (stored in ROM)
extern const bullet_pattern PATTERNS[BULLET_SIZE];

// Compact bullet struct
struct bullet
{
    bn::optional<bn::sprite_ptr> item;

    union
    {
        struct
        {
            int16_t x;      // Position * 4
            int16_t y;      // Position * 4
            int ticker;     // Frame counter
            int type;       // Animation type
            int state1;     // Generic state
            int state2;     // Generic state  
            int state3;     // Additional state for complex patterns
            int init_x;     // Initial x position for reference
            int speed;      // Speed multiplier
        } compact;
    };

    bullet(int16_t x_pos, int16_t y_pos, int anim_type, int speed_multiplier);
    void update();
    static void populate(bn::vector<bullet, bullet_count> *bullets, int anim_type, int speed_multiplier);

    bn::fixed get_x() const { return bn::fixed(compact.x) / 4; }
    bn::fixed get_y() const { return bn::fixed(compact.y) / 4; }
    void set_pos(bn::fixed x, bn::fixed y)
    {
        compact.x = (x * 4).integer();
        compact.y = (y * 4).integer();
    }
};

extern const int SINE_TABLE[64];

#endif

