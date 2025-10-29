#include "PaperS3DisplayHAL.h"

#include <M5Unified.h>


void PaperS3DisplayHAL::init()
{
    M5.Display.begin();

    canvas_raw_ = new M5Canvas(&M5.Display);
    canvas_ = new PaperS3DisplaySpriteHAL(canvas_raw_);

    // ERRATA: / Fixes the automatic wake display issue
    canvas_raw_->setColorDepth(1);
    canvas_raw_->createSprite(1, 1);  
    canvas_raw_->deleteSprite(); 
    // ERRATA: end /

    M5.Display.setRotation(90);
    
    canvas_raw_->createSprite(540, 960);
    canvas_raw_->setColor(TFT_WHITE);
    canvas_raw_->fillScreen();

   // M5.Display.startWrite();
   // M5.Display.setEpdMode(epd_mode_t::epd_fastest);
   // M5.Display.fillScreen(TFT_WHITE);
   // M5.Display.setTextColor(TFT_BLACK);
   // M5.Display.setTextSize(2);
   // M5.Display.setCursor(0, 0);
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
    canvas_raw_->pushSprite(0, 0);
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

ADisplaySpriteHAL *PaperS3DisplayHAL::getScreenSprite()
{
    return canvas_;
}

ADisplaySpriteHAL *PaperS3DisplayHAL::getNewSprite()
{
    return nullptr;
}

void PaperS3DisplayHAL::deleteSprite(ADisplaySpriteHAL *)
{
}
