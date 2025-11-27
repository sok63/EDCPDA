#include "LVF.h"

#include "M5Unified.h"

void LVFG::version_1::LVGFTileWorker::write_tile_to_pos(AStorageHAL* storage, ADisplaySpriteHAL* sprite, int32_t z, int32_t x, int32_t y, int16_t scr_x, int16_t scr_y, int16_t t_w, int16_t t_h)
{
    // Path to tile
    char path[64];
    snprintf(path, sizeof(path), "/ctiles/%d/%d/%d.mvt", z, x, y);

    File file = storage->open(path, FILE_READ);
    if (!file) {
        return;
    }

    // Read header
    sLVFHead header;
    if (file.read((uint8_t*) &header, sizeof(header)) != sizeof(header)) {
        file.close();
        return;
    }

    // Stream parsing
    uint8_t type;
    while (file.available()) {
        // Read elem type
        file.read(&type, 1);

        switch (type) {
        case 1: { // Point
            sPoint p;
            p.type = type;
            if (file.read((uint8_t*) &p.x, 2) != 2)
                break;
            if (file.read((uint8_t*) &p.y, 2) != 2)
                break;
            if (file.read((uint8_t*) &p.color, 4) != 4)
                break;
            // display->drawCircle(scr_x + p.x, scr_y + p.y, 1, 0);
            break;
        }
        case 2: { // Line
            sLine l;
            l.type = type;
            if (file.read((uint8_t*) &l.x, 2) != 2)
                break;
            if (file.read((uint8_t*) &l.y, 2) != 2)
                break;
            if (file.read((uint8_t*) &l.x1, 2) != 2)
                break;
            if (file.read((uint8_t*) &l.y1, 2) != 2)
                break;
            if (file.read((uint8_t*) &l.line_width, 2) != 2)
                break;
            if (file.read((uint8_t*) &l.color, 4) != 4)
                break;

            auto x1 = scr_x + map(l.x, 0, 4095, 0, t_w);
            auto x2 = scr_x + map(l.x1, 0, 4095, 0, t_w);

            auto y1 = scr_y + map(l.y, 0, 4095, 0, t_h);
            auto y2 = scr_y + map(l.y1, 0, 4095, 0, t_h);

            sprite->drawLine(x1, y1, x2, y2, 0);
            break;
        }
        case 3: { // Rect
            sRect r;
            r.type = type;
            if (file.read((uint8_t*) &r.x, 2) != 2)
                break;
            if (file.read((uint8_t*) &r.y, 2) != 2)
                break;
            if (file.read((uint8_t*) &r.w, 2) != 2)
                break;
            if (file.read((uint8_t*) &r.h, 2) != 2)
                break;
            if (file.read((uint8_t*) &r.line_width, 2) != 2)
                break;
            if (file.read((uint8_t*) &r.line_color, 4) != 4)
                break;
            if (file.read((uint8_t*) &r.fill_color, 4) != 4)
                break;

            auto x1 = scr_x + map(r.x, 0, 4095, 0, t_w);
            auto y1 = scr_y + map(r.y, 0, 4095, 0, t_h);
            auto x2 = map(r.w, 0, 4095, 0, t_w);
            auto y2 = map(r.h, 0, 4095, 0, t_h);

            sprite->drawRect(x1, y1, x2, y2, 0);

            break;
        }
        default:
            // Unknown type or broken sequence 
            file.close();
            return;
        }
    }

    file.close();
}
