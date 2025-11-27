#pragma once

#include <string>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class Edit : public AWidget
{
public:
    Edit(sRect size, uint32_t text_size_limit);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

    void set_selection(bool);
    char* get_text_();

protected:
    bool selected_ = false;
    uint32_t text_size_limit_;
    uint32_t text_pos_ = 0;
    char* text_;
};