#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(ApplicationRegistry * registry, ApplicationContext * context)
{
}

ApplicationManager::~ApplicationManager()
{
}

void ApplicationManager::init()
{
}

void ApplicationManager::launchApp(size_t appIndex)
{
}

void ApplicationManager::exitCurrentApp()
{
}

bool ApplicationManager::isAppRunning() const
{
    return currentApp_ != nullptr;
}

void ApplicationManager::update()
{
}

void ApplicationManager::render()
{
}

ApplicationRegistry *ApplicationManager::getRegistry()
{
    return registry_;
}

void ApplicationManager::transitionApp()
{
}
