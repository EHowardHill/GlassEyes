// ge_dialogue.cpp
// THIS IS AN AUTO-GENERATED FILE. DO NOT EDIT.

#include "ge_dialogue.h"

#include "bn_sprite_items_db_ch_vista.h"
#include "bn_sprite_items_db_ch_visker.h"
#include "bn_sprite_items_db_ch_visker_wife.h"
#include "bn_sprite_items_db_ch_ginger.h"
#include "bn_sprite_items_db_ch_croke.h"
#include "bn_sprite_items_db_ch_temmie.h"
#include "bn_sprite_items_db_ch_deadguy.h"
#include "bn_sprite_items_db_ch_grandma.h"
#include "bn_sprite_items_db_ch_wormguy.h"
#include "bn_sprite_items_db_ch_courier.h"
#include "bn_sprite_items_db_ch_primary.h"
#include "bn_sprite_items_db_ch_doll.h"
#include "bn_sprite_items_db_ch_greyfriar.h"
#include "bn_sprite_items_db_ch_jelly.h"
#include "bn_sprite_items_db_ch_horsey.h"
#include "bn_sprite_items_db_ch_glompy.h"
#include "bn_sprite_items_db_ch_sneaker.h"
#include "bn_sprite_items_db_ch_tollman.h"
#include "bn_sprite_items_db_ch_robin.h"

const conversation &scruffys_05_alt_01 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "Too afraid.", "I see.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_courier_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Do you know the", "way to Canterbury?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "..of course I do,", "do you not know", "who I am?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "No..?", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "Every local knows", "that this badge", "means \"courier\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "I wouldn't expect", "a princess to know", "that, though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I don't know what", "you're talking", "about.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "Oh.. Right.", "Of course.", "It's a secret.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "Now, I am", "fascinated by the..", "human here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "We just need to", "get to Canterbury.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_courier_02 = {
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "If you need my", "services, just let", "me know.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_courier_03 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Sir, we need this", "turkey delivered to", "the garbage pile.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_HAPPY, ACT_DEFAULT, "Oh.. Your highness,", "only humans and the", "rich use that pile.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "Just throw your", "trash off the cliff.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "No, it's for someone", "who lives there.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "..Visker?", "What does he want", "a turkey for?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Would you mind", "explaining?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "He asked me to.", "No reason.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_courier_03_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "A virtuous human..", "imagine that.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "One full of..", "patience.", "Admirable.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I will deliver it.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_courier_03_alt_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Is it poisoned?", "I hope so. That rat", "gets on my nerves.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_courier_04 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Sir, we need this", "turkey delivered to", "the garbage pile.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "My fee is 5G.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Oh.. Heheh..", "I apologize then.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "I would deliver it", "for free if my", "client was royalty.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Gee, it's a shame", "that I'm not royalty", "then, huh.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_courier, EM_DEFAULT, ACT_DEFAULT, "Whatever you say,", "princess.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_grandma_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Hello, ma'am?", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "Yes, what is it,", "sweetheart?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Do you know how", "to get to Canterbury", "from here?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "Say.. You look just", "like her majesty", "Princess Semura.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Hehe, I get that a", "lot but I'm, uh, not", "the Princess.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "What's the human", "doing here?", "Human..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "Please, cause some", "mischief, I'd like", "entertainment.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "We haven't had a", "good hanging in", "over a week.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "We need to get", "out of here.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_grandma_02 = {
    {0, &sprite_items::db_ch_grandma, EM_DEFAULT, ACT_DEFAULT, "Hmm.. Hmm..", "What a slow day..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Psst.. She kinda", "freaks me out..", "Let's go elsewhere..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_guy_01 = {
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "I-Is he dead?!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_deadguy, EM_DEFAULT, ACT_DEFAULT, "Nope, I just like", "sleeping face-down", "in the snow.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_deadguy, EM_DEFAULT, ACT_DEFAULT, "It's nice, you", "should try it", "sometime.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_NOODLE, &noodle_go, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Do you know", "how to get to", "Canterbury?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_deadguy, EM_DEFAULT, ACT_DEFAULT, "zzzzzzzzzzz", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Time to ask", "around, I suppose.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_guy_02 = {
    {0, &sprite_items::db_ch_deadguy, EM_DEFAULT, ACT_DEFAULT, "zzzzzzzzzzz", "zzzzzzzzzzz", "zzzzzzzzzzz", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_shop_01 = {
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "How'se you two", "fine folks doin on a", "day like today?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm doing well!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "I'm not, this", "town sucks so bad", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "I'd move but I spent", "like 500,000G on", "this shop", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "I need to pay it all", "off first", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Well that sucks", "You didn't rent?", "I'll buy the shop.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_shop_01_alt_02, &avalon_shop_01_alt_03},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "You'se can buy", "my things though", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_shop_01_alt_02 = {
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "I value ownership", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_shop_01_alt_03 = {
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "Come back with", "500,000G and let's", "chat some more, ok?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_shop_02 = {
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "Give me money ok", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "That's a lot of", "trash down there.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Yeah..", "I'mma stand", "back here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't like", "anything about that", "ledge.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "WELCOME TO", "AVALON VILLAGE", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "I think I smell", "something rotting.", "*retch*", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't want", "to stay long.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "GRAND MASTER", "SENATRIX", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Who is she?", "You look similar.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_sign_03_alt_03, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Muetos don't live", "very long. Maybe", "five years at most.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "The Senatrix has", "lived for two-", "hundred years.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Many muetos see", "her as a fixture of", "the world.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Officially, she's", "a demigoddess, the", "daughter of Losus.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "She rules as our", "queen.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "..Losus?", "200 years?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_sign_03_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Muetos believe", "in two goddesses,", "Losus and Genne.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Losus is all-good,", "while Genne is", "all-evil.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "They say Losus is", "still creating life,", "which is why", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "muetos spring out", "of holes in the", "ground,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "while humans come", "from Genne, which", "is the reason why", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "new humans come", "from other humans.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You believe that?", "Interesting.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_sign_03_alt_04, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I.. don't, but it's", "unwise not to be", "spiritual out here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_03_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "She goes through a", "ritual where she", "sheds her skin,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "And then she looks", "young again, but", "different.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Eww.", "Cool.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_sign_03_alt_02, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Yeah, it's kinda", "gross.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_03_alt_02 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Only problem is", "then they gotta go", "replace the statues.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_03_alt_03 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Yeah..", "I get that a lot.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_03_alt_04 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Yeah, that's one", "word for it.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_04 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "THE RED ROBIN", "TAVERN & INN", "BYOB", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_05 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Give me a moment,", "I think I can", "read this..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "\"Ma.. Ma.. Sel..\"", "", "Uh..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Yeah..", "I got nothing.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_sign_06 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "No idea what", "that says.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "All the blood", "all over the ground", "is really, uh..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Giving me a warm", "fuzzy feeling,", "though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_wormguy_01 = {
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "HUMAN, would", "you be kind enough", "to support", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "a poor, grieving", "father?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "But muetos don't-", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "(shush!!)", "(human doesn't", "know that!!)", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "The wicked fairies", "of the wood turned", "by beloved daughter", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "Into a statue!", "(The horror!)", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "If you pay me", "1G however,", "I can show you", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "her sorry fate.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "No way, worm guy.", "Sure. Why not.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &avalon_wormguy_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "You will regret it!", "I hope YOU turn to", "a statue as well!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_wormguy_01_alt_01 = {
    {0, &sprite_items::db_ch_wormguy, EM_DEFAULT, ACT_DEFAULT, "What a fine choice!", "Here is your ticket!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You found:", "WORM TICKET", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It was once a", "fast food receipt.", "Nice.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_TICKET, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation avalon_wormguy_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It's definitely a", "statue of a worm.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It appears to have", "been yard decor", "at one point.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Confusing.", "New Berlin doesn't", "have any yards.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Maybe muetos", "are into yard worms.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation bridge_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Yes.", "Avalon is", "that way.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "It probably won't", "get fixed for a", "while, though..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Muetos have", "a joke:", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "\"Mueto bridges", "are human bridges,", "but broken.\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "..but there's a", "tunnel around here", "somewhere.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "You can get most", "places through the", "tunnels.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation captive_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "W-WHERE ARE", "WE?!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "In a cave.", "Ow.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &captive_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I mean..", "Of course, but..", "What did..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I think we're", "trapped down here!!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I-I knew this was", "a bad idea..", "I knew", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I-I wasn't", "supposed to leave..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "W-We're gonna", "die down here..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation captive_01_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation cave_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "There are lots and", "lots of tunnels", "under the Old World.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "I'm, uh..", "not supposed to", "talk about them.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "How come?", "Understood.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &cave_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I know you're", "probably thinking,", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "\"Well, why did", "she say anything", "if she can't talk", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "about the tunnels.\"", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Well.. Uh.. If we", "have to go through", "tunnels,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "I'm sure you'll", "find out for", "yourself, but..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't want it", "coming from me.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation cave_01_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Right, just..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Don't put your", "guard down,", "down here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation cave_sign_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "WARNING:", "SKULL WORMS", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Eww..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation cave_sign_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "If you make", "a mistake,", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "go back to where", "you came from and", "get a breath of air.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You'll come back", "with fresh ideas.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation convo_document = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "None of this", "makes any sense.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation convo_lime = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It tastes sour.", "Lots of Vitamin C,", "though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "HP INCREASED", "BY 5", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_HP, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 5, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation convo_photo = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It just seems to", "be a photo of", "himself.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_01 = {
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_MUSIC_FADEOUT, "HALT NOW,", "FILTHY GLABBER!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_WAT, ACT_WALK, "Don't hurt us!!", "Please!", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_CROKE, static_cast<const animation*>(nullptr), {41, 8}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "Filthy Glabber", "can die!", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_CROKE, &croke_accuse, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "..with the mueto", "who is a glabber", "by association!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"Glabber\"?", "Hey. Chill out.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &croke_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "It's a slur for", "humans, it means", "\"bald.\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Now it's personal.", "Isn't he a frog?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &croke_01_alt_02, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Oh dear..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_CROKE_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_01_alt_01 = {
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "NO! NEVER!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_WAT, ACT_DEFAULT, "Hey! Stop!", "Don't you know", "who I am??", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "A glabber", "collaborator,", "no doubt!!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "Same thing as", "glabber in", "my book!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, ACT_FIGHT, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_CROKE_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_01_alt_02 = {
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "SHUT UP!!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_CROKE_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_02 = {
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "TASTE POISON,", "GLABBER!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "...", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_03 = {
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_croke, EM_DEFAULT, ACT_DEFAULT, "..A-", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_04 = {
    {0, &sprite_items::db_ch_ginger, EM_CONFUSED, ACT_DEFAULT, "..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_WAT, ACT_DEFAULT, "D-Did he just..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_05 = {
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_CROKE, &croke_lay_down, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_CONFUSED, ACT_DEFAULT, "He's.. Dead..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_CONFUSED, ACT_DEFAULT, "..I've never seen", "anyone use a poison", "dart so badly..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Let's raid his stuff", "RIP, frog man.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &croke_05_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "Doesn't that", "seem in bad taste?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "No", "On second thought..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &croke_05_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I guess it's fine if", "he has something we", "need to survive..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You found:", "PHOTOGRAPH", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_PHOTO, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation croke_05_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Rest in peace..", "Whoever you were..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation dart_01 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "I almost pity you,", "human.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "My grandfather", "INVENTED darts.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "There is none", "alive greater than", "I.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation dart_02 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "Beginner's luck!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation dart_03 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "I see.. It seems the", "gods have given you", "a gift.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation dart_04 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "N-NO!!", "IT CAN'T BE!!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation doll_guy_01 = {
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Hey, look at this", "doll, it's kinda", "cute.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_doll, EM_DEFAULT, ACT_DEFAULT, "Look, babe, I don't", "know where you're", "from,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_doll, EM_DEFAULT, ACT_DEFAULT, "But in this town,", "that's considered", "\"harrassment\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_WAT, ACT_DEFAULT, "I, uh.. I'm sorry,", "I didn't know you", "were.. uh.. alive.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_doll, EM_DEFAULT, ACT_DEFAULT, "That's extremely", "disrespectful,", "toots.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_doll, EM_DEFAULT, ACT_DEFAULT, "I'm just a shopper", "like any other.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "We're, uh..", "We're gonna go now.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_HAPPY, ACT_DEFAULT, "Hehehehe", "", "", 0, SIZE_SMALL, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "You'se should take", "my classes on", "ventriloquism.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation final_msg = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Thanks for", "trying out the", "demo so far!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I've only been", "working on this", "for 2 months,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "so I'm sure I'll", "make lots of", "progress.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "This village is", "only partially done", "for now.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Discord, X, BlueSky:", "", "\"@cinemint\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Feel free to reach", "out! Take care!", "~ Cinemint", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_01 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Oh- Not that way,", "That's the way to", "Berlin.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_GINGER, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I know.", "Oh.. Right.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &forest_dlg_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "They don't let", "humans back in", "through the gate.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I know it's right", "there, but..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Plus, with the war", "and all that..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "..I can read", "your face, I know", "it's tough.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Canterbury isn't", "too far though.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_01_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I know it's right", "there, but..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Plus, with the war", "and all that..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "..I can read", "your face, I know", "it's tough.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Canterbury isn't", "too far though.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_02 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Okay.. we're not", "too far from", "Avalon village.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I'll admit, though..", "Not sure what", "they'll do when", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "they see a human.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_03 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I don't know if", "trying to get in", "is wise.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_paper = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You found:", "DOCUMENT", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Nothing on it", "makes much", "sense, though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_DOCUMENT, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_sign_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "DANGEROUS!!!", "DO NOT ENTER", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "RESEARCHERS ONLY", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_sign_02 = {
    {0, &sprite_items::db_ch_ginger, EM_CONFUSED, ACT_DEFAULT, "I can't read this..", "I think it's for", "sale, though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You can't read?", "Got it.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &forest_dlg_sign_02_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "No, I can read,", "just not.. That.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation forest_dlg_sign_02_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Cute house though.", "Real shame.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_01 = {
    {0, nullptr, EM_SKIP, ACT_MUSIC_VISKER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_JEREMY, &jeremy_lay_down, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SULLEN, ACT_DEFAULT, "It body warm.", "", "Ewww.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, &visker_poke, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "NO, NO LIKE,", "First human down the", "chute in ages,", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "And it ALIVE?", "Hey, do something", "for me, human.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Go and DIE. NOW.", "I'm so so HUNGRY", "for HUMAN.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "HELP! HELP!!", "Well, excuse ME.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &garbage_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Ok.. I feel bad,", "human is kinda", "pathetic", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "I let you", "go but you have to", "do me favor.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Go to Avalon.", "Send me TURKEY.", "Hungry for turkey.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Tell them it for", "\"VISKER\".", "\"King of TRASH\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "Excuse me, human.", "I wait now..", "for DEAD human.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {2, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_01_alt_01 = {
    {0, &sprite_items::db_ch_visker, EM_SULLEN, ACT_DEFAULT, "*sigh*", "It okay.", "I forgive you.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "But I WON'T", "say where EXIT is", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_CONFUSED, ACT_DEFAULT, "Cos..", "I want you to die", "so I eat you.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "..Okay, I let you", "go but you have to", "do me favor.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Go to Avalon.", "Send me TURKEY.", "Hungry for turkey.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Tell them it for", "\"VISKER\".", "\"King of TRASH\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "Excuse me, human.", "I wait now..", "for DEAD human.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {2, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_02 = {
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Dead human fall..", "", "Any moment now..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_02b = {
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Aaaany day now…", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_03 = {
    {0, &sprite_items::db_ch_visker, EM_SKIP, ACT_TELEPORT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {14, 5}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "HEY HEY HEY", "Where YOU going?", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {19, 6}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SIDE_EYE, ACT_DEFAULT, "It, like,", "SO dangerous", "out there.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_WAT, ACT_DEFAULT, "Muetos hate humans.", "They ALL want", "you dead.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Oh no.", "Get out of my way.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &garbage_03_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "I..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SIDE_EYE, ACT_DEFAULT, "..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANNOYED, ACT_WALK, "Human win", "this time.", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {2, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_03_alt_01 = {
    {0, &sprite_items::db_ch_visker, EM_SIDE_EYE, ACT_DEFAULT, "If human insists,", "but I warn human..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Better to die here", "than out there.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_WALK, "Visker does not", "have conflict of", "interest.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {2, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_04 = {
    {0, &sprite_items::db_ch_visker, EM_SAD, ACT_DEFAULT, "So.. Human, uh..", "Close close to", "garbage exit..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Human doesn't", "LOOK like fighter", "though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SULLEN, ACT_DEFAULT, "Since human is", "gonna fight..", "a lot..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_HAPPY, ACT_DEFAULT, "I fight human.", "First.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SIDE_EYE, ACT_DEFAULT, "If human wins,", "then good enough", "to go home.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_EXCITED, ACT_DEFAULT, "If *I* win, then", "I get yummy", "human meal.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "Win-win scenario.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Let's go, ratboy.", "Not in the mood.", "Can we talk?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &garbage_04_alt_01, &garbage_04_alt_02},
    {0, &sprite_items::db_ch_visker, EM_EXCITED, ACT_DEFAULT, "Yay.", "Let's fight now.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_04_alt_01 = {
    {0, &sprite_items::db_ch_visker, EM_EXCITED, ACT_DEFAULT, "Well TOO BAD", "because I AM", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_04_alt_02 = {
    {0, &sprite_items::db_ch_visker, EM_EXCITED, ACT_DEFAULT, "No TALK", "only KICK ASS", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_05 = {
    {0, &sprite_items::db_ch_visker, EM_DISAPPOINTED, ACT_DEFAULT, "Fine.", "Grrr.", "Human can go.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "But if human", "*dies*..", "Remember..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_HAPPY, ACT_DEFAULT, "All trash returns", "back to VISKER.", "KING of TRASH.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_05b = {
    {0, &sprite_items::db_ch_visker, EM_HAPPY, ACT_DEFAULT, "*weird noises*", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_06 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Ugh, you again.", "Who are you?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &garbage_06_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker_wife, EM_HAPPY, ACT_DEFAULT, "Huh? Me?", "You not know me,", "human.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "HUMAN!", "Human don't speak to", "my wife like that!!", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {5, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Human really", "messed up.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Visker need to fight", "human AGAIN for", "wife's HONOR.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_02, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_06_alt_01 = {
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "Is HUMAN", "being rude to WIFE?!", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {5, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Human really", "messed up.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Visker need to fight", "human AGAIN for", "wife's HONOR.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_02, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_06_alt_02 = {
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_WALK, "Is HUMAN", "being rude to WIFE?!", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {5, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Human really", "messed up.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_ANGRY, ACT_DEFAULT, "Visker need to fight", "human AGAIN for", "wife's HONOR.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_FIGHT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOE_VISKERS_02, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_06b = {
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_JEREMY, &jeremy_lay_down, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_TELEPORT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISKER, static_cast<const animation*>(nullptr), {5, 2}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DISAPPOINTED, ACT_DEFAULT, "Let's go home, wife.", "I'm hungry.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker_wife, EM_DEFAULT, ACT_DEFAULT, "Why not eat human.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DISAPPOINTED, ACT_DEFAULT, "I'm angry at human.", "We eat human later.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, GARBAGE_TO_BLACK, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_fight_01 = {
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "You see that?", "That your", "\"THIRD EYE\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_DEFAULT, ACT_DEFAULT, "It a direct", "window to your soul.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_EXCITED, ACT_DEFAULT, "I so so hungry.", "I go first.", "Mkay?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_fight_02 = {
    {0, &sprite_items::db_ch_visker, EM_DISAPPOINTED, ACT_DEFAULT, "Human is good", "at this.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_visker, EM_SULLEN, ACT_DEFAULT, "But Human is not", "ready for", "NEXT ATTACK.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_fight_03 = {
    {0, &sprite_items::db_ch_visker, EM_ANNOYED, ACT_DEFAULT, "Ow", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_fight_04 = {
    {0, &sprite_items::db_ch_visker, EM_ANNOYED, ACT_DEFAULT, "OW OW OW", "OKAY, HUMAN WIN", "HUMAN WIN", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_fight_05 = {
    {0, &sprite_items::db_ch_visker, EM_ANNOYED, ACT_DEFAULT, "Taste WRATH", "of VISKER", "king of TRASH", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "MT. GARBAGE", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "(No Littering)", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign01b = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Look, man,", "I'm a sign.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I only say", "exactly one thing.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Not what you might", "call a", "conversationalist.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "VISKER HOUSE", "NO HUMANS ALLOWED", "UNLESS you DEAD", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "TO WHOEVER IS", "PAINTING ALL", "THESE POLKA DOTS", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "PAINT COSTS THE", "CITY MONEY", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "STOP IT", "THANK YOU", "MGMT", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign04 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "To escape, you must", "return to where", "you came from.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_sign05 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "ABANDON ALL HOPE,", "YE WHO ENTER", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation garbage_spare = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "SPARE is not", "effective on", "Visker.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "He seems very", "resolute to fight.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation henry_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I don't understand..", "I did the ritual", "correctly.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Blood isn't enough.", "The spirits require", "flesh.", COLOR_RED, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You'll need to", "give up one of", "your eyes.", COLOR_RED, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "..and you're certain", "that will be enough?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Have I ever given", "you a reason not", "to trust me?", COLOR_RED, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "No.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "", "", "I'm scared.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It will only", "hurt for a moment.", "", COLOR_RED, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation henry_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I'm sorry that", "it has to be", "this way.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You must be", "terrified,", "poor thing.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "My name is", "Dr. Henry Erickson.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "What is your", "name?", "If you can remember.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "", "", "V-Vista.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Welcome to my home,", "Vista.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You are going to", "be part of something", "very special.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation henry_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Good morning,", "pumpkin.", "Did you sleep well?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Morning, Henry.", "Not really.", "Too many thoughts.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Do you know what", "day it is?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It's.. Thursday?", "", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It's been one year", "since you woke up", "for the first time.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I made you a cake.", "It's your favorite,", "lemon.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Go ahead,", "make a wish.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I.. Don't know if", "I want to.", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "How come?", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I remember, the day", "you brought me here,", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I thought I wasn't", "going to make it.", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Back home.. I", "couldn't take it", "anymore.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "And then I woke", "up as.. This.", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I wanted to escape.", "It was a wish.", "And..", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You've been a", "good father to me.", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "But I gave up so", "many things, things", "I took for granted.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I wish I could see", "the sun again.", "I really, really do.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "But I'm afraid to", "wish because..", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "..Well, I don't want", "to give up anything", "else.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Anything that I", "might not be able", "to get back.", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I understand.", "Once I finish my", "research..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "We'll be able to", "get out of hiding?", "", COLOR_PURPLE, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Oh.. Much more", "than that, Vista.", "Much more.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation intro_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Deep within the", "woods of the", "old world,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "There once", "lay a cabin.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Forgotten by", "the man who", "built it,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Nearly forgotten", "by the woman", "who lived within,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "The last of her", "kind, a Marelon,", "named Vista.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation intro_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"I know it's hard,", "I know it's so hard,", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "But I need you", "to remember..\"", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation intro_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Cinemint", "presents", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation item_banana_hat_01 = {
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "We're running a", "special on the", "banana hat!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "\"BUY ONE:", "GET THAT ONE\"", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation item_enoki_01 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Is this supposed to", "be a human doll?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Her mouth is above", "her eyes..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "It is cute.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_CONFUSED, ACT_DEFAULT, "..", "Maybe not \"20,000G\"", "cute though.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation item_lime_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't think I", "could ever get sick", "of limes.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_ANNOYED, ACT_DEFAULT, "50,000G for a lime..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_primary, EM_DEFAULT, ACT_DEFAULT, "It's out of season.", "And we're in the", "woods.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation item_tire_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "A tire would be", "fantastic, if you", "had a car.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "But is 10,000G", "really fair?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_01 = {
    {0, nullptr, EM_SKIP, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_JEREMY, &jeremy_lay_down, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Absolutely", "everything hurts.", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_GINGER, &ginger_eat_lime, {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "For some reason,", "you smell like", "limes.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Surely an empty cot", "would have been", "better than a rug?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_02b = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You don't really", "feel tired anymore.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "The outpost computer", "must have all sorts", "of secrets.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "The password", "being one of them.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"ILOVELIMES\"", "\"LIMETIME\"", "\"password123\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_03_alt_01, &lab_03_alt_02},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "PASSWORD", "INCORRECT", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_03_alt_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "PASSWORD", "INCORRECT", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_03_alt_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "LOGIN SUCCESSFUL", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "December 31, 19XX", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "FINAL LOG.", "Funding cuts are", "sending us home.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Unfortunately,", "we haven't been", "able to find them.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "In all honesty", "this whole year", "feels like it's been", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "a huge waste", "of time.", "Our prevailing", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "theory as to where", "new muetos come", "from is that", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "they \"pop out of", "the ground\". It's as", "good as any.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_04 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "If you had been", "able to finish", "your degree,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You'd probably", "be able to \"get\"", "these books.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_05 = {
    {0, nullptr, EM_SKIP, ACT_MUSIC_GINGER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Oh! You're awake!", "Thank goodness.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "You're not, like,", "super injured,", "are you?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "If you smell like", "limes, that's..", "uh..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Because I have", "all these limes..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "..Lime juice is an", "antiseptic, right?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "NO?!", "Yes. Of course.", "..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Oh.", "", "Uh..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "", "", "You want a lime?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Yes.", "…Yes.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_02, static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "LIME has been", "added to your", "inventory!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Press START", "to view your", "inventory items.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_LIME, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I found you out", "near the garbage", "chute.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "The rat who lives", "out there usually", "eats dead humans.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm Ginger,", "by the way.", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_GINGER, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "It's hard for humans", "to get back into the", "city, huh?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm heading to", "Canterbury.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I figured that since", "you were a human,", "you were too.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Do you know", "how to get there?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Not a clue.", "I know everything.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_03, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Uh.. Well..", "There are signs", "everywhere..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I'm sure we'll", "figure it out.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_CUE_GINGER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_05_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Whew..", "Thank goodness!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "So..", "", "You want a lime?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Yes.", "…Yes.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_02, static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "LIME has been", "added to your", "inventory!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Press START", "to view your", "inventory items.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_LIME, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I found you out", "near the garbage", "chute.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "The rat who lives", "out there usually", "eats dead humans.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm Ginger,", "by the way.", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_GINGER, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "It's hard for humans", "to get back into the", "city, huh?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm heading to", "Canterbury.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I figured that since", "you were a human,", "you were too.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Do you know", "how to get there?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Not a clue.", "I know everything.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_03, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Uh.. Well..", "There are signs", "everywhere..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I'm sure we'll", "figure it out.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_CUE_GINGER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_05_alt_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "LIME has been", "added to your", "inventory!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Press START", "to view your", "inventory items.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_ITEM, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, OBJ_LIME, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "I found you out", "near the garbage", "chute.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "The rat who lives", "out there usually", "eats dead humans.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm Ginger,", "by the way.", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_GINGER, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "It's hard for humans", "to get back into the", "city, huh?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I'm heading to", "Canterbury.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I figured that since", "you were a human,", "you were too.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Do you know", "how to get there?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Not a clue.", "I know everything.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &lab_05_alt_03, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Uh.. Well..", "There are signs", "everywhere..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I'm sure we'll", "figure it out.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_CUE_GINGER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_05_alt_03 = {
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "YAY!", "This'll be easy!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Lead the way!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_MUSIC_RESET, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_SKIP, ACT_CUE_GINGER, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_06 = {
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "I've been hiding out", "in this old", "outpost lab.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "It's nice to have,", "y'know,", "running water.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Clean bathrooms", "are hard to come by", "out here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "I'll admit I'm not", "thrilled about", "leaving.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_07 = {
    {0, &sprite_items::db_ch_ginger, EM_WAT, ACT_DEFAULT, "Oh- you don't", "want to open", "the fridge door.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "The dehydrated", "limes were the only", "fresh things.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "Everything else..", "Let's just say it", "has a smell.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "This place was", "probably abandoned", "for a year or two.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation lab_08 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "They emptied", "out the lockers.", "Ugh.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation leaving_lab = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "You don't mind", "if I follow you,", "right?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You're fine.", "Yes I do mind.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &leaving_lab_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Thank you,", "I just, uh..", "Nevermind.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "It's scary", "out there.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "True.", "It's not that bad.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &leaving_lab_alt_02, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Alright..", "I'm ready.", "Let's go.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOREST_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation leaving_lab_alt_01 = {
    {0, &sprite_items::db_ch_ginger, EM_EMBARRASSED, ACT_DEFAULT, "Was that sarcasm?", "I'm sorry, I can't", "really tell.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Yes.", "No.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &leaving_lab_alt_03, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Oh..", "Thank goodness.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "It's scary", "out there.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "True.", "It's not that bad.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &leaving_lab_alt_02, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Alright..", "I'm ready.", "Let's go.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOREST_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation leaving_lab_alt_02 = {
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Well.. I guess it's", "good at least", "one of us", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "feels that way.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Alright..", "I'm ready.", "Let's go.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOREST_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation leaving_lab_alt_03 = {
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "Oh.. I see.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "Well, uh.. It's", "dangerous out there,", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "I'll tag along until", "we get to Avalon,", "then I'll..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SAD, ACT_DEFAULT, "figure something", "else out.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, FOREST_01, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation new_berlin_sign = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "They call it,", "\"New Berlin\".", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Airplanes come in", "through the slit at", "the top.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Most of the lower", "levels are destroyed", "because of the war.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Humans who leave", "don't tend to make", "it back alive.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_01 = {
    {0, &sprite_items::db_ch_greyfriar, EM_DEFAULT, ACT_DEFAULT, "I can't believe", "they'd slander me", "like that!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_greyfriar, EM_DEFAULT, ACT_DEFAULT, "My mates say", "I've got a", "\"gambling problem\".", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_greyfriar, EM_DEFAULT, ACT_DEFAULT, "I bet they're", "making fun of me", "right now.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I'm bet they're not.", "I bet you're right.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &scruffys_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_greyfriar, EM_DEFAULT, ACT_DEFAULT, "..", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_greyfriar, EM_DEFAULT, ACT_DEFAULT, "I'll give you $10", "if they're not.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_01_alt_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"B-Bet..\"", "I feel..", "An itch..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_02 = {
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "And that's when I", "said-..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_HAPPY, ACT_DEFAULT, "Um..", "Can I help you,", "human?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Do you know how", "to get to", "Canterbury?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_HAPPY, ACT_DEFAULT, "I asked the human,", "not you.", "Rude.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Where is Canterbury?", "Goodbye.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &scruffys_02_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "So a human shows", "up in the middle of", "Avalon,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "And doesn't know", "how to get to", "Canterbury.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_HAPPY, ACT_DEFAULT, "Every mueto knows", "how to get to", "Canterbury.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "That's why the", "gods love us more.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't-", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "What?", "Did I", "hear something?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_02_alt_01 = {
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "Hey, check out the", "tollhouse on the", "east side.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_jelly, EM_DEFAULT, ACT_DEFAULT, "That's the best way", "to leave and never", "come back.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_03 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Can you help us", "figure out how to", "get to Canterbury?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_horsey, EM_DEFAULT, ACT_DEFAULT, "..Nay.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_04 = {
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "They don't got", "alcohol here no", "more.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "I gotta drink this", "lake water and", "pretend a little.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "Look at it.", "I think it moved", "on its own.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Surely there's", "something else to", "drink.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "There is but I'd", "have to get up.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "If you two find", "somethin' else, I'll", "pay a little.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_04b = {
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "\"How dry I am..\"", "", "\"How dry I am..\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_04c = {
    {0, &sprite_items::db_ch_glompy, EM_DEFAULT, ACT_DEFAULT, "Oh!! Thank you!", "Here, take this,", "I don't need it.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You found:", "5G", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_05 = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "A human..", "They say your kind", "is good at darts.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "If you beat me,", "I'll give you 50G.", "Deal?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Deal.", "No deal.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &scruffys_05_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "Let's play!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, ACT_GAME, ACT_DEFAULT, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, GAME_DARTS, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_05b = {
    {0, &sprite_items::db_ch_sneaker, EM_DEFAULT, ACT_DEFAULT, "I.. I can't..", "YOU!", "GLABBER!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I'LL KILL YOU!!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_06 = {
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "I'm sorry, we", "haven't gotten any", "shipments in", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "in weeks.", "All we have is", "water.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "1G per glass.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_06b = {
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "What can I get", "for you?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "Water.", "No water.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &scruffys_06b_alt_01, static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "One water,", "coming right up.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "You found:", "WATER", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation scruffys_06b_alt_01 = {
    {0, &sprite_items::db_ch_robin, EM_DEFAULT, ACT_DEFAULT, "Your loss.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_01 = {
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "HOIDY AND", "WELCOM TO", "COWBEMMIE LAND", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "COM EXPERENCE", "OUR VIBRANT", "CULTURE", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_02 = {
    {0, &sprite_items::db_ch_temmie, EM_HAPPY, ACT_DEFAULT, "hoi-dy!!", "im cowbemmie", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "wat r you", "cowpokes doin", "round these parts", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_HAPPY, ACT_DEFAULT, "Oh hi!!", "I've heard all", "about y'all!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "we surviv on", "butter from", "da churn", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "What?", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "everythings gonna", "churn out ok", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"The beautiful", "blue tunnel flower", "can be found", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "all over the", "tunnels of the", "Old World.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It's toxic and", "everyone is", "slightly allergic.\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_04 = {
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "hoi cowbemmie", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_HAPPY, ACT_DEFAULT, "hoi to you too", "cowbemmie", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "this ton aint", "big nough for da", "two of us", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_EXCITED, ACT_DEFAULT, "okay", "", "..then draw", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "i cant draw", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_EXCITED, ACT_DEFAULT, "oh ok ok", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_EXCITED, ACT_DEFAULT, "maybe it is", "big nough then", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_05 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "\"AR HISTORY\"", "~ cowbemmie", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "The cowbemmie", "next to it appears", "to be painted on.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_06 = {
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "in da olden days", "cowbemmies rode", "da hose", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_ANGRY, ACT_DEFAULT, "MOO", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "good hose", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_07 = {
    {0, &sprite_items::db_ch_temmie, EM_HAPPY, ACT_DEFAULT, "no good culture", "is withot a", "CULT", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "if u wanna be", "honorary cow-", "bemmie", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_EXCITED, ACT_DEFAULT, "u gotta partake", "in da frot", "of da churn", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Fruit?", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_EXCITED, ACT_DEFAULT, "frot of da churn", "yes", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "it'll churn y'all's", "life around", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "then we mail u", "yor honorary", "cowbemmie hat", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_temmie, EM_DEFAULT, ACT_DEFAULT, "an u can come", "to secret meetings", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation temmie_sign = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "COWBEMMIE", "VILLAGE", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation test_convo = {
    {0, nullptr, EM_SKIP, ACT_WALK, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISTA, &vista_reminisce, {2, 6}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "In her cabin,", "most days were", "just the same.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "She read her books", "and cared for her", "sawdust doll.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_SFX_KNOCK, "But today,", "there was a knock", "at the door.", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISTA, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_vista, EM_DEFAULT, ACT_WALK, "Yes?", "Who is it?", "", 0, SIZE_DEFAULT, SP_DEFAULT, CHAR_VISTA, &vista_pickup, {1, 3}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_vista, EM_SULLEN, ACT_DEFAULT, "Hmm,", "What could this be?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_vista, EM_HAPPY, ACT_DEFAULT, "\"Dear Vista,", "I don't know if you", "remember me..\"", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_vista, EM_DEFAULT, ACT_DEFAULT, "\"It's been years", "and years..\"", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_vista, EM_DEFAULT, ACT_DEFAULT, "I don't..", "remember..", "anyone else..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_PROGRESS, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, CUTSCENE_TO_GARBAGE, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation tollhouse_01 = {
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Ask not for", "whom the bell", "tolls..", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "For it might be", "*I*!", "The tollman!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "You take your job", "very seriously.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "But of course I do.", "I spent every", "waking moment", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "of my life in this", "booth.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "If I didn't take it", "seriously, then my", "entire life would", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "be an enormous", "waste.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Can't you see how", "serious I am about", "getting into heaven?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "How much is", "the toll?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "50G.", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "50G?!", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Of course.", "How much is freedom", "worth it to you?", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "I don't like this", "toll man.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Your approval is", "not the approval", "I'm after.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation tollhouse_01b = {
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "You returned..", "but not with 50G!", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Your time may not", "be meaningful to", "yourself,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "But my time is", "the most precious", "thing in the world!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_tollman, EM_DEFAULT, ACT_DEFAULT, "Return.", "But only with", "enough.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation tunnel_01 = {
    {0, &sprite_items::db_ch_ginger, EM_DEFAULT, ACT_DEFAULT, "Hey- Just, uh..", "Before we go in..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, &sprite_items::db_ch_ginger, EM_SIDE_EYE, ACT_DEFAULT, "Just..", "Be careful, okay?", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation visker_h_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "This pile is mostly", "take-away food.", "(He took it away)", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation visker_h_02 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "A pile of tabloids.", "Also Infinite Jest.", "All are dog-eared.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Under the desk..", "Oh dear..", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You've never seen", "so many", "Reader's Digests.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation visker_h_03 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "His nest is made of", "discarded t-shirts.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Half of them are", "from the exact same", "family reunion.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation worm_action_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "It seems that", "someone left a", "bottle here.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "Perhaps it's to pay", "respects?", "No clue.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I'll take it.", "I'll leave it be.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, &worm_action_01_alt_01, static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "You found:", "WINE BOTTLE", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation worm_action_01_alt_01 = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "A considerate", "choice.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

const conversation youtube_ad = {
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "10 years ago,", "Toby Fox released", "\"Undertale\" for PC.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "That same year,", "I released my oldest", "fantasy novel.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "In some ways,", "the two works were", "very similar.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "In other ways,", "they were not.", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "To celebrate the", "anniversary of both,", "however,", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "I've decided to", "adapt the latter in", "the former's style.", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_DEFAULT, "An early demo is", "now available on", "Itch.io!", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)},
    {0, nullptr, EM_DEFAULT, ACT_END, "", "", "", 0, SIZE_DEFAULT, SP_DEFAULT, 0, static_cast<const animation*>(nullptr), {0, 0}, static_cast<const conversation*>(nullptr), static_cast<const conversation*>(nullptr)}};

