#include "CalendarApp.h"
#include <cstdio>

CalendarApp::CalendarApp(ApplicationContext* context,
                         ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
    , w_header_(context, appManager)
{
}

void CalendarApp::onStart()
{
    context_->getEventService()->addListener(this);
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

    if (dt.day != last_day || w_header_.take_dirty_flag()) {
        context_->getDisplay()->setNeedRedraw();
        last_day = dt.day;
    }
}

void CalendarApp::render()
{
    auto display = context_->getDisplay();
    display->clear();

    w_header_.render(display);

    auto dt = context_->getRTC()->getDateTime();

    char title[64];
    const char* monthNames[] = {"", "January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};
    if (dt.month >= 1 && dt.month <= 12) {
        sprintf(title, "%s %04d", monthNames[dt.month], dt.year);
    } else {
        sprintf(title, "Month %d %04d", dt.month, dt.year);
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
    if (dt.month == 4 || dt.month == 6 || dt.month == 9 || dt.month == 11) {
        daysInMonth = 30;
    } else if (dt.month == 2) {
        bool isLeap = (dt.year % 4 == 0 && dt.year % 100 != 0) || (dt.year % 400 == 0);
        daysInMonth = isLeap ? 29 : 28;
    }

    int currentDow = (dt.weekDay + 6) % 7; 
    int firstDayDow = (currentDow - (dt.day - 1) % 7 + 7) % 7;

    int gridY = startY + 50;
    for (int day = 1; day <= daysInMonth; ++day) {
        int pos = firstDayDow + (day - 1);
        int row = pos / 7;
        int col = pos % 7;

        int x = startX + col * cellW;
        int y = gridY + row * cellH;

        if (day == dt.day) {
            display->drawRoundRect(x + 5, y + 5, cellW - 10, cellH - 40, 5, 0);
            display->drawRoundRect(x + 6, y + 6, cellW - 12, cellH - 42, 4, 0);
        }

        char dayStr[4];
        sprintf(dayStr, "%d", day);
        uint32_t dw = display->getTextWidth(dayStr, 3);
        display->drawText(x + (cellW - dw) / 2, y + 15, dayStr, 0, 3);
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
    char timeStr[3];

    sprintf(timeStr, "%02d", dt.day);
    render->apply_draw_indexed_text(sprite, 28, 43, timeStr, 0, 2);
}

bool CalendarApp::onEvent(const Event& event)
{
    if (w_header_.feed_event(event)) {
        return true;
    }
    
    return false;
}
