#include "CharMatrix.h"

#include "M5Unified.h"

CharMatrix::CharMatrix(sRect size, char* matrix, uint16_t cols, uint16_t rows)
    : AWidget(size)
    , matrix_(matrix)
    , cols_(cols)
    , rows_(rows)
{
}

void CharMatrix::update()
{
}

void CharMatrix::render(ADisplaySpriteHAL* to)
{
    to->drawFillRect(size_.x, size_.y, size_.w, size_.h, TFT_WHITE);

    auto cell_w = size_.w / cols_;
    auto cell_h = size_.h / rows_;
    char w[2] = {0, 0};

    for (size_t ridx = 0; ridx < rows_; ridx++)
        for (size_t cidx = 0; cidx < cols_; ++cidx) {
            to->drawRect(size_.x + cell_w * cidx, size_.y + cell_h * ridx, cell_w, cell_h, 0);
            w[0] = matrix_[ridx + cidx * 10];
            auto tw = to->getTextWidth(w, 4);
            auto th = to->getTextHeight(w, 4);

            to->drawText(size_.x + cell_w * cidx + tw / 2, size_.y + cell_h * ridx + th / 2, w, 0, 4);
        }
}
