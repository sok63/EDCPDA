#pragma once 

#include <cstdint>

#include <pda/hal/ADisplaySpriteHAL.h>

class ADisplayHAL {
public:
    virtual ~ADisplayHAL() = default;
    virtual void init() = 0;
    virtual void beginTransaction() = 0;
    virtual void endTransaction() = 0;
    virtual void setNeedRedraw() = 0;
    virtual bool isNeedRedraw() = 0;
    virtual void refresh() = 0;
    virtual uint16_t width() const = 0;
    virtual uint16_t height() const = 0;
    virtual void sleep() = 0;
    virtual void wakeup() = 0;
    virtual void powerOff() = 0;

    virtual ADisplaySpriteHAL* getNewSprite(uint32_t width, uint32_t height, uint32_t bpp)  = 0;

    virtual void deleteSprite(ADisplaySpriteHAL*) = 0;
    virtual void applySpriteToScreen(ADisplaySpriteHAL *sprite, int32_t x, int32_t y) = 0;
};