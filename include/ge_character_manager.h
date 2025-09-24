// ge_character_manager.h

#ifndef GE_CHARACTER_MANAGER_H
#define GE_CHARACTER_MANAGER_H

#include "bn_list.h"
#include "bn_unique_ptr.h"
#include "bn_optional.h"
#include "ge_sprites.h"
#include "ge_text.h"
#include "main.h"

// Forward declarations to break circular dependencies
struct character;
struct map_manager;
struct dialogue_box;
struct items_box;

struct character_manager
{
    list<unique_ptr<character>, 32> characters;
    character *player_ptr;
    optional<dialogue_box> db;
    optional<items_box> ib;
    int status = CONTINUE;

    character_manager();

    character *add_character(int index, vector_2 position, int id);
    bool remove_character(character *ch);
    void clear_npcs();
    character *get_player() { return player_ptr; }
    character *find_at_position(vector_2 pos, int tolerance = 32);
    character *find_by_index(int index);
    character *find_by_id(int id);
    void update(map_manager *current_map);
    void alert();
    int size() const { return characters.size(); }

    bool music_fadeout = false;

    template <typename Func>
    void for_each(Func func)
    {
        for (auto &ch : characters)
        {
            if (ch)
            {
                func(ch.get());
            }
        }
    }
};

#endif // GE_CHARACTER_MANAGER_H