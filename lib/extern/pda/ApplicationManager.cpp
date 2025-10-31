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
  auto display = applicationContext_->getDisplay();

  if(!app->needRedraw()) return;


  display->beginTransaction();
  {
    // Render header
    auto hs = display->getHeaderSprite();

    hs->drawRect(0,0,539,29,0);
    display->applySpriteToScreen(hs,0,0);

    hs->drawRect(0,0,539,29,0);
    display->applySpriteToScreen(hs,15,15);

    // Render application
    app->render(display);
    applicationContext_->getApplicationSprite()->drawRect(0,0,200,200,0);
    display->applySpriteToScreen(applicationContext_->getApplicationSprite(),100,100);
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
