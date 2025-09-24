// ge_structs.cpp
#include "bn_fixed.h"

using namespace bn;

constexpr int screen_width = 240;
constexpr int screen_height = 160;

struct vector_2
{
    fixed_t<4> x;
    fixed_t<4> y;
};

struct bound
{
    vector_2 position;
    fixed_t<4> width;
    fixed_t<4> height;
};

constexpr bound screen = {{0, 0}, screen_width, screen_height};