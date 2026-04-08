#pragma once

#include <string>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class Edit : public AWidget
{
public:
    Edit(sRect size, uint32_t text_size_limit);
    ~Edit() override;

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

    void set_selection(bool);
    char* get_text_();

private:
    uint32_t text_size_limit_;
    char* text_;
    uint32_t text_pos_;
    bool selected_;
};
