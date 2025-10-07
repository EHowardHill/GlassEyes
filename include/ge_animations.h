#include "ge_text.h"
#include "ge_sprites.h"

// FRAMES   -   SIZE    -   SPEED   -   LOOPS

// Default
const animation anim_walk = {{0, 1, 0, 2}, 4, SP_DEFAULT, true};
const animation anim_stand = {{0}, 1, SP_DEFAULT, false};

// Vista
const animation vista_reminisce = {{9}, 1, SP_DEFAULT, true};
const animation vista_pickup = {{6, 10, 6, 11}, 4, SP_SLOW, false};

// Visker
const animation visker_poke = {{9, 10}, 2, SP_DEFAULT, true};

// Jeremy
const animation jeremy_lay_down = {{9}, 1, SP_DEFAULT, true};

// Ginger
const animation ginger_eat_lime = {{9}, 1, SP_DEFAULT, true};
const animation ginger_sit_alert = {{10}, 1, SP_DEFAULT, true};
const animation ginger_sit_sad = {{11}, 1, SP_DEFAULT, true};
const animation ginger_sit_chair = {{12}, 1, SP_DEFAULT, true};
const animation ginger_hide = {{13}, 1, SP_DEFAULT, true};

// Sebellus
const animation sebellus_hide = {{9}, 1, SP_DEFAULT, true};
const animation sm_stab_01 = {{0}, 1, SP_DEFAULT, true};
const animation sm_stab_02 = {{1}, 1, SP_DEFAULT, true};
const animation sm_dead = {{2}, 1, SP_DEFAULT, true};
const animation sebellus_sleep_01 = {{10}, 1, SP_DEFAULT, true};
const animation sebellus_sleep_02 = {{11}, 1, SP_DEFAULT, true};
const animation sebellus_sleep_03 = {{12, 13}, 2, SP_SLOW, true};

// Croke
const animation croke_accuse = {{9}, 1, SP_DEFAULT, true};
const animation croke_lay_down = {{10}, 1, SP_DEFAULT, true};

// NPCs
const animation noodle_go = {{0, 1, 2, 3, 3, 3, 3, 3, 3, 2, 1, 0}, 11, SP_DEFAULT, false};
const animation spamton_anim = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55}, 56, SP_DEFAULT, true};

// Elements
const animation elem_button_up = {{0}, 1, SP_DEFAULT, true};
const animation elem_button_down = {{1}, 1, SP_DEFAULT, true};
const animation elem_spike_up = {{3}, 1, SP_DEFAULT, true};
const animation elem_spike_down = {{2}, 1, SP_DEFAULT, true};

// Fire
const animation fire_out = {{9}, 1, SP_DEFAULT, true};
const animation fire_on = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 12, SP_DEFAULT, true};