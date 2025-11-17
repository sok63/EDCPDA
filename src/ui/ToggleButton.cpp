#include "ToggleButton.h"
#include "M5Unified.h"

#include <pda/apps/ApplicationContext.h>

ToggleButton::ToggleButton(sRect size, std::string text, uint32_t text_size)
    : AWidget(size)
    , text_(text)
    , text_size_(text_size)
{
}

void ToggleButton::update()
{
}

void ToggleButton::render(ADisplaySpriteHAL* sprite)
{
    auto tw = sprite->getTextWidth(text_.c_str(), text_size_);
    auto th = sprite->getTextHeight(text_.c_str(), text_size_);

    if (pressed_) {
        sprite->drawFillRect(size_.x, size_.y, size_.w, size_.h, TFT_BLACK);
        sprite->drawText(size_.x + size_.w / 2 - tw / 2, size_.y + size_.h / 2 - th / 2, text_.c_str(), TFT_WHITE, text_size_);
    } else {
        sprite->drawFillRect(size_.x, size_.y, size_.w, size_.h, TFT_WHITE);
        sprite->drawRect(size_.x, size_.y, size_.w, size_.h, 0);
        sprite->drawText(size_.x + size_.w / 2 - tw / 2, size_.y + size_.h / 2 - th / 2, text_.c_str(), 0, text_size_);
    }
}

bool ToggleButton::feed_event(const Event& event)
{
    if (event.type != eEventType::TOUCH_EVENT)
        return false;

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));
    if ((touch->gesture != eGestureType::ONEF_TAP) and (touch->gesture != eGestureType::ONEF_DOUBLE_TAP))
        return false;

    if (check_hit(size_, touch->startX, touch->startY)) {
        pressed_ = !pressed_;
        set_dirty_flag();
        return true;
    }

    return false;
}

bool ToggleButton::is_pressed()
{
    return pressed_;
}

void ToggleButton::set_pressed()
{
    pressed_ = true;
}
