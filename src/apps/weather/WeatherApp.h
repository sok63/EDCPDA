#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class WeatherApp : public AApplication {
public:
    WeatherApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~WeatherApp() = default;
    
    void update(uint32_t deltaTime) override;
    void render() override;
    
    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override; 
    
    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
};