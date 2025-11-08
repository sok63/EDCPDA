#include "PassGenApp.h"

PassGenApp::PassGenApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void PassGenApp::update(uint32_t deltaTime)
{
}

void PassGenApp::render()
{
}

const char *PassGenApp::getName() const
{
    return "PassGen";
}

void PassGenApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
    auto render = context_->getRender();
  render->apply_draw_indexed_text(sprite,16,28,"!a_8",0,2);
}

bool PassGenApp::onEvent(const Event &event)
{
    return false;
}
