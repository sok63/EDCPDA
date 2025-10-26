#pragma once 

#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

struct AppInfo {
    const char* name;
    const char* description;
    AApplication* application;
    const uint8_t* icon;
};


class ApplicationRegistry {
public:
    ApplicationRegistry();
    
    bool registerApp(const char* name, const char* description, AApplication* application);
    size_t getAppCount() const;
    const AppInfo& getAppInfo(size_t index) const;
    AApplication* createApp(size_t index, ApplicationContext* context);

private:
    static const size_t MAX_APPS = 16;
    AppInfo apps_[MAX_APPS];
    size_t appCount_ = 0;
};