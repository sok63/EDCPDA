#pragma

#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationFactory.h>

#include <pda/hal/interfaces/ADisplayHAL.h>
#include <pda/hal/interfaces/ALVRenderHAL.h>
#include <pda/hal/interfaces/APowerHAL.h>
#include <pda/hal/interfaces/ARTCHAL.h>
#include <pda/hal/interfaces/AStorageHAL.h>
#include <pda/hal/interfaces/ATouchHAL.h>

#include <pda/core/events/EventService.h>

#include <pda/sal/ConfigService.h>
#include <pda/sal/TimeService.h>

class Kernel
{
public:
    static Kernel* getInstance();

    // Application factory
    static void setApplicationFactory(AppFactory* application_factory);
    static AppFactory* getApplicationFactory();

    // Application
    static void setApplication(uint32_t application_id);
    static AApplication* getApplication();
    static AppDescriptor* getApplicationDescriptor(uint32_t id);
    static void exitApplication();

    // Context
    static void setDisplay(ADisplayHAL* display);
    static ADisplayHAL* getDisplay();

    static void setRender(ALVRenderHAL* render);
    static ALVRenderHAL* getRender();

    static void setTouch(ATouchHAL* touch);
    static ATouchHAL* getTouch();

    static void setStorage(AStorageHAL* storage);
    static AStorageHAL* getStorage();

    static void setRTC(ARTCHAL* rtc);
    static ARTCHAL* getRTC();

    static void setPower(APowerHAL* power);
    static APowerHAL* getPower();

    static void setEventService(EventService* event_service);
    static EventService* getEventService();

    static void setConfigService(ConfigService* config_service);
    static ConfigService* getConfigService();

    static void setTimerService(TimerService* timer_service);
    static TimerService* getTimerService();

private:
    Kernel() = default;
    Kernel(Kernel const&) = delete;
    void operator=(Kernel const&) = delete;

    // Application factory
    AppFactory* application_factory_ = nullptr;

    // Current application
    AApplication* application_ = nullptr;

    // Context
    ADisplayHAL* display_ = nullptr;
    ALVRenderHAL* render_ = nullptr;
    ADisplaySpriteHAL* application_sprite_ = nullptr;
    ATouchHAL* touch_ = nullptr;
    AStorageHAL* storage_ = nullptr;
    ARTCHAL* rtc_ = nullptr;
    APowerHAL* power_ = nullptr;
    EventService* event_service_ = nullptr;
    ConfigService* config_service_ = nullptr;
    TimerService* timer_service_ = nullptr;
};