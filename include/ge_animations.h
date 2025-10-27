#ifndef GE_ANIMATIONS_H
#define GE_ANIMATIONS_H

#include "ge_text.h"
#include "ge_sprites.h"

const animation anim_walk = {{0,1,0,2}, 4, 0, true};
const animation anim_stand = {{0}, 1, 0, false};
const animation anim_falling = {{0,3,6,9}, 4, 1, true};
const animation vista_reminisce = {{9}, 1, 0, true};
const animation vista_pickup = {{6,10,6,11}, 4, 1, false};
const animation vista_invisible = {{0}, 1, 0, false};
const animation vista_jeremy_lift = {{1,2,3}, 3, 0, false};
const animation vista_jeremy_lift_02 = {{4}, 1, 0, false};
const animation vista_drinking = {{9}, 1, 0, false};
const animation visker_poke = {{9,10}, 2, 0, true};
const animation jeremy_lay_down = {{9}, 1, 0, true};
const animation jeremy_fancy_invisible = {{9}, 1, 0, false};
const animation jeremy_fancy_hug = {{10}, 1, 1, true};
const animation ginger_eat_lime = {{9}, 1, 0, true};
const animation ginger_sit_alert = {{10}, 1, 0, true};
const animation ginger_sit_sad = {{11}, 1, 0, true};
const animation ginger_sit_chair = {{12}, 1, 0, true};
const animation ginger_hide = {{13}, 1, 0, true};
const animation ginger_fancy_sit = {{9,10}, 2, 1, true};
const animation ginger_fancy_wistful = {{11}, 1, 0, false};
const animation ginger_fancy_hug = {{12}, 1, 0, false};
const animation sebellus_hide = {{9}, 1, 0, true};
const animation sebellus_sleep_01 = {{10}, 1, 0, true};
const animation sebellus_sleep_02 = {{11}, 1, 0, true};
const animation sebellus_sleep_03 = {{12,13}, 2, 1, true};
const animation sebellus_fancy_stand = {{9,10}, 2, 1, true};
const animation sebellus_fancy_stand_thumb = {{11,12}, 2, 1, true};
const animation sebellus_fancy_sleep = {{13}, 1, 0, false};
const animation sm_stab_01 = {{0}, 1, 0, true};
const animation sm_stab_02 = {{1}, 1, 0, true};
const animation sm_dead = {{2}, 1, 0, true};
const animation croke_accuse = {{9}, 1, 0, true};
const animation croke_lay_down = {{10}, 1, 0, true};
const animation mcwebb_play = {{0,1,2,3}, 4, 1, true};
const animation mcwebb_dont = {{0}, 1, 0, true};
const animation npcs_noodle_go = {{0,1,2,3,3,3,3,3,3,2,1,0}, 12, 0, false};
const animation npcs_spamton_anim = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55}, 56, 0, true};
const animation elem_button_up = {{0}, 1, 0, true};
const animation elem_button_down = {{1}, 1, 0, true};
const animation elem_spike_up = {{3}, 1, 0, true};
const animation elem_spike_down = {{2}, 1, 0, true};
const animation elem_leaves_fresh = {{0}, 1, 0, false};
const animation elem_leaves_stepped = {{1}, 1, 0, false};
const animation fire_out = {{9}, 1, 0, true};
const animation fire_on = {{1,2,3,4,5,6,7,8,9,10,11,12}, 12, 0, true};
const animation boat_exhaust = {{0,1,2,3}, 4, 0, true};
const animation naomi_disappear = {{1,2,3,4}, 4, 0, false};
const animation ghost_spook = {{0,0,1,2,2,1}, 6, 1, true};
const animation ghost_disappear = {{3,4,5,6,7,8,9,10}, 8, 0, false};
const animation teddy_idle = {{0,1}, 2, 1, true};
const animation desmond_idle = {{0,1}, 2, 1, true};
const animation matt_yay = {{0}, 1, 0, false};
const animation matt_sit = {{1}, 1, 0, false};
const animation matt_erm = {{2}, 1, 0, false};
const animation matt_press = {{3,4}, 2, 0, false};
const animation matt_alas = {{5}, 1, 0, false};
const animation poster_01 = {{0}, 1, 0, false};
const animation poster_02 = {{1}, 1, 0, false};
const animation poster_03 = {{2}, 1, 0, false};

#endif