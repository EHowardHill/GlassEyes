import os
import json

data = {}

try:
    with open("headers.json", "r") as f:
        data = json.load(f)
except FileNotFoundError:
    print("Error: headers.json not found.")
    exit()
except json.JSONDecodeError:
    print("Error: Could not decode JSON from headers.json.")
    exit()


# Animation
# ------------------------------------------------------------------------------------------------------------------------------------------------------

animation_data = """#ifndef GE_ANIMATIONS_H
#define GE_ANIMATIONS_H

#include "ge_text.h"
#include "ge_sprites.h"

"""

# Check if the required keys exist before processing
if "animations" in data:
    for category in data["animations"]:
        for animation in data["animations"][category]:
            dat = data["animations"][category][animation]

            # 1. Convert frame numbers to strings before joining
            frame_strings = [str(f) for f in dat["frames"]]

            val = (
                "const animation "
                + category
                + "_"
                + animation
                + " = {{"
                + ",".join(frame_strings)
                + "}, "
                + str(len(dat["frames"]))
                + ", "
                + str(dat["speed"])
                + ", "
                + ("true" if dat["loop"] else "false")  # Simplified the boolean check
                + "};\n"  # 2. Added semicolon and newline for proper C++ formatting
            )

            # 3. Use += to append to a string
            animation_data += val

animation_data += "\n#endif"

with open("include/ge_animations.h", "w") as f:
    f.write(animation_data)

# Items
# ------------------------------------------------------------------------------------------------------------------------------------------------------

text_h_data = """#ifndef GE_TEXT_AUTO_H
#define GE_TEXT_AUTO_H

enum ITEMS
{"""

h_labels = "const char *ITEM_LABELS[ITEMS_SIZE] = {\n"
h_drop = "const bool ITEM_DROP[ITEMS_SIZE] = {\n"
h_convos = "const conversation *ITEM_CONVOS[ITEMS_SIZE] = {\n"

labels = []
drop = []

if "items" in data:
    for item in data["items"].keys():
        h_labels += '\t"' + item + '",\n'

        name = item.upper().replace(" ", "_")
        text_h_data += "\tOBJ_" + name + ",\n"

        if "drop" in data["items"].keys():
            h_drop += (
                "\t" + ("true" if data["items"][item]["drop"] else "false") + ",\n"
            )
        else:
            h_drop += "\tfalse,\n"

        h_convos += "\t&convo_obj_" + name.lower() + ",\n"

    text_h_data += "\tITEMS_SIZE\n};\n\n#endif"
    h_labels += "};"
    h_drop += "};"
    h_convos += "};"

with open("include/ge_text_auto.h", "w") as f:
    f.write(text_h_data)

with open("src/ge_text_auto.cpp", "w") as f:
    f.write(
        f"""#include "ge_dialogue.h"
#include "ge_text.h"
#include "ge_text_auto.h"

{h_labels}

{h_drop}

{h_convos}
"""
    )

# Objects
# ------------------------------------------------------------------------------------------------------------------------------------------------------

sprites_h_data = """#ifndef GE_SPRITES_AUTO_H
#define GE_SPRITES_AUTO_H

#include "bn_sprite_item.h"
#include "ge_sprites.h"

enum character_list
{
    CHAR_DEFAULT,
"""

spr_includes = ""
spr_switch = ""
spr_follow_id = ""
spr_animation = ""
spr_pressed = ""

if "objects" in data:
    for object in data["objects"].keys():
        fixed = object.replace(" ", "_").upper()

        sprites_h_data += "\tCHAR_" + fixed + ",\n"
        spr_includes += '#include "bn_sprite_items_spr_' + fixed.lower() + '.h"\n'
        spr_switch += (
            "\tcase CHAR_"
            + fixed
            + ": { return &sprite_items::spr_"
            + fixed.lower()
            + "; break; }\n"
        )

        dat = data["objects"][object]
        if "follow" in dat.keys():
            spr_follow_id += (
                "\tcase CHAR_"
                + object.upper().replace(" ", "_")
                + ": { return CHAR_"
                + dat["follow"].upper().replace(" ", "_")
                + "; break; }\n"
            )

        if "idle_animation" in dat.keys():
            spr_animation += (
                "\tcase CHAR_"
                + object.upper().replace(" ", "_")
                + ": { return &"
                + dat["idle_animation"]
                + "; break; }\n"
            )

        if "is_pressed" in dat.keys():
            spr_pressed += (
                "\tcase CHAR_"
                + object.upper().replace(" ", "_")
                + ": { return "
                + ("true" if dat["is_pressed"] else "false")
                + "; break; }\n"
            )

sprites_h_data += """\tCHAR_SIZE,
\tCHAR_TYPEWRITER
};

const bn::sprite_item *resolve_sprite_item(int character);
int resolve_sprite_id(int character);
const animation *resolve_sprite_idle_animation(int character);
const bool resolve_sprite_is_pressed(int character);

#endif"""

with open("include/ge_sprites_auto.h", "w") as f:
    f.write(sprites_h_data)

with open("src/ge_sprites_auto.cpp", "w") as f:
    f.write(
        """#include "bn_sprites.h"
#include "bn_sprite_item.h"

#include "ge_animations.h"
#include "ge_sprites_auto.h"

"""
        + spr_includes
        + """
using namespace bn;

const sprite_item *resolve_sprite_item(int character)
{
    switch (character)
    {
"""
        + spr_switch
        + """    default:
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
"""
        + spr_follow_id
        + """    default:
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
"""
        + spr_animation
        + """    default:
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
"""
        + spr_pressed
        + """    default:
    {
        return false;
        break;
    }
    }
}
"""
    )

# Typewriter
# ------------------------------------------------------------------------------------------------------------------------------------------------------

typewriters = ""
typewriter_type = ""
typewriter_sfx = ""
typewriter_conversation = ""
typewriter_music = ""

if "cutscenes" in data:
    for cutscene in data["cutscenes"].keys():
        title = cutscene.upper().replace(" ", "_")
        typewriters += "\tTYPEWRITER_" + title + ",\n"
        dat = data["cutscenes"][cutscene]

        if "conversation" in dat.keys():
            typewriter_conversation += (
                "\tcase TYPEWRITER_"
                + title
                + ": { return &"
                + dat["conversation"]
                + "; break; }\n"
            )

        if "music" in dat.keys():
            typewriter_music += "\tcase TYPEWRITER_" + title + ": {"

            if dat["music"] == False:
                typewriter_music += "return nullptr; break; }\n"

            else:
                typewriter_music += (
                    "return &music_items::" + dat["music"] + "; break; }\n"
                )

        if "sfx" in dat.keys():
            typewriter_sfx += "\tcase TYPEWRITER_" + title + ": {"

            if dat["sfx"] == False:
                typewriter_sfx += "return nullptr; break; }\n"

            else:
                typewriter_sfx += "return &sound_items::" + dat["sfx"] + "; break; }\n"

        if "type" in dat.keys():
            if dat["type"] == "text":
                typewriter_type += (
                    "\tcase TYPEWRITER_"
                    + title
                    + ": { return TYPE_"
                    + dat["type"].upper()
                    + "; break; }\n"
                )

with open("include/ge_typewriter_auto.h", "w") as f:
    f.write(
        """#ifndef GE_TYPEWRITER_AUTO_H
#define GE_TYPEWRITER_AUTO_H

enum TYPEWRITER_SCENES
{
"""
        + typewriters
        + """};\n\n#endif"""
    )

with open("src/ge_typewriter_auto.cpp", "w") as f:
    f.write(
        """#include "bn_music.h"
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
"""
        + typewriter_type
        + """
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
"""
        + typewriter_sfx
        + """
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
"""
        + typewriter_conversation
        + """
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
"""
        + typewriter_music
        + """
    default:
    {
        return nullptr;
        break;
    }
    }
}
"""
    )

# Actions
# ------------------------------------------------------------------------------------------------------------------------------------------------------

interactive_block = """int perform_action_interactive(int index, character_manager &ch_man)
{
    switch (index)
    {"""

automatic_block = """int perform_action_automatic(int index, character_manager &ch_man)
{
    switch (index)
    {"""

references = ""


def handle_action(dat):
    global references

    full_block = ""
    for key in dat.keys():
        entry = dat[key]
        block = "\tcase " + key + ":\n\t{\n"
        return_type = None

        entry_keys = entry.keys()

        if "music" in entry_keys:
            block += "\t\tmusic_items::" + entry["music"] + ".play();\n"

        if "stage" in entry_keys:
            block += "\t\tglobal_data_ptr->process_stage = " + entry["stage"] + ";\n"
            return_type = "NEW_CHAPTER"

        if "new_map" in entry_keys:
            datt = entry["new_map"]
            if "map" in datt.keys():
                block += "\t\tglobal_data_ptr->entry_map = &map_" + datt["map"] + ";\n"
            if "bg_track" in datt.keys():
                block += (
                    "\t\tglobal_data_ptr->bg_track = &music_items::"
                    + datt["bg_track"]
                    + ";\n"
                )
            if "bg" in datt.keys():
                block += (
                    "\t\tglobal_data_ptr->bg = &regular_bg_items::" + datt["bg"] + ";\n"
                )
                references += '#include "bn_regular_bg_items_' + datt["bg"] + '.h"\n'
                block += "\t\tmusic::stop();\n"
            if "positions" in datt.keys():
                characters = datt["positions"]
                for c_key in characters.keys():
                    block += (
                        "\t\tglobal_data_ptr->"
                        + c_key
                        + "_position = {"
                        + str(characters[c_key][0])
                        + ", "
                        + str(characters[c_key][1])
                        + "};\n"
                    )
            return_type = "NEW_MAP"

        if "sequence" in entry_keys:
            t = 1
            for line in entry["sequence"]:
                block += (
                    "\t\tif (global_data_ptr->action_iterations["
                    + key
                    + "] == "
                    + str(t)
                    + ") { ch_man.load(&"
                    + line
                    + "); } else\n"
                )
                t += 1
            if "auto" in entry_keys:
                block += "\t\t{ ch_man.load(&" + line + "); }\n"
            else:
                block += "\t\t{ };\n"

        elif "auto" in entry_keys:
            block += "\t\tch_man.load(&" + entry["auto"] + ");\n"

        if return_type != None:
            block += "\t\treturn " + return_type + ";\n"

        block += "\t\tbreak;\n\t}\n"
        full_block += block
    return full_block


if "actions" in data:
    if "interactable" in data["actions"]:
        dat = data["actions"]["interactable"]
        interactive_block += handle_action(dat)

    if "automatic" in data["actions"]:
        dat = data["actions"]["automatic"]
        automatic_block += handle_action(dat)

interactive_block += "\t}\n\treturn -1;\n}"
automatic_block += "\t}\n\treturn -1;\n}"

ge_actions_cpp = f"""#include "bn_music.h"
#include "bn_music_items.h"

{references}
#include "main_auto.h"
#include "ge_globals.h"
#include "ge_dialogue.h"
#include "ge_character_manager.h"
#include "ge_actions_auto.h"
#include "ge_map_data.h"

using namespace bn;

{interactive_block}

{automatic_block}"""

with open("src/ge_actions_auto.cpp", "w") as f:
    f.write(ge_actions_cpp)
