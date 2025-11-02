#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class HeaderApplication : public AApplication {
public:
    HeaderApplication(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~HeaderApplication() = default;
    
    void update(uint32_t deltaTime) override;
    void render() override;
    
    const char* getName() const override;
    const char* getDescription() const override;
    const uint8_t* getIcon() const override;
    
    void onEvent(const Event& event) override;
private:
    void drawTimeBlock();
    void drawBatteryBlock();
    void drawDebugBlock();
    
private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
    size_t selectedIndex_;
    size_t scrollOffset_;
};