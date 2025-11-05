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
  auto display = applicationContext_->getDisplay();

  if(!display->isNeedRedraw()) return;

  auto app = applicationRegistry_->getApplication(currentApp_);
  auto header = applicationRegistry_->getHeaderApplication();
    
  display->beginTransaction();
  {
    // Render at first app to screen, than header (cause header can overlap application)
    app->render();
    header->render();
  }
  display->endTransaction();

  // Apply to screen
  display->refresh();
}

ApplicationRegistry *ApplicationManager::getApplicationRegistry()
{
    return applicationRegistry_;
}

void ApplicationManager::transitionApp()
{
}
