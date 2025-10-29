/*

switch (global_data_ptr->foe)
{
case FOE_VISKERS_01:
    enemy_sprite_item = &sprite_items::visker_battle;
    global_data_ptr->enemy_max_hp[0] = 12;
    global_data_ptr->enemy_hp[0] = 12;
    moveset = 3;
    speed = 100;

    // Just Jeremy for this battle
    party_size = 1;
    character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
    character_sprites[0]->set_z_order(0);

    convos[RESULT_FIRST].push_back(&garbage_fight_01);
    convos[RESULT_UP].push_back(&garbage_fight_02);
    convos[RESULT_UP].push_back(&garbage_fight_03);
    convos[RESULT_LAST_WIN].push_back(&garbage_fight_04);

    spare_convos.push_back(&garbage_spare);
    spare_convos.push_back(&garbage_fight_02);
    spare_convos.push_back(&garbage_fight_03);
    break;

case FOE_VISKERS_02:
    enemy_sprite_item = &sprite_items::visker_battle;
    global_data_ptr->enemy_max_hp[0] = 99;
    global_data_ptr->enemy_hp[0] = 99;
    moveset = BULLET_SIZE;
    speed = 300;

    party_size = 1;
    character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);

    convos[RESULT_FIRST].push_back(&garbage_fight_05);
    spare_convos.push_back(&garbage_spare);
    break;

case FOE_CROKE_01:
    enemy_sprite_item = &sprite_items::croke_battle;
    global_data_ptr->enemy_max_hp[0] = 0;
    global_data_ptr->enemy_hp[0] = 0;

    party_size = 2;
    character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
    character_sprites[1] = sprite_items::ginger_battle.create_sprite(-96, get_character_y_position(1), 0);

    // For Croke, we don't use the normal convos array
    // We'll handle his sequence specially
    croke_conv_index = 0;
    croke_anim_frame = 0;
    break;

case FOE_TEST:
    enemy_sprite_item = &sprite_items::visker_battle;
    global_data_ptr->enemy_max_hp[0] = 99;
    global_data_ptr->enemy_hp[0] = 99;
    moveset = BULLET_SIZE;
    speed = 5;

    party_size = 2;
    character_sprites[0] = sprite_items::jeremy_battle.create_sprite(-96, get_character_y_position(0), 0);
    character_sprites[1] = sprite_items::ginger_battle.create_sprite(-96, get_character_y_position(1), 0);

    convos[RESULT_FIRST].push_back(&garbage_fight_05);
    break;

default:
    break;
}

*/