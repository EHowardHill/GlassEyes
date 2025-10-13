#ifndef GE_SPRITES_AUTO_H
#define GE_SPRITES_AUTO_H

#include "bn_sprite_item.h"
#include "ge_sprites.h"

enum character_list
{
    CHAR_DEFAULT,
	CHAR_VISTA,
	CHAR_JEREMY,
	CHAR_VISKER,
	CHAR_VISKER_WIFE,
	CHAR_GINGER,
	CHAR_CROKE,
	CHAR_BUTTON,
	CHAR_SPIKE,
	CHAR_NOODLE,
	CHAR_GRANDMA,
	CHAR_WORMGUY,
	CHAR_COURIER,
	CHAR_PRIMARY,
	CHAR_GOAT,
	CHAR_BEAR,
	CHAR_BIRB,
	CHAR_HONSE,
	CHAR_ROBIN,
	CHAR_SNEAKER,
	CHAR_TOLLBOOTH,
	CHAR_SPAMTON,
	CHAR_TOGORE,
	CHAR_FIRE,
	CHAR_SEBELLUS,
	CHAR_SEBELLUS_MONSTER,
	CHAR_PIE,
	CHAR_MCWEBB,
	CHAR_SIZE,
	CHAR_TYPEWRITER
};

const bn::sprite_item *resolve_sprite_item(int character);
int resolve_sprite_id(int character);
const animation *resolve_sprite_idle_animation(int character);
const bool resolve_sprite_is_pressed(int character);

#endif