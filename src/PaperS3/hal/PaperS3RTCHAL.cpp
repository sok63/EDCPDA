#include "PaperS3RTCHAL.h"

#include <M5Unified.h>

void PaperS3RTCHAL::init()
{
    // Read time data from RTC
    m5::rtc_time_t rtcTime;
    m5::rtc_date_t rtcDate;
    
    M5.Rtc.getTime(&rtcTime);
    M5.Rtc.getDate(&rtcDate);

    // Make ESP32 timedata format
    struct tm timeinfo;
    timeinfo.tm_year  = rtcDate.year - 1900;  // tm_year - годы с 1900
    timeinfo.tm_mon   = rtcDate.month - 1;    // tm_mon: 0-11
    timeinfo.tm_mday  = rtcDate.date;
    timeinfo.tm_hour  = rtcTime.hours;
    timeinfo.tm_min   = rtcTime.minutes;
    timeinfo.tm_sec   = rtcTime.seconds;
    timeinfo.tm_wday  = rtcDate.weekDay;
    timeinfo.tm_isdst = -1;                   // auto DST

    // Convert to time_t
    time_t t = mktime(&timeinfo);
    
    // Set system time of ESP32
    struct timeval now = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&now, NULL);

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
