#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(ADisplayHAL *display, ALVRenderHAL *render, ATouchHAL *touch, AStorageHAL *storage, ARTCHAL *rtc, APowerHAL *power, EventService *eventService, ConfigService *configService, TimerService *timerService):
  display_(display), render_(render), touch_(touch), storage_(storage), rtc_(rtc), power_(power), eventService_(eventService), configService_(configService), timerService_(timerService) 
{
}

void ApplicationContext::setApplicationSprite(ADisplaySpriteHAL *sprite)
{
    application_sprite_ = sprite;
}

ADisplayHAL *ApplicationContext::getDisplay() const
{
    return display_;
}

ALVRenderHAL *ApplicationContext::getRender() const
{
    return render_;
}

ADisplaySpriteHAL *ApplicationContext::getApplicationSprite() const
{
    return application_sprite_;
}

ATouchHAL *ApplicationContext::getTouch() const
{
    return touch_;
}

AStorageHAL *ApplicationContext::getStorage() const
{
    return storage_;
}

ARTCHAL *ApplicationContext::getRTC() const
{
    return rtc_;
}

APowerHAL *ApplicationContext::getPower() const
{
    return power_;
}

EventService *ApplicationContext::getEventService() const
{
    return eventService_;
}

ConfigService *ApplicationContext::getConfigService() const
{
    return configService_;
}

TimerService *ApplicationContext::getTimerService() const
{
    return timerService_;
}
