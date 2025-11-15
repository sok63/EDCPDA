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

    uint8_t count = M5.Touch.getCount();
    if (count) {
        for (size_t i = 0; i < count; ++i) {
            const auto& t = M5.Touch.getDetail(i);

            input.n = i;
            input.x = t.x;
            input.y = t.y;
            input.isPressed = t.isPressed();
            input.justPressed = t.wasPressed();
            input.justReleased = t.wasReleased();
            input.timestamp = millis();

            // Update touch driver
            touchDriver_.update(input);
        }
    } else {
        input.n = 0;
        input.x = 0;
        input.y = 0;
        input.isPressed = false;
        input.justPressed = false;
        input.justReleased = false;
        input.timestamp = millis();
        // Update touch driver
        touchDriver_.update(input);
    }
}
