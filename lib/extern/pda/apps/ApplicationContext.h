#include <pda/hal/ADisplayHAL.h>
#include <pda/hal/ATouchHAL.h>
#include <pda/hal/AStorageHAL.h>
#include <pda/hal/ARTCHAL.h>
#include <pda/hal/APowerHAL.h>

#include <pda/sal/EventService.h>
#include <pda/sal/ConfigService.h>
#include <pda/sal/TimeService.h>


class ApplicationContext {
private:
    ADisplayHAL* display_;
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
    
    ADisplayHAL* getDisplay() const { return display_; }
    ATouchHAL* getTouch() const { return touch_; }
    AStorageHAL* getStorage() const { return storage_; }
    ARTCHAL* getRTC() const { return rtc_; }
    APowerHAL* getPower() const { return power_; }
    EventService* getEventService() const { return eventService_; }
    ConfigService* getConfigService() const { return configService_; }
    TimerService* getTimerService() const { return timerService_; }
};