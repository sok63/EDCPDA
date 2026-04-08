#pragma once

#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>
#include <pda/ui/widgets/Header.h>

class CalendarApp : public AApplication
{
public:
    CalendarApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~CalendarApp() = default;

    void onStart() override;
    void onStop() override;

    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    Header w_header_;

    int view_month_;
    int view_year_;
};
