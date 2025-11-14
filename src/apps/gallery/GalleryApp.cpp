#include "GalleryApp.h"

GalleryApp::GalleryApp(ApplicationContext* context, ApplicationManager* appManager)
    : context_(context)
    , appManager_(appManager)
{
}

void GalleryApp::update(uint32_t deltaTime)
{
}

void GalleryApp::render()
{
}

const char* GalleryApp::getName() const
{
    return "Gallery";
}

void GalleryApp::drawIconTo(ADisplaySpriteHAL* sprite)
{
    auto render = context_->getRender();

    render->apply_draw_indexed_rect(sprite, 10, 10, 60, 60, 1, 0);
    render->apply_draw_indexed_circle(sprite, 27, 25, 5, 1, 0);

    render->apply_draw_indexed_line(sprite, 10, 50, 25, 35, 1, 0);
    render->apply_draw_indexed_line(sprite, 25, 35, 35, 45, 1, 0);
    render->apply_draw_indexed_line(sprite, 35, 45, 50, 30, 1, 0);
    render->apply_draw_indexed_line(sprite, 50, 30, 69, 50, 1, 0);
}

bool GalleryApp::onEvent(const Event& event)
{
    return false;
}
