#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class SafePassApp : public AApplication {
public:
    SafePassApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~SafePassApp() = default;
    
    void update(uint32_t deltaTime) override;
    void render() override;
    
    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override; 
    
    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
};