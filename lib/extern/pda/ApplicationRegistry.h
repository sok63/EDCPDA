#pragma once 

#include "defines.h"
#include "apps/AApplication.h"
#include "apps/ApplicationContext.h"

class ApplicationRegistry {
public:
    ApplicationRegistry();
    
    bool registerApp(AApplication* application);
    void setHeaderApplication(AApplication* applicaiton);
    size_t getAppCount() const;
    AApplication* getApplication(size_t index) const;
    AApplication* getHeaderApplication() const;

private:
    AApplication* apps_[LIMIT_MAX_APPS];
    AApplication* header_ = nullptr;
    size_t appCount_ = 0;
};