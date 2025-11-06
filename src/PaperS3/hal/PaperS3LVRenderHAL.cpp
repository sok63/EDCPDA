#include "PaperS3LVRenderHAL.h"

void PaperS3LVRenderHAL::apply_draw_indexed_line(ADisplaySpriteHAL *sprite, uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint64_t width, uint64_t color)
{
    auto csprite = (PaperS3DisplaySpriteHAL*) sprite;

    csprite->drawLine(x,y,x2,y2,color);

}
