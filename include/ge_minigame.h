#ifndef GE_MINIGAME_H
#define GE_MINIGAME_H

#include "bn_sprite_ptr.h"
#include "bn_optional.h"
#include "bn_vector.h"

using namespace bn;

// Forward declare to avoid circular dependency
struct battle_state;

enum minigame_type
{
    MINIGAME_BULLET_DODGE,
    MINIGAME_RHYTHM_ATTACK,
    MINIGAME_PUZZLE,
    // Add more as needed
};

struct minigame_result
{
    bool complete = false;
    int damage_dealt = 0;        // Damage to party members
    int damage_to_enemy = 0;     // Damage to enemy (if applicable)
    int affected_character = -1; // Which party member was hit
};

// Generic shared data structure
struct minigame_state
{
    minigame_type type;
    battle_state *bs; // Back-reference for party/enemy data

    // Generic reusable resources
    optional<sprite_ptr> sprites[8];
    optional<regular_bg_ptr> backgrounds[2];
    vector_2 positions[8];
    int integers[16];

    // Timing and state
    int ticker = 0;
    minigame_result result;

    // Custom data pointer for minigame-specific structs
    void *custom_data = nullptr;
};

// Main interface functions
void minigame_init(minigame_state *mg);
void minigame_update(minigame_state *mg);
void minigame_cleanup(minigame_state *mg);
bool minigame_is_complete(const minigame_state *mg);

#endif