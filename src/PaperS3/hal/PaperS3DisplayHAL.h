#pragma once 

#include <pda/hal/ADisplayHAL.h>

class PaperS3DisplayHAL: public ADisplayHAL {
public:
    virtual ~PaperS3DisplayHAL() = default;
    
    void init() override;
    void clear() override;
    void refresh() override;
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) override;
    uint16_t width() const override;
    uint16_t height() const override;
    void sleep() override;
    void wakeup() override;
};