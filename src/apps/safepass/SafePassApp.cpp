#include "SafePassApp.h"

SafePassApp::SafePassApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void SafePassApp::update(uint32_t deltaTime)
{
}

void SafePassApp::render()
{
}

const char *SafePassApp::getName() const
{
    return "SafePass";
}

void SafePassApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
    auto render = context_->getRender();
    render->apply_draw_indexed_text(sprite,25,28,"***",0,2);
}

bool SafePassApp::onEvent(const Event &event)
{
    return false;
}
