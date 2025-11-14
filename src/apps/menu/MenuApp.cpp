#include "MenuApp.h"
#include <cstdio>

#include <M5Unified.h>

MenuApp::MenuApp(ApplicationContext* context, ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
    , w_header_(context)
{
    context_->getEventService()->addListener(this);
    icon_ = context_->getDisplay()->getNewSprite(80, 80, 4);

    for (auto idx = 0; idx < 32; idx++) {
        apps_[idx].app = -1;
        apps_[idx].column = idx / CELLS_IN_ROW;
        ;
        apps_[idx].row = idx % CELLS_IN_ROW;
        ;
    }
}

void MenuApp::update(uint32_t deltaTime)
{
}

void MenuApp::render()
{
    auto display = context_->getDisplay();
    display->clear();

    w_header_.render(display);

    // [0:1] Time block
    drawDateTimeBlock();

    // Application blocks
    for (auto idx = 0; idx < 32; idx++) {
        if (apps_[idx].app >= 0)
            drawAppAtCell(apps_[idx].app, idx);
    }
}

const char* MenuApp::getName() const
{
    return "Menu";
}

void MenuApp::drawIconTo(ADisplaySpriteHAL*)
{
}

bool MenuApp::onEvent(const Event& event)
{

    // Process event
    if (event.type != eEventType::TOUCH_EVENT)
        return false;

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));

    // Start apps only from double tap (to ignore false touching)

    if (touch->gesture != eGestureType::ONEF_DOUBLE_TAP)
        return true;

    // Try to understand cell where touch is detected
    // Calculate roughly nearest cell
    int x = (touch->x) / (CELL_SIZE + CELL_SPACING);
    int y = (touch->y - 30) / (CELL_SIZE + CELL_SPACING);

    // Check with precise
    calculateCellRect(x, y);
    if ((touch->x < rect_.x) or (touch->x > rect_.x + rect_.width))
        return true;
    if ((touch->y < rect_.y) or (touch->y > rect_.y + rect_.height))
        return true;

    auto appPosition = x + y * 4;
    auto appNum = apps_[appPosition].app;

    // Switch to app
    Serial.printf("  Double tap at (%d, %d)\n", x, y);

    if (appNum != -1) {
        appManager_->launchApp(appNum);
    }

    return true;
}

void MenuApp::setAppPosition(uint32_t appNum, uint32_t position)
{
    apps_[position].app = appNum;
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
    calculateCellRect(row, column);
}

void MenuApp::calculateCellRect(uint32_t row, uint32_t column)
{
    // Position in cell grid
    rect_.idx = column * CELLS_IN_ROW + row;
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
    auto display = context_->getDisplay();
    calculateCellRect(0);

    // Line 1 - Time
    {
        char timeStr[16];
        sprintf(timeStr, "%02d:%02d", dt.hour, dt.minute);
        uint32_t text_width = display->getTextWidth(timeStr, 7);
        uint32_t text_height = display->getTextHeight(timeStr, 7);
        display->drawText(rect_.x + CELL_SIZE + CELL_SPACING / 2 - (text_width) / 2, rect_.y + MINIMAL_SPACING * 2, timeStr, 0, 7);
    }

    // Line 2 - Date, Day of the week
    const char* daysOfWeek[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"};

    char dateStr[64];
    sprintf(dateStr, "%02d.%02d.%04d %s",
            dt.day,
            dt.month,
            dt.year,
            daysOfWeek[dt.weekDay]);
    uint32_t text_width = display->getTextWidth(dateStr, 2);
    uint32_t text_height = display->getTextHeight(dateStr, 2);
    display->drawText(rect_.x + CELL_SIZE + CELL_SPACING / 2 - (text_width) / 2, rect_.y + CELL_SIZE - text_height - MINIMAL_SPACING, dateStr, 0, 2);
}

void MenuApp::drawSliderBlock()
{
}

void MenuApp::drawFastAccessBlock()
{
}

void MenuApp::drawAppAtCell(uint32_t appNum, uint32_t position)
{
    auto display = context_->getDisplay();
    auto app = appManager_->getApplicationRegistry()->getApplication(appNum);

    // Calculate CellRectInfo
    calculateCellRect(position);

    // Draw Icon
    icon_->clear();

    app->drawIconTo(icon_);
    display->drawRoundRect(rect_.x + (CELL_SIZE - ICON_SIZE) / 2, rect_.y + MINIMAL_SPACING, ICON_SIZE, ICON_SIZE, 5, 0);
    context_->getDisplay()->applySpriteToScreen(icon_, rect_.x + (CELL_SIZE - ICON_SIZE) / 2, rect_.y + MINIMAL_SPACING, TFT_WHITE);

    // Draw App name
    uint32_t text_width = display->getTextWidth(app->getName(), 2);
    uint32_t text_height = display->getTextHeight(app->getName(), 2);
    display->drawText(rect_.x + (rect_.width - text_width) / 2, rect_.y + CELL_SIZE - text_height, app->getName(), 0, 2);
}
