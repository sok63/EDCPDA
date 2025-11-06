#include "ADevice.h"

void ADevice::setApplicationContext(ApplicationContext *context)
{
    applicationContext_ = context;
}

void ADevice::setApplicationManager(ApplicationManager *manager)
{
    applicationManager_ = manager;
}

void ADevice::setApplicationRegistry(ApplicationRegistry *registry)
{
    applicationRegistry_ = registry;
}

ApplicationContext *ADevice::getApplicationContext()
{
    return applicationContext_;
}

ApplicationManager *ADevice::getApplicationManager()
{
    return applicationManager_;
}

ApplicationRegistry *ADevice::getApplicationRegistry()
{
    return applicationRegistry_;
}

void ADevice::registerApplication(AApplication *application)
{
    getApplicationRegistry()->registerApp(application);
}

void ADevice::setDisplayHAL(ADisplayHAL *displayHAL)
{
    displayHAL_ = displayHAL;
}

void ADevice::setLVRenderHAL(ALVRenderHAL *lvrenderHAL)
{
    lvrenderHAL_ = lvrenderHAL;
}

void ADevice::setTouchHAL(ATouchHAL *touchHAL)
{
    touchHAL_ = touchHAL;
}

void ADevice::setStorageHAL(AStorageHAL *storageHAL)
{
    storageHAL_ = storageHAL;
}

void ADevice::setRTCHAL(ARTCHAL *rtcHAL)
{
    rtcHAL_ = rtcHAL;
}

void ADevice::setPowerHAL(APowerHAL *powerHAL)
{
    powerHAL_ = powerHAL;
}

ADisplayHAL *ADevice::getDisplayHAL()
{
    return displayHAL_;
}

ALVRenderHAL *ADevice::getLVRenderHAL()
{
    return lvrenderHAL_;
}

ATouchHAL *ADevice::getTouchHAL()
{
    return touchHAL_;
}

AStorageHAL *ADevice::getStorageHAL()
{
    return storageHAL_;
}

ARTCHAL *ADevice::getRTCHAL()
{
    return rtcHAL_;
}

APowerHAL *ADevice::getPowerHAL()
{
    return powerHAL_;
}

void ADevice::setEventService(EventService *eventService)
{
    eventService_ = eventService;
}

void ADevice::setConfigService(ConfigService *configService)
{
    configService_ = configService;
}

void ADevice::setTimerService(TimerService *timerService)
{
    timerService_ = timerService;
}

EventService *ADevice::getEventService()
{
    return eventService_;
}

ConfigService *ADevice::getConfigService()
{
    return configService_;
}

TimerService *ADevice::getTimerService()
{
    return timerService_;
}
