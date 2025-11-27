#pragma once

#include <cstdint>

#include <pda/core/TouchPrimitives.h>

class ATouchHAL
{
public:
    virtual ~ATouchHAL() = default;

    virtual void init() = 0;
    virtual sTouchEvent getNext() = 0;
    virtual void update() = 0;
};