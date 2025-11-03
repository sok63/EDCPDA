#pragma once 

#include <M5Unified.h>

#include <pda/hal/ATouchHAL.h>
#include "driver/touch/TouchGestureDriver.h"


class PaperS3TouchHAL: public ATouchHAL {
public:
    virtual ~PaperS3TouchHAL() = default;
    
    void init() override;
    sTouchEvent getNext() override;
    void update() override;
private:
    TouchGestureDriver touchDriver_;
};