#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class MapsApp : public AApplication {
public:
    MapsApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~MapsApp() = default;
    
    void update(uint32_t deltaTime) override;
    void render() override;
    
    const char* getName() const override;
    const char* getDescription() const override;
    const uint8_t* getIcon() const override;
    
    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
    size_t selectedIndex_;
    size_t scrollOffset_;
    
    void drawMenu();
    void handleTouch(int16_t x, int16_t y);
};