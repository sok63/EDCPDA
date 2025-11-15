#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(ApplicationRegistry* applicationRegistry, ApplicationContext* applicationContext)
    : applicationContext_(applicationContext)
    , applicationRegistry_(applicationRegistry)
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
    auto app_prev = applicationRegistry_->getApplication(currentApp_);
    auto app_next = applicationRegistry_->getApplication(appIndex);

    // -= Stop previous application =-
    app_prev->onStop();
   
    // -= Start new application =-
    app_next->onStart();
    currentApp_ = appIndex;

    // Set needRedraw flag
    applicationContext_->getDisplay()->setNeedRedraw();
}

void ApplicationManager::exitCurrentApp()
{
    launchApp(0);
}

bool ApplicationManager::isAppRunning() const
{
    auto app = applicationRegistry_->getApplication(currentApp_);
    return app->getState() == eApplicationState::RUNNING;
}

void ApplicationManager::update()
{
    applicationRegistry_->getApplication(currentApp_)->update(0);
}

void ApplicationManager::render()
{
    auto display = applicationContext_->getDisplay();
    if (!display->isNeedRedraw())
        return;

    display->beginTransaction();
    applicationRegistry_->getApplication(currentApp_)->render();
    display->endTransaction();

    display->refresh();
}

ApplicationRegistry* ApplicationManager::getApplicationRegistry()
{
    return applicationRegistry_;
}

uint32_t ApplicationManager::getCurrentApplicationNum()
{
    return currentApp_;
}