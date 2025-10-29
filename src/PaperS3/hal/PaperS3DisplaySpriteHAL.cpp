#include "PaperS3DisplaySpriteHAL.h"

PaperS3DisplaySpriteHAL::PaperS3DisplaySpriteHAL(M5Canvas *canvas): canvas_(canvas)
{
}

void PaperS3DisplaySpriteHAL::init(uint16_t width, uint16_t height)
{

}

void PaperS3DisplaySpriteHAL::clear()
{
}

void PaperS3DisplaySpriteHAL::drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

void PaperS3DisplaySpriteHAL::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    canvas_->setColor(TFT_BLACK);
    canvas_->drawRect(x,y,w,h);
}

void PaperS3DisplaySpriteHAL::drawText(int16_t x, int16_t y, const char *text, uint16_t color, uint8_t size)
{
}

uint16_t PaperS3DisplaySpriteHAL::width() const
{
    return 0;
}

uint16_t PaperS3DisplaySpriteHAL::height() const
{
    return 0;
}
