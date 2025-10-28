#include "ApplicationRegistry.h"

ApplicationRegistry::ApplicationRegistry()
{
}

bool ApplicationRegistry::registerApp(AApplication *application)
{
    if(appCount_< LIMIT_MAX_APPS) return false;
    apps_[appCount_] = application;
    application->onCreate();
    return true;
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
