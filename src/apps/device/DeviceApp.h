#include <pda/ApplicationManager.h>
#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

class DeviceApp : public AApplication
{
public:
    DeviceApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~DeviceApp() = default;

    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
};