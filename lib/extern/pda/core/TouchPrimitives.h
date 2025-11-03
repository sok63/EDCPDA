#pragma once 

#include <cstdint>

enum class eGestureType : uint8_t {
    NONE,
    ONEF_TAP,
    ONEF_DOUBLE_TAP,
    ONEF_LONG_PRESS,
    ONEF_SWIPE_UP,
    ONEF_SWIPE_DOWN,
    ONEF_SWIPE_LEFT,
    ONEF_SWIPE_RIGHT,
    ONEF_DRAG_START,
    ONEF_DRAG_MOVE,
    ONEF_DRAG_END,
    TWOF_ZOOM_IN,
    TWOF_ZOOM_OUT,
    TWOF_ROTATION
};

struct sTouchEvent {
    eGestureType gesture;
    int16_t x;          
    int16_t y;             
    int16_t startX;         
    int16_t startY;        
    int16_t deltaX;       
    int16_t deltaY;       
    uint32_t duration;     
    uint32_t timestamp;   
    
    sTouchEvent() : gesture(eGestureType::NONE), x(0), y(0), 
                    startX(0), startY(0), deltaX(0), deltaY(0),
                    duration(0), timestamp(0) {}
};