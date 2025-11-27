#include "PaperS3StorageHAL.h"

bool PaperS3StorageHAL::init()
{
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
    if (!SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
        Serial.print("SD card not detected");
        return false;
    }

    
    return true;
}

File PaperS3StorageHAL::open(const String& path, const char* mode, const bool create)
{
    return SD.open(path, FILE_READ);
}

bool PaperS3StorageHAL::exists(const char* path)
{
    return false;
}

bool PaperS3StorageHAL::readFile(const char* path, uint8_t* buffer, size_t* size)
{
    return false;
}

bool PaperS3StorageHAL::writeFile(const char* path, const uint8_t* buffer, size_t size)
{
    return false;
}

bool PaperS3StorageHAL::deleteFile(const char* path)
{
    return false;
}

bool PaperS3StorageHAL::mkdir(const char* path)
{
    return false;
}

bool PaperS3StorageHAL::listDir(const char* path, char** files, size_t* count)
{
    return false;
}
