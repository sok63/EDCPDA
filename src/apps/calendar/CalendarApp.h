#include <pda/ApplicationManager.h>
#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

class CalendarApp : public AApplication
{
public:
    CalendarApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~CalendarApp() = default;

    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
};