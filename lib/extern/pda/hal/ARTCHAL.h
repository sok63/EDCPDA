#pragma once 

#include <cstdint>

struct DateTime {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

class ARTCHAL {
public:
    virtual ~ARTCHAL() = default;
    
    virtual void init() = 0;
    virtual DateTime getDateTime() = 0;
    virtual void setDateTime(const DateTime& dt) = 0;
    virtual void setAlarm(const DateTime& dt) = 0;
};