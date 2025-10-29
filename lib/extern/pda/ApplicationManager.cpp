#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(ApplicationRegistry * applicationRegistry, ApplicationContext * applicationContext): applicationContext_(applicationContext), applicationRegistry_(applicationRegistry)
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
  auto app = applicationRegistry_->getApplication(appIndex);
  
  // Stop before start if not stopped
  if(app->getState() != eApplicationState::STOPPED){
    app->onStop();
  }

  app->onStart();
}

void ApplicationManager::exitCurrentApp()
{
}

bool ApplicationManager::isAppRunning() const
{
    auto app = applicationRegistry_->getApplication(currentApp_);
    return app->getState() == eApplicationState::RUNNING;
}

void ApplicationManager::update()
{
}

void ApplicationManager::render()
{
  auto app = applicationRegistry_->getApplication(currentApp_);
  auto display = applicationContext_->getDisplay();

  if(!app->needRedraw()) return;
 
  display->getScreenSprite()->clear();
  app->render(display);
  display->refresh();
}

ApplicationRegistry *ApplicationManager::getApplicationRegistry()
{
    return applicationRegistry_;
}

void ApplicationManager::transitionApp()
{
}
