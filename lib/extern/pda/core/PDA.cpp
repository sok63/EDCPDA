#include "PDA.h"

#include <pda/core/Kernel.h>

void PDA::run_cycle()
{

    auto k = Kernel::getInstance();
    auto app = k->getApplication();
    auto display = k->getDisplay();

    // If no app - restore default app
    if (!app) {
        k->setApplication(0);
        if (!app) {
            return;
        }
    }

    // Process touches
    k->getTouch()->update();

    auto touch = k->getTouch()->getNext();
    if (touch.gesture != eGestureType::NONE) {
        Serial.println("Touch detect");
        Event event;
        event.type = eEventType::TOUCH_EVENT;
        memcpy(event.data, &touch, sizeof(touch));
        event.timestamp = millis();
        k->getEventService()->postEvent(event);
        return;
    }

    // Update services
    k->getTimerService()->update();

    // Update and render app
    app->update(0);

    if (display->isNeedRedraw()) {
        Serial.println("Need redraw");
        display->beginTransaction();
        app->render();
        display->endTransaction();
        display->refresh();
    }

    delay(10);
}
