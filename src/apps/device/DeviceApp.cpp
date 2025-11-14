#include "DeviceApp.h"

DeviceApp::DeviceApp(ApplicationContext* context, ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
{
}

void DeviceApp::update(uint32_t deltaTime)
{
}

void DeviceApp::render()
{
}

const char* DeviceApp::getName() const
{
    return "Device";
}

void DeviceApp::drawIconTo(ADisplaySpriteHAL* sprite)
{
    auto render = context_->getRender();

    render->apply_draw_indexed_rect(sprite, 15, 5, 50, 70, 1, 0);
    render->apply_draw_indexed_rect(sprite, 20, 15, 40, 55, 1, 0);
    render->apply_draw_indexed_rect(sprite, 13, 10, 2, 10, 1, 0);

    render->apply_draw_indexed_text(sprite, 28, 32, "M5", 0, 2);
}

bool DeviceApp::onEvent(const Event& event)
{
    return false;
}
