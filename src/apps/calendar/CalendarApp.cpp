#include "CalendarApp.h"
#include <cstdio>

CalendarApp::CalendarApp(ApplicationContext* context,
                         ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
    , w_header_(context, appManager)
    , view_month_(-1)
    , view_year_(-1)
{
}

void CalendarApp::onStart()
{
    context_->getEventService()->addListener(this);
    auto dt = context_->getRTC()->getDateTime();
    view_month_ = dt.month;
    view_year_ = dt.year;
    context_->getDisplay()->setNeedRedraw();
}

void CalendarApp::onStop()
{
    context_->getEventService()->removeListener(this);
}

void CalendarApp::update(uint32_t deltaTime)
{
    static int last_day = -1;
    auto dt = context_->getRTC()->getDateTime();

    w_header_.update();
    bool header_dirty = w_header_.take_dirty_flag();

    bool day_changed = (dt.day != last_day);
    if (day_changed) {
        last_day = dt.day;
    }

    if (day_changed && view_month_ == dt.month && view_year_ == dt.year) {
        context_->getDisplay()->setNeedRedraw();
    } else if (header_dirty) {
        w_header_.render(context_->getDisplay());
    }
}

void CalendarApp::render()
{
    auto display = context_->getDisplay();
    display->clear();

    w_header_.render(display);

    auto dt = context_->getRTC()->getDateTime();

    char title[64];
    const char* monthNames[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};
    
    if (view_month_ >= 0 && view_month_ <= 11) {
        sprintf(title, "%s %04d", monthNames[view_month_], view_year_);
    } else {
        sprintf(title, "Month %d %04d", view_month_, view_year_);
    }

    uint32_t titleWidth = display->getTextWidth(title, 4);
    display->drawText((540 - titleWidth) / 2, 60, title, 0, 4);

    const char* dow[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
    int startX = 25;
    int startY = 140;
    int cellW = 70;
    int cellH = 90;

    for (int i = 0; i < 7; ++i) {
        uint32_t w = display->getTextWidth(dow[i], 3);
        display->drawText(startX + i * cellW + (cellW - w) / 2, startY, dow[i], 0, 3);
    }

    int daysInMonth = 31;
    if (view_month_ == 3 || view_month_ == 5 || view_month_ == 8 || view_month_ == 10) {
        daysInMonth = 30;
    } else if (view_month_ == 1) {
        bool isLeap = (view_year_ % 4 == 0 && view_year_ % 100 != 0) || (view_year_ % 400 == 0);
        daysInMonth = isLeap ? 29 : 28;
    }

    int m = view_month_ + 1;
    int y = view_year_;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (1 + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    int firstDayDow = (h + 5) % 7;

    int gridY = startY + 50;

    display->drawLine(startX, startY - 10, startX + 7 * cellW, startY - 10, 0);
    for (int i = 0; i <= 6; ++i) {
        display->drawLine(startX, gridY + i * cellH, startX + 7 * cellW, gridY + i * cellH, 0);
    }
    for (int i = 0; i <= 7; ++i) {
        display->drawLine(startX + i * cellW, startY - 10, startX + i * cellW, gridY + 6 * cellH, 0);
    }

    for (int day = 1; day <= daysInMonth; ++day) {
        int pos = firstDayDow + (day - 1);
        int row = pos / 7;
        int col = pos % 7;

        int x = startX + col * cellW;
        int y_pos = gridY + row * cellH;

        if (day == dt.day && view_month_ == dt.month && view_year_ == dt.year) {
            display->drawRoundRect(x + 5, y_pos + 5, cellW - 10, cellH - 40, 5, 0);
            display->drawRoundRect(x + 6, y_pos + 6, cellW - 12, cellH - 42, 4, 0);
        }

        char dayStr[4];
        sprintf(dayStr, "%d", day);
        uint32_t dw = display->getTextWidth(dayStr, 3);
        display->drawText(x + (cellW - dw) / 2, y_pos + 15, dayStr, 0, 3);
    }
}

const char* CalendarApp::getName() const
{
    return "Calendar";
}

void CalendarApp::drawIconTo(ADisplaySpriteHAL* sprite)
{
    auto render = context_->getRender();

    render->apply_draw_indexed_rect(sprite, 15, 15, 50, 50, 1, 0);

    render->apply_draw_indexed_rect(sprite, 25, 8, 8, 15, 1, 0);
    render->apply_draw_indexed_rect(sprite, 45, 8, 8, 15, 1, 0);

    auto dt = context_->getRTC()->getDateTime();

    const char* shortDow[] = {"SU", "MO", "TU", "WE", "TH", "FR", "SA"};
    int wd = dt.weekDay % 7;
    render->apply_draw_indexed_text(sprite, 28, 28, shortDow[wd], 0, 2);

    char timeStr[3];
    sprintf(timeStr, "%02d", dt.day);
    render->apply_draw_indexed_text(sprite, 28, 48, timeStr, 0, 2);
}

bool CalendarApp::onEvent(const Event& event)
{
    if (w_header_.feed_event(event)) {
        return true;
    }

    if (event.type == eEventType::TOUCH_EVENT) {
        sTouchEvent* touch = (sTouchEvent*)(&event.data);
        if (touch->gesture == eGestureType::ONEF_SWIPE_LEFT) {
            view_month_++;
            if (view_month_ > 11) {
                view_month_ = 0;
                view_year_++;
            }
            context_->getDisplay()->setNeedRedraw();
            return true;
        } else if (touch->gesture == eGestureType::ONEF_SWIPE_RIGHT) {
            view_month_--;
            if (view_month_ < 0) {
                view_month_ = 11;
                view_year_--;
            }
            context_->getDisplay()->setNeedRedraw();
            return true;
        }
    }
    
    return false;
}
