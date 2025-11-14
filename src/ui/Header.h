#pragma once

#include <string>

#include <pda/apps/ApplicationContext.h>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class Header : public AWidget
{
public:
    Header(ApplicationContext* context);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

private:
    ApplicationContext* context_;
};