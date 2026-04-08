#include "Edit.h"
#include <cstring>

#include "M5Unified.h"

Edit::Edit(sRect size, uint32_t text_size_limit)
    : AWidget(size)
    , text_size_limit_(text_size_limit)
    , text_(new char[text_size_limit])
    , text_pos_(0)
    , selected_(false)
{
    text_[0] = 0;
}

Edit::~Edit()
{
    delete[] text_;
}

void Edit::update()
{
}

void Edit::render(ADisplaySpriteHAL* sprite)
{
    // Clear background (fill with white)
    sprite->drawFillRect(size_.x, size_.y, size_.w, size_.h, TFT_WHITE);
    // Draw border
    sprite->drawRect(size_.x, size_.y, size_.w, size_.h, 0);
    
    auto th = sprite->getTextHeight(text_, 3);
    // Draw text
    sprite->drawText(10 + size_.x, size_.y + (size_.h - th) / 2, text_, 0, 3);
    // Draw cursor if selected
    if (selected_) {
        int textWidth = sprite->getTextWidth(text_, 3);
        int cursorX = 10 + size_.x + textWidth;
        sprite->drawLine(cursorX, size_.y + 2, cursorX, size_.y + size_.h - 2, 0);
    }
}

bool Edit::feed_event(const Event& ev)
{
    if (!selected_)
        return false;
    if (ev.type != eEventType::KEY_CHAR_EVENT)
        return false;

    Serial.println("recv1");

    bool changed = false;
    // Handle backspace
    if (ev.data[0] == '\b') {
        if (text_pos_ > 0) {
            text_pos_--;
            text_[text_pos_] = 0;
            changed = true;
        }
    } else {
        // Handle regular character
        if (text_pos_ < text_size_limit_ - 1) {
            text_[text_pos_] = ev.data[0];
            text_pos_++;
            text_[text_pos_] = 0;
            changed = true;
        }
    }
    if (changed) {
        set_dirty_flag();
        // Force immediate redraw by marking the widget as dirty
        // The dirty flag will be taken during the next render cycle
    }
    return true;
}

void Edit::set_selection(bool val)
{
    selected_ = val;
    set_dirty_flag(); // Force redraw to show/hide cursor
}

char* Edit::get_text_()
{
    return text_;
}
