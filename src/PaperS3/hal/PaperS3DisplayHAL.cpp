#include "PaperS3DisplayHAL.h"

#include <M5Unified.h>

void PaperS3DisplayHAL::init()
{
    M5.Display.begin();
    M5.Display.setRotation(90);
    M5.Display.setEpdMode(epd_mode_t::epd_fastest);
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.setTextColor(TFT_BLACK);

    // ERRATA: / Fixes the automatic wake display issue
    canvas_raw_ = new M5Canvas(&M5.Display);
    canvas_raw_->setColorDepth(1);
    canvas_raw_->createSprite(1, 1);
    canvas_raw_->deleteSprite();
    // ERRATA: end /
}

void PaperS3DisplayHAL::beginTransaction()
{
    M5.Display.startWrite();
}

void PaperS3DisplayHAL::endTransaction()
{
    M5.Display.endWrite();
}

void PaperS3DisplayHAL::setNeedRedraw()
{
    need_redraw_ = true;
}

bool PaperS3DisplayHAL::isNeedRedraw()
{
    return need_redraw_;
}

void PaperS3DisplayHAL::refresh()
{
    need_redraw_ = false;
    M5.Display.display();
    M5.Display.waitDisplay();
}

uint16_t PaperS3DisplayHAL::width() const
{
    return 540;
}

uint16_t PaperS3DisplayHAL::height() const
{
    return 960;
}

void PaperS3DisplayHAL::sleep()
{
}

void PaperS3DisplayHAL::wakeup()
{
}

void PaperS3DisplayHAL::powerOff()
{
    M5.Display.sleep();
    M5.Display.waitDisplay();
    delay(200);
}

ADisplaySpriteHAL* PaperS3DisplayHAL::getNewSprite(uint32_t width, uint32_t height, uint32_t bpp)
{
    return new PaperS3DisplaySpriteHAL(getNewCanvas(width, height, bpp));
}

void PaperS3DisplayHAL::deleteSprite(ADisplaySpriteHAL*)
{
}

void PaperS3DisplayHAL::applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y)
{
    if (!sprite)
        return;
    auto canvas = ((PaperS3DisplaySpriteHAL*) sprite)->get_canvas();
    if (!canvas)
        return;

    canvas->pushSprite(x, y);
}

void PaperS3DisplayHAL::applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y, uint32_t transparent_color)
{
    if (!sprite)
        return;
    auto canvas = ((PaperS3DisplaySpriteHAL*) sprite)->get_canvas();
    if (!canvas)
        return;

    canvas->pushSprite(x, y, transparent_color);
}

void PaperS3DisplayHAL::init(uint16_t width, uint16_t height)
{
}

void PaperS3DisplayHAL::clear()
{
    auto mode = M5.Display.getEpdMode();
    M5.Display.setEpdMode(epd_mode_t::epd_quality);
    M5.Display.fillScreen(TFT_WHITE);
    M5.Display.display();
    M5.Display.waitDisplay();
    M5.Display.setEpdMode(mode);
}

void PaperS3DisplayHAL::drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

void PaperS3DisplayHAL::drawLine(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t color)
{
    M5.Display.setColor(color);
    M5.Display.drawLine(x, y, x2, y2);
    M5.Display.waitDisplay();
}

void PaperS3DisplayHAL::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    M5.Display.setColor(color);
    M5.Display.drawRect(x, y, w, h);
    M5.Display.waitDisplay();
}

void PaperS3DisplayHAL::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color)
{
    M5.Display.setColor(color);
    M5.Display.drawCircle(x, y, r);
    M5.Display.waitDisplay();
}

void PaperS3DisplayHAL::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
    M5.Display.setColor(color);
    M5.Display.drawRoundRect(x, y, w, h, r);
    M5.Display.waitDisplay();
}

void PaperS3DisplayHAL::drawFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    M5.Display.setColor(color);
    M5.Display.fillRect(x, y, w, h);
    M5.Display.waitDisplay();
}

void PaperS3DisplayHAL::drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size)
{
    M5.Display.setTextSize(size);
    M5.Display.setTextColor(color);
    M5.Display.drawString(text, x, y);
    M5.Display.waitDisplay();
}

uint16_t PaperS3DisplayHAL::getTextWidth(const char* text, uint8_t size)
{
    M5.Display.setTextSize(size);
    return M5.Display.textWidth(text);
}

uint16_t PaperS3DisplayHAL::getTextHeight(const char* text, uint8_t size)
{
    M5.Display.setTextSize(size);
    return M5.Display.fontHeight();
}

M5Canvas* PaperS3DisplayHAL::getNewCanvas(uint32_t width, uint32_t height, uint32_t bpp)
{
    auto canvas = new M5Canvas(&M5.Display);
    canvas->setColorDepth(bpp);
    canvas->createSprite(width, height);
    canvas->fillScreen(TFT_WHITE);
    return canvas;
}
