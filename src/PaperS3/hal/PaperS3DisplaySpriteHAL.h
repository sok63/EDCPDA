#pragma once

#include <cstdint>

#include <M5Unified.h>

#include <pda/hal/ADisplaySpriteHAL.h>

class PaperS3DisplaySpriteHAL: public ADisplaySpriteHAL {
public:
    virtual ~PaperS3DisplaySpriteHAL() = default;
    PaperS3DisplaySpriteHAL(M5Canvas*);

    void init(uint16_t width, uint16_t height) override;
    void clear() override;
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) override;
    uint16_t width() const override;
    uint16_t height() const override;
private:
    M5Canvas* canvas_ = nullptr;
};