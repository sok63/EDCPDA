#pragma once 

#include <cstdint>

enum class eGestureType {
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
    TWOF_ZOOM_OUT,
    TWOF_ROTATION
};

struct TouchDetection {
   int16_t x;
    int16_t y;
    uint32_t timestamp;
    bool valid;
};

struct sTouchAction {
  eGestureType type;
  TouchDetection detection1;
  TouchDetection detection2;
};


class ATouchHAL {
public:
    virtual ~ATouchHAL() = default;
    
    virtual void init() = 0;
    virtual sTouchAction getNext() = 0;
    virtual void update() = 0;
};