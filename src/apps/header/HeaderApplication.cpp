#include "HeaderApplication.h"
#include <cstdio>

HeaderApplication::HeaderApplication(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void HeaderApplication::update(uint32_t deltaTime)
{
}

void HeaderApplication::render()
{
    // Draw debug block (delete later)
    drawDebugBlock();

    // Draw normal blocks
    drawTimeBlock();
    drawBatteryBlock();

}

const char *HeaderApplication::getName() const
{
    return nullptr;
}

const char *HeaderApplication::getDescription() const
{
    return nullptr;
}

const uint8_t *HeaderApplication::getIcon() const
{
    return nullptr;
}

void HeaderApplication::onEvent(const Event &event)
{
}

void HeaderApplication::drawTimeBlock()
{
    auto sprite = context_->getDisplay()->getHeaderSprite();
    auto dt = context_->getRTC()->getDateTime();
    char timeStr[16];

    sprintf(timeStr, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = sprite->getTextWidth(timeStr,2);
    uint32_t text_height = sprite->getTextHeight(timeStr,2);
    sprite->drawText(270  - (text_width)/2,10,timeStr,0,2);
}

void HeaderApplication::drawBatteryBlock()
{
}

void HeaderApplication::drawDebugBlock()
{
    auto sprite = context_->getDisplay()->getHeaderSprite();
    sprite->drawRect(0,0,539,29,0);
}
