#pragma once 

#include <pda/hal/ADisplayHAL.h>
#include <pda/hal/ATouchHAL.h>
#include <pda/hal/AStorageHAL.h>
#include <pda/hal/ARTCHAL.h>
#include <pda/hal/APowerHAL.h>

#include <pda/events/EventService.h>
#include <pda/sal/ConfigService.h>
#include <pda/sal/TimeService.h>


class ApplicationContext {
private:
    ADisplayHAL* display_;
    ADisplaySpriteHAL* application_sprite_ = nullptr;
    ATouchHAL* touch_;
    AStorageHAL* storage_;
    ARTCHAL* rtc_;
    APowerHAL* power_;
    EventService* eventService_;
    ConfigService* configService_;
    TimerService* timerService_;
    
public:
    ApplicationContext(ADisplayHAL* display, ATouchHAL* touch, AStorageHAL* storage,
               ARTCHAL* rtc, APowerHAL* power, EventService* eventService,
               ConfigService* configService, TimerService* timerService);
    
    void setApplicationSprite(ADisplaySpriteHAL*);

    ADisplayHAL* getDisplay() const;
    ADisplaySpriteHAL* getApplicationSprite() const;
    ATouchHAL* getTouch() const;
    AStorageHAL* getStorage() const;
    ARTCHAL* getRTC() const; 
    APowerHAL* getPower() const; 
    EventService* getEventService() const;
    ConfigService* getConfigService() const;
    TimerService* getTimerService() const;
};