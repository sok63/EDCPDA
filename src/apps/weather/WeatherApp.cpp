#include "WeatherApp.h"

WeatherApp::WeatherApp(ApplicationContext* context, ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
{
}

void WeatherApp::update(uint32_t deltaTime)
{
}

void WeatherApp::render()
{
}

const char* WeatherApp::getName() const
{
    return "Weather";
}

void WeatherApp::drawIconTo(ADisplaySpriteHAL* sprite)
{
    auto render = context_->getRender();

    render->apply_draw_indexed_line(sprite, 10, 10, 70, 10, 1, 0);
    render->apply_draw_indexed_line(sprite, 15, 20, 60, 20, 1, 0);
    render->apply_draw_indexed_line(sprite, 20, 30, 65, 30, 1, 0);
    render->apply_draw_indexed_line(sprite, 35, 40, 70, 40, 1, 0);
    render->apply_draw_indexed_line(sprite, 40, 50, 60, 50, 1, 0);
    render->apply_draw_indexed_line(sprite, 35, 60, 50, 60, 1, 0);
    render->apply_draw_indexed_line(sprite, 30, 70, 40, 70, 1, 0);
}

bool WeatherApp::onEvent(const Event& event)
{
    return false;
}
