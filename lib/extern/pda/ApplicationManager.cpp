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
  // Update header part

  // Update application part
}

void ApplicationManager::render()
{
  auto app = applicationRegistry_->getApplication(currentApp_);
  auto header = applicationRegistry_->getHeaderApplication();
  auto display = applicationContext_->getDisplay();

  if(!app->needRedraw()) return;


  display->beginTransaction();
  {
    // Render header
    if(header){
      header->render();
      display->applySpriteToScreen( display->getHeaderSprite(),0,0);
    }
    // Render application
    app->render();
    display->applySpriteToScreen(applicationContext_->getApplicationSprite(),0,29);
  }
  display->endTransaction();

  // Apply to all
  display->refresh();
}

ApplicationRegistry *ApplicationManager::getApplicationRegistry()
{
    return applicationRegistry_;
}

void ApplicationManager::transitionApp()
{
}
