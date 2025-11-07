#include "ReaderApp.h"

ReaderApp::ReaderApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

void ReaderApp::update(uint32_t deltaTime)
{
}

void ReaderApp::render()
{
}

const char *ReaderApp::getName() const
{
    return "Reader";
}

void ReaderApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
   auto render = context_->getRender();

   // Vertical lines
   render->apply_draw_indexed_line(sprite,10,30,10,70,1,0);
   render->apply_draw_indexed_line(sprite,30,10,30,70,1,0);
   render->apply_draw_indexed_line(sprite,50,10,50,70,1,0);
   render->apply_draw_indexed_line(sprite,70,20,70,70,1,0);

   // Horizontal part
   render->apply_draw_indexed_line(sprite,10,70,70,70,1,0);


   render->apply_draw_indexed_line(sprite,10,30,30,30,1,0);
   render->apply_draw_indexed_line(sprite,30,10,50,10,1,0);
   render->apply_draw_indexed_line(sprite,50,20,70,20,1,0);
   
   render->apply_draw_indexed_line(sprite,14,60,26,60,1,0);
   render->apply_draw_indexed_line(sprite,34,60,46,60,1,0);
   render->apply_draw_indexed_line(sprite,54,60,66,60,1,0);
   
}

bool ReaderApp::onEvent(const Event &event)
{
    return false;
}
