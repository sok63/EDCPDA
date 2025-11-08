#include "PaperS3LVRenderHAL.h"

void PaperS3LVRenderHAL::apply_draw_indexed_line(ADisplaySpriteHAL *sprite, uint64_t x, uint64_t y, uint64_t x2, uint64_t y2, uint64_t width, uint64_t color_index)
{
    auto csprite = (PaperS3DisplaySpriteHAL*) sprite;
    csprite->drawLine(x,y,x2,y2,paperS3ColorIndexes[color_index]);
}

void PaperS3LVRenderHAL::apply_draw_indexed_rect(ADisplaySpriteHAL *sprite, uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t line_width, uint64_t color_index)
{
    auto csprite = (PaperS3DisplaySpriteHAL*) sprite;
    csprite->drawRect(x,y,w,h,paperS3ColorIndexes[color_index]);
}

void PaperS3LVRenderHAL::apply_draw_indexed_circle(ADisplaySpriteHAL *sprite, uint64_t x, uint64_t y, uint64_t radius, uint64_t line_width, uint64_t color_index)
{
    auto csprite = (PaperS3DisplaySpriteHAL*) sprite;
    csprite->drawCircle(x,y,radius,paperS3ColorIndexes[color_index]);
}

void PaperS3LVRenderHAL::apply_draw_indexed_text(ADisplaySpriteHAL *sprite, uint64_t x, uint64_t y, const char *text, uint64_t color_index, uint8_t size)
{
    auto csprite = (PaperS3DisplaySpriteHAL*) sprite;
    csprite->drawText(x,y,text,paperS3ColorIndexes[color_index],size);
}
