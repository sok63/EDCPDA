#pragma once 

#include <pda/defines.h>
#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

class ApplicationRegistry {
public:
    ApplicationRegistry();
    
    bool registerApp(AApplication* application);
    size_t getAppCount() const;
    AApplication* getApplication(size_t index) const;

private:
    AApplication* apps_[LIMIT_MAX_APPS];
    size_t appCount_ = 0;
};