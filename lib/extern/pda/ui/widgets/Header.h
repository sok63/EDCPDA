#pragma once

#include <string>

#include <pda/applications/ApplicationContext.h>
#include <pda/applications/ApplicationManager.h>

#include <pda/ui/widgets/AWidget.h>

#define HEADER_SIZE 30

class Header : public AWidget
{
public:
    Header(ApplicationContext* context, ApplicationManager* appManager);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

private:
    ApplicationContext* context_;
    ApplicationManager* app_manager_;

    uint64_t last_draw_ = 0;
};