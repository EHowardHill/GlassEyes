// ge_minigame_bullet_dodge.cpp

#include "ge_minigame_bullet_dodge.h"
#include "ge_battle.h"
#include "bn_regular_bg_items_bg_battle_box.h"
#include "bn_sprite_items_hearts.h"

#include "bn_keypad.h"      // For keypad::right_held(), etc.
#include "bn_math.h"        // For abs(), max(), min()
#include "bn_sound_items.h" // For sound_items::sfx_damage
#include "ge_text.h"        // For text::add_toast()

void bullet_dodge_init(minigame_state *mg)
{
    // Allocate custom data
    mg->custom_data = new bullet_dodge_data();
    auto *data = static_cast<bullet_dodge_data *>(mg->custom_data);

    // Setup from battle state
    data->moveset_index = mg->bs->selected_moveset;
    data->speed = mg->bs->speed;

    // Create background (using shared resources)
    mg->backgrounds[0] = regular_bg_items::bg_battle_box.create_bg(0, 0);

    // Create heart sprite (sprites[0] = heart)
    mg->sprites[0] = sprite_items::hearts.create_sprite(0, 0, 1);
    mg->positions[0] = {0, 0}; // Heart position

    // Spawn initial bullets
    bullet::populate(&data->bullets, data->moveset_index, data->speed);
}

void bullet_dodge_update(minigame_state *mg)
{
    auto *data = static_cast<bullet_dodge_data *>(mg->custom_data);

    // Check if all party members are dead or enemy is defeated
    if (next_living(-1, mg->bs) < 0 || global_data_ptr->enemy_hp[0] <= 0)
    {
        mg->result.complete = true;
        return;
    }

    // Update heart position with input
    mg->positions[0].x += keypad::right_held() - keypad::left_held();
    mg->positions[0].y += keypad::down_held() - keypad::up_held();

    // Clamp positions
    mg->positions[0].x = max(-48, min(48, mg->positions[0].x));
    mg->positions[0].y = max(-48, min(48, mg->positions[0].y));

    mg->sprites[0]->set_position(mg->positions[0].x, mg->positions[0].y);

    // Update bullets and check collisions
    for (auto &b : data->bullets)
    {
        b.update();

        if (b.item && b.item->visible())
        {
            int dx = bn::abs(mg->positions[0].x - b.item->x()).integer();
            int dy = bn::abs(mg->positions[0].y - b.item->y()).integer();

            if (dx + dy < 12)
            {
                // Hit detected!
                int who = random_living(mg->bs);
                if (who >= 0)
                {
                    mg->result.damage_dealt = 2;
                    mg->result.affected_character = who;
                    global_data_ptr->hp[who] -= 2;

                    // Visual feedback
                    text::add_toast(-2, vector_2(-96, -44 + (who * 8)));
                    sound_items::sfx_damage.play();

                    // Trigger hurt animation
                    mg->bs->character_states[who] = 2;
                    mg->bs->character_tickers[who] = 0;
                }
                b.item->set_visible(false);
            }
        }
    }

    // Check timeout
    if (mg->ticker > 400)
    {
        mg->result.complete = true;
    }
}

void bullet_dodge_cleanup(minigame_state *mg)
{
    if (mg->custom_data)
    {
        auto *data = static_cast<bullet_dodge_data *>(mg->custom_data);
        data->bullets.clear();
        delete data;
        mg->custom_data = nullptr;
    }
}