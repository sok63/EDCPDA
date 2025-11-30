#pragma once

#include <pda/applications/AApplication.h>

#include <pda/ui/widgets/Button.h>
#include <pda/ui/widgets/Header.h>

#include "MapCalculator.h"

class MapsApp : public AApplication
{
public:
    static AApplication* createInstance();
    MapsApp();
    virtual ~MapsApp() = default;

    void update(uint32_t deltaTime) override;
    void render() override;

    static void drawIcon(ADisplaySpriteHAL*);

    bool onEvent(const Event& event) override;

private:
    MapCalculator calculator_;

    Button w_btn_more_details_;
    Button w_btn_less_details_;

    Header w_header_;
};