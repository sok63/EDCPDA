#include "PaperS3StorageHAL.h"

bool PaperS3StorageHAL::init()
{
    return false;
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
