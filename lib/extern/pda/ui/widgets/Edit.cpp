#include "Edit.h"
#include <cstring>

#include "M5Unified.h"

Edit::Edit(sRect size, uint32_t text_size_limit)
    : AWidget(size)
    , text_size_limit_(text_size_limit)
    , text_(new char[text_size_limit])
{
    text_[0] = 0;
}

void Edit::update()
{
}

void Edit::render(ADisplaySpriteHAL* sprite)
{
    auto th = sprite->getTextHeight(text_, 3);

    sprite->drawRect(size_.x, size_.y, size_.w, size_.h, 0);
    sprite->drawText(10 + size_.x, size_.y + (size_.h - th) / 2, text_, 0, 3);
}

bool Edit::feed_event(const Event& ev)
{

    if (!selected_)
        return false;
    if (ev.type != eEventType::KEY_CHAR_EVENT)
        return false;

    Serial.println("recv1");

    text_[text_pos_] = ev.data[0];
    text_pos_++;
    text_[text_pos_] = 0;

    set_dirty_flag();

    return true;
}

void Edit::set_selection(bool val)
{
    selected_ = val;
}

char* Edit::get_text_()
{
    return text_;
}
