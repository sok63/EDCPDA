#pragma once

#include <pda/hal/interfaces/AStorageHAL.h>

class ConfigService
{
public:
    ConfigService(AStorageHAL* storage);

    bool loadConfig(const char* key, char* value, size_t maxLen);
    bool saveConfig(const char* key, const char* value);
    bool deleteConfig(const char* key);

private:
    AStorageHAL* storage_;
};