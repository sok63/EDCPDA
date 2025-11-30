#pragma once

#include <string>

#include <pda/ui/widgets/AWidget.h>

#define HEADER_SIZE 30

class Header : public AWidget
{
public:
    Header();

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

private:
    uint64_t last_draw_ = 0;
};