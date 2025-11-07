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
  auto app_prev = applicationRegistry_->getApplication(currentApp_);
  auto app_next = applicationRegistry_->getApplication(appIndex);

  // Stop before start if not stopped
  if(app_prev->getState() != eApplicationState::STOPPED){
    app_prev->onStop();
  }

  app_next->onStart();
  currentApp_ = appIndex;
  
  // Set needRedraw flag
  applicationContext_->getDisplay()->setNeedRedraw();
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
  // FIXME: deltatime != 0
  applicationRegistry_->getHeaderApplication()->update(0);
  applicationRegistry_->getApplication(currentApp_)->update(0);
  
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

uint32_t ApplicationManager::getCurrentApplicationNum()
{
    return currentApp_;
}

void ApplicationManager::transitionApp()
{
}
