#pragma once 

#include "ApplicationRegistry.h"

#include "apps/ApplicationContext.h"
#include "apps/AApplication.h"

enum class AppState {
    CREATED,
    STARTED,
    RESUMED,
    PAUSED,
    STOPPED,
    DESTROYED
};

class ApplicationManager {
public:
    ApplicationManager(ApplicationRegistry* registry, ApplicationContext* context);
    ~ApplicationManager();
    
    void init();
    void launchApp(size_t appIndex);
    void exitCurrentApp();
    bool isAppRunning() const;
    
    void update();
    void render();
    
    ApplicationRegistry* getApplicationRegistry();

private:
    ApplicationRegistry* applicationRegistry_;
    ApplicationContext* applicationContext_;
    
    size_t currentApp_ = 0;
    
    AppState currentAppState_;
    
    uint32_t lastUpdateTime_;
    
    void transitionApp();
};