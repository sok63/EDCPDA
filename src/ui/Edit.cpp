#include "Edit.h"
#include <cstring>

Edit::Edit(sRect size, char* text, uint32_t text_size_limit)
    : AWidget(size)
    , text_size_limit_(text_size_limit)
    , text_(text)
{
}

void Edit::update()
{
}

void Edit::render(ADisplaySpriteHAL* sprite)
{
    auto th = sprite->getTextHeight(text_, 3);

    sprite->drawRect(size_.x, size_.y, size_.w, size_.h, 0);
    sprite->drawText(size_.x, size_.y + (size_.h - th) / 2, text_, 0, 3);
}

bool Edit::feed_event(const Event& ev)
{
    return false;
}
