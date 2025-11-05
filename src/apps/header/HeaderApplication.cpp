#include "HeaderApplication.h"
#include <cstdio>

#include <M5Unified.h>

HeaderApplication::HeaderApplication(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
    context_->getEventService()->addListener(this);
    sprite_collapsed_ = context_->getDisplay()->getNewSprite(540,30,1);
    sprite_extended_ = context_->getDisplay()->getNewSprite(540,300,1);
}

void HeaderApplication::update(uint32_t deltaTime)
{
}

void HeaderApplication::render()
{
    if(extended_){
        sprite_extended_->clear();
        sprite_extended_->drawRect(0,0,sprite_extended_->width()-1,sprite_extended_->height()-1,0);
        context_->getDisplay()->applySpriteToScreen(sprite_extended_,0,0);
    } else {   
        sprite_collapsed_->clear();
        // Draw debug block (delete later)
        sprite_collapsed_->drawRect(0,0,sprite_collapsed_->width()-1,sprite_collapsed_->height()-1,0);
    
        // Draw normal blocks
        drawCollapsedTimeBlock();
        drawCollapsedBatteryBlock();

        // Set it here for now
        context_->getDisplay()->applySpriteToScreen(sprite_collapsed_,0,0);
        }
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

bool HeaderApplication::onEvent(const Event &event)
{
    // Process only touch gestures at now
    if(event.type != eEventType::TOUCH_EVENT) return false;
    sTouchEvent *touch = (sTouchEvent*)(&(event.data));

    
    if(extended_){
        // Process only swipe down at now
        if(touch->gesture != eGestureType::ONEF_SWIPE_UP) return false;
        if(touch->startY > sprite_extended_->height()) return false;

        // Process event - change to wide sprite
        extended_ = false;
        context_->getDisplay()->setNeedRedraw();
        Serial.printf("Swipe UP to MENU collapse from (%d, %d) to (%d, %d), delta: (%d, %d)\n", touch->startX, touch->startY, touch->x, touch->y, touch->deltaX, touch->deltaY);
        return true;
    } else {
        // Process only swipe down at now
        if(touch->gesture != eGestureType::ONEF_SWIPE_DOWN) return false;
        if(touch->startY > sprite_collapsed_->height()) return false;
        
        // Process event - change to wide sprite
        extended_ = true;
        context_->getDisplay()->setNeedRedraw();
        Serial.printf("Swipe DOWN to MENU EXTEND from (%d, %d) to (%d, %d), delta: (%d, %d)\n", touch->startX, touch->startY, touch->x, touch->y, touch->deltaX, touch->deltaY);
        return true;
    }
    return false;
}

void HeaderApplication::drawCollapsedTimeBlock()
{
    auto dt = context_->getRTC()->getDateTime();
    char timeStr[16];

    sprintf(timeStr, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = sprite_collapsed_->getTextWidth(timeStr,2);
    uint32_t text_height = sprite_collapsed_->getTextHeight(timeStr,2);
    sprite_collapsed_->drawText(270  - (text_width)/2,10,timeStr,0,2);
}

void HeaderApplication::drawCollapsedBatteryBlock()
{

    auto BATTERY_WIDTH = 40;
    auto BATTERY_HEIGHT = 20;
    auto BATTERY_TIP_OFFSET = 2;
    auto BATTERY_TIP_WIDTH = 4;
    auto BATTERY_TIP_HEIGHT = 15;
    auto x = 450;
    auto y = 5;

    sprite_collapsed_->drawRect(x, y, BATTERY_WIDTH, BATTERY_HEIGHT, 0);
    sprite_collapsed_->drawRect(x + BATTERY_WIDTH, y + BATTERY_TIP_OFFSET, BATTERY_TIP_WIDTH, BATTERY_TIP_HEIGHT, 0);

    // Fill battery based on percentage
    for (int i = x; i < x + BATTERY_WIDTH; i++) {
        sprite_collapsed_->drawLine(i, y, i, y + BATTERY_HEIGHT - 1, 0);
        if ((i - x) * 100.0 / BATTERY_WIDTH > context_->getPower()->getBatteryLevel()) {
            break;
        }
    }

    // Draw text
    char prcnt[5];

    sprintf(prcnt, "%02d", context_->getPower()->getBatteryLevel());
    uint32_t text_width = sprite_collapsed_->getTextWidth(prcnt,2);
    uint32_t text_height = sprite_collapsed_->getTextHeight(prcnt,2);
    sprite_collapsed_->drawText(x + BATTERY_WIDTH + 5,10,prcnt,0,2);

}

void HeaderApplication::drawCollapsedDebugBlock()
{

    sprite_collapsed_->drawRect(0,0,539,29,0);
}
