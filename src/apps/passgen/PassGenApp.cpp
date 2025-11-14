#include "PassGenApp.h"

#include "M5Unified.h"

#include "./driver/shuffler/Shuffler.h"
#include "./ui/Label.h"

PassGenApp::PassGenApp(ApplicationContext *context, ApplicationManager *appManager): context_(context), appManager_(appManager), 
w_edit_site_({110,585,300,40},(char*)site_str_,15), w_edit_secret_({110,650,300,40},(char*)secret_str_,15), w_header_(context), 
w_btn_sw_({420,585,110,110},"SW",3), 

     w_btn_chd_({10,540,60,40},"DG",2),
     w_btn_chb_({75,540,60,40},"CB",2),
     w_btn_chs_({140,540,60,40},"CS",2),
     w_btn_chs1_({205,540,60,40},"S1",2),
    
     w_btn_chs2_({270,540,60,40},"S2",2),
     w_btn_chs3_({335,540,60,40},"S3",2),
     w_btn_chs4_({400,540,60,40},"S4",2),
     w_btn_chs5_({465,540,60,40},"S5",2)
{
    context_->getEventService()->addListener(this);

    // Special on place case
    wm_.renderList()->push_back(new CharMatrix({20,30,500,500},(char*)matrix_,10,10));
    wm_.renderList()->push_back(new Label({10,585,100,40},"Site",2));
    wm_.renderList()->push_back(new Label({10,650,100,40},"Secret",2));

    // Fill widget manager
    wm_.push_front(&w_header_);

    wm_.push_back(&w_btn_sw_);
    wm_.push_back(&w_edit_site_);
    wm_.push_back(&w_edit_secret_);
    wm_.push_back(&w_btn_chb_);
    wm_.push_back(&w_btn_chd_);
    wm_.push_back(&w_btn_chs_);
    wm_.push_back(&w_btn_chs1_);
    wm_.push_back(&w_btn_chs2_);              
    wm_.push_back(&w_btn_chs3_);
    wm_.push_back(&w_btn_chs4_);
    wm_.push_back(&w_btn_chs5_);
    wm_.push_back(&w_keyboard_);

    sprintf(secret_str_, "");
    sprintf(site_str_, "");    
}

void PassGenApp::update(uint32_t deltaTime)
{
  // Update keyboard  
  auto ch = w_keyboard_.get_char();
  if(ch>0){
    if(is_secret_selected){
      secret_str_[secret_str_pos_] = ch;
      secret_str_pos_+=1;
      secret_str_[secret_str_pos_] = '\0'; 
    } else {
      site_str_[site_str_pos_] = ch;
      site_str_pos_+=1;
      site_str_[site_str_pos_] = '\0'; 
    }
    context_->getDisplay()->setNeedRedraw();
  }

  // Update buttons
  if(w_btn_sw_.is_pressed()){
    is_secret_selected = !is_secret_selected;
  }


 }

void PassGenApp::render()
{
  // Before render recalculate matrix
  ShufflerConfig config;
  config.charset_mask = CHARSET_DIGITS | CHARSET_UPPER | CHARSET_LOWER | CHARSET_SPECIAL_1;
  config.rows = 10;
  config.cols = 10;

  Shuffler shuffler;
  shuffler.init(config, alphabet_buffer, matrix_);
    

  shuffler.shuffle(site_str_, secret_str_);

  // Now draw result
  auto display = context_->getDisplay();

  // Render widgets
  for(auto& el: *wm_.renderList()){
    el->render(display);
  }
  
  }

const char *PassGenApp::getName() const
{
    return "PassGen";
}

void PassGenApp::drawIconTo(ADisplaySpriteHAL *sprite)
{
  auto render = context_->getRender();
  render->apply_draw_indexed_text(sprite,15,32,"!a_8",0,2);
}

bool PassGenApp::onEvent(const Event &event)
{

  // Feed widgets with event
  for(auto& el: *wm_.listnersList()){
    if(el->feed_event(event)) return true;
  }

  return false;
}