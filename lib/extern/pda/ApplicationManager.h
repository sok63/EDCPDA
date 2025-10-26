#include "ApplicationRegistry.h"

#include "apps/ApplicationContext.h"
#include "apps/AApplication.h"

class ApplicationManager {
private:
    ApplicationRegistry* registry_;
    ApplicationContext* context_;
    
    AApplication* currentApp_;
    AApplication* nextApp_;
    
    enum class AppState {
        CREATED,
        STARTED,
        RESUMED,
        PAUSED,
        STOPPED,
        DESTROYED
    };
    
    AppState currentAppState_;
    
    uint32_t lastUpdateTime_;
    
    void transitionApp();
    
public:
    ApplicationManager(ApplicationRegistry* registry, ApplicationContext* context);
    ~ApplicationManager();
    
    void init();
    void launchApp(size_t appIndex);
    void exitCurrentApp();
    bool isAppRunning() const { return currentApp_ != nullptr; }
    
    void update();
    void render();
    
    ApplicationRegistry* getRegistry() { return registry_; }
};