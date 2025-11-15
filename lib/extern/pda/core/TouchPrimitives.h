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
    eGestureType gesture;
    int16_t x, y;
    int16_t startX, startY;
    int16_t deltaX, deltaY;
    uint32_t duration;
    uint32_t timestamp;

    sTouchEvent()
        : gesture(eGestureType::NONE)
        , x(0)
        , y(0)
        , startX(0)
        , startY(0)
        , deltaX(0)
        , deltaY(0)
        , duration(0)
        , timestamp(0)
    {
    }
};

inline bool check_hit(const sRect& r, int x, int y)
{
    return (x >= r.x) && (x < r.x + r.w) && (y >= r.y) && (y < r.y + r.h);
}
