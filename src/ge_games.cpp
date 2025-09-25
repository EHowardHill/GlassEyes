// ge_battle.cpp

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "bn_random.h"
#include "bn_blending.h"

#include "bn_regular_bg_items_bg_battle_grid.h"
#include "bn_regular_bg_items_bg_dialogue_box.h"
#include "bn_sprite_items_hearts.h"
#include "bn_sprite_items_battle_chars.h"
#include "bn_sprite_items_battle_squares.h"

#include "bn_sprite_items_dartboard.h"
#include "bn_sprite_items_darts.h"

#include "ge_text.h"
#include "ge_character_manager.h"
#include "ge_dialogue.h"
#include "ge_games.h"

using namespace bn;

// Dialogue functions
static void init_dialogue(conversation *conv, game_state *gs)
{
    if (!gs->bg_ptr)
    {
        gs->bg_ptr = regular_bg_items::bg_dialogue_box.create_bg(0, 0);
    }

    gs->active_conv = conv;
    gs->dlg_index = 0;
    gs->dlg_size = 0;
    gs->dlg_ticker = 0;

    // Count lines
    for (int i = 0; i < 64 && (*conv)[i].action != ACT_END; ++i)
    {
        gs->dlg_size++;
    }

    if (gs->dlg_size > 0)
    {
        const auto &line = (*conv)[0];
        if (line.portrait)
        {
            gs->portrait = line.portrait->create_sprite(-84, 56, line.emotion);
        }

        for (int i = 0; i < 3; ++i)
        {
            gs->dlg_lines[i].init(line.raw_text[i]);
            gs->dlg_lines[i].size = line.size;
        }
    }
}

static void update_dialogue(game_state *gs)
{
    if (!gs->active_conv || gs->dlg_index >= gs->dlg_size)
        return;

    const auto &line = (*gs->active_conv)[gs->dlg_index];

    // Update portrait animation
    if (gs->portrait && line.portrait)
    {
        gs->portrait->set_tiles(line.portrait->tiles_item(),
                                (line.emotion * 2) + (gs->dlg_ticker % 12 < 6));
    }

    // Update text
    if (gs->dlg_ticker % 3 == 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (!gs->dlg_lines[i].is_ended())
            {
                gs->dlg_lines[i].update(line.portrait, false);
                break;
            }
        }
    }

    // Update letter effects
    for (int i = 0; i < 3; ++i)
    {
        for (auto &letter : gs->dlg_lines[i].letters)
        {
            letter.update(line.shake, line.size);
        }
    }

    gs->dlg_ticker++;
}

static bool advance_dialogue(game_state *gs)
{
    if (gs->dlg_index < gs->dlg_size - 1)
    {
        gs->dlg_index++;
        gs->dlg_ticker = 0;

        const auto &line = (*gs->active_conv)[gs->dlg_index];

        if (line.portrait)
        {
            gs->portrait = line.portrait->create_sprite(-84, 56, line.emotion);
        }
        else
        {
            gs->portrait.reset();
        }

        for (int i = 0; i < 3; ++i)
        {
            gs->dlg_lines[i].init(line.raw_text[i]);
            gs->dlg_lines[i].size = line.size;
        }
        return true;
    }
    return false;
}

static void clear_dialogue(game_state *gs)
{
    gs->bg_ptr.reset();
    gs->portrait.reset();
    gs->active_conv = nullptr;
    gs->dlg_ticker = 0;
    for (int i = 0; i < 3; ++i)
    {
        gs->dlg_lines[i].letters.clear();
        gs->dlg_lines[i].index = 0;
        gs->dlg_lines[i].size = 0;
    }
}

static bool is_dialogue_active(game_state *gs)
{
    return gs->active_conv && gs->dlg_index < gs->dlg_size;
}

static bool are_lines_complete(game_state *gs)
{
    return gs->dlg_lines[0].is_ended() &&
           gs->dlg_lines[1].is_ended() &&
           gs->dlg_lines[2].is_ended();
}

static int get_character_y_position(int index)
{
    // Stack characters vertically, with first character highest
    return 8 - (index * 32);
}

static void update_character_animation(int char_index, game_state &gs)
{
    if (!gs.character_sprites[char_index])
        return;

    auto &sprite = gs.character_sprites[char_index];
    int &state = gs.character_states[char_index];
    int &ticker = gs.character_tickers[char_index];

    const sprite_item *spr_item = nullptr;
    spr_item = &sprite_items::spr_jeremy_game_dart_01;

    int y_offset = get_character_y_position(char_index) + gs.y_delta;

    if (state == 3) // Throwing state
    {
        // Animate throwing: frame 1 for first 8 frames, then stay on frame 2
        if (ticker < 2)
        {
            sprite->set_tiles(spr_item->tiles_item(), 1);
        }
        else
        {
            sprite->set_tiles(spr_item->tiles_item(), 2);
        }

        ticker++;

        // Reset state after throw animation completes (optional)
        // You might want to reset when dart reaches target instead
        if (ticker > 60) // Adjust timing as needed
        {
            state = 0; // Back to idle
            ticker = 0;
        }
    }
    else
    {
        // Default idle animation
        sprite->set_tiles(spr_item->tiles_item(), 0);
        state = 0;
        ticker = 0;
    }

    sprite->set_position(-96, y_offset);
}

static void init_dart_game(game_state &gs)
{
    gs.darts = dart_game();   // Reset dart game state
    gs.darts.max_rounds = 12; // Explicitly set to 12 rounds

    // Create dartboard
    gs.darts.dartboard = sprite_items::dartboard.create_sprite(0, -16);
    gs.darts.dartboard->set_z_order(1);
    gs.darts.dartboard->set_blending_enabled(true);

    bn::blending::set_transparency_alpha(0.4);

    // Create crosshair (using a small icon or custom sprite)
    gs.darts.crosshair = sprite_items::hearts.create_sprite(0, -16, 1);
    gs.darts.crosshair->set_z_order(-1);

    // Create power meter sprites
    for (int i = 0; i < 5; ++i)
    {
        gs.darts.power_meter[i] = sprite_items::battle_squares.create_sprite(
            -60 + (i * 8), 32, 0);
        gs.darts.power_meter[i]->set_visible(false);
    }

    // Initialize score text displays
    gs.darts.player_score_text = text("You: 0", {-100, 70});
    gs.darts.enemy_score_text = text("Foe: 0", {60, 70});
    gs.darts.round_text = text("Round 1/12", {-32, -70}); // Updated to show 12

    gs.darts.state = DART_INTRO;
    gs.darts.state_timer = 0;
}

static int calculate_dart_score(fixed x, fixed y)
{
    // Calculate distance from dartboard center (dartboard is at 0, -16)
    // So we need to offset y by +16 to get distance from visual center
    fixed center_y = y + 16; // Adjust for dartboard position
    fixed dist = bn::sqrt((x * x) + (center_y * center_y));

    // Score based on distance (dartboard has ~32 pixel radius)
    if (dist < 4)
        return 50; // Bullseye!
    else if (dist < 8)
        return 25; // Inner bull
    else if (dist < 16)
        return 20; // Triple zone
    else if (dist < 24)
        return 10; // Double zone
    else if (dist < 32)
        return 5; // Single zone
    else
        return 0; // Miss
}

static void update_dart_aiming(game_state &gs)
{
    auto &d = gs.darts;
    d.wobble_timer++;

    // MUCH slower - one full pattern every ~12 seconds (720 frames)
    fixed t = fixed(d.wobble_timer % 12800) / 12800;

    // Select pattern based on round
    int pattern = d.current_round % 3;
    fixed base_angle = t * 360; // Full rotation over the cycle

    switch (pattern)
    {

    case 1: // Elliptical pattern - wider horizontally
        d.aim_x = bn::cos(base_angle) * 30;
        d.aim_y = -16 + bn::sin(base_angle) * 20;
        // Add wobble
        d.aim_x += bn::cos(base_angle * 3) * 5;
        d.aim_y += bn::sin(base_angle * 3) * 5;
        break;

    default: // Spiraling pattern
        fixed radius = 15 + (bn::sin(base_angle * 2) * 15);
        d.aim_x = bn::cos(base_angle) * radius;
        d.aim_y = -16 + bn::sin(base_angle) * radius;
        break;
    }

    // Very occasional small drift
    if (d.wobble_timer % 60 == 0)
    {
        d.random_jitter_x = gs.rng.get_fixed(-2, 2);
        d.random_jitter_y = gs.rng.get_fixed(-2, 2);
    }

    // Fade jitter
    d.random_jitter_x *= 0.98;
    d.random_jitter_y *= 0.98;

    // Update crosshair position
    if (d.crosshair)
    {
        d.wobbled_aim_x = d.aim_x + d.random_jitter_x;
        d.wobbled_aim_y = d.aim_y + d.random_jitter_y;
        d.crosshair->set_position(d.wobbled_aim_x, d.wobbled_aim_y);
    }

    // Press A to lock aim
    if (keypad::a_pressed())
    {
        d.state = DART_POWER;
        d.power = 0;
        d.power_direction = 2;
        sound_items::snd_select.play();

        for (auto &meter : d.power_meter)
        {
            if (meter)
                meter->set_visible(true);
        }
    }
}

static void update_dart_power(game_state &gs)
{
    auto &d = gs.darts;

    // Make power oscillation less predictable
    int base_direction = d.power_direction.integer();

    // Occasionally change direction unexpectedly
    if (gs.rng.get_int(100) < 3) // 3% chance each frame
    {
        d.power_direction = -d.power_direction;
    }

    // Variable power increment for less predictable timing
    int power_increment = base_direction + gs.rng.get_int(-1, 1);
    d.power += power_increment;

    if (d.power >= d.max_power || d.power <= 0)
    {
        d.power = bn::clamp(d.power, fixed(0), d.max_power);
        d.power_direction = -d.power_direction;
    }

    // Update power meter visual
    int filled_segments = (d.power / 20).integer();
    for (int i = 0; i < 5; ++i)
    {
        if (d.power_meter[i])
        {
            d.power_meter[i]->set_tiles(
                sprite_items::battle_squares.tiles_item(),
                i < filled_segments ? 1 : 0);
        }
    }

    // Press A to throw with current power
    if (keypad::a_pressed())
    {
        d.state = DART_THROWING;
        d.throw_timer = 0;

        // Trigger player throwing animation
        gs.character_states[0] = 3;  // Set first character to throwing state
        gs.character_tickers[0] = 0; // Reset animation ticker

        // Power ranges from 0 to 100 (max_power)
        // Perfect power is 100, worst is 0
        // Calculate accuracy: 1.0 at max power, 0.0 at min power
        fixed accuracy = d.power / d.max_power;

        // Invert to get error amount: 0 at max power, 1.0 at min power
        fixed error_multiplier = 1.0 - accuracy;

        // Scale error up to 48 pixels as requested
        fixed max_error = 48;
        fixed actual_error = max_error * error_multiplier;

        // Apply random error based on power level
        if (actual_error != 0)
        {
            d.dart_target_x = d.wobbled_aim_x + gs.rng.get_fixed(-actual_error, actual_error);
            d.dart_target_y = d.wobbled_aim_y + gs.rng.get_fixed(-actual_error, actual_error);
        }

        // Create dart sprite at starting position (always from left for player)
        d.dart = sprite_items::darts.create_sprite(-80, 60, 0);
        d.dart_start_x = -80;
        d.dart_start_y = 60;

        // Hide power meter and crosshair
        for (auto &meter : d.power_meter)
        {
            if (meter)
                meter->set_visible(false);
        }
        if (d.crosshair)
            d.crosshair->set_visible(false);

        sound_items::snd_cnaut.play();
    }
}

static void update_dart_throwing(game_state &gs)
{
    auto &d = gs.darts;

    d.throw_timer++;

    // Animate dart flying to target
    fixed t = bn::min(fixed(d.throw_timer) / 30, fixed(1));

    // Use easing for smooth motion
    fixed ease_t = t * t * (3 - 2 * t);

    // Calculate current position using stored start position
    d.dart_x = (d.dart_start_x * (1 - ease_t)) + (d.dart_target_x * ease_t);
    d.dart_y = (d.dart_start_y * (1 - ease_t)) + (d.dart_target_y * ease_t);

    // Add rotation to dart during flight
    if (d.dart)
    {
        d.dart->set_position(d.dart_x, d.dart_y);
        d.dart->set_rotation_angle((d.throw_timer * 12) % 360);
    }

    // When dart reaches target
    if (d.throw_timer >= 30)
    {
        d.state = DART_RESULT;
        d.result_timer = 0;

        // Reset throwing animations if still active
        if (gs.character_states[0] == 3)
        {
            gs.character_states[0] = 0;
            gs.character_tickers[0] = 0;
        }
        if (gs.enemy_state == 3)
        {
            gs.enemy_state = 0;
            gs.enemy_ticker = 0;
        }

        // Calculate and store score using the final dart position
        int score = calculate_dart_score(d.dart_target_x, d.dart_target_y);

        if (d.player_turn)
        {
            d.round_scores[d.current_round] = score;
            d.player_score += score;

            // Play appropriate sound
            if (score >= 25)
                sound_items::snd_hit.play();
            else if (score > 0)
                sound_items::snd_hit.play();
            else
                sound_items::snd_miss.play();
        }
        else
        {
            d.round_scores[3 + d.current_round] = score;
            d.enemy_score += score;
        }

        // Stop dart rotation
        if (d.dart)
            d.dart->set_rotation_angle(0);

        // Show score text
        string<32> score_text;
        if (score == 50)
            score_text = "BULLSEYE!";
        else if (score > 0)
            score_text = "+" + to_string<16>(score);
        else
            score_text = "MISS!";

        text::add_toast(score_text, {0, 32});
    }
}

static void update_dart_result(game_state &gs)
{
    auto &d = gs.darts;

    d.result_timer++;

    // Wait for result display
    if (d.result_timer >= 60)
    {
        // Clean up dart
        d.dart.reset();

        if (d.player_turn)
        {
            // Switch to enemy turn
            d.player_turn = false;
            d.state = DART_ENEMY_TURN;
            d.state_timer = 0;
        }
        else
        {
            // End of round
            d.current_round++;

            if (d.current_round >= d.max_rounds)
            {
                // Game over - Winner takes all!
                d.state = DART_GAME_OVER;
                d.state_timer = 0;

                // Determine winner and apply battle effects
                if (d.player_score > d.enemy_score)
                {
                    // Player wins - enemy HP to 0
                    gs.result = G_WIN;                // Changed to G_WIN for immediate victory
                    global_data_ptr->enemy_hp[0] = 0; // Set enemy HP to 0

                    // Trigger enemy hurt animation
                    gs.enemy_state = 2;
                    gs.enemy_ticker = 0;

                    text::add_toast("YOU WIN!", {0, 0});
                }
                else if (d.enemy_score > d.player_score)
                {
                    // Enemy wins - player HP to 0
                    gs.result = G_LOSE;         // Assuming G_LOSE exists, otherwise use appropriate value
                    global_data_ptr->hp[0] = 0; // Set player HP to 0

                    // Trigger player hurt animation
                    gs.character_states[0] = 2;
                    gs.character_tickers[0] = 0;

                    text::add_toast("YOU LOSE!", {0, 0});
                }
                else
                {
                    // Draw - no one loses HP
                    gs.result = G_FIRST;
                    text::add_toast("DRAW!", {0, 0});
                }
            }
            else
            {
                // Next round, back to player
                d.player_turn = true;
                d.state = DART_AIMING;
                d.aim_x = 0;
                d.aim_y = -16;
                if (d.crosshair)
                    d.crosshair->set_visible(true);
            }
        }
    }
}

static void update_enemy_dart_turn(game_state &gs)
{
    auto &d = gs.darts;

    d.state_timer++;

    // Simulate enemy thinking
    if (d.state_timer == 30)
    {
        // Random position within pixel radius of the dartboard center
        fixed target_x = gs.rng.get_fixed(-24, 24);
        fixed target_y = -16 + gs.rng.get_fixed(-24, 24);

        // STORE THE TARGET POSITION for later use
        d.dart_target_x = target_x;
        d.dart_target_y = target_y;

        // Show enemy's crosshair briefly
        if (d.crosshair)
        {
            d.crosshair->set_visible(true);
            d.crosshair->set_position(target_x, target_y);
        }
    }
    else if (d.state_timer == 60)
    {
        // Enemy throws - USE THE STORED TARGET from aiming phase
        d.state = DART_THROWING;
        d.throw_timer = 0;

        // Don't recalculate! Use the stored d.dart_target_x and d.dart_target_y
        // They were already set at state_timer == 30

        // Optional: Add some inaccuracy based on enemy skill
        fixed accuracy_error = 10 * (1.0 - d.enemy_accuracy); // Use the enemy_accuracy field
        if (accuracy_error != 0)
        {
            d.dart_target_x += gs.rng.get_fixed(-accuracy_error, accuracy_error);
            d.dart_target_y += gs.rng.get_fixed(-accuracy_error, accuracy_error);
        }

        // Create dart sprite at starting position (from RIGHT side for enemy)
        d.dart = sprite_items::darts.create_sprite(80, 60, 0);
        d.dart->set_horizontal_flip(true);
        d.dart_start_x = 80; // Enemy starts from right
        d.dart_start_y = 60;

        if (d.crosshair)
            d.crosshair->set_visible(false);

        // Trigger enemy attack animation
        gs.enemy_state = 3;
        gs.enemy_ticker = 0;

        sound_items::snd_cnaut.play();
    }
}

static void update_dart_game(game_state &gs)
{
    auto &d = gs.darts;

    switch (d.state)
    {
    case DART_INTRO:
        d.state_timer++;
        if (d.state_timer >= 30)
        {
            d.state = DART_AIMING;
        }
        break;

    case DART_AIMING:
        update_dart_aiming(gs);
        break;

    case DART_POWER:
        update_dart_power(gs);
        break;

    case DART_THROWING:
        update_dart_throwing(gs);
        break;

    case DART_RESULT:
        update_dart_result(gs);
        break;

    case DART_ENEMY_TURN:
        update_enemy_dart_turn(gs);
        break;

    case DART_GAME_OVER:
        d.state_timer++;
        if (d.state_timer == 30)
        {
            // Clean up dart game sprites
            d.dartboard.reset();
            d.dart.reset();
            d.crosshair.reset();
            for (auto &meter : d.power_meter)
            {
                meter.reset();
            }

            // Clear text displays
            d.player_score_text.letters.clear();
            d.enemy_score_text.letters.clear();
            d.round_text.letters.clear();

            // Return to dialogue/battle
            gs.stage = G_TALKING;
        }
        break;

    default:
    {
        break;
    }
    }

    // Display scores
    if (d.state != DART_GAME_OVER && d.state != DART_INTRO)
    {
        // Update score text with larger buffer sizes
        string<32> player_str = "You: " + to_string<16>(d.player_score);
        string<32> enemy_str = "Foe: " + to_string<16>(d.enemy_score);
        string<48> round_str = "Round " + to_string<16>(d.current_round + 1) + "/" + to_string<16>(d.max_rounds); // Increased buffer size

        d.player_score_text.init(player_str);
        d.enemy_score_text.init(enemy_str);
        d.round_text.init(round_str);

        // Render the text
        d.player_score_text.render();
        d.enemy_score_text.render();
        d.round_text.render();
    }
}

// Main battle function
int game_map()
{
    music::stop();
    music_items::boss.play();
    sound_items::snd_fight_start.play();

    auto bg_grid = regular_bg_items::bg_battle_grid.create_bg(0, 0);

    // Create and reset battle state
    game_state gs;

    // Setup conversations based on foe
    vector<conversation *, 3> convos[G_SIZE];

    switch (global_data_ptr->foe)
    {
    default:
        gs.enemy_sprite_item = &sprite_items::spr_sneaker_game_dart_01;
        global_data_ptr->enemy_max_hp[0] = 12;
        global_data_ptr->enemy_hp[0] = 12;

        // Just Jeremy for this battle
        gs.party_size = 1;
        gs.character_sprites[0] = sprite_items::spr_jeremy_game_dart_01.create_sprite(-96, get_character_y_position(0), 0);
        gs.character_sprites[0]->set_z_order(0);

        convos[G_FIRST].push_back(&dart_01);
        convos[G_UP].push_back(&dart_02);
        convos[G_UP].push_back(&dart_02);
        convos[G_WIN].push_back(&dart_04);
        break;
    }

    for (int i = 0; i < gs.party_size; ++i)
    {
        if (gs.character_sprites[i].has_value())
            gs.character_sprites[i].value().set_z_order(i);
    }

    gs.enemy_sprite = gs.enemy_sprite_item->create_sprite(96, 16, 0);

    // Main game loop
    while (true)
    {
        bg_grid.set_position(bg_grid.x() - 1, bg_grid.y() - 1);

        // Update all character animations
        for (int i = 0; i < gs.party_size; ++i)
        {
            update_character_animation(i, gs);
        }

        // Normal enemy animation for other enemies
        switch (gs.enemy_state)
        {
        case 3: // Enemy throwing state
        {
            // Animate enemy throwing: frame 1 for first 8 frames, then stay on frame 2
            if (gs.enemy_ticker < 8)
            {
                gs.enemy_sprite->set_tiles(gs.enemy_sprite_item->tiles_item(), 1);
            }
            else
            {
                gs.enemy_sprite->set_tiles(gs.enemy_sprite_item->tiles_item(), 2);
            }

            gs.enemy_ticker++;

            // Reset state after throw animation completes
            if (gs.enemy_ticker > 60) // Adjust timing as needed
            {
                gs.enemy_state = 0; // Back to idle
                gs.enemy_ticker = 0;
                gs.enemy_sprite->set_tiles(gs.enemy_sprite_item->tiles_item(), 0);
            }
        }
        break;
        default:
            if (gs.enemy_state == 0)
            {
                gs.enemy_sprite->set_tiles(gs.enemy_sprite_item->tiles_item(), 0);
            }
            break;
            break;
        }

        if (gs.enemy_sprite.has_value())
        {
            gs.enemy_sprite.value().set_position(96, 16 + gs.y_delta);
        }

        // Y offset for dialogue
        gs.y_delta += is_dialogue_active(&gs) ? (gs.y_delta > -32 ? -4 : 0) : (gs.y_delta < 0 ? 4 : 0);

        // Stage: Talking
        if (gs.stage == G_TALKING)
        {
            // Normal battle dialogue flow
            if (global_data_ptr->enemy_hp[0] <= 0)
            {
                gs.result = G_WIN;
            }

            if (!is_dialogue_active(&gs))
            {
                if (gs.result < G_SIZE && convos[gs.result].size() > 0)
                {
                    conversation *c = convos[gs.result].front();
                    convos[gs.result].erase(convos[gs.result].begin());
                    init_dialogue(c, &gs);
                }
                else
                {
                    gs.stage = G_PLAYING;
                }
            }
            else
            {
                update_dialogue(&gs);

                if (keypad::a_pressed() && are_lines_complete(&gs))
                {
                    if (!advance_dialogue(&gs))
                    {
                        clear_dialogue(&gs);
                    }
                }
            }
        }
        else if (gs.stage == G_PLAYING)
        {
            // Check if we should start dart game
            if (!gs.darts.dartboard)
            {
                init_dart_game(gs);
            }

            // Update dart game
            update_dart_game(gs);
        }

        text::update_toasts();
        core::update();
    }
}