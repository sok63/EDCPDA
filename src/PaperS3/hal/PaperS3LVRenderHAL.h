#pragma once

#include <M5Unified.h>

#include <pda/hal/ALVRenderHAL.h>
#include "PaperS3DisplaySpriteHAL.h"

const uint16_t paperS3ColorIndexes[16] = {
  0x0000, // 0 — Black
  0x1084, // 1
  0x2108, // 2
  0x318C, // 3
  0x4208, // 4
  0x528A, // 5
  0x6318, // 6
  0x739C, // 7
  0x8410, // 8 — 50% gray
  0x9492, // 9
  0xA514, // 10
  0xB596, // 11
  0xC618, // 12
  0xD69A, // 13
  0xE71C, // 14
  0xFFFF  // 15 — White
};

class PaperS3LVRenderHAL: public ALVRenderHAL {
public:
    void apply_draw_indexed_line(ADisplaySpriteHAL* sprite, uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint64_t width, uint64_t color_index) override;

};