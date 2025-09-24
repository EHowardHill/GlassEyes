// ge_maps.h

#ifndef GE_MAPS_H
#define GE_MAPS_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_sound_item.h"
#include "bn_array.h"
#include "bn_optional.h"

#include "ge_structs.h"
#include "ge_character_manager.h"

// Using bn namespace types
using bn::array;
using bn::regular_bg_item;
using bn::sound_item;

struct map
{
  vector_2 size;
  vector_2 raw_size;
  array<int, 2048> metadata;
  array<int, 2048> collisions;
  array<int, 2048> actions;
  array<int, 2048> characters;
  const regular_bg_item *bg_item_ptr;

  // Constexpr constructor for compile-time initialization
  constexpr map(vector_2 size_,
                vector_2 raw_size_,
                const array<int, 2048> &metadata_,
                const array<int, 2048> &collisions_,
                const array<int, 2048> &actions_,
                const array<int, 2048> &characters_,
                const regular_bg_item *bg_item_ptr_)
      : size(size_),
        raw_size(raw_size_),
        metadata(metadata_),
        collisions(collisions_),
        actions(actions_),
        characters(characters_),
        bg_item_ptr(bg_item_ptr_) {}
};

struct map_manager
{
  optional<regular_bg_ptr> bg_ptr;
  optional<regular_bg_ptr> collider_ptr;
  const map *current_map;

  map_manager(const map *current_map_);

  void update();
  int collision(vector_2 location, character_manager *ch_man);
  bool check_box_collision(bound box, character_manager *ch_man);
  int action(vector_2 location); // Added this declaration
};

#endif