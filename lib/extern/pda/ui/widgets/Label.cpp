#include "Label.h"

Label::Label(sRect size, std::string text, uint16_t text_size)
    : AWidget(size)
    , text_(text)
    , text_size_(text_size)
{
}

void Label::update()
{
}

void Label::render(ADisplaySpriteHAL* to)
{
    // For debug uncmment to show rect: to->drawRect(size_.x,size_.y,size_.w,size_.h,0);

    auto tw = to->getTextWidth(text_.c_str(), text_size_);
    auto th = to->getTextHeight(text_.c_str(), text_size_);
    to->drawText(size_.x + (size_.w - tw) / 2, size_.y + (size_.h - th) / 2, text_.c_str(), 0, text_size_);
}
