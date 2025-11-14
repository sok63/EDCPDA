#pragma once 

#include <pda/hal/ADisplayHAL.h>
#include <pda/hal/ALVRenderHAL.h>
#include <pda/hal/ATouchHAL.h>
#include <pda/hal/AStorageHAL.h>
#include <pda/hal/ARTCHAL.h>
#include <pda/hal/APowerHAL.h>

#include <pda/events/EventService.h>
#include <pda/sal/ConfigService.h>
#include <pda/sal/TimeService.h>


class ApplicationContext {
public:
    ApplicationContext(ADisplayHAL* display, ALVRenderHAL* render, ATouchHAL* touch,
               AStorageHAL* storage, ARTCHAL* rtc, APowerHAL* power, EventService* eventService,
               ConfigService* configService, TimerService* timerService);
    
    ADisplayHAL* getDisplay() const;
    ALVRenderHAL* getRender() const;
    ATouchHAL* getTouch() const;
    AStorageHAL* getStorage() const;
    ARTCHAL* getRTC() const; 
    APowerHAL* getPower() const; 
    EventService* getEventService() const;
    ConfigService* getConfigService() const;
    TimerService* getTimerService() const;

private:
    ADisplayHAL* display_;
    ALVRenderHAL* render_;
    ADisplaySpriteHAL* application_sprite_ = nullptr;
    ATouchHAL* touch_;
    AStorageHAL* storage_;
    ARTCHAL* rtc_;
    APowerHAL* power_;
    EventService* eventService_;
    ConfigService* configService_;
    TimerService* timerService_;
};