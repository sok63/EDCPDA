#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>

class ReaderApp : public AApplication
{
public:
    ReaderApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~ReaderApp() = default;

    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;

    size_t selectedIndex_;
    size_t scrollOffset_;
};