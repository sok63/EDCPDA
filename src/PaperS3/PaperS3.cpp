#include "PaperS3.h"

#include "hal/PaperS3DisplayHAL.h"
#include "hal/PaperS3PowerHAL.h"
#include "hal/PaperS3RTCHAL.h"
#include "hal/PaperS3StorageHAL.h"
#include "hal/PaperS3TouchHAL.h"


// // Define serevices


// // Define Application stuff
// ApplicationContext appContext(&displayHal, &touchHal, &storageHal, &rtcHal, &powerHal, &eventService, &configService, &timerService);
// ApplicationRegistry appRegistry;
// ApplicationManager appManager(&appRegistry, &appContext);

void PaperS3::init()
{
    M5.begin();

    setDisplayHAL(new PaperS3DisplayHAL());
    setTouchHAL(new PaperS3TouchHAL());
    setStorageHAL(new PaperS3StorageHAL());
    setRTCHAL(new PaperS3RTCHAL());
    setPowerHAL(new PaperS3PowerHAL());

    getDisplayHAL()->init();
    getTouchHAL()->init();
    getStorageHAL()->init();
    getRTCHAL()->init();
    getPowerHAL()->init();

    setApplicationRegistry(new ApplicationRegistry());
    setApplicationContext(new ApplicationContext(getDisplayHAL(),getTouchHAL(),getStorageHAL(),getRTCHAL(),getPowerHAL(),getEventService(),getConfigService(),getTimerService()));    
    setApplicationManager(new ApplicationManager(getApplicationRegistry(),getApplicationContext()));

}

void PaperS3::launch()
{
    getApplicationManager()->launchApp(0);
}

void PaperS3::update()
{
    M5.update();
        
    // Process hardware events
    if (getTouchHAL()->available()) {
        TouchPoint point = getTouchHAL()->getPoint();
        Event event;
        event.type = point.pressed ? EventType::TOUCH_PRESS : EventType::TOUCH_RELEASE;
        event.data = &point;
        event.timestamp = millis();
        getEventService()->postEvent(event);
    }
    
    // Update services
    getTimerService()->update();
    getEventService()->processEvents();
    
    // Update and render app
    getApplicationManager()->update();
    getApplicationManager()->render();
    
    delay(10);
}

void PaperS3::powerOff()
{
}
