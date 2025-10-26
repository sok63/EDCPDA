#include "PaperS3TouchHAL.h"

void PaperS3TouchHAL::init()
{
}

bool PaperS3TouchHAL::available()
{
    return false;
}

TouchPoint PaperS3TouchHAL::getPoint()
{
    return TouchPoint();
}

bool PaperS3TouchHAL::isPressed()
{
    return false;
}
