#include "Header.h"

#include <M5Unified.h>

Header::Header(ApplicationContext* context)
    : AWidget({0, 0, 540, 30})
    , context_(context)
{
}

void Header::update()
{
}

void Header::render(ADisplaySpriteHAL* to)
{
    char buf[15];

    // Draw time
    auto dt = context_->getRTC()->getDateTime();
    sprintf(buf, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = to->getTextWidth(buf, 2);
    to->drawText(270 - (text_width) / 2, 10, buf, 0, 2);

    // Draw HEAP info
    sprintf(buf, "%02db", ESP.getFreeHeap());
    to->drawText(350, 10, buf, 0, 2);

    // Draw Battery info
    sprintf(buf, "[%02d]", context_->getPower()->getBatteryLevel());
    to->drawText(470, 10, buf, 0, 2);

    // Draw bottom line
    to->drawLine(0, 26, 540, 26, 0);
}

bool Header::feed_event(const Event& ev)
{
    return false;
}
