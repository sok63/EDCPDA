#include "MenuApp.h"
#include <cstdio>

MenuApp::MenuApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void MenuApp::update(uint32_t deltaTime)
{
}

void MenuApp::render()
{
    needRedraw_ = false;
    auto sprite = context_->getApplicationSprite();

    // TEMPORARY: Draw cell grid
    for(auto idx=0;idx<=32;idx++){
        calculateCellRect(idx);

        // Draw full border for app placement
        sprite->drawRect(rect_.x,rect_.y,rect_.width,rect_.height,0);
    }

    // [0:1] Time block
    drawDateTimeBlock();

    // [2:19] Application blocks
    drawAppAtCell(1,2);
    drawAppAtCell(2,3);
    
    
    // [20:23] Slide area

    // [24:27] Fast access area

}

const char *MenuApp::getName() const
{
    return "Menu";
}

const char *MenuApp::getDescription() const
{
    return "Application Launcher";
}

const uint8_t *MenuApp::getIcon() const
{
    return nullptr;
}

void MenuApp::onEvent(const Event &event)
{
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
    // Calculate CellRectInfo
    calculateCellRect(position);

    // Draw full border for app placement
    sprite->drawRect(rect_.x,rect_.y,rect_.width,rect_.height,0);

    // Draw Icon
    sprite->drawRect(rect_.x+(CELL_SIZE - ICON_SIZE)/2,rect_.y+MINIMAL_SPACING,ICON_SIZE,ICON_SIZE,0);

    // Draw App name
    auto app = appManager_->getApplicationRegistry()->getApplication(appNum);
    uint32_t text_width = sprite->getTextWidth(app->getName(),2);
    uint32_t text_height = sprite->getTextHeight(app->getName(),2);
    sprite->drawText(rect_.x + (rect_.width - text_width)/2,rect_.y+CELL_SIZE- text_height,app->getName(),0,2);
}

