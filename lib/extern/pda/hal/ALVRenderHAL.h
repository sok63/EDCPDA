#pragma once

#include "ADisplaySpriteHAL.h"

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;
};

enum class eLVTypes : uint8_t
{
    // Special types
    END = 0,
    CONTROL_WORD = 1,
    CONTROL_SUM = 2,
    VERSION = 3,
    PREDEFINED_COLOR_PALETTE = 4,
    CUSTOM_COLOR_PALETTE = 5,
    OBJECTS_COUNT = 6,
    FILLER = 7,

    // Indexed types
    INDEXED_POINT = 50,
    INDEXED_LINE = 51,
    INDEXED_RECT = 52,
    INDEXED_ROUND_RECT = 53,
    INDEXED_FILLED_RECT = 54,
    INDEXED_RILLED_ROUND_RECT = 55,
    INDEXED_CIRCLE = 56,
    INDEXED_FILLED_CIRCLE = 57,

    // NonIndexed types (mirrow numering)
    POINT = 150,
    LINE = 151,
    RECT = 152,
    ROUND_RECT = 153,
    FILLED_RECT = 154,
    RILLED_ROUND_RECT = 155,
    CIRCLE = 156,
    FILLED_CIRCLE = 157

};

class ALVRenderHAL
{
public:
    // Parse commands
    void renderDataToSprite(ADisplaySpriteHAL*, uint8_t* data_sequence);
    eLVTypes getNextType(uint8_t* data_sequence, uint32_t shift);

    // Draw commands
    virtual void apply_draw_indexed_line(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint64_t line_width, uint64_t color_index) = 0;
    virtual void apply_draw_indexed_rect(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t line_width, uint64_t color_index) = 0;
    virtual void apply_draw_indexed_circle(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, uint64_t radius, uint64_t line_width, uint64_t color_index) = 0;
    virtual void apply_draw_indexed_text(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, const char* text, uint64_t color_index, uint8_t size) = 0;
};
