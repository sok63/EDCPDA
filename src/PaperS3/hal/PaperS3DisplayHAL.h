#pragma once 

#include <pda/hal/ADisplayHAL.h>

#include "PaperS3DisplaySpriteHAL.h"

class PaperS3DisplayHAL: public ADisplayHAL {
public:
    virtual ~PaperS3DisplayHAL() = default;
    
    void init() override;
    void beginTransaction() override;
    void endTransaction() override;
    void refresh() override;
    uint16_t width() const override;
    uint16_t height() const override;
    void sleep() override;
    void wakeup() override;
    void powerOff() override;

    ADisplaySpriteHAL* getScreenSprite() override;
    ADisplaySpriteHAL* getNewSprite() override;
    void deleteSprite(ADisplaySpriteHAL*) override;

private:
    M5Canvas* canvas_raw_;
    PaperS3DisplaySpriteHAL* canvas_;
};