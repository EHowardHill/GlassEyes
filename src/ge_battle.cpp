// ge_battle.cpp

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_random.h"

#include "bn_regular_bg_items_bg_battle_grid.h"
#include "bn_regular_bg_items_bg_dialogue_box.h"
#include "bn_sprite_items_hearts.h"
#include "bn_sprite_items_battle_icons.h"
#include "bn_sprite_items_battle_chars.h"
#include "bn_sprite_items_battle_squares.h"

#include "ge_text.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_battle.h"
#include "ge_bullet.h"

using namespace bn;

// Helper functions
static bool is_alive(int idx, battle_state *bs)
{
    return idx >= 0 && idx < bs->party_size && global_data_ptr->hp[idx] > 0;
}

static int next_living(int from, battle_state *bs)
{
    for (int i = 1; i <= bs->party_size; ++i)
    {
        int idx = (from + i) % bs->party_size;
        if (is_alive(idx, bs))
            return idx;
    }
    return -1;
}

static int random_living(battle_state *bs)
{
    int cnt = 0, alive[4];
    for (int i = 0; i < bs->party_size; ++i)
    {
        if (is_alive(i, bs))
            alive[cnt++] = i;
    }
    return cnt > 0 ? alive[global_data_ptr->bn_random.get_int(0, cnt)] : -1;
}

static const char *get_name(int i)
{
    const char *names[] = {"JEREMY", "GINGER", "SEBELLUS", "VISTA"};
    return i < 4 ? names[i] : "ALLY";
}

static int count_action(battle_state *bs, int action)
{
    int count = 0;
    for (int i = 0; i < bs->party_size; ++i)
    {
        if (is_alive(i, bs) && bs->character_actions[i] == action)
            count++;
    }
    return count;
}

// Dialogue functions
static void init_dialogue(conversation *conv, battle_state *bs)
{
    if (!bs->bg_ptr)
    {
        bs->bg_ptr = regular_bg_items::bg_dialogue_box.create_bg(0, 0);
    }

    bs->active_conv = conv;
    bs->dlg_index = 0;
    bs->dlg_size = 0;
    bs->dlg_ticker = 0;

    // Count lines
    for (int i = 0; i < 64 && (*conv)[i].action != ACT_END; ++i)
    {
        bs->dlg_size++;
    }

    if (bs->dlg_size > 0)
    {
        const auto &line = (*conv)[0];
        if (line.portrait)
        {
            bs->portrait = line.portrait->create_sprite(-84, 56, line.emotion);
        }

        for (int i = 0; i < 3; ++i)
        {
            bs->dlg_lines[i].init(line.raw_text[i]);
            bs->dlg_lines[i].size = line.size;
        }
    }
}

static void update_dialogue(battle_state *bs)
{
    if (!bs->active_conv || bs->dlg_index >= bs->dlg_size)
        return;

    const auto &line = (*bs->active_conv)[bs->dlg_index];

    // Update portrait animation
    if (bs->portrait && line.portrait)
    {
        bs->portrait->set_tiles(line.portrait->tiles_item(),
                                (line.emotion * 2) + (bs->dlg_ticker % 12 < 6));
    }

    // Update text
    if (bs->dlg_ticker % 3 == 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (!bs->dlg_lines[i].is_ended())
            {
                bs->dlg_lines[i].update(line.portrait, false);
                break;
            }
        }
    }

    // Update letter effects
    for (int i = 0; i < 3; ++i)
    {
        for (auto &letter : bs->dlg_lines[i].letters)
        {
            letter.update(line.color, line.size);
        }
    }

    bs->dlg_ticker++;
}

static bool advance_dialogue(battle_state *bs)
{
    if (bs->dlg_index < bs->dlg_size - 1)
    {
        bs->dlg_index++;
        bs->dlg_ticker = 0;

        const auto &line = (*bs->active_conv)[bs->dlg_index];

        if (line.portrait)
        {
            bs->portrait = line.portrait->create_sprite(-84, 56, line.emotion);
        }
        else
        {
            bs->portrait.reset();
        }

        for (int i = 0; i < 3; ++i)
        {
            bs->dlg_lines[i].init(line.raw_text[i]);
            bs->dlg_lines[i].size = line.size;
        }
        return true;
    }
    return false;
}

static void clear_dialogue(battle_state *bs)
{
    bs->bg_ptr.reset();
    bs->portrait.reset();
    bs->active_conv = nullptr;
    bs->dlg_ticker = 0;
    for (int i = 0; i < 3; ++i)
    {
        bs->dlg_lines[i].letters.clear();
        bs->dlg_lines[i].index = 0;
        bs->dlg_lines[i].size = 0;
    }
}

static bool is_dialogue_active(battle_state *bs)
{
    return bs->active_conv && bs->dlg_index < bs->dlg_size;
}

static bool are_lines_complete(battle_state *bs)
{
    return bs->dlg_lines[0].is_ended() &&
           bs->dlg_lines[1].is_ended() &&
           bs->dlg_lines[2].is_ended();
}

static int get_character_y_position(int index)
{
    // Stack characters vertically, with first character highest
    return 8 - (index * 32);
}

static void update_character_animation(int char_index, battle_state &bs)
{
    if (!bs.character_sprites[char_index])
        return;

    auto &sprite = bs.character_sprites[char_index];
    int &state = bs.character_states[char_index];
    int &ticker = bs.character_tickers[char_index];

    // Get appropriate sprite item and frame ranges based on character
    const sprite_item *spr_item = nullptr;
    int idle_start, idle_end, hurt_start, hurt_end, atk_start, atk_end;
    int intro_frames = 55; // Default intro length

    switch (char_index)
    {
    case 0: // Jeremy
        spr_item = &sprite_items::jeremy_battle;
        idle_start = JEREMY_IDLE_START;
        idle_end = JEREMY_IDLE_START; // Single frame idle for Jeremy
        hurt_start = JEREMY_HURT_START;
        hurt_end = JEREMY_HURT_END;
        atk_start = JEREMY_ATK_START;
        atk_end = JEREMY_ATK_END;
        break;

    case 1: // Ginger
        spr_item = &sprite_items::ginger_battle;
        idle_start = GINGER_IDLE_START;
        idle_end = GINGER_IDLE_END;
        hurt_start = GINGER_HURT_START;
        hurt_end = GINGER_HURT_END;
        atk_start = GINGER_ATK_START;
        atk_end = GINGER_ATK_END;
        intro_frames = 40;
        break;

    // Add cases for other characters as needed
    default:
        return; // Unknown character
    }

    int y_offset = get_character_y_position(char_index) + bs.y_delta;

    switch (state)
    {
    case 0:
    { // INTRO
        if (ticker < intro_frames)
        {
            // Intro animation
            if (char_index == 0) // Jeremy has special intro
            {
                sprite->set_tiles(spr_item->tiles_item(), ticker / 5);
            }
            else if (char_index == 1) // Ginger intro
            {
                // Ginger's intro uses frames 0-7 (before idle starts at 8)
                int frame = ticker / 5;
                if (frame >= idle_start)
                {
                    frame = idle_start - 1;
                }
                sprite->set_tiles(spr_item->tiles_item(), frame);
            }
            ticker++;
        }
        else
        {
            state = 1; // Go to idle
            ticker = 0;
            sprite->set_tiles(spr_item->tiles_item(), idle_start);
        }
        break;
    }

    case 1:
    {                              // IDLE
        if (idle_end > idle_start) // Animated idle
        {
            int frame = idle_start + ((ticker / 8) % (idle_end - idle_start + 1));
            sprite->set_tiles(spr_item->tiles_item(), frame);
            ticker++;
        }
        else // Static idle
        {
            sprite->set_tiles(spr_item->tiles_item(), idle_start);
        }
        break;
    }

    case 2: // HURT
    {
        constexpr int TICKS_PER_FRAME = 4;
        int anim_frame_idx = ticker / TICKS_PER_FRAME;
        int frame = hurt_start + anim_frame_idx;

        if (frame > hurt_end)
        {
            state = 1; // Back to idle
            ticker = 0;
            sprite->set_tiles(spr_item->tiles_item(), idle_start);
        }
        else
        {
            sprite->set_tiles(spr_item->tiles_item(), frame);
            ticker++;
        }

        break;
    }

    case 3: // ATTACK
    {
        constexpr int TICKS_PER_FRAME = 3;
        int anim_frame_idx = ticker / TICKS_PER_FRAME;
        int frame = atk_start + anim_frame_idx;

        if (frame > atk_end)
        {
            state = 1; // Back to idle
            ticker = 0;
            sprite->set_tiles(spr_item->tiles_item(), idle_start);
        }
        else
        {
            sprite->set_tiles(spr_item->tiles_item(), frame);
            ticker++;
        }

        break;
    }

    default:
    {
        break;
    }
    }

    sprite->set_position(-96, y_offset);
}

// Main battle function
int battle_map()
{
    music::stop();
    music_items::boss.play();
    sound_items::snd_fight_start.play();

    auto bg_grid = regular_bg_items::bg_battle_grid.create_bg(0, 0);

    // Create and reset battle state
    battle_state bs;

    bs.heart = sprite_items::hearts.create_sprite(0, 0, 1);

    // Setup conversations based on foe
    vector<conversation *, 3> convos[RESULT_SIZE];
    vector<conversation *, 3> spare_convos;

    switch (global_data_ptr->foe)
    {
    case FOE_VISKERS_01:
        bs.enemy_sprite_item = &sprite_items::visker_battle;
        global_data_ptr->enemy_max_hp[0] = 12;
        global_data_ptr->enemy_hp[0] = 12;
        bs.moveset = 3;
        bs.speed = 100;

        // Just Jeremy for this battle
        bs.party_size = 1;
        bs.character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
        bs.character_sprites[0]->set_z_order(0);

        convos[RESULT_FIRST].push_back(&garbage_fight_01);
        convos[RESULT_UP].push_back(&garbage_fight_02);
        convos[RESULT_UP].push_back(&garbage_fight_03);
        convos[RESULT_LAST_WIN].push_back(&garbage_fight_04);

        spare_convos.push_back(&garbage_spare);
        spare_convos.push_back(&garbage_fight_02);
        spare_convos.push_back(&garbage_fight_03);
        break;

    case FOE_VISKERS_02:
        bs.enemy_sprite_item = &sprite_items::visker_battle;
        global_data_ptr->enemy_max_hp[0] = 99;
        global_data_ptr->enemy_hp[0] = 99;
        bs.moveset = BULLET_SIZE;
        bs.speed = 300;

        bs.party_size = 1;
        bs.character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);

        convos[RESULT_FIRST].push_back(&garbage_fight_05);
        spare_convos.push_back(&garbage_spare);
        break;

    case FOE_CROKE_01:
        bs.enemy_sprite_item = &sprite_items::croke_battle;
        global_data_ptr->enemy_max_hp[0] = 0;
        global_data_ptr->enemy_hp[0] = 0;

        bs.party_size = 2;
        bs.character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
        bs.character_sprites[1] = sprite_items::ginger_battle.create_sprite(-96, get_character_y_position(1), 0);

        // For Croke, we don't use the normal convos array
        // We'll handle his sequence specially
        bs.croke_conv_index = 0;
        bs.croke_anim_frame = 0;
        break;

    case FOE_TEST:
        bs.enemy_sprite_item = &sprite_items::visker_battle;
        global_data_ptr->enemy_max_hp[0] = 99;
        global_data_ptr->enemy_hp[0] = 99;
        bs.moveset = BULLET_SIZE;
        bs.speed = 5;

        bs.party_size = 2;
        bs.character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
        bs.character_sprites[1] = sprite_items::ginger_battle.create_sprite(-96, get_character_y_position(1), 0);

        convos[RESULT_FIRST].push_back(&garbage_fight_05);
        break;

    default:
        break;
    }

    for (int i = 0; i < bs.party_size; ++i)
    {
        if (bs.character_sprites[i])
            bs.character_sprites[i]->set_z_order(i);
    }

    bs.enemy_sprite = bs.enemy_sprite_item->create_sprite(96, 16, 0);

    // Main game loop
    while (true)
    {
        bg_grid.set_position(bg_grid.x() - 1, bg_grid.y() - 1);

        // Update all character animations
        for (int i = 0; i < bs.party_size; ++i)
        {
            update_character_animation(i, bs);
        }

        // Update enemy animation
        if (global_data_ptr->foe == FOE_CROKE_01)
        {
            // Special animation handling for Croke
            if (bs.stage == stage_talking && bs.active_conv)
            {
                // Determine frame range based on conversation index
                int start_frame = 0, end_frame = 4;

                if (bs.croke_conv_index == 1)
                { // croke_02 (first conv)
                    start_frame = 0;
                    end_frame = 4;
                }
                else if (bs.croke_conv_index == 2)
                { // croke_03 (second conv)
                    start_frame = 5;
                    end_frame = 12;
                }
                else if (bs.croke_conv_index == 3)
                { // croke_04 (third conv)
                    start_frame = 19;
                    end_frame = 21;
                }

                // Animate through the frames slowly
                if (bs.enemy_ticker % 6 == 0)
                {
                    if (bs.croke_anim_frame < end_frame)
                    {
                        bs.croke_anim_frame++;
                    }
                }

                // Clamp to valid range
                if (bs.croke_anim_frame > end_frame)
                    bs.croke_anim_frame = end_frame;
                if (bs.croke_anim_frame < start_frame)
                    bs.croke_anim_frame = start_frame;

                bs.enemy_sprite->set_tiles(sprite_items::croke_battle.tiles_item(), bs.croke_anim_frame);
                bs.enemy_ticker++;
            }
        }
        else
        {
            // Normal enemy animation for other enemies
            switch (bs.enemy_state)
            {
            case 0: // INTRO
                if (bs.enemy_ticker < 35)
                {
                    bs.enemy_sprite->set_tiles(sprite_items::visker_battle.tiles_item(),
                                               bs.enemy_ticker / 5);
                    bs.enemy_ticker++;
                }
                else
                {
                    bs.enemy_state = 1;
                }
                break;

            case 1: // IDLE
                bs.enemy_sprite->set_tiles(sprite_items::visker_battle.tiles_item(),
                                           ((bs.enemy_ticker / 5) % 4) + 6);
                bs.enemy_ticker++;
                break;

            case 2: // ATTACK
                bs.enemy_sprite->set_tiles(sprite_items::visker_battle.tiles_item(),
                                           ((bs.enemy_ticker / 5) % 6) + 10);
                bs.enemy_ticker++;
                break;

            default:
                break;
            }
        }
        bs.enemy_sprite->set_position(96, 16 + bs.y_delta);

        // Y offset for dialogue
        bs.y_delta += is_dialogue_active(&bs) ? (bs.y_delta > -32 ? -4 : 0) : (bs.y_delta < 0 ? 4 : 0);

        // Stage: Talking
        if (bs.stage == stage_talking)
        {
            // Special handling for Croke battle
            if (global_data_ptr->foe == FOE_CROKE_01)
            {
                if (!is_dialogue_active(&bs))
                {
                    // Start the appropriate Croke conversation
                    if (bs.croke_conv_index == 0)
                    {
                        init_dialogue(&croke_02, &bs);
                        bs.croke_anim_frame = 0;
                        bs.croke_conv_index = 1;
                    }
                    else if (bs.croke_conv_index == 1)
                    {
                        init_dialogue(&croke_03, &bs);
                        bs.croke_anim_frame = 5;
                        bs.croke_conv_index = 2;
                    }
                    else if (bs.croke_conv_index == 2)
                    {
                        init_dialogue(&croke_04, &bs);
                        bs.croke_anim_frame = 13;
                        bs.croke_conv_index = 3;
                    }
                    else
                    {
                        // All Croke conversations done, end battle
                        music::stop();
                        text::toasts.clear();
                        return CONTINUE;
                    }
                }
                else
                {
                    update_dialogue(&bs);

                    if (keypad::a_pressed() && are_lines_complete(&bs))
                    {
                        if (!advance_dialogue(&bs))
                        {
                            clear_dialogue(&bs);
                            // For Croke, stay in talking stage
                        }
                    }
                }
            }
            else
            {
                // Normal battle dialogue flow
                if (global_data_ptr->enemy_hp[0] <= 0)
                {
                    bs.result = RESULT_LAST_WIN;
                }

                if (!is_dialogue_active(&bs))
                {
                    if (bs.result < RESULT_SIZE && convos[bs.result].size() > 0)
                    {
                        conversation *c = convos[bs.result].front();
                        convos[bs.result].erase(convos[bs.result].begin());
                        init_dialogue(c, &bs);
                    }
                    else
                    {
                        bs.stage = stage_recv;
                    }
                }
                else
                {
                    update_dialogue(&bs);

                    if (keypad::a_pressed() && are_lines_complete(&bs))
                    {
                        if (!advance_dialogue(&bs))
                        {
                            clear_dialogue(&bs);
                        }
                    }
                }
            }
        }

        // Stage: Recv (enemy turn)
        else if (bs.stage == stage_recv)
        {
            bs.bg_ptr = regular_bg_items::bg_battle_box.create_bg(0, 0);

            if (!bs.heart.has_value())
                bs.heart = sprite_items::hearts.create_sprite(0, 0, 1);

            if (bs.recv_ticker == 0)
            {
                bs.enemy_state = 2;
                bs.enemy_ticker = 0;
                bullet::populate(&bs.bullets, bs.selected_moveset, bs.speed);
                BN_LOG("MOVESET: ", bs.selected_moveset);
                bs.selected_moveset = (bs.selected_moveset + 1) % bs.moveset;
            }

            if (next_living(-1, &bs) < 0 || global_data_ptr->enemy_hp[0] <= 0)
            {
                music::stop();
                text::toasts.clear();
                return CONTINUE;
            }

            // Update heart position
            bs.heart_pos.x += keypad::right_held() - keypad::left_held();
            bs.heart_pos.y += keypad::down_held() - keypad::up_held();

            // Clamp positions
            if (bs.heart_pos.x < -48)
                bs.heart_pos.x = -48;
            if (bs.heart_pos.x > 48)
                bs.heart_pos.x = 48;
            if (bs.heart_pos.y < -48)
                bs.heart_pos.y = -48;
            if (bs.heart_pos.y > 48)
                bs.heart_pos.y = 48;

            bs.heart->set_position(bs.heart_pos.x, bs.heart_pos.y);
            bs.heart->set_tiles(sprite_items::hearts.tiles_item(), 1);

            // Update bullets
            for (auto &b : bs.bullets)
            {
                b.update();

                if (b.item && b.item->visible())
                {
                    if (abs(bs.heart_pos.x - b.item->x()) + abs(bs.heart_pos.y - b.item->y()) < 12)
                    {
                        int who = random_living(&bs);
                        if (who >= 0)
                        {
                            global_data_ptr->hp[who] -= 2;

                            // Position toast based on character's Y position
                            text::add_toast(-2, vector_2(-96, -44 + (who * 8)));
                            sound_items::sfx_damage.play();

                            // Trigger hurt animation for hit character
                            bs.character_states[who] = 2; // HURT state
                            bs.character_tickers[who] = 0;
                        }
                        b.item->set_visible(false);
                    }
                }
            }

            if (++bs.recv_ticker > 400)
            {
                bs.recv_ticker = 0;
                bs.current_actor = -1;

                // Reset for new round of turns
                for (int i = 0; i < MAX_PARTY_SIZE; ++i)
                {
                    bs.has_acted[i] = false;
                    bs.character_actions[i] = ACTION_NONE;
                }

                bs.choosing_for = 0;

                bs.stage = stage_status;
            }
        }

        // Stage: Status (player menu)
        else if (bs.stage == stage_status)
        {
            bs.bg_ptr.reset();
            bs.enemy_state = 1; // stay in idle
            bs.heart.reset();
            bs.bullets.clear();

            if (next_living(-1, &bs) < 0)
            {
                music::stop();
                text::toasts.clear();
                return CONTINUE;
            }

            // Check if item menu is active
            if (bs.item_menu.is_active())
            {
                bs.item_menu.update();

                if (keypad::a_pressed())
                {
                    // Get selected item
                    int selected_item = bs.item_menu.get_selected_item_index();
                    if (selected_item >= 0 && selected_item < ITEMS_SIZE)
                    {
                        // Check if item is available
                        if (global_data_ptr->items[selected_item])
                        {
                            sound_items::snd_alert.play();

                            // CHANGE: Instead of storing for later, use the item immediately

                            // Close item menu first
                            bs.item_menu.close();

                            // Clean up current character's UI
                            bs.char_img.reset();
                            for (int i = 0; i < 5; ++i)
                            {
                                bs.labels[i].reset();
                            }
                            for (int i = 0; i < 3; ++i)
                            {
                                bs.battle_icons[i].reset();
                            }

                            // Load the item's conversation immediately
                            if (ITEM_CONVOS[selected_item] != nullptr)
                            {
                                init_dialogue(const_cast<conversation *>(ITEM_CONVOS[selected_item]), &bs);

                                // Store which item was used so we can remove it after dialogue if needed
                                bs.used_item_index = selected_item;

                                // Set a new stage to handle returning from item dialogue
                                bs.stage = stage_item_dialogue;
                            }
                            else
                            {
                                // No conversation for this item, just remove it if needed and continue
                                if (ITEM_DROP[selected_item])
                                {
                                    global_data_ptr->items[selected_item] = false;
                                }

                                // Record that this character used an item
                                bs.character_actions[bs.choosing_for] = ACTION_ITEM;

                                // Move to next character
                                bs.choosing_for++;
                            }
                        }
                    }
                }

                else if (keypad::b_pressed())
                {
                    // Return to main menu
                    sound_items::snd_dialogue_generic.play();
                    bs.item_menu.close();
                    bs.selected_menu = STATUS_BAR_NONE;

                    // Restore main menu UI
                    bs.menu_index = 1; // Set to ITEM position
                    int icon_indices[] = {0, 2, 3};
                    for (int i = 0; i < 3; ++i)
                    {
                        bs.battle_icons[i] = sprite_items::battle_icons.create_sprite(-22, -12 + (18 * i), icon_indices[i]);
                    }
                }

                // Handle up/down navigation in item menu
                if (keypad::up_pressed())
                {
                    if (bs.item_menu.cursor_position > 0)
                    {
                        bs.item_menu.cursor_position--;
                        sound_items::snd_dialogue_generic.play();
                    }
                    else if (bs.item_menu.scroll_offset > 0)
                    {
                        bs.item_menu.scroll_offset--;
                        sound_items::snd_dialogue_generic.play();
                    }
                    bs.item_menu.refresh_display();
                }
                else if (keypad::down_pressed())
                {
                    int max_visible = min(3, bs.item_menu.total_items);
                    if (bs.item_menu.cursor_position < max_visible - 1)
                    {
                        bs.item_menu.cursor_position++;
                        sound_items::snd_dialogue_generic.play();
                    }
                    else if (bs.item_menu.scroll_offset + max_visible < bs.item_menu.total_items)
                    {
                        bs.item_menu.scroll_offset++;
                        sound_items::snd_dialogue_generic.play();
                    }
                    bs.item_menu.refresh_display();
                }
            }
            else
            {
                // Setup for character if needed
                if (!bs.char_img)
                {
                    // Find next character who needs to choose
                    while (bs.choosing_for < bs.party_size && !is_alive(bs.choosing_for, &bs))
                    {
                        bs.choosing_for++;
                    }

                    if (bs.choosing_for >= bs.party_size)
                    {
                        // All characters have chosen, execute actions
                        bs.choosing_for = 0;

                        // Check if anyone chose spare
                        if (count_action(&bs, ACTION_SPARE) > 0)
                        {
                            if (spare_convos.size() > 0)
                            {
                                conversation *spare_conv = spare_convos.front();
                                spare_convos.erase(spare_convos.begin());
                                init_dialogue(spare_conv, &bs);
                                bs.stage = stage_talking_then_attack;
                            }
                            else
                            {
                                bs.stage = stage_execute_attacks;
                            }
                        }
                        // Check if anyone used an item
                        else if (count_action(&bs, ACTION_ITEM) > 0 && bs.pending_item_conv)
                        {
                            init_dialogue(bs.pending_item_conv, &bs);
                            bs.pending_item_conv = nullptr;
                            bs.stage = stage_talking_then_attack;
                        }
                        else
                        {
                            bs.stage = stage_execute_attacks;
                        }

                        continue;
                    }

                    bs.current_actor = bs.choosing_for;
                    bs.char_img = sprite_items::battle_chars.create_sprite(-42, -42, bs.choosing_for);

                    // Setup labels
                    string<20> hp_str = "HP:";
                    hp_str.push_back('0' + global_data_ptr->hp[bs.choosing_for] / 10);
                    hp_str.push_back('0' + global_data_ptr->hp[bs.choosing_for] % 10);
                    hp_str.push_back('/');
                    hp_str.push_back('0' + global_data_ptr->max_hp[bs.choosing_for] / 10);
                    hp_str.push_back('0' + global_data_ptr->max_hp[bs.choosing_for] % 10);

                    bs.labels[0] = {get_name(bs.choosing_for), {0, -52}};
                    bs.labels[1] = {hp_str, {0, -36}};
                    bs.labels[0]->render();
                    bs.labels[1]->render();

                    // Setup main menu
                    bs.menu_index = 0;
                    bs.selected_menu = STATUS_BAR_NONE;

                    // Create 3 menu icons
                    int icon_indices[] = {0, 2, 3};
                    for (int i = 0; i < 3; ++i)
                    {
                        bs.battle_icons[i] = sprite_items::battle_icons.create_sprite(-22, -12 + (18 * i), icon_indices[i]);
                    }

                    const char *menu_labels[] = {"ATTACK", "ITEM", "SPARE"};
                    bs.labels[2] = {menu_labels[0], {0, -12}};
                    bs.labels[2]->render();
                }

                // Handle menu selection
                if (bs.selected_menu == STATUS_BAR_NONE)
                {
                    if (keypad::up_pressed())
                    {
                        bs.menu_index = (bs.menu_index + 2) % 3;
                        sound_items::snd_dialogue_generic.play();
                    }
                    else if (keypad::down_pressed())
                    {
                        bs.menu_index = (bs.menu_index + 1) % 3;
                        sound_items::snd_dialogue_generic.play();
                    }
                    else if (keypad::a_pressed())
                    {
                        sound_items::snd_alert.play();

                        switch (bs.menu_index)
                        {
                        case 0: // ATTACK
                        {
                            bs.character_actions[bs.choosing_for] = ACTION_ATTACK;

                            // Clean up and move to next character
                            bs.char_img.reset();
                            for (int i = 0; i < 5; ++i)
                            {
                                bs.labels[i].reset();
                            }
                            for (int i = 0; i < 3; ++i)
                            {
                                bs.battle_icons[i].reset();
                            }
                            bs.choosing_for++;
                            break;
                        }

                        case 1: // ITEM - Open item menu
                        {
                            // Hide main menu icons
                            for (int i = 0; i < 3; ++i)
                            {
                                bs.battle_icons[i].reset();
                            }
                            bs.labels[2].reset();

                            // Initialize and open item menu
                            bs.item_menu.init();
                            break;
                        }

                        case 2:
                        {
                            bs.character_actions[bs.choosing_for] = ACTION_SPARE;

                            // Clean up and move to next character
                            bs.char_img.reset();
                            for (int i = 0; i < 5; ++i)
                            {
                                bs.labels[i].reset();
                            }
                            for (int i = 0; i < 3; ++i)
                            {
                                bs.battle_icons[i].reset();
                            }
                            bs.choosing_for++;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                        }
                    }

                    if (!bs.item_menu.is_active())
                    {
                        const char *menu_labels[] = {"ATTACK", "ITEM", "SPARE"};
                        bs.labels[2].reset();
                        bs.labels[2] = {menu_labels[bs.menu_index], {0, -12 + (18 * bs.menu_index)}};
                        bs.labels[2]->render();
                    }
                }
            }
        }

        else if (bs.stage == stage_talking_then_attack)
        {
            // Clear any remaining UI labels before showing dialogue
            for (int i = 0; i < 5; ++i)
            {
                bs.labels[i].reset();
            }

            if (!is_dialogue_active(&bs))
            {
                bs.stage = stage_execute_attacks;
            }
            else
            {
                update_dialogue(&bs);

                if (keypad::a_pressed() && are_lines_complete(&bs))
                {
                    if (!advance_dialogue(&bs))
                    {
                        clear_dialogue(&bs);
                    }
                }
            }
        }

        else if (bs.stage == stage_execute_attacks)
        {
            for (int i = 0; i < 5; ++i)
            {
                bs.labels[i].reset();
            }

            // Count attackers and start attack stage if any
            bs.num_attackers = count_action(&bs, ACTION_ATTACK);

            if (bs.num_attackers > 0)
            {
                // Setup attack lanes for all attackers
                int attacker_idx = 0;
                for (int i = 0; i < bs.party_size; ++i)
                {
                    if (is_alive(i, &bs) && bs.character_actions[i] == ACTION_ATTACK)
                    {
                        // Position based on how many attackers there are
                        int y_pos = -32 + (attacker_idx * 32) - ((bs.num_attackers - 1) * 16);

                        bs.attack_headers[i] = sprite_items::battle_chars.create_sprite(-42, y_pos, i);
                        bs.attack_recvs[i] = sprite_items::battle_squares.create_sprite(-10, y_pos, 0);

                        // Don't create attack_units yet - they'll be created after launch delay
                        bs.attack_units[i].reset();

                        bs.attack_pressed[i] = false;
                        bs.attack_damages[i] = 0;
                        bs.attack_launched[i] = false;

                        // Set individual timing parameters based on character
                        switch (i)
                        {
                        case 0: // Jeremy - medium speed, launches first
                            bs.attack_speeds[i] = fixed(1.2);
                            bs.attack_launch_delays[i] = 0;
                            break;
                        case 1: // Ginger - faster, launches slightly later
                            bs.attack_speeds[i] = fixed(1.5);
                            bs.attack_launch_delays[i] = 20;
                            break;
                        case 2: // Sebellus - slower but precise
                            bs.attack_speeds[i] = fixed(0.9);
                            bs.attack_launch_delays[i] = 10;
                            break;
                        case 3: // Vista - variable speed
                            bs.attack_speeds[i] = 1.0 + (global_data_ptr->bn_random.get_fixed(0, fixed(0.4)));
                            bs.attack_launch_delays[i] = 30;
                            break;
                        default:
                            bs.attack_speeds[i] = fixed(1.2);
                            bs.attack_launch_delays[i] = 0;
                            break;
                        }

                        bs.attack_launch_timers[i] = 0;
                        attacker_idx++;
                    }
                }
                bs.stage = stage_attack;
            }
            else
            {
                // No one attacked, go to talking
                bs.stage = stage_talking;
            }
        }
        else if (bs.stage == stage_attack)
        {
            bool all_done = true;

            // First, handle launching attacks after their delays
            for (int i = 0; i < bs.party_size; ++i)
            {
                if (bs.attack_headers[i] && !bs.attack_launched[i])
                {
                    bs.attack_launch_timers[i]++;
                    if (bs.attack_launch_timers[i] >= bs.attack_launch_delays[i])
                    {
                        // Launch this attack!
                        int y_pos = bs.attack_headers[i]->y().integer();
                        bs.attack_units[i] = sprite_items::battle_squares.create_sprite(64, y_pos, 2);
                        bs.attack_launched[i] = true;

                        // Small visual effect on launch
                        bs.attack_units[i]->set_scale(1.2);
                    }
                }
            }

            // Check for button press and find closest unpressed attack unit
            if (keypad::a_pressed())
            {
                int closest_idx = -1;
                fixed closest_dist = 200; // Large initial value

                // Find the closest unpressed attack unit
                for (int i = 0; i < bs.party_size; ++i)
                {
                    if (bs.attack_units[i] && !bs.attack_pressed[i])
                    {
                        fixed dist = abs(bs.attack_units[i]->x() - bs.attack_recvs[i]->x());
                        if (dist < closest_dist)
                        {
                            closest_dist = dist;
                            closest_idx = i;
                        }
                    }
                }

                // Handle the closest attack
                if (closest_idx >= 0)
                {
                    bs.attack_pressed[closest_idx] = true;

                    // Check if it's in the hit zone (within 8 pixels of target)
                    if (closest_dist < 8)
                    {
                        // Good hit! Calculate damage based on accuracy
                        bs.character_states[closest_idx] = 3; // ATTACK animation
                        bs.character_tickers[closest_idx] = 0;

                        if (closest_dist < 2)
                        {
                            bs.attack_damages[closest_idx] = 5; // Perfect hit
                            sound_items::snd_alert.play();      // Use different sound if available
                        }
                        else if (closest_dist < 5)
                        {
                            bs.attack_damages[closest_idx] = 3; // Good hit
                            sound_items::snd_alert.play();
                        }
                        else
                        {
                            bs.attack_damages[closest_idx] = 1; // Grazing hit
                            sound_items::snd_dialogue_generic.play();
                        }

                        // Visual feedback - flash the unit
                        bs.attack_units[closest_idx]->set_tiles(
                            sprite_items::battle_squares.tiles_item(), 3); // Use different tile if available
                    }
                    else
                    {
                        // Pressed too early - this attack misses
                        bs.attack_damages[closest_idx] = 0;
                        sound_items::sfx_damage.play(); // Miss sound

                        // Remove the attack unit immediately
                        bs.attack_units[closest_idx].reset();
                    }
                }
            }

            // Update all active attack units
            for (int i = 0; i < bs.party_size; ++i)
            {
                if (bs.attack_units[i])
                {
                    // Reset scale after launch effect
                    if (bs.attack_units[i]->horizontal_scale() > 1.0)
                    {
                        bs.attack_units[i]->set_scale(bs.attack_units[i]->horizontal_scale() - 0.05);
                    }

                    // Move the attack unit at its individual speed
                    bs.attack_units[i]->set_x(bs.attack_units[i]->x() - bs.attack_speeds[i]);

                    // Check if this unit is still active
                    if (bs.attack_units[i]->x() > -42 && !bs.attack_pressed[i])
                    {
                        all_done = false;
                    }

                    // Auto-miss if it goes past the target
                    if (bs.attack_units[i]->x() <= -42 && !bs.attack_pressed[i])
                    {
                        bs.attack_pressed[i] = true;
                        bs.attack_damages[i] = 0; // Missed
                        bs.attack_units[i].reset();
                    }

                    // Clean up pressed units that are hit successes
                    if (bs.attack_pressed[i] && bs.attack_damages[i] > 0)
                    {
                        // Immediately remove successful hits (they already played their animation)
                        if (bs.attack_units[i])
                        {
                            bs.attack_units[i].reset();
                        }
                    }
                }
                else if (bs.attack_headers[i] && !bs.attack_pressed[i] && bs.attack_launched[i])
                {
                    // This attack was launched but unit is gone (early press miss)
                    // Still not done if we're waiting for other attacks
                    all_done = false;
                }
                else if (bs.attack_headers[i] && !bs.attack_launched[i])
                {
                    // Still waiting to launch
                    all_done = false;
                }
            }

            // When all attack lanes are done
            if (all_done)
            {
                // Apply all damage
                int total_damage = 0;
                for (int i = 0; i < bs.party_size; ++i)
                {
                    if (bs.attack_damages[i] > 0)
                    {
                        total_damage += bs.attack_damages[i];
                    }
                }

                if (total_damage > 0)
                {
                    global_data_ptr->enemy_hp[0] -= total_damage;
                    text::add_toast(-total_damage, {96, -36});
                }
                else
                {
                    // Show miss feedback with sound
                    sound_items::sfx_damage.play();
                }

                // Clean up all attack UI
                for (int i = 0; i < MAX_PARTY_SIZE; ++i)
                {
                    bs.attack_headers[i].reset();
                    bs.attack_recvs[i].reset();
                    bs.attack_units[i].reset();
                    bs.attack_damages[i] = 0;
                    bs.attack_pressed[i] = false;
                    bs.attack_launched[i] = false;
                    bs.attack_launch_timers[i] = 0;
                }

                bs.stage = stage_talking;
            }
        }

        else if (bs.stage == stage_item_dialogue)
        {
            if (!is_dialogue_active(&bs))
            {
                // Dialogue finished, remove item if needed
                if (bs.used_item_index >= 0 && bs.used_item_index < ITEMS_SIZE)
                {
                    if (ITEM_DROP[bs.used_item_index])
                    {
                        global_data_ptr->items[bs.used_item_index] = false;
                    }
                }

                // Record that this character used an item
                bs.character_actions[bs.choosing_for] = ACTION_ITEM;

                // Move to next character
                bs.choosing_for++;

                // Return to status stage to continue character selection
                bs.stage = stage_status;
            }
            else
            {
                update_dialogue(&bs);

                if (keypad::a_pressed() && are_lines_complete(&bs))
                {
                    if (!advance_dialogue(&bs))
                    {
                        clear_dialogue(&bs);
                    }
                }
            }
        }

        text::update_toasts();
        core::update();
    }
}