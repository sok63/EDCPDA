#include "ApplicationRegistry.h"

ApplicationRegistry::ApplicationRegistry()
{
}

uint16_t ApplicationRegistry::registerApp(AApplication *application)
{
    apps_[appCount_] = application;
    appCount_+=1;
    application->onCreate();
    return appCount_ - 1;
}

size_t ApplicationRegistry::getAppCount() const
{
    return appCount_; 
}

AApplication *ApplicationRegistry::getApplication(size_t index) const
{
    if(index > appCount_) return nullptr;
    if(index >= LIMIT_MAX_APPS) return nullptr;
    return apps_[index];
}
