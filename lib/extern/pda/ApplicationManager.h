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
    
    ApplicationRegistry* getRegistry();

private:
    ApplicationRegistry* registry_;
    ApplicationContext* context_;
    
    AApplication* currentApp_;
    AApplication* nextApp_;
    
    AppState currentAppState_;
    
    uint32_t lastUpdateTime_;
    
    void transitionApp();
};