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
    if(last_redraw_ != (millis()/60000)) context_->getDisplay()->setNeedRedraw();
}

void HeaderApplication::render()
{
    last_redraw_ = millis() / 60000;
    
    // Select sprite
    sprite_active_ = extended_ ? sprite_extended_:sprite_collapsed_;

    // Clear
    sprite_active_->clear();

    // Draw universal top blocks 
    drawTimeBlock();
    drawBatteryBlock();

    // Draw special blocks
    drawHeapBlock();
    drawAppNameBlock();

    // Apply sprite to screen
    sprite_active_->drawRect(0,0,sprite_collapsed_->width()-1,sprite_collapsed_->height()-1,0);
    sprite_active_->drawRect(0,0,sprite_active_->width()-1,sprite_active_->height()-1,0);
    context_->getDisplay()->applySpriteToScreen(sprite_active_,0,0); 
}

const char *HeaderApplication::getName() const
{
    return nullptr;
}

void HeaderApplication::drawIconTo(ADisplaySpriteHAL *)
{
}

bool HeaderApplication::onEvent(const Event &event)
{

    bool result = false;

    // Process only touch gestures at now
    if(event.type != eEventType::TOUCH_EVENT) return false;
    sTouchEvent *touch = (sTouchEvent*)(&(event.data));

    // Catch events started from our sprite
    if((touch->startY)<= sprite_active_->height()) result = true;
    if(touch->startY > sprite_active_->height()) return result;

    if(extended_){
        // Process only swipe up 
        if(touch->gesture != eGestureType::ONEF_SWIPE_UP) return result;
 
        // Process event - change to small sprite
        extended_ = false;
        context_->getDisplay()->setNeedRedraw();

        return true;
    } else {
        // Process only swipe down
        if(touch->gesture != eGestureType::ONEF_SWIPE_DOWN) return result;
        
        // Process event - change to big sprite
        extended_ = true;
        context_->getDisplay()->setNeedRedraw();
        
        return true;
    }
    return result;
}

void HeaderApplication::drawTimeBlock()
{
    auto dt = context_->getRTC()->getDateTime();
    char timeStr[16];

    sprintf(timeStr, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = sprite_active_->getTextWidth(timeStr,2);
    sprite_active_->drawText(270  - (text_width)/2,10,timeStr,0,2);
}

void HeaderApplication::drawBatteryBlock()
{

    auto BATTERY_WIDTH = 40;
    auto BATTERY_HEIGHT = 20;
    auto BATTERY_TIP_OFFSET = 2;
    auto BATTERY_TIP_WIDTH = 4;
    auto BATTERY_TIP_HEIGHT = 15;
    auto x = 450;
    auto y = 5;

    sprite_active_->drawRect(x, y, BATTERY_WIDTH, BATTERY_HEIGHT, 0);
    sprite_active_->drawRect(x + BATTERY_WIDTH, y + BATTERY_TIP_OFFSET, BATTERY_TIP_WIDTH, BATTERY_TIP_HEIGHT, 0);

    // Fill battery based on percentage
    for (int i = x; i < x + BATTERY_WIDTH; i++) {
        sprite_active_->drawLine(i, y, i, y + BATTERY_HEIGHT - 1, 0);
        if ((i - x) * 100.0 / BATTERY_WIDTH > context_->getPower()->getBatteryLevel()) {
            break;
        }
    }

    // Draw text
    char prcnt[5];
    sprintf(prcnt, "%02d", context_->getPower()->getBatteryLevel());
    sprite_active_->drawText(x + BATTERY_WIDTH + 5,10,prcnt,0,2);
}

void HeaderApplication::drawHeapBlock()
{
    char prcnt[10];
    sprintf(prcnt, "%02db", ESP.getMaxAllocHeap());
    sprite_active_->drawText(330 ,10,prcnt,0,2);
}

void HeaderApplication::drawAppNameBlock()
{
    auto registry = appManager_->getApplicationRegistry();

    sprite_active_->drawText(30 ,10,registry->getApplication(appManager_->getCurrentApplicationNum())->getName(),0,2);
}
