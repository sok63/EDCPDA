#include "MenuApp.h"

MenuApp::MenuApp(ApplicationContext *context, ApplicationManager *appManager)
{
}

void MenuApp::onCreate()
{
}

void MenuApp::onStart()
{
}

void MenuApp::onResume()
{
}

void MenuApp::onPause()
{
}

void MenuApp::onStop()
{
}

void MenuApp::update(uint32_t deltaTime)
{
}

void MenuApp::render(ADisplayHAL *display)
{
}

const char *MenuApp::getName() const
{
    return "Menu";
}

const char *MenuApp::getDescription() const
{
    return "Application Launcher";
}

const uint8_t *MenuApp::getIcon() const
{
    return nullptr;
}

void MenuApp::onEvent(const Event &event)
{
}

AApplication *MenuApp::create(ApplicationContext *context)
{
    return nullptr;
}

void MenuApp::drawMenu()
{
}

void MenuApp::handleTouch(int16_t x, int16_t y)
{
}
