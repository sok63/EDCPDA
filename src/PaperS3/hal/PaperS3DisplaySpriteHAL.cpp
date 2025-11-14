#include "PaperS3DisplaySpriteHAL.h"

PaperS3DisplaySpriteHAL::PaperS3DisplaySpriteHAL(M5Canvas *canvas): canvas_(canvas)
{
}

void PaperS3DisplaySpriteHAL::init(uint16_t width, uint16_t height)
{

}

void PaperS3DisplaySpriteHAL::clear()
{
    canvas_->clear(TFT_WHITE);
}

void PaperS3DisplaySpriteHAL::drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

void PaperS3DisplaySpriteHAL::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    canvas_->setColor(color);
    canvas_->drawRect(x,y,w,h);
}

void PaperS3DisplaySpriteHAL::drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color)
{
    canvas_->setColor(color);
    canvas_->drawCircle(x,y,r);
}

void PaperS3DisplaySpriteHAL::drawLine(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t color)
{  
    canvas_->setColor(color);
    canvas_->drawLine(x,y,x2,y2);
}

void PaperS3DisplaySpriteHAL::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
    canvas_->setColor(color);
    canvas_->drawRoundRect(x,y,w,h,r);
}

void PaperS3DisplaySpriteHAL::drawFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    canvas_->setColor(color);
    canvas_->fillRect(x,y,w,h);
}

void PaperS3DisplaySpriteHAL::drawText(int16_t x, int16_t y, const char *text, uint16_t color, uint8_t size)
{
   // canvas_->setTextDatum(textdatum_t::top_left);  
    canvas_->setTextSize(size);
    canvas_->setTextColor(color);
    canvas_->drawString(text,x,y);
}

uint16_t PaperS3DisplaySpriteHAL::getTextWidth(const char *text, uint8_t size)
{
    canvas_->setTextSize(size);
    return (uint16_t) canvas_->textWidth(text);
}

uint16_t PaperS3DisplaySpriteHAL::getTextHeight(const char *text, uint8_t size)
{
    canvas_->setTextSize(size);
    return (uint16_t) canvas_->fontHeight();
}

uint16_t PaperS3DisplaySpriteHAL::width() const
{
    return canvas_->width();
}

uint16_t PaperS3DisplaySpriteHAL::height() const
{
    return canvas_->height();
}

M5Canvas *PaperS3DisplaySpriteHAL::get_canvas()
{
    return canvas_;
}
