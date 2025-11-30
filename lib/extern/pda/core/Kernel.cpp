#include "Kernel.h"

Kernel* Kernel::getInstance()
{
    static Kernel instance;
    return &instance;
}

void Kernel::setApplicationFactory(AppFactory* application_factory)
{
    getInstance()->application_factory_ = application_factory;
}

AppFactory* Kernel::getApplicationFactory()
{
    return getInstance()->application_factory_;
}

void Kernel::setApplication(uint32_t application_id)
{
    auto kernel = getInstance();
    kernel->application_ = kernel->application_factory_->create(application_id);
    Kernel::getEventService()->addListener(kernel->application_);
    Kernel::getDisplay()->setNeedRedraw();
}

AApplication* Kernel::getApplication()
{
    return getInstance()->application_;
}

AppDescriptor* Kernel::getApplicationDescriptor(uint32_t id)
{

    auto kernel = getInstance();
    return kernel->application_factory_->getById(id);
}

void Kernel::exitApplication()
{
    auto app = getInstance()->application_;
    if (!app) {
        return;
    }
    Kernel::getEventService()->removeListener(getInstance()->application_);
    delete app;
    getInstance()->application_ = nullptr;
}

void Kernel::setDisplay(ADisplayHAL* display)
{
    getInstance()->display_ = display;
}

ADisplayHAL* Kernel::getDisplay()
{
    return getInstance()->display_;
}

void Kernel::setRender(ALVRenderHAL* render)
{
    getInstance()->render_ = render;
}

ALVRenderHAL* Kernel::getRender()
{
    return getInstance()->render_;
}

void Kernel::setTouch(ATouchHAL* touch)
{
    getInstance()->touch_ = touch;
}

ATouchHAL* Kernel::getTouch()
{
    return getInstance()->touch_;
}

void Kernel::setStorage(AStorageHAL* storage)
{
    getInstance()->storage_ = storage;
}

AStorageHAL* Kernel::getStorage()
{
    return getInstance()->storage_;
}

void Kernel::setRTC(ARTCHAL* rtc)
{
    getInstance()->rtc_ = rtc;
}

ARTCHAL* Kernel::getRTC()
{
    return getInstance()->rtc_;
}

void Kernel::setPower(APowerHAL* power)
{
    getInstance()->power_ = power;
}

APowerHAL* Kernel::getPower()
{
    return getInstance()->power_;
}

void Kernel::setEventService(EventService* event_service)
{
    getInstance()->event_service_ = event_service;
}

EventService* Kernel::getEventService()
{
    return getInstance()->event_service_;
}

void Kernel::setConfigService(ConfigService* config_service)
{
    getInstance()->config_service_ = config_service;
}

ConfigService* Kernel::getConfigService()
{
    return getInstance()->config_service_;
}

void Kernel::setTimerService(TimerService* timer_service)
{
    getInstance()->timer_service_ = timer_service;
}

TimerService* Kernel::getTimerService()
{
    return getInstance()->timer_service_;
}
