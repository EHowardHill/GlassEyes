#!/usr/bin/env python3

# generate-script.py

import csv
import chardet
import os
import sys


def parse_navigate_coords(nav_str):
    """Parse coordinate string like '{2, 6}' into tuple (2, 6)"""
    if not nav_str or nav_str.strip() == "":
        return (0, 0)
    nav_str = nav_str.strip().strip("{}")
    coords = nav_str.split(",")
    if len(coords) == 2:
        try:
            return (int(coords[0].strip()), int(coords[1].strip()))
        except ValueError:
            return (0, 0)
    return (0, 0)


sprites = []


def validate_line_length(line, line_name, convo_name, row_num):
    """Validate that a dialogue line is 20 characters or less"""
    if len(line) > 20:
        print(f"ERROR: Line exceeds 20 character limit!")
        print(f"Conversation: {convo_name}")
        print(f"Row: {row_num}")
        print(f"Field: {line_name}")
        print(f"Line content: '{line}'")
        print(f"Line length: {len(line)} characters")
        sys.exit(1)


def process_csv(filename):
    """Processes the dialogue.txt file into a dictionary of conversations."""
    conversations = {}
    current_convo = None
    current_entries = []
    row_num = 0

    with open(filename, "rb") as f:
        raw_data = f.read()
        result = chardet.detect(raw_data)
        encoding = result["encoding"] or "utf-8"

    with open(filename, "r", newline="", encoding=encoding) as csvfile:
        reader = csv.reader(csvfile, delimiter="\t")

        for row in reader:
            row_num += 1

            if not any(cell.strip() for cell in row):
                continue

            if row[0].strip() and all(not cell.strip() for cell in row[1:]):
                if current_convo and current_entries:
                    conversations[current_convo] = current_entries
                current_entries = []
                current_convo = row[0].strip()
                continue

            if row[0] == "Name / ID":
                continue

            if current_convo:
                # (Parsing logic is unchanged)
                name_id = int(row[0]) if row[0].strip() else 0
                portrait = row[1].strip() if row[1].strip() else "nullptr"
                emotion = row[2].strip() if row[2].strip() else "EM_DEFAULT"
                action = row[3].strip() if row[3].strip() else "ACT_DEFAULT"

                # Extract lines
                line1 = row[4].strip() if len(row) > 4 else ""
                line2 = row[5].strip() if len(row) > 5 else ""
                line3 = row[6].strip() if len(row) > 6 else ""

                # Validate line lengths
                validate_line_length(line1, "line1", current_convo, row_num)
                validate_line_length(line2, "line2", current_convo, row_num)
                validate_line_length(line3, "line3", current_convo, row_num)

                # Parse color field as integer (replacing shake)
                color = 0  # Default value
                if len(row) > 7 and row[7].strip():
                    try:
                        color = row[7].strip()
                    except ValueError:
                        print(
                            f"WARNING: Invalid color value '{row[7]}' at row {row_num}, using default 0"
                        )
                        color = 0

                size = (
                    row[8].strip()
                    if (len(row) > 8 and row[8].strip())
                    else "SIZE_DEFAULT"
                )
                speed = (
                    row[9].strip()
                    if (len(row) > 9 and row[9].strip())
                    else "SP_DEFAULT"
                )
                index = row[10].strip() if (len(row) > 10 and row[10].strip()) else "0"
                anim_ptr = (
                    row[11].strip()
                    if (len(row) > 11 and row[11].strip())
                    else "nullptr"
                )
                nav_str = row[12].strip() if len(row) > 12 else ""
                nav_coords = parse_navigate_coords(nav_str)
                dlg_opt_1 = (
                    row[13].strip()
                    if (len(row) > 13 and row[13].strip())
                    else "nullptr"
                )
                dlg_opt_2 = (
                    row[14].strip()
                    if (len(row) > 14 and row[14].strip())
                    else "nullptr"
                )

                if portrait != "nullptr" and portrait not in sprites:
                    sprites.append(portrait)

                if portrait != "nullptr":
                    portrait = "&sprite_items::" + portrait

                entry = {
                    "id": name_id,
                    "portrait": portrait,
                    "emotion": emotion,
                    "action": action,
                    "line1": line1.replace('"', '\\"'),
                    "line2": line2.replace('"', '\\"'),
                    "line3": line3.replace('"', '\\"'),
                    "color": color,
                    "size": size,
                    "speed": speed,
                    "index": index,
                    "anim": anim_ptr,
                    "nav": nav_coords,
                    "dlg1": dlg_opt_1,
                    "dlg2": dlg_opt_2,
                }
                current_entries.append(entry)

    if current_convo and current_entries:
        conversations[current_convo] = current_entries

    return conversations


# --- NEW: Function to generate header file content ---
def generate_header_content(conversations, sprite_list):
    """Generates the content for the .h file with only extern declarations."""

    sprite_includes = "\n".join(
        [f'#include "bn_sprite_items_{s}.h"' for s in sprite_list if s != "nullptr"]
    )

    declarations = ["// Forward declarations for conversations"]
    for convo_name in sorted(conversations.keys()):
        declarations.append(f"extern const conversation {convo_name};")

    template_h = f"""// ge_dialogue.h
// THIS IS AN AUTO-GENERATED FILE. DO NOT EDIT.

#ifndef GE_DIALOGUE_H
#define GE_DIALOGUE_H

#include "ge_text.h"
#include "ge_sprites.h"
#include "ge_animations.h"

using namespace bn;

typedef const dialogue_line conversation[128];

{sprite_includes}

{'\n'.join(declarations)}

#endif // GE_DIALOGUE_H
"""
    return template_h


# --- Corrected function to generate source file content ---
def generate_cpp_content(conversations, sprite_list):
    """Generates the content for the .cpp file with the actual definitions."""

    sprite_includes = "\n".join(
        [f'#include "bn_sprite_items_{s}.h"' for s in sprite_list if s != "nullptr"]
    )

    definitions = []
    for convo_name in sorted(conversations.keys()):
        entries = conversations[convo_name]
        definitions.append(f"const conversation {convo_name} = {{")

        for entry in entries:
            index_value = entry["index"] if entry["index"] else "0"

            # --- FIX #1: Use a single '&' for variable addresses ---
            anim_value = (
                f'{entry["anim"]}'
                if entry["anim"] != "nullptr"
                else "static_cast<const animation*>(nullptr)"
            )

            dlg1_value = (
                f'{entry["dlg1"]}'
                if entry["dlg1"] != "nullptr"
                else "static_cast<const conversation*>(nullptr)"
            )
            dlg2_value = (
                f'{entry["dlg2"]}'
                if entry["dlg2"] != "nullptr"
                else "static_cast<const conversation*>(nullptr)"
            )

            # --- FIX #2: Removed extra '}' at the very end of the line ---
            line = (
                f'    {{{entry["id"]}, {entry["portrait"]}, {entry["emotion"]}, {entry["action"]}, '
                f'"{entry["line1"]}", "{entry["line2"]}", "{entry["line3"]}", '
                f'{entry["color"]}, {entry["size"]}, {entry["speed"]}, '
                f"{index_value}, {anim_value}, "
                f'{{{entry["nav"][0]}, {entry["nav"][1]}}}, '
                f"{dlg1_value}, {dlg2_value}}}"
            )
            definitions.append(line + ",")

        eol_line = '    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}'
        definitions.append(eol_line + "};")
        definitions.append("")

    template_cpp = f"""// ge_dialogue.cpp
// THIS IS AN AUTO-GENERATED FILE. DO NOT EDIT.

#include "ge_dialogue.h"

{sprite_includes}

{'\n'.join(definitions)}
"""
    return template_cpp


# --- Main Execution Logic ---
if __name__ == "__main__":
    input_file = "dialogue.txt"

    # Create output directories if they don't exist
    if not os.path.exists("include"):
        os.makedirs("include")
    if not os.path.exists("src"):
        os.makedirs("src")

    output_header_path = "include/ge_dialogue.h"
    output_source_path = "src/ge_dialogue.cpp"

    print(f"Processing '{input_file}'...")

    try:
        conversations = process_csv(input_file)
    except SystemExit:
        # Re-raise SystemExit to ensure the script exits with the proper code
        raise
    except Exception as e:
        print(f"ERROR: An unexpected error occurred: {e}")
        sys.exit(1)

    # Generate content for both files
    header_file_content = generate_header_content(conversations, sprites)
    cpp_file_content = generate_cpp_content(conversations, sprites)

    # Write the header file
    with open(output_header_path, "w", encoding="utf-8") as f:
        f.write(header_file_content)
    print(f"Successfully generated header file: {output_header_path}")

    # Write the source file
    with open(output_source_path, "w", encoding="utf-8") as f:
        f.write(cpp_file_content)
    print(f"Successfully generated source file: {output_source_path}")

    print("All dialogue lines validated successfully (≤20 characters).")
