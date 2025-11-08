#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>

class PassGenApp : public AApplication {
public:
    PassGenApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~PassGenApp() = default;
    
    void update(uint32_t deltaTime) override;
    void render() override;
    
    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override; 
    
    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
};