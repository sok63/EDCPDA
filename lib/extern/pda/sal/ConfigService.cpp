#include "ConfigService.h"

ConfigService::ConfigService(AStorageHAL* storage)
{
}

bool ConfigService::loadConfig(const char* key, char* value, size_t maxLen)
{
    return false;
}

bool ConfigService::saveConfig(const char* key, const char* value)
{
    return false;
}

bool ConfigService::deleteConfig(const char* key)
{
    return false;
}
