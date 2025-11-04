#pragma once

#include <cstdint>

class ADisplaySpriteHAL {
public:
    virtual ~ADisplaySpriteHAL() = default;
    
    virtual void init(uint16_t width, uint16_t height) = 0;
    virtual void clear() = 0;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) = 0;
    virtual void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) = 0;
    

    virtual void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) = 0;
    virtual uint16_t getTextWidth(const char* text, uint8_t size) = 0;
    virtual uint16_t getTextHeight(const char* text, uint8_t size) = 0;
    
    virtual uint16_t width() const = 0;
    virtual uint16_t height() const = 0;
};