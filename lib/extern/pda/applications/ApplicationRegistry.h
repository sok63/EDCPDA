#pragma once

#include "pda/applications/AApplication.h"
#include "pda/applications/ApplicationContext.h"
#include "pda/defines.h"

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