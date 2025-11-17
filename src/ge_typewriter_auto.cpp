#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"
#include "bn_sound_item.h"
#include "bn_sound_items.h"

#include "ge_text.h"
#include "ge_dialogue.h"
#include "ge_typewriter.h"
#include "ge_typewriter_auto.h"

using namespace bn;

int resolve_typewriter_type(int scene)
{
    switch (scene)
    {
	case TYPEWRITER_INTRO: { return TYPE_TEXT; break; }
	case TYPEWRITER_INTRO2: { return TYPE_TEXT; break; }
	case TYPEWRITER_INTRO3: { return TYPE_TEXT; break; }
	case TYPEWRITER_MSG: { return TYPE_TEXT; break; }
	case TYPEWRITER_NEW_BERLIN: { return TYPE_TEXT; break; }
	case TYPEWRITER_DOG_AND_PONY: { return TYPE_TEXT; break; }

    default:
    {
        return TYPE_IMG;
        break;
    }
    }
}

const sound_item *resolve_typewriter_sfx(int scene)
{
    switch (scene)
    {
	case TYPEWRITER_TITLE: {return &sound_items::snd_intro; break; }
	case TYPEWRITER_GARBAGE: {return &sound_items::sfx_drag; break; }

    default:
    {
        return nullptr;
        break;
    }
    }
}

const conversation *resolve_typewriter_conversation(int scene)
{
    switch (scene)
    {
	case TYPEWRITER_INTRO: { return &intro_01; break; }
	case TYPEWRITER_INTRO2: { return &intro_02; break; }
	case TYPEWRITER_INTRO3: { return &intro_03; break; }
	case TYPEWRITER_MSG: { return &final_msg; break; }
	case TYPEWRITER_NEW_BERLIN: { return &new_berlin_sign; break; }
	case TYPEWRITER_DOG_AND_PONY: { return &dog_and_pony; break; }
	case TYPEWRITER_CCUTSCENE_07: { return &cutscene_07; break; }
	case TYPEWRITER_CCUTSCENE_01: { return &cutscene_01; break; }
	case TYPEWRITER_CCUTSCENE_02: { return &cutscene_02; break; }
	case TYPEWRITER_CCUTSCENE_03: { return &cutscene_03; break; }

    default:
    {
        return nullptr;
        break;
    }
    }
}

const music_item *resolve_typewriter_music(int scene)
{
    switch (scene)
    {
	case TYPEWRITER_INTRO: {return &music_items::intro; break; }
	case TYPEWRITER_INTRO2: {return nullptr; break; }
	case TYPEWRITER_TITLE: {return nullptr; break; }
	case TYPEWRITER_GARBAGE: {return nullptr; break; }
	case TYPEWRITER_MSG: {return nullptr; break; }
	case TYPEWRITER_NEW_BERLIN: {return nullptr; break; }
	case TYPEWRITER_DOG_AND_PONY: {return &music_items::z02_the_champ; break; }
	case TYPEWRITER_GAME_OVER: {return &music_items::intro; break; }
	case TYPEWRITER_CCUTSCENE_01: {return &music_items::cave_01; break; }
	case TYPEWRITER_CCUTSCENE_02: {return &music_items::cave_01; break; }
	case TYPEWRITER_CCUTSCENE_03: {return &music_items::ambient_heartbeat; break; }

    default:
    {
        return nullptr;
        break;
    }
    }
}
