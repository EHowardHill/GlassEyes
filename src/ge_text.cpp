// ge_text.cpp

#include "bn_log.h"
#include "bn_sound_items.h"
#include "bn_sound_items_info.h"
#include "bn_random.h"

#include "ge_sprites.h"
#include "ge_globals.h"
#include "ge_text.h"
#include "ge_character_manager.h"

#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_music_items_info.h"

// Sprites
#include "bn_sprite_items_spr_font_01.h"
#include "bn_sprite_items_hearts.h"
#include "bn_regular_bg_items_bg_dialogue_box.h"

#include "bn_sprite_items_db_ch_jeremy.h"
#include "bn_sprite_items_db_ch_vista.h"
#include "bn_sprite_items_db_ch_visker.h"
#include "bn_sprite_items_db_ch_visker_wife.h"
#include "bn_sprite_items_db_ch_ginger.h"
#include "bn_sprite_items_db_ch_temmie.h"

#include "ge_dialogue.h"

using namespace bn;

constexpr char alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
    '[', ']', '\\', '{', '}', '|', ';', '\'', ':', '"', ',', '.', '/',
    '<', '>', '?'};

const char *ITEM_LABELS[ITEMS_SIZE] = {
    "Lime",
    "Photo (Croke)",
    "Document"};

const bool ITEM_DROP[ITEMS_SIZE] = {
    true,
    false,
    false};

const conversation *ITEM_CONVOS[ITEMS_SIZE] = {
    &convo_lime,
    &convo_photo};

vector<toast, 16> text::toasts;

letter::letter(char ch, vector_2 ideal_position_) : ideal_position(ideal_position_)
{
    char_index = -1;

    for (size_t i = 0; i < sizeof(alphabet); ++i)
    {
        if (ch == alphabet[i])
        {
            char_index = i;
            break;
        }
    }

    if (char_index > -1)
    {
        sprite = sprite_items::spr_font_01.create_sprite(ideal_position_.x, ideal_position_.y, char_index);
    }
}

void letter::update(bool shake, int size)
{
    if (size == SIZE_LARGE)
    {
        sprite.value().set_scale(2, 2);
    }
    else if (size == SIZE_SMALL)
    {
        sprite.value().set_scale(0.75, 0.75);
    }

    if (shake)
    {
        temp_position = {
            ideal_position.x + global_data_ptr->bn_random.get_int(6) - 3,
            ideal_position.y + global_data_ptr->bn_random.get_int(6) - 3,
        };

        if (sprite.value().x().integer() < temp_position.x.integer())
        {
            sprite.value().set_x(sprite.value().x() + 1);
        }
        else if (sprite.value().x() > temp_position.x.integer())
        {
            sprite.value().set_x(sprite.value().x() - 1);
        }

        if (sprite.value().y().integer() < temp_position.y.integer())
        {
            sprite.value().set_y(sprite.value().y() + 1);
        }
        else if (sprite.value().y().integer() > temp_position.y.integer())
        {
            sprite.value().set_y(sprite.value().y() - 1);
        }
    }
}

text::text()
{
}

text::text(vector_2 start_) : start(start_)
{
}

text::text(const char *value, vector_2 start_) : start(start_)
{
    if (value)
        init(value);
}

text::text(const string<20> &value, vector_2 start_) : start(start_)
{
    reference = value;
    letters.clear();
    current_x = 0;
    index = 0;
}

void text::init(const char *value)
{
    if (!value)
    {
        reference.clear();
        letters.clear();
        current_x = 0;
        index = 0;
        return;
    }

    // Convert C-string to bn::string
    reference = string<20>(value);
    letters.clear();
    current_x = 0;
    index = 0;
}

void text::init(const string<20> &value)
{
    // Convert C-string to bn::string
    reference = value;
    letters.clear();
    current_x = 0;
    index = 0;
}

void text::update(const bn::sprite_item *portrait = nullptr, bool typewriter = false)
{
    if (index >= reference.size() || is_ended())
    {
        return;
    }

    if (index % 2 == 0)
    {
        if (portrait == &sprite_items::db_ch_vista || portrait == &sprite_items::db_ch_ginger)
        {
            sound_items::snd_dialogue_vista.play(0.7);
        }
        else if (portrait == &sprite_items::db_ch_jeremy)
        {
            sound_items::snd_dialogue_jeremy.play(0.7);
        }
        else if (portrait == &sprite_items::db_ch_visker)
        {
            sound_items::snd_dialogue_visker.play(0.4);
        }
        else if (typewriter)
        {
            sound_items::snd_dialogue_typewriter.play(0.5);
        }
        else
        {
            sound_items::snd_dialogue_generic.play(0.5);
        }
    }

    char ch = reference[index];

    int current_size = SIZE_DEFAULT;
    int spacing = 8; // Default portrait spacing

    // Adjust spacing based on size
    if (current_size == SIZE_LARGE)
    {
        spacing = 16; // Larger spacing for large text
    }
    else if (current_size == SIZE_SMALL)
    {
        spacing = 6; // Smaller spacing for small text
    }

    if (ch == ' ')
    {
        current_x += spacing; // Use the size-adjusted spacing
        index++;
        return;
    }

    // Create letter at current position
    letter new_letter = {ch, {start.x + current_x, start.y}};

    if (new_letter.char_index > -1)
    {
        letters.push_back(new_letter);
        current_x += spacing; // Use size-adjusted spacing instead of hardcoded 8
        index++;
    }
}

void text::render()
{
    // Clear any existing letters first
    letters.clear();
    current_x = 0;

    // Check if reference is empty before processing
    if (reference.empty())
    {
        index = 0;
        return;
    }

    index = 0;
    while (index < reference.size())
    {
        int current_size = SIZE_DEFAULT;
        int spacing = 8; // Default spacing

        // Adjust spacing based on size
        if (current_size == SIZE_LARGE)
        {
            spacing = 16; // Larger spacing for large text
        }
        else if (current_size == SIZE_SMALL)
        {
            spacing = 6;
        }

        char ch = reference[index];

        if (ch == ' ')
        {
            current_x += spacing;
            index++;
        }
        else
        {
            // Create letter at current position
            letter new_letter = {ch, {start.x + current_x, start.y}};

            if (new_letter.char_index > -1)
            {
                letters.push_back(new_letter);
                current_x += spacing;
            }
            index++;
        }
    }
}

bool text::is_ended()
{
    return index >= reference.size() || reference[index] == '\0'; // Fixed end condition
}

void text::set_position(int x, int y)
{
    start.x = x;
    start.y = y;
    int current_x_pos = x;
    for (auto &letter : letters)
    {
        letter.ideal_position = {current_x_pos, y};
        current_x_pos += 8;
    }
}

dialogue_box::dialogue_box()
{
    box = regular_bg_items::bg_dialogue_box.create_bg(0, 0);
    pointer = sprite_items::spr_font_01.create_sprite(-52, 32, 73);
    ticker = 0;
    active_conversation = nullptr;
    index = 0;
    size = 0;
    is_branching = false;
    branching_selection = 0;
    num_options = 0;
}

void dialogue_box::load(const conversation *new_conversation)
{
    active_conversation = new_conversation;
    index = 0;
    size = 0;

    for (int i = 0; i < 64; i++)
    {
        if ((*active_conversation)[i].action == ACT_END)
        {
            break;
        }
        size++;
    }
}

void dialogue_box::init(character_manager *ch_man)
{
    if (!active_conversation || is_ended())
    {
        return;
    }

    bool skip = false;

    do
    {
        skip = false;
        const dialogue_line &line = (*active_conversation)[index];

        // Check if this is a branching dialogue
        is_branching = (line.dlg01 != nullptr);

        if (is_branching)
        {
            // Set up branching mode
            branching_selection = 0;
            num_options = (line.dlg02 != nullptr) ? 3 : 2;

            // Change pointer to hearts sprite for selection
            BN_LOG("setting pointer:");
            pointer = sprite_items::hearts.create_sprite(-64, 36, 1);

            // Instantly render all options
            for (int t = 0; t < num_options; t++)
            {
                lines[t].init(line.raw_text[t]);
                lines[t].size = line.size;
                lines[t].render(); // Instant display for branching
            }

            // Clear unused lines if only 2 options
            if (num_options == 2)
            {
                lines[2].init("");
            }

            // Don't show portrait in branching mode
            portrait.reset();

            // Update selector position
            update_branching_selector();

            // Skip the rest of normal dialogue processing
            return;
        }

        // Rest of your existing init code for normal dialogue...
        if (line.portrait != nullptr)
        {
            portrait = line.portrait->create_sprite(-84, 56, line.emotion);
        }
        else
        {
            portrait.reset();
        }

        if (line.action == ACT_SPAWN)
        {
            ch_man->add_character(line.index, line.navigate, 0);
        }

        auto ch = ch_man->find_by_index(line.index);
        if (ch)
        {
            if (line.navigate.x != 0 && line.navigate.y != 0)
            {
                if (line.action == ACT_TELEPORT)
                {
                    ch->v_sprite.bounds.position.x = line.navigate.x * 32;
                    ch->v_sprite.bounds.position.y = line.navigate.y * 32;
                }
                else if (line.action == ACT_WALK)
                {
                    ch->move_to = line.navigate;
                }
            }
            ch->idle_animation = line.anim;
        }

        for (int t = 0; t < 3; t++)
        {
            lines[t].init(line.raw_text[t]);
            lines[t].size = line.size;
        }

        // Rest of your existing switch statement...
        switch (line.action)
        {
        case ACT_ITEM:
        {
            global_data_ptr->items[line.index] = true;
            break;
        }
        case ACT_SFX_KNOCK:
        {
            sound_items::sfx_knock.play();
            break;
        }
        case ACT_MUSIC_VISKER:
        {
            music::stop();
            music_items::theme_visker.play(0.75);
            break;
        }
        case ACT_MUSIC_GINGER:
        {
            music::stop();
            music_items::theme_ginger.play(0.75);
            break;
        }
        case ACT_MUSIC_FADEOUT:
        {
            ch_man->music_fadeout = true;
            break;
        }
        case ACT_MUSIC_RESET:
        {
            music::stop();
            global_data_ptr->bg_track->play(0.5);
            break;
        }
        case ACT_GOLD:
        {
            global_data_ptr->gold += line.index;
            break;
        }
        case ACT_FIGHT:
        {
            auto ginger = ch_man->find_by_index(CHAR_GINGER);
            if (ginger != nullptr)
            {
                auto g_pos = ginger->v_sprite.bounds.position;
                global_data_ptr->ginger_position = {g_pos.x.integer() / 32, g_pos.y.integer() / 32};
            }

            auto pos = ch_man->player_ptr->v_sprite.bounds.position;
            global_data_ptr->entry_position = {pos.x.integer() / 32, pos.y.integer() / 32};
            global_data_ptr->battle_foe = line.index;
            ch_man->alert();
            break;
        }
        case ACT_PROGRESS:
        {
            global_data_ptr->process_stage = line.index;
            ch_man->status = NEW_CHAPTER;
            break;
        }
        case ACT_CUE_GINGER:
        {
            auto ginger = ch_man->find_by_index(CHAR_GINGER);
            ginger->is_follow = true;
            ginger->follow_id = CHAR_JEREMY;
            break;
        }
        default:
        {
            break;
        }
        }

        if (line.emotion == EM_SKIP)
        {
            skip = true;
            index++;
        }
    } while (skip);
}

void dialogue_box::update()
{
    if (!active_conversation || index >= size)
    {
        return;
    }

    // Don't do normal update in branching mode
    if (is_branching)
    {
        return;
    }

    auto l = (*active_conversation)[index];

    // Only update portrait if it exists and has a valid portrait pointer
    if (portrait.has_value() && l.portrait != nullptr)
    {
        portrait.value().set_tiles(l.portrait->tiles_item(), (l.emotion * 2));
    }

    for (int t = 0; t < 3; t++)
    {
        for (auto &letter_ : lines[t].letters)
        {
            letter_.update(l.shake, l.size);
        }
    }

    if (!active_conversation || (lines[0].is_ended() && lines[1].is_ended() && lines[2].is_ended()))
    {
        return;
    }

    ticker++;

    // Speed controls go around here:

    if (portrait.has_value() && l.portrait != nullptr && ticker % 12 < 6)
    {
        portrait.value().set_tiles(l.portrait->tiles_item(), (l.emotion * 2) + 1);
    }

    if (ticker % 3 == 0)
    {
        for (int t = 0; t < 3; t++)
        {
            if (!lines[t].is_ended())
            {
                lines[t].update(l.portrait);
                return;
            }
        }
    }
}

void dialogue_box::handle_branching_input(character_manager *ch_man)
{
    if (!is_branching)
    {
        return;
    }

    // Handle up/down navigation
    if (keypad::up_pressed())
    {
        if (branching_selection > 0)
        {
            branching_selection--;
            sound_items::snd_dialogue_generic.play(0.3);
            update_branching_selector();
        }
    }
    else if (keypad::down_pressed())
    {
        if (branching_selection < num_options - 1)
        {
            branching_selection++;
            sound_items::snd_dialogue_generic.play(0.3);
            update_branching_selector();
        }
    }
    else if (keypad::a_pressed())
    {
        const dialogue_line &line = (*active_conversation)[index];

        // Play selection sound
        sound_items::snd_dialogue_generic.play(0.5);

        if (branching_selection == 0)
        {
            // Option 1: Continue normally
            is_branching = false;
            index++;

            // Reset pointer to normal dialogue pointer
            pointer = sprite_items::spr_font_01.create_sprite(-52, 32, 73);

            // Initialize the next dialogue line
            init(ch_man);
        }
        else if (branching_selection == 1 && line.dlg01 != nullptr)
        {
            // Option 2: Switch to dlg01
            is_branching = false;
            active_conversation = line.dlg01;
            index = 0;

            // Recalculate size for new conversation
            size = 0;
            for (int i = 0; i < 64; i++)
            {
                if ((*active_conversation)[i].action == ACT_END)
                {
                    break;
                }
                size++;
            }

            // Reset pointer to normal dialogue pointer
            pointer = sprite_items::spr_font_01.create_sprite(-52, 32, 73);

            // Initialize the new conversation
            init(ch_man);
        }
        else if (branching_selection == 2 && line.dlg02 != nullptr)
        {
            // Option 3: Switch to dlg02
            is_branching = false;
            active_conversation = line.dlg02;
            index = 0;

            // Recalculate size for new conversation
            size = 0;
            for (int i = 0; i < 64; i++)
            {
                if ((*active_conversation)[i].action == ACT_END)
                {
                    break;
                }
                size++;
            }

            // Reset pointer to normal dialogue pointer
            pointer = sprite_items::spr_font_01.create_sprite(-52, 32, 73);

            // Initialize the new conversation
            init(ch_man);
        }
    }
}

void dialogue_box::update_branching_selector()
{
    if (pointer.has_value() && is_branching)
    {
        // Position selector at the selected option
        pointer.value().set_y(32 + (branching_selection * 16));
        pointer.value().set_visible(true);
    }
}

bool dialogue_box::is_ended()
{
    if (!active_conversation)
    {
        return true;
    }
    return (*active_conversation)[index].action == ACT_END;
}

// Add this method to the dialogue_box class to check if current text is fully displayed
bool dialogue_box::is_text_complete()
{
    if (!active_conversation || index >= size)
    {
        return true;
    }

    // Check if all three lines are either ended or empty
    for (int i = 0; i < 3; i++)
    {
        if (!lines[i].reference.empty() && !lines[i].is_ended())
        {
            return false;
        }
    }
    return true;
}

// Add this method to instantly complete the current text
void dialogue_box::instant_complete_text()
{
    if (!active_conversation || index >= size)
    {
        return;
    }

    // Instantly render all three lines
    for (int i = 0; i < 3; i++)
    {
        if (!lines[i].reference.empty())
        {
            lines[i].render();
        }
    }
}

// Modified method to handle A button press
// This should be called from your main game loop or input handler
void dialogue_box::handle_a_button_press(character_manager *ch_man)
{
    if (!active_conversation || is_ended())
    {
        return;
    }

    // If in branching mode, let handle_branching_input handle it
    if (is_branching)
    {
        handle_branching_input(ch_man);
        return;
    }

    if (is_text_complete())
    {
        // Text is fully displayed, advance to next dialogue
        advance(ch_man);
    }
    else
    {
        // Text is still being revealed, instantly complete it
        instant_complete_text();
    }
}

// Add this method to advance to the next dialogue line
void dialogue_box::advance(character_manager *ch_man)
{
    index++;

    if (!is_ended())
    {
        init(ch_man); // Initialize the next dialogue line
    }
}

char digit_conv(int digit)
{
    return (char)((digit % 10) + 48);
}

toast::toast() {}

void text::add_toast(string<20> value, vector_2 pos)
{
    toast new_toast;

    if (text::at_location(pos))
    {
        pos.y -= 16;
    }

    new_toast.value = text(value, pos);
    new_toast.ticker = 0;
    text::toasts.push_back(new_toast);

    // Render the new toast
    text::toasts.back().value.render();
}

void text::add_toast(int value, vector_2 pos)
{
    string<20> temp;

    // Handle zero case
    if (value == 0)
    {
        temp.push_back('0');
    }
    else
    {
        // Check if negative and store the sign
        bool is_negative = false;
        if (value < 0)
        {
            is_negative = true;
            value = -value; // Make it positive for digit extraction
        }

        // Extract digits and store them in reverse
        string<20> reversed;
        while (value > 0)
        {
            reversed.push_back(digit_conv(value));
            value = value / 10;
        }

        // Add negative sign first if needed
        if (is_negative)
        {
            temp.push_back('-');
        }

        // Now push the digits to temp in correct order
        for (int i = reversed.size() - 1; i >= 0; i--)
        {
            temp.push_back(reversed[i]);
        }
    }

    toast new_toast;

    if (text::at_location(pos))
    {
        pos.y -= 16;
    }

    new_toast.value = text(temp, pos);
    new_toast.ticker = 0;
    text::toasts.push_back(new_toast);

    // Render the new toast
    text::toasts.back().value.render();
}

bool text::at_location(vector_2 pos)
{
    for (auto &t : text::toasts)
    {
        if (t.value.start.x == pos.x && t.value.start.y == pos.y)
        {
            return true;
        }
    }
    return false;
}

void text::update_toasts()
{
    int delete_toast = -1;
    for (int t = 0; t < text::toasts.size(); t++)
    {
        text::toasts.at(t).ticker++;

        if (text::toasts.at(t).ticker > 96)
        {
            delete_toast = t;
        }
    }
    if (delete_toast > -1)
    {
        text::toasts.erase(text::toasts.begin() + delete_toast);
    }
}

items_box::items_box() : cursor_position(0),
                         scroll_offset(0),
                         total_items(0),
                         active(false)
{
    // Initialize lines with proper positions
    lines[0] = text(nullptr, {-40, 32});
    lines[1] = text(nullptr, {-40, 48});
    lines[2] = text(nullptr, {-40, 64});
}

void items_box::init()
{
    // Create the dialogue box background
    box = regular_bg_items::bg_dialogue_box.create_bg(0, 0);

    // Create the selector sprite (using the same font sprite for "*")
    selector = sprite_items::spr_font_01.create_sprite(-52, 32, 73); // Adjust index for "*" character

    // Count items in inventory
    total_items = 0;
    for (int i = 0; i < ITEMS_SIZE; i++)
    {
        if (global_data_ptr->items[i])
        {
            item_indices[total_items] = i;
            total_items++;
        }
    }

    cursor_position = 0;
    scroll_offset = 0;
    active = true;

    string<20> temp;
    int value = global_data_ptr->gold;

    if (value == 0)
    {
        temp.push_back('0');
    }
    else
    {
        // Build digits without std::to_string to stay consistent with your text pipeline
        string<20> reversed;
        bool is_negative = false;
        if (value < 0)
        {
            is_negative = true;
            value = -value;
        }
        while (value > 0)
        {
            reversed.push_back(digit_conv(value));
            value /= 10;
        }
        if (is_negative)
        {
            temp.push_back('-');
        }
        for (int i = reversed.size() - 1; i >= 0; --i)
        {
            temp.push_back(reversed[i]);
        }
    }
    temp.push_back('G'); // append the "G" suffix (e.g., "10G")

    gold.init(temp); // set the reference string
    gold.render();   // create the letters

    refresh_display();
}

void items_box::refresh_display()
{
    // Clear all lines first
    for (int i = 0; i < 3; i++)
    {
        lines[i].init("");
    }

    if (total_items == 0)
    {
        // Display "No Items" on the first line
        lines[0].init("* No Items");
        lines[0].render();

        // Hide selector when no items
        if (selector.has_value())
        {
            selector.value().set_visible(false);
        }
    }
    else
    {
        // Display up to 3 items starting from scroll_offset
        for (int i = 0; i < 3 && (scroll_offset + i) < total_items; i++)
        {
            int item_idx = item_indices[scroll_offset + i];

            // Create item text with some spacing from the selector
            string<20> item_text = "  "; // Two spaces for selector area
            item_text.append(ITEM_LABELS[item_idx]);

            lines[i].init(item_text.c_str());
            lines[i].render();
        }

        // Show and position selector
        if (selector.has_value())
        {
            selector.value().set_visible(true);
            // Position selector at current cursor position
            selector.value().set_position(-52, 32 + (cursor_position * 16));
        }
    }
}

void items_box::handle_input(character_manager *ch_man)
{
    if (!active || total_items == 0)
    {
        return;
    }

    // Handle up/down navigation
    if (keypad::up_pressed())
    {
        if (cursor_position > 0)
        {
            cursor_position--;
            sound_items::snd_dialogue_generic.play(0.3);
        }
        else if (scroll_offset > 0)
        {
            scroll_offset--;
            sound_items::snd_dialogue_generic.play(0.3);
        }
        refresh_display();
    }
    else if (keypad::down_pressed())
    {
        int items_on_screen = min(3, total_items - scroll_offset);

        if (cursor_position < items_on_screen - 1)
        {
            cursor_position++;
            sound_items::snd_dialogue_generic.play(0.3);
        }
        else if (scroll_offset + items_on_screen < total_items)
        {
            scroll_offset++;
            sound_items::snd_dialogue_generic.play(0.3);
        }
        refresh_display();
    }
    // Handle item selection
    else if (keypad::a_pressed())
    {
        int selected_idx = get_selected_item_index();
        if (selected_idx >= 0 && selected_idx < ITEMS_SIZE)
        {
            // Play selection sound
            sound_items::snd_alert.play(0.5);

            // Load the associated conversation
            if (ITEM_CONVOS[selected_idx] != nullptr)
            {
                // Create dialogue box and load conversation
                ch_man->db = dialogue_box();
                ch_man->db.value().load(ITEM_CONVOS[selected_idx]);
                ch_man->db.value().init(ch_man);
            }

            // Remove item if needed
            if (ITEM_DROP[selected_idx])
            {
                global_data_ptr->items[selected_idx] = false;

                // Rebuild item list
                int new_total = 0;
                for (int i = 0; i < ITEMS_SIZE; i++)
                {
                    if (global_data_ptr->items[i])
                    {
                        item_indices[new_total] = i;
                        new_total++;
                    }
                }
                total_items = new_total;

                // Adjust cursor and scroll if needed
                if (cursor_position >= total_items && total_items > 0)
                {
                    cursor_position = total_items - 1;
                }
                if (scroll_offset >= total_items && total_items > 0)
                {
                    scroll_offset = max(0, total_items - 3);
                }
            }

            // Close items box
            close();
        }
    }
    // Handle cancel/back
    else if (keypad::b_pressed())
    {
        sound_items::snd_dialogue_generic.play(0.3);
        close();
    }
}

void items_box::update()
{
    if (!active)
    {
        return;
    }

    // Just keep the display updated
    // Animation or other visual updates could go here
}

void items_box::close()
{
    active = false;
    box.reset();
    selector.reset();

    // Clear text lines
    for (int i = 0; i < 3; i++)
    {
        lines[i].letters.clear();
    }
}

int items_box::get_selected_item_index() const
{
    if (total_items == 0)
    {
        return -1;
    }

    int actual_selection = scroll_offset + cursor_position;
    if (actual_selection >= 0 && actual_selection < total_items)
    {
        return item_indices[actual_selection];
    }

    return -1;
}