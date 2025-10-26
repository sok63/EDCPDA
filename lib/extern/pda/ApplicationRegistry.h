#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

struct AppInfo {
    const char* name;
    const char* description;
    AApplication* application;
    const uint8_t* icon;
};


class ApplicationRegistry {
private:
    static const size_t MAX_APPS = 16;
    AppInfo apps_[MAX_APPS];
    size_t appCount_ = 0;
    
public:
    ApplicationRegistry();
    
    bool registerApp(const char* name, const char* description, AApplication* application);
    size_t getAppCount() const { return appCount_; }
    const AppInfo& getAppInfo(size_t index) const { return apps_[index]; }
    AApplication* createApp(size_t index, ApplicationContext* context);
};