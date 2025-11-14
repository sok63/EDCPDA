#include "MapsApp.h"


MapsApp::MapsApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager)
{
}

const char *MapsApp::getName() const
{
    return "Maps";
}

void MapsApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
   auto render = context_->getRender();

   // Vertical lines
   render->apply_draw_indexed_line(sprite,10,20,10,60,1,0);
   render->apply_draw_indexed_line(sprite,25,5,25,45,1,0);
   render->apply_draw_indexed_line(sprite,40,20,40,60,1,0);
   render->apply_draw_indexed_line(sprite,55,5,55,45,1,0);
   render->apply_draw_indexed_line(sprite,70,20,70,60,1,0);
   
   // Horizontal up part
   render->apply_draw_indexed_line(sprite,10,20,25,5,1,0);
   render->apply_draw_indexed_line(sprite,25,5,40,20,1,0);
   render->apply_draw_indexed_line(sprite,40,20,55,5,1,0);
   render->apply_draw_indexed_line(sprite,55,5,70,20,1,0);

   // Horizontal down part
   render->apply_draw_indexed_line(sprite,10,60,25,45,1,0);
   render->apply_draw_indexed_line(sprite,25,45,40,60,1,0);
   render->apply_draw_indexed_line(sprite,40,60,55,45,1,0);
   render->apply_draw_indexed_line(sprite,55,45,70,60,1,0);

}

bool MapsApp::onEvent(const Event &event)
{
    return false;
}

void MapsApp::update(uint32_t deltaTime)
{
}

void MapsApp::render()
{
    // auto sprite = context_->getApplicationSprite();
    // sprite->clear();
    // context_->getDisplay()->applySpriteToScreen(context_->getApplicationSprite(),0,29);
}
