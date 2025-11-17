#pragma once

#include "CorePrimitives.h"
#include <cstdint>

enum class eGestureType : uint8_t
{
    NONE,
    ONEF_TAP,
    ONEF_DOUBLE_TAP,
    ONEF_LONG_PRESS,
    ONEF_SWIPE_UP,
    ONEF_SWIPE_DOWN,
    ONEF_SWIPE_LEFT,
    ONEF_SWIPE_RIGHT,
    ONEF_DRAG,
    TWOF_ZOOM_IN,
    TWOF_ZOOM_OUT
};

struct sTouchEvent
{
    eGestureType gesture = eGestureType::NONE;
    int16_t x = 0;
    int16_t y = 0;
    int16_t startX = 0;
    int16_t startY = 0;
    int16_t deltaX = 0;
    int16_t deltaY = 0;
    uint32_t duration = 0;
    uint32_t timestamp = 0;
};

inline bool check_hit(const sRect& r, int x, int y)
{
    return (x >= r.x) && (x < r.x + r.w) && (y >= r.y) && (y < r.y + r.h);
}
