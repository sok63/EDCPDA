#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>

class SafePassApp : public AApplication
{
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