#include "PaperS3TouchHAL.h"
#include <cmath>
#include <esp32-hal.h>

void PaperS3TouchHAL::init()
{
}

sTouchEvent PaperS3TouchHAL::getNext()
{
    sTouchEvent event;
    touchDriver_.getNextEvent(event);
    return event;
}

void PaperS3TouchHAL::update()
{
    // Convert from M5 to universal touchpoint
    sTouchInput input;
    auto t = M5.Touch.getDetail();

    input.x = t.x;
    input.y = t.y;
    input.isPressed = t.isPressed();
    input.justPressed = t.wasPressed();
    input.justReleased = t.wasReleased();
    input.timestamp = millis();

    // Update touch driver
    touchDriver_.update(input);
}
