#pragma once

#include <cstdint>


struct sPosition {
    int16_t x;
    int16_t y;
};


struct sRect {
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h; 
};

inline bool check_hit(const sRect& r, int x, int y) {
    return (x >= r.x) && (x < r.x + r.w) &&
           (y >= r.y) && (y < r.y + r.h);
}
