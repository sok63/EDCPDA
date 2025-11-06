#include "MenuApp.h"
#include <cstdio>

#include <M5Unified.h>


MenuApp::MenuApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
   context_->getEventService()->addListener(this);
   icon_ = context_->getDisplay()->getNewSprite(80,80,4);
}

void MenuApp::update(uint32_t deltaTime)
{
}

void MenuApp::render()
{
    auto sprite = context_->getApplicationSprite();
    sprite->clear();
    context_->getDisplay()->applySpriteToScreen(context_->getApplicationSprite(),0,29);
    // TEMPORARY: Draw cell grid
    // for(auto idx=0;idx<=32;idx++){
    //     calculateCellRect(idx);
    //     sprite->drawRect(rect_.x,rect_.y,rect_.width,rect_.height,0);
    // }

    // [0:1] Time block
    drawDateTimeBlock();

    // [2:19] Application blocks
    drawAppAtCell(1,2);

    drawAppAtCell(2,3);
    
    
    // [20:23] Slide area

    // [24:27] Fast access area
    
    // Set it here for now
    context_->getDisplay()->applySpriteToScreen(context_->getApplicationSprite(),0,29, TFT_WHITE);
}

const char *MenuApp::getName() const
{
    return "Menu";
}

void MenuApp::drawIconTo(ADisplaySpriteHAL *)
{
}

bool MenuApp::onEvent(const Event &event)
{

  // Process event
    if(event.type != eEventType::TOUCH_EVENT) return false;

    sTouchEvent *touch = (sTouchEvent*)(&(event.data));


        switch (touch->gesture) {
            case eGestureType::ONEF_TAP:
                Serial.printf("  Single tap at (%d, %d)\n", touch->x, touch->y);
                break;
                
            case eGestureType::ONEF_DOUBLE_TAP:
                Serial.printf("  Double tap at (%d, %d)\n", touch->x, touch->y);
                break;
                
            case eGestureType::ONEF_LONG_PRESS:
                Serial.printf("  Long press at (%d, %d), duration: %lu ms\n", 
                             touch->x, touch->y, touch->duration);
                break;
                
            case eGestureType::ONEF_SWIPE_UP:
                Serial.printf("  Swipe UP from (%d, %d) to (%d, %d), delta: (%d, %d)\n",
                             touch->startX, touch->startY, touch->x, touch->y,
                             touch->deltaX, touch->deltaY);
                break;            
            case eGestureType::ONEF_SWIPE_DOWN:
                Serial.printf("  Swipe DOWN from (%d, %d) to (%d, %d), delta: (%d, %d)\n",
                             touch->startX, touch->startY, touch->x, touch->y,
                             touch->deltaX, touch->deltaY);
                break;            
            case eGestureType::ONEF_SWIPE_LEFT:
                Serial.printf("  Swipe LEFT from (%d, %d) to (%d, %d), delta: (%d, %d)\n",
                             touch->startX, touch->startY, touch->x, touch->y,
                             touch->deltaX, touch->deltaY);
                break;
            case eGestureType::ONEF_SWIPE_RIGHT:
                Serial.printf("  Swipe RIGHT from (%d, %d) to (%d, %d), delta: (%d, %d)\n",
                             touch->startX, touch->startY, touch->x, touch->y,
                             touch->deltaX, touch->deltaY);
                break;
                
            case eGestureType::ONEF_DRAG_START:
                Serial.printf("  Drag started at (%d, %d)\n", touch->startX, touch->startY);
                break;
                
            case eGestureType::ONEF_DRAG_END:
                Serial.printf("  Drag ended at (%d, %d), total delta: (%d, %d), duration: %lu ms\n",
                             touch->x, touch->y, touch->deltaX, touch->deltaY, touch->duration);
                break;
                
            default:
                break;
        }
   return false;
}

void MenuApp::drawMenu()
{
}

void MenuApp::handleTouch(int16_t x, int16_t y)
{
}

void MenuApp::calculateCellRect(uint32_t position)
{
  uint32_t row = position % CELLS_IN_ROW;
  uint32_t column = position / CELLS_IN_ROW;
  calculateCellRect(row,column);
}

void MenuApp::calculateCellRect(uint32_t row, uint32_t column)
{
    // Position in cell grid
    rect_.idx = column*CELLS_IN_ROW + row;
    rect_.row = row;
    rect_.column = column;

    // Position in pixels
    rect_.width = CELL_SIZE;
    rect_.height = CELL_SIZE;

    rect_.x = CELL_SPACING + row * (CELL_SIZE + CELL_SPACING);
    rect_.y = CELL_SPACING + column * (CELL_SIZE + CELL_SPACING);
}

void MenuApp::drawDateTimeBlock()
{
  auto dt = context_->getRTC()->getDateTime();
  auto sprite = context_->getApplicationSprite();
  calculateCellRect(0);

  // Line 1 - Time
  {
    char timeStr[16];
    sprintf(timeStr, "%02d:%02d", dt.hour, dt.minute);
    uint32_t text_width = sprite->getTextWidth(timeStr,7);
    uint32_t text_height = sprite->getTextHeight(timeStr,7);
    sprite->drawText(rect_.x + CELL_SIZE+CELL_SPACING/2 - (text_width)/2,rect_.y+MINIMAL_SPACING*2,timeStr,0,7);
  }

  // Line 2 - Date, Day of the week
  const char* daysOfWeek[] = {
    "Sunday", "Monday", "Someday", "Someday", 
    "Someday", "Someday", "Someday"
  };

  char dateStr[64];
  sprintf(dateStr, "%02d.%02d.%04d %s", 
          dt.day, 
          dt.month, 
          dt.year,
          daysOfWeek[dt.weekDay]);
  uint32_t text_width = sprite->getTextWidth(dateStr,2);
      uint32_t text_height = sprite->getTextHeight(dateStr,2);
  sprite->drawText(rect_.x + CELL_SIZE+CELL_SPACING/2 - (text_width)/2,rect_.y+ CELL_SIZE- text_height - MINIMAL_SPACING,dateStr,0,2);
}

void MenuApp::drawSliderBlock()
{
}

void MenuApp::drawFastAccessBlock()
{
}

void MenuApp::drawAppAtCell(uint32_t appNum, uint32_t position)
{
    auto sprite = context_->getApplicationSprite();
    auto app = appManager_->getApplicationRegistry()->getApplication(appNum);

    // Calculate CellRectInfo
    calculateCellRect(position);

    // Draw Icon
    icon_->clear();
    sprite->drawRoundRect(rect_.x+(CELL_SIZE - ICON_SIZE)/2,rect_.y+MINIMAL_SPACING,ICON_SIZE,ICON_SIZE,5,0);
    app->drawIconTo(icon_);  
    context_->getDisplay()->applySpriteToScreen(icon_,rect_.x+(CELL_SIZE - ICON_SIZE)/2,HEADER_SPACING+rect_.y+MINIMAL_SPACING);

    // Draw App name
    uint32_t text_width = sprite->getTextWidth(app->getName(),2);
    uint32_t text_height = sprite->getTextHeight(app->getName(),2);
    sprite->drawText(rect_.x + (rect_.width - text_width)/2,rect_.y+CELL_SIZE- text_height,app->getName(),0,2);
}

