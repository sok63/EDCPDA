#pragma once

#include <string>

#include "AWidget.h"

class ToggleButton : public AWidget
{
public:
    ToggleButton(sRect size, std::string text, uint32_t text_size);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;
    bool is_pressed();

protected:
    bool pressed_ = false;
    std::string text_;
    uint32_t text_size_;
};