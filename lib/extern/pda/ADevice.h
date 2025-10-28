#pragma once

#include <pda/ApplicationManager.h>
#include <pda/ApplicationRegistry.h>

class ADevice {
public:
    virtual ~ADevice() = default;

    virtual void init() = 0;
    void registerApplication(AApplication*);
    virtual void launch() =0;

    virtual void update() = 0;
    virtual void powerOff() =0;

public:
    void setDisplayHAL(ADisplayHAL*);
    void setTouchHAL(ATouchHAL*);
    void setStorageHAL(AStorageHAL*);
    void setRTCHAL(ARTCHAL*);
    void setPowerHAL(APowerHAL*);

    ADisplayHAL* getDisplayHAL();
    ATouchHAL*   getTouchHAL();
    AStorageHAL* getStorageHAL();
    ARTCHAL*     getRTCHAL();
    APowerHAL*  getPowerHAL();
    
    void setEventService(EventService*);
    void setConfigService(ConfigService*);
    void setTimerService(TimerService*);
    
    EventService* getEventService();
    ConfigService* getConfigService();
    TimerService* getTimerService();

    void setApplicationContext(ApplicationContext*);
    void setApplicationManager(ApplicationManager*);
    void setApplicationRegistry(ApplicationRegistry*);

    ApplicationContext*  getApplicationContext();
    ApplicationManager*  getApplicationManager();
    ApplicationRegistry* getApplicationRegistry();

protected:
    ADisplayHAL* displayHAL_ = nullptr;
    ATouchHAL*   touchHAL_   = nullptr;
    AStorageHAL* storageHAL_ = nullptr;
    ARTCHAL*     rtcHAL_     = nullptr;
    APowerHAL*   powerHAL_   = nullptr;

    EventService* eventService_   = nullptr;
    ConfigService* configService_ = nullptr;
    TimerService* timerService_   = nullptr;

    ApplicationContext*  applicationContext_  = nullptr;
    ApplicationManager*  applicationManager_  = nullptr;
    ApplicationRegistry* applicationRegistry_ = nullptr;
};