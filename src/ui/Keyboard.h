#pragma once

#include <string>
#include <vector>

#include "AWidget.h"
#include <pda/events/EventService.h>

#define EDIT_LIM_SIZE 30

struct Key
{
    std::string label;
    float units;
};

struct KeyRectInfo
{
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
};

class Keyboard : public AWidget
{
public:
    Keyboard(EventService* event_service);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

    bool feed_event(const Event& ev) override;

    void calc_keyRectInfo(std::vector<Key>& row, uint32_t row_num, uint32_t cidx);
    char get_char();

protected:
    void post_event();

    char ch_ = '\0';
    bool pressed_ = false;
    uint32_t position_;
    sRect key_rect_info_;
    char text_[EDIT_LIM_SIZE];
    EventService* event_service_ = nullptr;
};