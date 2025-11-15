#include "Button.h"

#include <pda/apps/ApplicationContext.h>
#include <pda/core/TouchPrimitives.h>

Button::Button(sRect size, std::string text, uint32_t text_size)
    : AWidget(size)
    , text_(text)
    , text_size_(text_size)
{
}

void Button::update()
{
}

void Button::render(ADisplaySpriteHAL* sprite)
{
    sprite->drawRect(size_.x, size_.y, size_.w, size_.h, 0);

    auto tw = sprite->getTextWidth(text_.c_str(), text_size_);
    auto th = sprite->getTextHeight(text_.c_str(), text_size_);

    sprite->drawText(size_.x + size_.w / 2 - tw / 2, size_.y + size_.h / 2 - th / 2, text_.c_str(), 0, text_size_);
}

bool Button::feed_event(const Event& event)
{

    if (event.type != eEventType::TOUCH_EVENT)
        return false;

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));
    if ((touch->gesture != eGestureType::ONEF_TAP) and (touch->gesture != eGestureType::ONEF_DOUBLE_TAP))
        return false;

    if (check_hit(size_, touch->startX, touch->startY)) {
        pressed_ = true;
        return true;
    }

    return false;
}

bool Button::is_pressed()
{
    auto result = pressed_;
    pressed_ = false;
    return result;
}
