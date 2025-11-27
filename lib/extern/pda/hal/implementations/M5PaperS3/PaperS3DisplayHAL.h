#pragma once

#include <pda/hal/interfaces/ADisplayHAL.h>

#include "PaperS3DisplaySpriteHAL.h"

class PaperS3DisplayHAL : public ADisplayHAL
{
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
    void applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y) override;
    void applySpriteToScreen(ADisplaySpriteHAL* sprite, int32_t x, int32_t y, uint32_t transparent_color) override;

    // Sprite HAL
    void init(uint16_t width, uint16_t height) override;
    void clear() override;
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

    void drawLine(int16_t x, int16_t y, int16_t x2, int16_t y2, uint16_t color) override;
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color) override;
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) override;
    void drawFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;

    void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) override;
    uint16_t getTextWidth(const char* text, uint8_t size) override;
    uint16_t getTextHeight(const char* text, uint8_t size) override;

private:
    M5Canvas* getNewCanvas(uint32_t width, uint32_t height, uint32_t bpp);

private:
    bool need_redraw_ = true;
    bool transparent_ = false;
    M5Canvas* canvas_raw_;
    PaperS3DisplaySpriteHAL* canvas_;
};