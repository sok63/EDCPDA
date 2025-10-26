#include <pda/hal/AStorageHAL.h>

class ConfigService {
private:
    AStorageHAL* storage_;
    
public:
    ConfigService(AStorageHAL* storage);
    
    bool loadConfig(const char* key, char* value, size_t maxLen);
    bool saveConfig(const char* key, const char* value);
    bool deleteConfig(const char* key);
};