// ge_minigame.cpp

#include "ge_minigame.h"
#include "ge_minigame_bullet_dodge.h"
#include "ge_minigame_rhythm.h"

void minigame_init(minigame_state *mg)
{
    mg->ticker = 0;
    mg->result = minigame_result();

    switch (mg->type)
    {
    case MINIGAME_BULLET_DODGE:
        bullet_dodge_init(mg);
        break;
    case MINIGAME_RHYTHM_ATTACK:
        rhythm_attack_init(mg);
        break;
    // Add more cases
    default:
        break;
    }
}

void minigame_update(minigame_state *mg)
{
    switch (mg->type)
    {
    case MINIGAME_BULLET_DODGE:
        bullet_dodge_update(mg);
        break;
    case MINIGAME_RHYTHM_ATTACK:
        rhythm_attack_update(mg);
        break;
    default:
        break;
    }
    mg->ticker++;
}

void minigame_cleanup(minigame_state *mg)
{
    // Generic cleanup
    for (int i = 0; i < 8; ++i)
    {
        mg->sprites[i].reset();
    }
    for (int i = 0; i < 2; ++i)
    {
        mg->backgrounds[i].reset();
    }

    // Type-specific cleanup
    switch (mg->type)
    {
    case MINIGAME_BULLET_DODGE:
        bullet_dodge_cleanup(mg);
        break;
    case MINIGAME_RHYTHM_ATTACK:
        rhythm_attack_cleanup(mg);
        break;
    default:
        break;
    }
}

bool minigame_is_complete(const minigame_state *mg)
{
    return mg->result.complete;
}