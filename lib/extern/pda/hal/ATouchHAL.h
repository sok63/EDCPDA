#pragma once 

#include <cstdint>

struct TouchPoint {
    int16_t x;
    int16_t y;
    bool pressed;
};

class ATouchHAL {
public:
    virtual ~ATouchHAL() = default;
    
    virtual void init() = 0;
    virtual bool available() = 0;
    virtual TouchPoint getPoint() = 0;
    virtual bool isPressed() = 0;
};