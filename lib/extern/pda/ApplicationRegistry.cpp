#include "ApplicationRegistry.h"

ApplicationRegistry::ApplicationRegistry()
{
}

bool ApplicationRegistry::registerApp(const char *name, const char *description, AApplication *application)
{
    return false;
}

size_t ApplicationRegistry::getAppCount() const
{
    return appCount_; 
}

const AppInfo &ApplicationRegistry::getAppInfo(size_t index) const
{
    return apps_[index]; 
}

AApplication *ApplicationRegistry::createApp(size_t index, ApplicationContext *context)
{
    return nullptr;
}
