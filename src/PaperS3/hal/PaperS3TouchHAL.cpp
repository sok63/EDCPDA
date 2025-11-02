#include "PaperS3TouchHAL.h"
#include <cmath>
#include <esp32-hal.h>




// TODO: move to config with passing to constructor
const uint32_t DOUBLE_TAP_TIME = 300;      // delay btw taps
const uint32_t LONG_PRESS_TIME = 500;      // delay long press
const int16_t SWIPE_THRESHOLD = 50;        // min distance for swipe
const int16_t TAP_THRESHOLD = 10;          // max tap moving




eGestureType detectGesture(TouchDetection start, TouchDetection end, uint32_t duration) {
    int16_t dx = end.x - start.x;
    int16_t dy = end.y - start.y;
    int16_t distance = sqrt(dx * dx + dy * dy);
    static uint32_t lastTapTime = 0;
    
    // Долгое нажатие
    if (duration >= LONG_PRESS_TIME && distance < TAP_THRESHOLD) {
        return eGestureType::ONEF_LONG_PRESS;
    }

    // Свайп
    if (distance >= SWIPE_THRESHOLD) {
        if (abs(dx) > abs(dy)) {
            return (dx > 0) ? eGestureType::ONEF_SWIPE_RIGHT : eGestureType::ONEF_SWIPE_LEFT;
        } else {
            return (dy > 0) ? eGestureType::ONEF_SWIPE_DOWN : eGestureType::ONEF_SWIPE_UP;
        }
    }

    // Тап
    if (distance < TAP_THRESHOLD) {
        uint32_t currentTime = millis();
        if (currentTime - lastTapTime < DOUBLE_TAP_TIME) {
            lastTapTime = 0; // Сброс для предотвращения тройного тапа
            return eGestureType::ONEF_DOUBLE_TAP;
        }
        lastTapTime = currentTime;
        return eGestureType::ONEF_TAP;
    }

    return eGestureType::NONE;
}


void PaperS3TouchHAL::init()
{
}

sTouchAction PaperS3TouchHAL::getNext()
{
    return sTouchAction();
}

void PaperS3TouchHAL::update()
{
}
