#pragma once 

#include <pda/hal/ADisplayHAL.h>

#include "PaperS3DisplaySpriteHAL.h"

class PaperS3DisplayHAL: public ADisplayHAL {
public:
    virtual ~PaperS3DisplayHAL() = default;
    
    void init() override;
    void beginTransaction() override;
    void endTransaction() override;
    void setNeedRedraw() override;
    bool isNeedRedraw() override;
    void refresh() override;
    uint16_t width() const override;
    uint16_t height() const override;
    void sleep() override;
    void wakeup() override;
    void powerOff() override;

    ADisplaySpriteHAL* getNewSprite(uint32_t width, uint32_t height, uint32_t bpp) override;

    void deleteSprite(ADisplaySpriteHAL*) override;
    void applySpriteToScreen(ADisplaySpriteHAL *sprite, int32_t x, int32_t y) override;
    void applySpriteToScreen(ADisplaySpriteHAL *sprite, int32_t x, int32_t y, uint32_t transparent_color) override;

private:
     M5Canvas* getNewCanvas(uint32_t width, uint32_t height, uint32_t bpp);

private:
    bool need_redraw_ = true;
    bool transparent_ = false;
    M5Canvas* canvas_raw_;
    PaperS3DisplaySpriteHAL* canvas_;
};