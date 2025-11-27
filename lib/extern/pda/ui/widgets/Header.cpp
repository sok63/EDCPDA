#include "Header.h"

#include <M5Unified.h>
#include <pda/helpers/touch/TouchGestureDriver.h>


Header::Header(ApplicationContext* context, ApplicationManager* appManager)
    : AWidget({0, 0, 540, HEADER_SIZE})
    , context_(context)
    , app_manager_(appManager)
{
}

void Header::update()
{
    if ((millis() - last_draw_) > 60000.)
        set_dirty_flag();
}

void Header::render(ADisplaySpriteHAL* to)
{
    // Clean area
    to->drawFillRect(size_.x, size_.y, size_.x+size_.w, size_.y+size_.h, TFT_WHITE);

    char buf[15];

    // Draw time
    auto dt = context_->getRTC()->getDateTime();
    sprintf(buf, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = to->getTextWidth(buf, 2);
    to->drawText(270 - (text_width) / 2, 6, buf, 0, 2);

    // Draw HEAP info
    sprintf(buf, "%02db", ESP.getFreeHeap());
    to->drawText(350, 6, buf, 0, 2);

    // Draw Battery info
    sprintf(buf, "[%02d]", context_->getPower()->getBatteryLevel());
    to->drawText(470, 6, buf, 0, 2);

    // Draw bottom line
    to->drawLine(size_.x, size_.y + size_.h, size_.x + size_.w, size_.y + size_.h, 0);

    // Update counter
    last_draw_ = millis();
}

bool Header::feed_event(const Event& event)
{
    if (event.type != eEventType::TOUCH_EVENT)
        return false;

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));
    Serial.println(TouchGestureDriver::getGestureName(touch->gesture));

    if ((touch->gesture != eGestureType::ONEF_SWIPE_DOWN))
        return false;

    if (check_hit(size_, touch->startX, touch->startY)) {
        app_manager_->exitCurrentApp();
        return true;
    }

    return false;
}
