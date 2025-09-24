#ifndef GE_STRUCTS_H
#define GE_STRUCTS_H

#include "bn_fixed.h"

using namespace bn;

constexpr int screen_width = 240;
constexpr int screen_height = 160;

struct vector_2
{
    fixed_t<4> x = 0;
    fixed_t<4> y = 0;
};

struct bound
{
    vector_2 position;
    fixed_t<4> width;
    fixed_t<4> height;
    
    // Default constructor
    constexpr bound() : position(0, 0), width(0), height(0) {}
    
    // Constructor for initialization
    constexpr bound(vector_2 pos, fixed_t<4> w, fixed_t<4> h) 
        : position(pos), width(w), height(h) {}
};

const bound screen = {{0, 0}, screen_width, screen_height};

#endif // GE_STRUCTS_H