#pragma once 

#include <cstdint>

#include <pda/hal/APowerHAL.h>

class PaperS3PowerHAL: public APowerHAL {
public:
    virtual ~PaperS3PowerHAL() = default;
    
    void init() override;
    uint8_t getBatteryLevel() override;
    bool isCharging() override;
    void sleep(uint32_t milliseconds) override;
    void deepSleep() override;
};