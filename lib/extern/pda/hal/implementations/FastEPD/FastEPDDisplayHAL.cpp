#include "FastEPDDisplayHAL.h"

void FastEPDDisplayHAL::init()
{
    epd.initPanel(BB_PANEL_M5PAPERS3, 26666666);
    epd.setRotation(3);
    epd.setPanelSize(540, 960);
    epd.clearWhite(true);
    epd.setFont(Roboto_Black_40);
    epd.setTextColor(BBEP_BLACK);

    epd.fillScreen(BBEP_WHITE);
    epd.setCursor(100, 100);
    epd.print("Hello fast test");
    epd.fullUpdate();
}

void FastEPDDisplayHAL::beginTransaction()
{
}

void FastEPDDisplayHAL::endTransaction()
{
}

void FastEPDDisplayHAL::setNeedRedraw()
{
}

bool FastEPDDisplayHAL::isNeedRedraw()
{
    return false;
}

void FastEPDDisplayHAL::refresh()
{
}

uint16_t FastEPDDisplayHAL::width() const
{
    return 0;
}

uint16_t FastEPDDisplayHAL::height() const
{
    return 0;
}

void FastEPDDisplayHAL::sleep()
{
}

void FastEPDDisplayHAL::wakeup()
{
}

void FastEPDDisplayHAL::powerOff()
{
}

ADisplaySpriteHAL* FastEPDDisplayHAL::getNewSprite(uint32_t width, uint32_t height, uint32_t bpp)
{
    return nullptr;
}

void FastEPDDisplayHAL::deleteSprite(ADisplaySpriteHAL*)
{
}

void FastEPDDisplayHAL::applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y)
{
}

void FastEPDDisplayHAL::applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y, uint32_t transparent_color)
{
}

void FastEPDDisplayHAL::init(uint16_t width, uint16_t height)
{
}

void FastEPDDisplayHAL::clear()
{
}

void FastEPDDisplayHAL::drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

void FastEPDDisplayHAL::drawLine(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t color)
{
}

void FastEPDDisplayHAL::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
}

void FastEPDDisplayHAL::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color)
{
}

void FastEPDDisplayHAL::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
}

void FastEPDDisplayHAL::drawFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
}

void FastEPDDisplayHAL::drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size)
{
}

uint16_t FastEPDDisplayHAL::getTextWidth(const char* text, uint8_t size)
{
    return 0;
}

uint16_t FastEPDDisplayHAL::getTextHeight(const char* text, uint8_t size)
{
    return 0;
}
