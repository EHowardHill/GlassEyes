#include "bn_sprites.h"
#include "bn_sprite_item.h"

#include "ge_animations.h"
#include "ge_sprites_auto.h"

#include "bn_sprite_items_spr_vista.h"
#include "bn_sprite_items_spr_jeremy.h"
#include "bn_sprite_items_spr_visker.h"
#include "bn_sprite_items_spr_visker_wife.h"
#include "bn_sprite_items_spr_ginger.h"
#include "bn_sprite_items_spr_croke.h"
#include "bn_sprite_items_spr_button.h"
#include "bn_sprite_items_spr_spike.h"
#include "bn_sprite_items_spr_noodle.h"
#include "bn_sprite_items_spr_grandma.h"
#include "bn_sprite_items_spr_wormguy.h"
#include "bn_sprite_items_spr_courier.h"
#include "bn_sprite_items_spr_primary.h"
#include "bn_sprite_items_spr_goat.h"
#include "bn_sprite_items_spr_bear.h"
#include "bn_sprite_items_spr_birb.h"
#include "bn_sprite_items_spr_honse.h"
#include "bn_sprite_items_spr_robin.h"
#include "bn_sprite_items_spr_sneaker.h"
#include "bn_sprite_items_spr_tollbooth.h"
#include "bn_sprite_items_spr_spamton.h"
#include "bn_sprite_items_spr_togore.h"
#include "bn_sprite_items_spr_fire.h"
#include "bn_sprite_items_spr_sebellus.h"
#include "bn_sprite_items_spr_sebellus_monster.h"
#include "bn_sprite_items_spr_pie.h"
#include "bn_sprite_items_spr_mcwebb.h"
#include "bn_sprite_items_spr_boat_exhaust.h"
#include "bn_sprite_items_spr_naomi_cooking.h"
#include "bn_sprite_items_spr_naomi_fortune.h"
#include "bn_sprite_items_spr_leaves.h"
#include "bn_sprite_items_spr_ghost.h"
#include "bn_sprite_items_spr_dima.h"
#include "bn_sprite_items_spr_kathy.h"
#include "bn_sprite_items_spr_pringle.h"
#include "bn_sprite_items_spr_eggplant.h"
#include "bn_sprite_items_spr_ack.h"
#include "bn_sprite_items_spr_teddy.h"
#include "bn_sprite_items_spr_vista_lift.h"
#include "bn_sprite_items_spr_vista_02.h"
#include "bn_sprite_items_spr_desmond.h"
#include "bn_sprite_items_spr_matt_poster_01.h"
#include "bn_sprite_items_spr_matt_poster_02.h"
#include "bn_sprite_items_spr_matt.h"
#include "bn_sprite_items_spr_kiara.h"
#include "bn_sprite_items_spr_matt_legs.h"
#include "bn_sprite_items_spr_jeremy_battle.h"
#include "bn_sprite_items_spr_ginger_battle.h"
#include "bn_sprite_items_spr_visker_battle.h"
#include "bn_sprite_items_spr_croke_battle.h"
#include "bn_sprite_items_spr_henry.h"
#include "bn_sprite_items_spr_vista_bed.h"
#include "bn_sprite_items_spr_vista_young.h"
#include "bn_sprite_items_spr_constance.h"
#include "bn_sprite_items_spr_ginger_fancy2.h"
#include "bn_sprite_items_spr_vista_drunk.h"
#include "bn_sprite_items_spr_pills.h"
#include "bn_sprite_items_spr_cs_mspx.h"
#include "bn_sprite_items_spr_cs_ge.h"
#include "bn_sprite_items_spr_cs_fox.h"
#include "bn_sprite_items_spr_sans.h"
#include "bn_sprite_items_spr_stand.h"

using namespace bn;

const sprite_item *resolve_sprite_item(int character)
{
    switch (character)
    {
	case CHAR_VISTA: { return &sprite_items::spr_vista; break; }
	case CHAR_JEREMY: { return &sprite_items::spr_jeremy; break; }
	case CHAR_VISKER: { return &sprite_items::spr_visker; break; }
	case CHAR_VISKER_WIFE: { return &sprite_items::spr_visker_wife; break; }
	case CHAR_GINGER: { return &sprite_items::spr_ginger; break; }
	case CHAR_CROKE: { return &sprite_items::spr_croke; break; }
	case CHAR_BUTTON: { return &sprite_items::spr_button; break; }
	case CHAR_SPIKE: { return &sprite_items::spr_spike; break; }
	case CHAR_NOODLE: { return &sprite_items::spr_noodle; break; }
	case CHAR_GRANDMA: { return &sprite_items::spr_grandma; break; }
	case CHAR_WORMGUY: { return &sprite_items::spr_wormguy; break; }
	case CHAR_COURIER: { return &sprite_items::spr_courier; break; }
	case CHAR_PRIMARY: { return &sprite_items::spr_primary; break; }
	case CHAR_GOAT: { return &sprite_items::spr_goat; break; }
	case CHAR_BEAR: { return &sprite_items::spr_bear; break; }
	case CHAR_BIRB: { return &sprite_items::spr_birb; break; }
	case CHAR_HONSE: { return &sprite_items::spr_honse; break; }
	case CHAR_ROBIN: { return &sprite_items::spr_robin; break; }
	case CHAR_SNEAKER: { return &sprite_items::spr_sneaker; break; }
	case CHAR_TOLLBOOTH: { return &sprite_items::spr_tollbooth; break; }
	case CHAR_SPAMTON: { return &sprite_items::spr_spamton; break; }
	case CHAR_TOGORE: { return &sprite_items::spr_togore; break; }
	case CHAR_FIRE: { return &sprite_items::spr_fire; break; }
	case CHAR_SEBELLUS: { return &sprite_items::spr_sebellus; break; }
	case CHAR_SEBELLUS_MONSTER: { return &sprite_items::spr_sebellus_monster; break; }
	case CHAR_PIE: { return &sprite_items::spr_pie; break; }
	case CHAR_MCWEBB: { return &sprite_items::spr_mcwebb; break; }
	case CHAR_BOAT_EXHAUST: { return &sprite_items::spr_boat_exhaust; break; }
	case CHAR_NAOMI_COOKING: { return &sprite_items::spr_naomi_cooking; break; }
	case CHAR_NAOMI_FORTUNE: { return &sprite_items::spr_naomi_fortune; break; }
	case CHAR_LEAVES: { return &sprite_items::spr_leaves; break; }
	case CHAR_GHOST: { return &sprite_items::spr_ghost; break; }
	case CHAR_DIMA: { return &sprite_items::spr_dima; break; }
	case CHAR_KATHY: { return &sprite_items::spr_kathy; break; }
	case CHAR_PRINGLE: { return &sprite_items::spr_pringle; break; }
	case CHAR_EGGPLANT: { return &sprite_items::spr_eggplant; break; }
	case CHAR_ACK: { return &sprite_items::spr_ack; break; }
	case CHAR_TEDDY: { return &sprite_items::spr_teddy; break; }
	case CHAR_VISTA_LIFT: { return &sprite_items::spr_vista_lift; break; }
	case CHAR_VISTA_02: { return &sprite_items::spr_vista_02; break; }
	case CHAR_DESMOND: { return &sprite_items::spr_desmond; break; }
	case CHAR_MATT_POSTER_01: { return &sprite_items::spr_matt_poster_01; break; }
	case CHAR_MATT_POSTER_02: { return &sprite_items::spr_matt_poster_02; break; }
	case CHAR_MATT: { return &sprite_items::spr_matt; break; }
	case CHAR_KIARA: { return &sprite_items::spr_kiara; break; }
	case CHAR_MATT_LEGS: { return &sprite_items::spr_matt_legs; break; }
	case CHAR_JEREMY_BATTLE: { return &sprite_items::spr_jeremy_battle; break; }
	case CHAR_GINGER_BATTLE: { return &sprite_items::spr_ginger_battle; break; }
	case CHAR_VISKER_BATTLE: { return &sprite_items::spr_visker_battle; break; }
	case CHAR_CROKE_BATTLE: { return &sprite_items::spr_croke_battle; break; }
	case CHAR_HENRY: { return &sprite_items::spr_henry; break; }
	case CHAR_VISTA_BED: { return &sprite_items::spr_vista_bed; break; }
	case CHAR_VISTA_YOUNG: { return &sprite_items::spr_vista_young; break; }
	case CHAR_CONSTANCE: { return &sprite_items::spr_constance; break; }
	case CHAR_GINGER_FANCY2: { return &sprite_items::spr_ginger_fancy2; break; }
	case CHAR_VISTA_DRUNK: { return &sprite_items::spr_vista_drunk; break; }
	case CHAR_PILLS: { return &sprite_items::spr_pills; break; }
	case CHAR_CS_MSPX: { return &sprite_items::spr_cs_mspx; break; }
	case CHAR_CS_GE: { return &sprite_items::spr_cs_ge; break; }
	case CHAR_CS_FOX: { return &sprite_items::spr_cs_fox; break; }
	case CHAR_SANS: { return &sprite_items::spr_sans; break; }
	case CHAR_STAND: { return &sprite_items::spr_stand; break; }
    default:
    {
        return &sprite_items::spr_vista;
        break;
    }
    }
}

int resolve_sprite_id(int character)
{
    switch (character)
    {
	case CHAR_GINGER: { return CHAR_JEREMY; break; }
	case CHAR_SEBELLUS: { return CHAR_GINGER; break; }
	case CHAR_VISTA_LIFT: { return CHAR_JEREMY; break; }
	case CHAR_KIARA: { return CHAR_JEREMY; break; }
    default:
    {
        return 0;
        break;
    }
    }
}

const animation *resolve_sprite_idle_animation(int character)
{
    switch (character)
    {
	case CHAR_BUTTON: { return &elem_button_up; break; }
	case CHAR_SPIKE: { return &elem_spike_up; break; }
	case CHAR_SPAMTON: { return &npcs_spamton_anim; break; }
	case CHAR_MCWEBB: { return &mcwebb_play; break; }
	case CHAR_BOAT_EXHAUST: { return &boat_exhaust; break; }
	case CHAR_GHOST: { return &ghost_spook; break; }
	case CHAR_TEDDY: { return &teddy_idle; break; }
	case CHAR_VISTA_LIFT: { return &vista_invisible; break; }
	case CHAR_DESMOND: { return &desmond_idle; break; }
	case CHAR_MATT: { return &matt_sit; break; }
	case CHAR_JEREMY_BATTLE: { return &jeremy_battle_idle; break; }
	case CHAR_GINGER_BATTLE: { return &ginger_battle_idle; break; }
	case CHAR_VISKER_BATTLE: { return &visker_battle_idle; break; }
    default:
    {
        return nullptr;
        break;
    }
    }
}

const bool resolve_sprite_is_pressed(int character)
{
    switch (character)
    {
	case CHAR_SPIKE: { return true; break; }
    default:
    {
        return false;
        break;
    }
    }
}
