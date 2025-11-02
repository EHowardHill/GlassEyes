// ge_battle_acts_auto.h

#ifndef GE_BATTLE_ACTS_AUTO_H
#define GE_BATTLE_ACTS_AUTO_H

#include "ge_text.h"

struct battle_action {
    const char *title = nullptr;
    const conversation * dialogue = nullptr;
};

#endif