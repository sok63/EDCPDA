#pragma once 

#include <cstdint>

class APowerHAL {
public:
    virtual ~APowerHAL() = default;
    
    virtual void init() = 0;
    virtual uint8_t getBatteryLevel() = 0;
    virtual bool isCharging() = 0;
    virtual void sleep(uint32_t milliseconds) = 0;
    virtual void deepSleep() = 0;
};