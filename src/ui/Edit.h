#pragma once

#include <string>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class Edit: public AWidget {
public:
    Edit(sRect size, char *text, uint32_t text_size_limit);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event &ev) override;

protected:
    bool pressed_ = false;
    uint32_t text_size_limit_;
    char* text_;
};