// ge_game_numpad.cpp

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sound_items.h"
#include "bn_sound_items_info.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_number_pad.h"

#include "ge_game_numpad.h"

using namespace bn;

constexpr int WINNING_CODE[4] = {3, 4, 7, 7};

int game_numpad()
{
    int success = -1; // -1 = ongoing, 1 = success, 0 = failure

    vector<sprite_ptr, 10> numpad_sprites;
    vector<int, 4> input_code;

    // Create 3x3 grid for numbers 1-9
    int number = 1;
    for (int y = 0; y < 3; y++) // Iterate row first for clarity

    {
        for (int x = 0; x < 3; x++) // Iterate column second

        {

            // 1. Calculate the Y position:
            int sprite_y = -56 + (y * 36);

            // 2. Calculate the X position:
            int sprite_x = -36 + (x * 36);

            auto sprite = sprite_items::number_pad.create_sprite(
                sprite_x,
                sprite_y,
                number);
            numpad_sprites.push_back(sprite);

            number++;
        }
    }

    // Place '0' centered below the 7, 8, 9 row (index 9, tile index 0).
    // The '8' button is at index 7.
    auto zero = sprite_items::number_pad.create_sprite(0, 56, 0);
    numpad_sprites.push_back(zero);

    int selected_number = 0; // The vector index, starting at '1' sprite (index 0).

    /* The sprite tiles are arranged from 0-9 in three sets:
       0-9: Normal State
       10-19: Selected State (A-button pressed)
       20-29: Hover/Cursor State (currently focused)
    */

    // Helper to map the vector index (0-9) to the base tile index (0-9).
    // Indices 0-8 (for numbers 1-9) map to base tiles 1-9.
    // Index 9 (for number 0) maps to base tile 0.
    auto get_base_tile_index = [](int vector_index)

    {
        return (vector_index == 9) ? 0 : vector_index + 1;
    };

    // Helper to check if a number has been selected and is in the input_code
    auto is_number_in_input_code = [&](int number)

    {
        for (int code_val : input_code)

        {
            if (code_val == number)

            {
                return true;
            }
        }
        return false;
    };

    // Set initial button to hover state (20-29)
    int initial_base_tile = get_base_tile_index(selected_number);
    numpad_sprites.at(selected_number).set_tiles(sprite_items::number_pad.tiles_item(),
                                                 initial_base_tile + 20); // Hover/Cursor state (20-29)

    while (success == -1)

    {
        // --- Input Handling (Movement) ---
        int old_selected_number = selected_number;

        if (keypad::left_pressed())

        {
            // Simple circular wrap around all 10 buttons (0-9)
            selected_number = (selected_number + 9) % 10;
        }
        else if (keypad::right_pressed())

        {
            // Simple circular wrap around all 10 buttons (0-9)
            selected_number = (selected_number + 1) % 10;
        }
        else if (keypad::up_pressed())

        {
            // Fixes for the 3x3 grid structure with '0' below '8'
            if (selected_number == 9) // Current is '0'

            {
                // Move from '0' (index 9) UP to '8' (index 7)
                selected_number = 7;
            }
            else if (selected_number >= 3) // Middle (3-5) and Bottom (6-8) rows

            {
                // Standard UP movement (subtract 3 from index)
                selected_number -= 3;
            }
            else if (selected_number >= 0 && selected_number <= 2)

            {
                // Wrap from Top Row (0-2) UP to Bottom Row (6-8)
                selected_number += 6;
            }
        }
        else if (keypad::down_pressed())

        {
            // Fixes for the 3x3 grid structure with '0' below '8'
            if (selected_number == 7) // Current is '8'

            {
                // Move from '8' (index 7) DOWN to '0' (index 9)
                selected_number = 9;
            }
            else if (selected_number <= 5) // Top (0-2) and Middle (3-5) rows

            {
                // Standard DOWN movement (add 3 to index)
                selected_number += 3;
            }
            else if (selected_number == 6 || selected_number == 8)

            {
                // Wrap from Bottom Row corners (6 and 8) DOWN to Top Row (0-2)
                selected_number -= 6;
            }
        }

        // Only play sound if the selection index changed after processing the input
        if (old_selected_number != selected_number)

        {
            sound_items::snd_select.play();
        }

        // --- Visual Updates after Movement ---
        if (old_selected_number != selected_number)

        {
            // 1. Revert Old Sprite
            // Map old vector index to number value (0-9)
            int old_number_value = (old_selected_number == 9) ? 0 : old_selected_number + 1;
            int old_base_tile = get_base_tile_index(old_selected_number);

            if (is_number_in_input_code(old_number_value))

            {
                // If it was entered (A pressed), set it to the permanent SELECTED state (10-19)
                numpad_sprites.at(old_selected_number).set_tiles(sprite_items::number_pad.tiles_item(),
                                                                 old_base_tile + 10); // Permanent SELECTED state (10-19)
            }
            else
            {
                // Otherwise, revert to the NORMAL state (0-9)
                numpad_sprites.at(old_selected_number).set_tiles(sprite_items::number_pad.tiles_item(),
                                                                 old_base_tile); // Normal state (0-9)
            }

            // 2. Set New Sprite
            int new_base_tile = get_base_tile_index(selected_number);
            // The currently selected tile always gets the HOVER/CURSOR visual (20-29)
            numpad_sprites.at(selected_number).set_tiles(sprite_items::number_pad.tiles_item(),
                                                         new_base_tile + 20); // Hover/Cursor state (20-29)
        }

        // --- Input Handling (A button press) ---
        if (keypad::a_pressed())

        {
            // Map selected_number (vector index) to actual number value
            int number = (selected_number == 9) ? 0 : selected_number + 1;
            input_code.push_back(number);
            sound_items::sfx_click.play();

            // The currently selected tile is already in the HOVER state (20-29),
            // which provides visual feedback that a button was pressed.
            // The state change to SELECTED (10-19) only happens when the cursor moves off it (see above).

            if (input_code.size() == 4)

            {
                bool correct = true;
                for (int i = 0; i < 4; i++)

                {
                    if (input_code[i] != WINNING_CODE[i])

                    {
                        correct = false;
                        break;
                    }
                }

                if (correct)

                {
                    success = 1; // Code correct
                }
                else
                {
                    success = 0; // Code incorrect
                }
            }
        }

        core::update();
    }

    // --- Cleanup after loop ---
    // Revert all sprites to their normal state before feedback.
    for (int i = 0; i < numpad_sprites.size(); ++i)

    {
        int base_tile = get_base_tile_index(i);
        numpad_sprites.at(i).set_tiles(sprite_items::number_pad.tiles_item(), base_tile);
    }

    if (success == 1)

    {
        // Code was correct, proceed accordingly
        sound_items::snd_chime.play();
    }
    else
    {
        // Code was incorrect, handle failure
        sound_items::snd_miss.play();
    }

    for (int t = 0; t < 128; t++)

    {
        core::update();
    }

    return success;
}
