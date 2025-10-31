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

    canvas_ =  (PaperS3DisplaySpriteHAL*)getNewSprite(540,30,1);
    canvas_raw_ = canvas_->get_canvas();
}

void PaperS3DisplayHAL::beginTransaction()
{
    M5.Display.startWrite();
}

void PaperS3DisplayHAL::endTransaction()
{
    M5.Display.endWrite();
}

void PaperS3DisplayHAL::refresh()
{
    M5.Display.display();
    M5.Display.waitDisplay();
}

uint16_t PaperS3DisplayHAL::width() const
{
    return 0;
}

uint16_t PaperS3DisplayHAL::height() const
{
    return 0;
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

ADisplaySpriteHAL *PaperS3DisplayHAL::getHeaderSprite()
{
    return canvas_;
}

ADisplaySpriteHAL *PaperS3DisplayHAL::getNewSprite(uint32_t width, uint32_t height, uint32_t bpp) 
{
    return new PaperS3DisplaySpriteHAL(getNewCanvas(width,height,bpp));
}

void PaperS3DisplayHAL::deleteSprite(ADisplaySpriteHAL *)
{

}

void PaperS3DisplayHAL::applySpriteToScreen(ADisplaySpriteHAL *sprite, int32_t x, int32_t y)
{
    if(!sprite) return;
    auto canvas = ((PaperS3DisplaySpriteHAL*) sprite)->get_canvas();
    if(!canvas) return;

    if(!transparent_) canvas->pushSprite(x,y);
    else canvas->pushSprite(x,y,TFT_TRANSPARENT); 
}

M5Canvas *PaperS3DisplayHAL::getNewCanvas(uint32_t width, uint32_t height, uint32_t bpp)
{
    auto canvas = new M5Canvas(&M5.Display);
    canvas->setColorDepth(bpp); 
    canvas->createSprite(width, height);
    canvas->fillScreen(TFT_WHITE);  
    return canvas;
}
