#include "PaperS3DisplayHAL.h"

#include <M5Unified.h>


void PaperS3DisplayHAL::init()
{
    M5.Display.begin();
    M5Canvas canvas(&M5.Display);

    // ERRATA: / Fixes the automatic wake display issue
    canvas.setColorDepth(16);
    canvas.createSprite(1, 1);  
    canvas.deleteSprite();  
    // ERRATA: end /

    M5.Display.setEpdMode(epd_mode_t::epd_fastest);
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
    // Prepare screen
    M5.Display.fillScreen(TFT_WHITE); 
    M5.Display.setCursor(0, 0);

    // Apply canvas to screen
    //canvas_.pushSprite(0, 0);
    //canvas_.deleteSprite();

    // Display changes
    M5.Display.display();
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
    return nullptr;
}

ADisplaySpriteHAL *PaperS3DisplayHAL::getNewSprite()
{
    return nullptr;
}

void PaperS3DisplayHAL::deleteSprite(ADisplaySpriteHAL *)
{
}
