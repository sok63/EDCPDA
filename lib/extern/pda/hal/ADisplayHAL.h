#pragma once 

#include <cstdint>

#include <pda/hal/ADisplaySpriteHAL.h>

class ADisplayHAL {
public:
    virtual ~ADisplayHAL() = default;
    virtual void init() = 0;
    virtual void beginTransaction() = 0;
    virtual void endTransaction() = 0;
    virtual void refresh() = 0;
    virtual uint16_t width() const = 0;
    virtual uint16_t height() const = 0;
    virtual void sleep() = 0;
    virtual void wakeup() = 0;
    virtual void powerOff() = 0;

    virtual ADisplaySpriteHAL* getScreenSprite() = 0;
    virtual ADisplaySpriteHAL* getNewSprite() = 0;
    virtual void deleteSprite(ADisplaySpriteHAL*) = 0;
};