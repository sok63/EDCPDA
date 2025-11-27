#pragma once

#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>

#include <pda/ui/widgets/Header.h>
#include <pda/ui/widgets/Button.h>

#include "MapCalculator.h"

class MapsApp : public AApplication
{
public:
    MapsApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~MapsApp() = default;

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

    MapCalculator calculator_;

Button w_btn_more_details_;
Button w_btn_less_details_;

    //double center_lat_ = 55.80592346;
    //double center_lon_ = 37.75491055;
    //int z_ = 14;

    Header w_header_;

};