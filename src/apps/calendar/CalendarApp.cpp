#include "CalendarApp.h"
#include <cstdio>

CalendarApp::CalendarApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void CalendarApp::update(uint32_t deltaTime)
{
}

void CalendarApp::render()
{
}

const char *CalendarApp::getName() const
{
    return "Calendar";
}

void CalendarApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
    auto render = context_->getRender();

    render->apply_draw_indexed_rect(sprite,15,15,50,50,1,0);

    render->apply_draw_indexed_rect(sprite,25,8,8,15,1,0);
    render->apply_draw_indexed_rect(sprite,45,8,8,15,1,0);

    // Draw current day num
    auto dt = context_->getRTC()->getDateTime();
    char timeStr[3];

    sprintf(timeStr, "%02d", dt.day);
    auto tw = sprite->getTextWidth(timeStr,2);
    render->apply_draw_indexed_text(sprite,28,43,timeStr,0,2);

}

bool CalendarApp::onEvent(const Event &event)
{
    return false;
}
