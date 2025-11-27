#pragma once
#include <cstdint>

#include <pda/hal/interfaces/ADisplayHAL.h>
#include <pda/hal/interfaces/AStorageHAL.h>

namespace LVFG {

namespace version_1 {

    struct sLVFHead
    {
        uint64_t control_word;
        uint16_t fletcher16;
        uint8_t version;
        uint8_t compression;
    };

    struct sPoint
    {
        uint8_t type = 1;
        int16_t x;
        int16_t y;
        uint32_t color;
    };

    struct sLine
    {
        uint8_t type = 2;
        int16_t x;
        int16_t y;
        int16_t x1;
        int16_t y1;
        int16_t line_width;
        uint32_t color;
    };

    struct sRect
    {
        uint8_t type = 3;
        int16_t x;
        int16_t y;
        int16_t w;
        int16_t h;
        int16_t line_width;
        uint32_t line_color;
        uint32_t fill_color;
    };

    class LVGFTileWorker
    {
    public:
        static void write_tile_to_pos(AStorageHAL* storage, ADisplaySpriteHAL* sprite, int32_t z, int32_t x, int32_t y, int16_t scr_x, int16_t scr_y, int16_t t_w, int16_t t_h);
    };

}



}
