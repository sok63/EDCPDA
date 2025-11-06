#pragma once

#include <M5Unified.h>

#include <pda/hal/ALVRenderHAL.h>
#include "PaperS3DisplaySpriteHAL.h"

class PaperS3LVRenderHAL: public ALVRenderHAL {
public:
    void apply_draw_indexed_line(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint64_t width, uint64_t color) override;

};