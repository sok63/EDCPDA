#pragma once

#include <string>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class Label : public AWidget
{
public:
    Label(sRect size, std::string text, uint16_t text_size);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

protected:
    uint32_t text_size_;
    std::string text_;
};