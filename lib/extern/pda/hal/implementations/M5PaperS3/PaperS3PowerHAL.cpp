#include "PaperS3PowerHAL.h"

#include <M5Unified.h>

void PaperS3PowerHAL::init()
{
}

uint8_t PaperS3PowerHAL::getBatteryLevel()
{
    return M5.Power.getBatteryLevel();
}

bool PaperS3PowerHAL::isCharging()
{
    return false;
}

void PaperS3PowerHAL::sleep(uint32_t milliseconds)
{
}

void PaperS3PowerHAL::deepSleep()
{
}
