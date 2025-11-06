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
    void drawIconTo(ADisplaySpriteHAL*) override; 

    bool onEvent(const Event& event) override;
private:
    
    void drawCollapsedTimeBlock();
    void drawCollapsedBatteryBlock();
    void drawCollapsedDebugBlock();
    
private:
    bool extended_ = false;

    uint64_t last_redraw_ = 0;

    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
    ADisplaySpriteHAL* sprite_collapsed_ = nullptr;
    ADisplaySpriteHAL* sprite_extended_ = nullptr;

    size_t selectedIndex_;
    size_t scrollOffset_;
};