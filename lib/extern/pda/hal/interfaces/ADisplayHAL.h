#pragma once

#include <cstdint>

#include <pda/hal/interfaces/ADisplaySpriteHAL.h>

class ADisplayHAL : public ADisplaySpriteHAL
{
public:
    // Work as display
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

    // Work as sprite
    virtual void init(uint16_t width, uint16_t height) = 0;
    virtual void clear() = 0;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

    virtual void drawLine(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color) = 0;
    virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) = 0;

    virtual void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) = 0;
    virtual uint16_t getTextWidth(const char* text, uint8_t size) = 0;
    virtual uint16_t getTextHeight(const char* text, uint8_t size) = 0;

    // Work with sprite
    virtual ADisplaySpriteHAL* getNewSprite(uint32_t width, uint32_t height, uint32_t bpp) = 0;
    virtual void deleteSprite(ADisplaySpriteHAL*) = 0;
    virtual void applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y) = 0;
    virtual void applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y, uint32_t transparent_color) = 0;
};