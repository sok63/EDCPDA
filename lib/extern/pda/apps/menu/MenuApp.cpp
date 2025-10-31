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
    needRedraw_ = false;



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

void MenuApp::calculateApplicationRectInfo(uint32_t idx)
{
   rect_.applicationIdx_ = idx;

    // Вычисляем ряд и колонку
    rect_.row = (idx - 1) / 3;
    rect_.column = (idx - 1) % 3;

    

}
