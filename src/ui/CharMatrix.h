#pragma once

#include <string>

#include "AWidget.h"

#define EDIT_LIM_SIZE 30

class CharMatrix: public AWidget {
public:
    CharMatrix(sRect size, char* matrix, uint16_t cols, uint16_t rows);

    void update() override;
    void render(ADisplaySpriteHAL* sprite) override;

protected:
    char* matrix_;
    uint16_t cols_;
    uint16_t rows_;
};