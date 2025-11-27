#pragma once

#include <M5Unified.h>

#include <pda/helpers/touch/TouchGestureDriver.h>
#include <pda/hal/interfaces/ATouchHAL.h>

class PaperS3TouchHAL : public ATouchHAL
{
public:
    virtual ~PaperS3TouchHAL() = default;

    void init() override;
    sTouchEvent getNext() override;
    void update() override;

private:
    TouchGestureDriver touchDriver_;
};