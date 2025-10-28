#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class MenuApp : public AApplication {
public:
    MenuApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~MenuApp() = default;
    
    void onCreate() override;
    void onStart() override;
    void onResume() override;
    void onPause() override;
    void onStop() override;
    
    void update(uint32_t deltaTime) override;
    void render(ADisplayHAL* display) override;
    
    const char* getName() const override;
    const char* getDescription() const override;
    const uint8_t* getIcon() const override;
    
    void onEvent(const Event& event) override;
    
    static AApplication* create(ApplicationContext* context);

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
    size_t selectedIndex_;
    size_t scrollOffset_;
    
    void drawMenu();
    void handleTouch(int16_t x, int16_t y);
    

};