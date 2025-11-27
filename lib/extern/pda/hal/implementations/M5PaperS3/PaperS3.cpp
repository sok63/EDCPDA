#include "PaperS3.h"

#include <pda/hal/implementations/M5PaperS3/PaperS3DisplayHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3LVRenderHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3PowerHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3RTCHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3StorageHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3TouchHAL.h>

void PaperS3::init()
{
    auto cfg = M5.config();
    cfg.clear_display = false;
    M5.begin(cfg);

    setDisplayHAL(new PaperS3DisplayHAL());
    setLVRenderHAL(new PaperS3LVRenderHAL());
    setTouchHAL(new PaperS3TouchHAL());
    setStorageHAL(new PaperS3StorageHAL());
    setRTCHAL(new PaperS3RTCHAL());
    setPowerHAL(new PaperS3PowerHAL());

    getDisplayHAL()->init();
    getTouchHAL()->init();
    getStorageHAL()->init();
    getRTCHAL()->init();
    getPowerHAL()->init();

    setEventService(new EventService());

    setApplicationRegistry(new ApplicationRegistry());
    setApplicationContext(new ApplicationContext(getDisplayHAL(), getLVRenderHAL(), getTouchHAL(), getStorageHAL(), getRTCHAL(), getPowerHAL(), getEventService(), getConfigService(), getTimerService()));
    setApplicationManager(new ApplicationManager(getApplicationRegistry(), getApplicationContext()));
}

void PaperS3::launch()
{
    getApplicationManager()->launchApp(0);
}

void PaperS3::update()
{
    // M5.update(); // Go to touchhal

    // Process touches
    getTouchHAL()->update();

    auto touch = getTouchHAL()->getNext();
    if (touch.gesture != eGestureType::NONE) {
        Event event;
        event.type = eEventType::TOUCH_EVENT;
        memcpy(event.data, &touch, sizeof(touch));
        event.timestamp = millis();
        getEventService()->postEvent(event);
    }

    // Update services
    getTimerService()->update();

    // Update and render app
    getApplicationManager()->update();
    getApplicationManager()->render();

    delay(10);
}

void PaperS3::powerOff()
{
}
