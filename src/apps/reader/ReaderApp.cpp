#include "ReaderApp.h"

ReaderApp::ReaderApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void ReaderApp::update(uint32_t deltaTime)
{
}

void ReaderApp::render()
{
}

const char *ReaderApp::getName() const
{
    return "Reader";
}

void ReaderApp::drawIconTo(ADisplaySpriteHAL *)
{
}

bool ReaderApp::onEvent(const Event &event)
{
    return false;
}
