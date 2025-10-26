#pragma once 

#include <cstdint>
#include <cstddef>

class AStorageHAL {
public:
    virtual ~AStorageHAL() = default;
    
    virtual bool init() = 0;
    virtual bool exists(const char* path) = 0;
    virtual bool readFile(const char* path, uint8_t* buffer, size_t* size) = 0;
    virtual bool writeFile(const char* path, const uint8_t* buffer, size_t size) = 0;
    virtual bool deleteFile(const char* path) = 0;
    virtual bool mkdir(const char* path) = 0;
    virtual bool listDir(const char* path, char** files, size_t* count) = 0;
};