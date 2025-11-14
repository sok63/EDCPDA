#pragma once

#include <cstddef>
#include <cstdint>

#include <pda/hal/AStorageHAL.h>

class PaperS3StorageHAL : public AStorageHAL
{
public:
    virtual ~PaperS3StorageHAL() = default;

    bool init() override;
    bool exists(const char* path) override;
    bool readFile(const char* path, uint8_t* buffer, size_t* size) override;
    bool writeFile(const char* path, const uint8_t* buffer, size_t size) override;
    bool deleteFile(const char* path) override;
    bool mkdir(const char* path) override;
    bool listDir(const char* path, char** files, size_t* count) override;
};