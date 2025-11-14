#pragma once

#include "apps/AApplication.h"
#include "apps/ApplicationContext.h"
#include "defines.h"

class ApplicationRegistry
{
public:
    ApplicationRegistry();

    uint16_t registerApp(AApplication* application);
    size_t getAppCount() const;
    AApplication* getApplication(size_t index) const;

private:
    AApplication* apps_[LIMIT_MAX_APPS];
    size_t appCount_ = 0;
};