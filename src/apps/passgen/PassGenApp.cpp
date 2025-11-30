#include "PassGenApp.h"

#include <M5Unified.h>

#include <pda/core/Kernel.h>

#include <pda/helpers/shuffler/Shuffler.h>
#include <pda/ui/widgets/Label.h>

AApplication* PassGenApp::createInstance()
{
    return new PassGenApp;
}

PassGenApp::PassGenApp()
    : w_edit_site_({110, 585, 300, 40}, 15)
    , w_edit_secret_({110, 650, 300, 40}, 15)
    , w_header_()
    , w_btn_sw_({420, 585, 110, 110}, "SW", 3)
    ,

    w_btn_chd_({10, 540, 60, 40}, "DG", 2)
    , w_btn_chb_({75, 540, 60, 40}, "CB", 2)
    , w_btn_chs_({140, 540, 60, 40}, "CS", 2)
    , w_btn_chs1_({205, 540, 60, 40}, "S1", 2)
    ,

    w_btn_chs2_({270, 540, 60, 40}, "S2", 2)
    , w_btn_chs3_({335, 540, 60, 40}, "S3", 2)
    , w_btn_chs4_({400, 540, 60, 40}, "S4", 2)
    , w_btn_chs5_({465, 540, 60, 40}, "S5", 2)
    , w_keyboard_(Kernel::getEventService())
{

    // Special on place case
    wm_.renderList()->push_back(new CharMatrix({20, 30, 500, 500}, (char*) matrix_, 10, 10));
    wm_.renderList()->push_back(new Label({10, 585, 100, 40}, "Site", 2));
    wm_.renderList()->push_back(new Label({10, 650, 100, 40}, "Secret", 2));

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

    w_edit_secret_.set_selection(is_secret_selected);
    w_btn_chb_.set_pressed();
    w_btn_chd_.set_pressed();
    w_btn_chs_.set_pressed();
    w_btn_chs1_.set_pressed();
}

void PassGenApp::update(uint32_t deltaTime)
{
    // Update buttons
    if (w_btn_sw_.is_pressed()) {
        is_secret_selected = !is_secret_selected;
        w_edit_secret_.set_selection(is_secret_selected);
        w_edit_site_.set_selection(!is_secret_selected);
    }

    // Check others
    for (auto& el : *wm_.renderList()) {
        if (el->take_dirty_flag())
            Kernel::getDisplay()->setNeedRedraw();
    }
}

void PassGenApp::render()
{

    // Before render recalculate matrix
    ShufflerConfig config;
    config.charset_mask = 0;

    if (w_btn_chb_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_UPPER;
    if (w_btn_chd_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_DIGITS;
    if (w_btn_chs_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_LOWER;

    if (w_btn_chs1_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_SPECIAL_1;
    if (w_btn_chs2_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_SPECIAL_2;
    if (w_btn_chs3_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_SPECIAL_3;
    if (w_btn_chs4_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_SPECIAL_4;
    if (w_btn_chs5_.is_pressed())
        config.charset_mask = config.charset_mask | CHARSET_SPACE;

    config.rows = 10;
    config.cols = 10;

    if (config.charset_mask) {
        Shuffler shuffler;
        shuffler.init(config, alphabet_buffer, matrix_);
        shuffler.shuffle(w_edit_site_.get_text_(), w_edit_secret_.get_text_());
    }

    // Now draw result
    auto display = Kernel::getDisplay();

    // Render widgets
    for (auto& el : *wm_.renderList()) {
        el->render(display);
    }
}

void PassGenApp::drawIcon(ADisplaySpriteHAL* sprite)
{
    auto render = Kernel::getRender();
    render->apply_draw_indexed_text(sprite, 15, 32, "!a_8", 0, 2);
}

bool PassGenApp::onEvent(const Event& event)
{

    // Feed widgets with event
    for (auto& el : *wm_.listnersList()) {
        if (el->feed_event(event))
            return true;
    }

    return false;
}