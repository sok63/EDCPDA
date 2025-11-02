#include "PaperS3RTCHAL.h"

#include <M5Unified.h>

void PaperS3RTCHAL::init()
{
}

DateTime PaperS3RTCHAL::getDateTime()
{
    auto result = DateTime();
    auto dt = M5.Rtc.getDateTime();
 
    result.year = dt.date.year;
    result.month = dt.date.month;
    result.day = dt.date.date;

    result.weekDay = dt.date.weekDay;

    result.hour = dt.time.hours;
    result.minute = dt.time.minutes;
    result.second = dt.time.seconds;

    return result;
}

void PaperS3RTCHAL::setDateTime(const DateTime &dt)
{
}

void PaperS3RTCHAL::setAlarm(const DateTime &dt)
{
}
