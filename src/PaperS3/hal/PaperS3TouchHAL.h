#pragma once 

#include <pda/hal/ATouchHAL.h>

class PaperS3TouchHAL: public ATouchHAL {
public:
    virtual ~PaperS3TouchHAL() = default;
    
    void init() override;
    bool available() override;
    TouchPoint getPoint() override;
    bool isPressed() override;
};