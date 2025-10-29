#include "AApplication.h"

bool AApplication::needRedraw()
{
    return needRedraw_;
}

eApplicationState AApplication::getState()
{
    return state_;
}