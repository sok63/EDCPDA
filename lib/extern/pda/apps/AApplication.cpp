#include "AApplication.h"

void AApplication::onCreate()
{
}

void AApplication::onStart()
{
}

void AApplication::onResume()
{
}

void AApplication::onPause()
{
}

void AApplication::onStop()
{
}

bool AApplication::needRedraw()
{
    return needRedraw_;
}

eApplicationState AApplication::getState()
{
    return state_;
}