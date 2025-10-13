#ifndef GE_ACTIONS_AUTO_H
#define GE_ACTIONS_AUTO_H

#include "ge_character_manager.h"

int perform_action_interactive(int index, character_manager * ch_man);
int perform_action_automatic(int index, character_manager * ch_man);

#endif