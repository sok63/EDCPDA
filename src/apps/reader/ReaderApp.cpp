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

const char *ReaderApp::getDescription() const
{
    return "Reader application";
}

const uint8_t *ReaderApp::getIcon() const
{
    return nullptr;
}

bool ReaderApp::onEvent(const Event &event)
{
    return false;
}
