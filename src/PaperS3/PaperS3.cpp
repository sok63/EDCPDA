#include "PaperS3.h"

#include "hal/PaperS3DisplayHAL.h"
#include "hal/PaperS3PowerHAL.h"
#include "hal/PaperS3RTCHAL.h"
#include "hal/PaperS3StorageHAL.h"
#include "hal/PaperS3TouchHAL.h"

void PaperS3::init()
{

    auto cfg = M5.config();
    M5.begin(cfg);


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

    setEventService(new EventService());

    setApplicationRegistry(new ApplicationRegistry());
    setApplicationContext(new ApplicationContext(getDisplayHAL(),getTouchHAL(),getStorageHAL(),getRTCHAL(),getPowerHAL(),getEventService(),getConfigService(),getTimerService()));    
    setApplicationManager(new ApplicationManager(getApplicationRegistry(),getApplicationContext()));

    // Set default application sprite
    getApplicationContext()->setApplicationSprite(getDisplayHAL()->getNewSprite(540,930,1));

}

void PaperS3::launch()
{
    getApplicationManager()->launchApp(0);
}

void PaperS3::update()
{
    M5.update();
    
    // Process touches
    getTouchHAL()->update();
    auto touch = getTouchHAL()->getNext();
    if (touch.gesture!=eGestureType::NONE) {
        Event event;
        event.type = eEventType::TOUCH_EVENT;
        memcpy(event.data,&touch,sizeof(touch));
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
