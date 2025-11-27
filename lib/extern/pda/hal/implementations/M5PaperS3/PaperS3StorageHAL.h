#pragma once

#include <cstddef>
#include <cstdint>

#include <M5Unified.h>

#include <pda/hal/interfaces/AStorageHAL.h>

// #include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define SD_SPI_CS_PIN 47
#define SD_SPI_SCK_PIN 39
#define SD_SPI_MOSI_PIN 38
#define SD_SPI_MISO_PIN 40

class PaperS3StorageHAL : public AStorageHAL
{
public:
    virtual ~PaperS3StorageHAL() = default;

    bool init() override;
    File open(const String& path, const char* mode = FILE_READ, const bool create = false) override;
    bool exists(const char* path) override;
    bool readFile(const char* path, uint8_t* buffer, size_t* size) override;
    bool writeFile(const char* path, const uint8_t* buffer, size_t size) override;
    bool deleteFile(const char* path) override;
    bool mkdir(const char* path) override;
    bool listDir(const char* path, char** files, size_t* count) override;
};