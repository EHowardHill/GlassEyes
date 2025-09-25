// ge_text.h

#ifndef GE_TEXT_H
#define GE_TEXT_H

#include "bn_vector.h"
#include "bn_string.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"

#include "ge_structs.h"
#include "ge_sprites.h"

// Forward declaration to avoid circular dependency
struct character_manager;

using namespace bn;

enum progress
{
    CUTSCENE_01,
    CUTSCENE_02,
    CUTSCENE_TO_GARBAGE,
    GARBAGE_TO_BLACK,
    BLACK_TO_LAB,
    FOREST_01,
    FINAL_MSG,
    AVALON,
    NEW_BERLIN,
    YOUTUBE_AD,
    TEST_MAP
};

enum foes
{
    FOE_VISKERS_01,
    FOE_VISKERS_02,
    FOE_CROKE_01,
    FOE_TEST
};

enum games
{
    GAME_DARTS
};

enum actions
{
    ACT_DEFAULT,
    ACT_EMOTE,
    ACT_TURN,
    ACT_WALK,
    ACT_TELEPORT,
    ACT_SPAWN,
    ACT_MULTIPLE_CHOICE,
    ACT_END,
    ACT_FIGHT,
    ACT_PROGRESS,
    ACT_ITEM,
    ACT_CUE_GINGER,
    ACT_SFX_KNOCK,
    ACT_HP,
    ACT_GAME,
    ACT_GOLD,
    ACT_MUSIC_VISKER,
    ACT_MUSIC_GINGER,
    ACT_MUSIC_FADEOUT,
    ACT_MUSIC_RESET,
};

enum speed
{
    SP_DEFAULT,
    SP_SLOW,
    SP_FAST,
    SP_REALTIME
};

enum emotion
{
    EM_DEFAULT,
    EM_HAPPY,
    EM_EXCITED,
    EM_ANGRY,
    EM_SAD,
    EM_DISAPPOINTED,
    EM_SULLEN,
    EM_SIDE_EYE,
    EM_LAUGH,
    EM_EMBARRASSED,
    EM_ANNOYED,
    EM_WAT,
    EM_CONFUSED,
    EM_PAIN,
    EM_SKIP
};

enum size
{
    SIZE_DEFAULT,
    SIZE_SMALL,
    SIZE_LARGE
};

enum colors
{
    COLOR_WHITE,
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_PINK,
    COLOR_PURPLE
};

struct dialogue_line;
typedef const dialogue_line conversation[128];

struct dialogue_line
{
    int id = 0;
    const sprite_item *portrait = nullptr;
    int emotion = EM_DEFAULT;
    int action = ACT_DEFAULT;
    const char *raw_text[3] = {nullptr, nullptr, nullptr};

    int branches[3] = {0, 0, 0};
    int color = COLOR_WHITE;
    int size = SIZE_DEFAULT;
    int speed = SP_DEFAULT;

    int index = 0;
    const animation *anim = nullptr;
    vector_2 navigate = {0, 0};

    const conversation *dlg01 = nullptr;
    const conversation *dlg02 = nullptr;

    constexpr dialogue_line(
        int id_ = 0,
        const sprite_item *char_ = nullptr,
        int emotion_ = EM_DEFAULT,
        int action_ = ACT_DEFAULT,
        const char *line1 = nullptr,
        const char *line2 = nullptr,
        const char *line3 = nullptr,
        int color_ = COLOR_WHITE,
        int size_ = SIZE_DEFAULT,
        int speed_ = SP_DEFAULT,
        int index_ = 0,
        const animation *anim_ = nullptr,
        vector_2 navigate_ = {0, 0},
        const conversation *dlg01_ = nullptr,
        const conversation *dlg02_ = nullptr) : id(id_),
                                                portrait(char_),
                                                emotion(emotion_),
                                                action(action_),
                                                raw_text{line1, line2, line3},
                                                color(color_),
                                                size(size_),
                                                speed(speed_),
                                                index(index_),
                                                anim(anim_),
                                                navigate(navigate_),
                                                dlg01(dlg01_),
                                                dlg02(dlg02_)
    {
    }
};

typedef const dialogue_line conversation[128];

enum ITEMS
{
    OBJ_LIME,
    OBJ_PHOTO,
    OBJ_DOCUMENT,
    OBJ_TICKET,
    ITEMS_SIZE
};

extern const char *ITEM_LABELS[ITEMS_SIZE];
extern const bool ITEM_DROP[ITEMS_SIZE];
extern const conversation *ITEM_CONVOS[ITEMS_SIZE];

struct letter
{
    optional<sprite_ptr> sprite;
    vector_2 ideal_position;
    vector_2 temp_position;
    int char_index;
    int color;

    letter(char ch, vector_2 ideal_position_, int color);

    void update(int color, int size);
};

// Forward declare toast before text
struct toast;

struct text
{
    vector<letter, 20> letters;
    vector_2 start;
    int index = 0;
    int current_x = 0;
    bool active = false;
    string<20> reference;
    int size = SIZE_DEFAULT;
    int color = COLOR_WHITE;

    static vector<toast, 16> toasts;
    static void add_toast(string<20> value, vector_2 pos);
    static void add_toast(int value, vector_2 pos);
    static void update_toasts();
    static bool at_location(vector_2 pos);

    text();
    text(vector_2 start_ = {0, 0});
    text(const char *value = nullptr, vector_2 start_ = {0, 0});
    text(const string<20> &value, vector_2 start_ = {0, 0});

    void init(const char *value);
    void init(const string<20> &value);
    void update(const sprite_item *portrait, bool typewriter);
    void render();
    void set_position(int x, int y);
    bool is_ended();
};

char digit_conv(int digit);

struct toast
{
    text value = {nullptr, {0, 0}};
    int ticker;

    toast();
};

struct dialogue_box
{
    optional<sprite_ptr> portrait;
    optional<regular_bg_ptr> box;
    optional<sprite_ptr> pointer;
    int ticker;
    const conversation *active_conversation;
    int index;
    int size;
    text lines[3] = {
        {nullptr, {-40, 32}},
        {nullptr, {-40, 48}},
        {nullptr, {-40, 64}}};

    // Add these new members for branching dialogue
    bool is_branching;
    int branching_selection; // 0-2 for the three options
    int num_options;         // 2 or 3 depending on dlg02

    dialogue_box();
    void load(const conversation *new_conversation);
    void init(character_manager *ch_man);
    void update();
    bool is_ended();

    bool is_text_complete();                               // Check if current text is fully displayed
    void instant_complete_text();                          // Instantly complete current text
    void handle_a_button_press(character_manager *ch_man); // Handle A button input
    void advance(character_manager *ch_man);               // Advance to next dialogue

    // Add these new methods for branching
    void handle_branching_input(character_manager *ch_man);
    void update_branching_selector();
};

struct items_box
{
    optional<regular_bg_ptr> box;
    optional<sprite_ptr> selector; // The "*" selector sprite
    text gold = {nullptr, {-96, 48}};
    text lines[3] = {
        {nullptr, {-40, 32}},
        {nullptr, {-40, 48}},
        {nullptr, {-40, 64}}};
    int cursor_position;          // Current selection (0-2 visible)
    int scroll_offset;            // Offset for scrolling
    int total_items;              // Total number of items in inventory
    int item_indices[ITEMS_SIZE]; // Indices of items in inventory
    bool active;

    items_box();
    void init();
    void update();
    void handle_input(character_manager *ch_man);
    void close();
    bool is_active() const { return active; }

    void refresh_display();
    int get_selected_item_index() const;
};

#endif // GE_TEXT_H