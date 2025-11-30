#include "MapsApp.h"
#include "M5Unified.h"

#include <pda/core/Kernel.h>
#include <pda/helpers/lvf/LVF.h>

AApplication* MapsApp::createInstance()
{
    return new MapsApp();
}

MapsApp::MapsApp()
    : w_header_()
    , calculator_(540, 960)
    , w_btn_less_details_({30, 800, 110, 110}, "-", 3)
    , w_btn_more_details_({400, 800, 110, 110}, "+", 3)
{
    calculator_.setCenterLatLon(52.53, 13.40);
    calculator_.setNewZoom(8.0);
    calculator_.setNewDetailLevel(13);
}

void MapsApp::drawIcon(ADisplaySpriteHAL* sprite)
{
    auto render = Kernel::getRender();

    // Vertical lines
    render->apply_draw_indexed_line(sprite, 10, 20, 10, 60, 1, 0);
    render->apply_draw_indexed_line(sprite, 25, 5, 25, 45, 1, 0);
    render->apply_draw_indexed_line(sprite, 40, 20, 40, 60, 1, 0);
    render->apply_draw_indexed_line(sprite, 55, 5, 55, 45, 1, 0);
    render->apply_draw_indexed_line(sprite, 70, 20, 70, 60, 1, 0);

    // Horizontal up part
    render->apply_draw_indexed_line(sprite, 10, 20, 25, 5, 1, 0);
    render->apply_draw_indexed_line(sprite, 25, 5, 40, 20, 1, 0);
    render->apply_draw_indexed_line(sprite, 40, 20, 55, 5, 1, 0);
    render->apply_draw_indexed_line(sprite, 55, 5, 70, 20, 1, 0);

    // Horizontal down part
    render->apply_draw_indexed_line(sprite, 10, 60, 25, 45, 1, 0);
    render->apply_draw_indexed_line(sprite, 25, 45, 40, 60, 1, 0);
    render->apply_draw_indexed_line(sprite, 40, 60, 55, 45, 1, 0);
    render->apply_draw_indexed_line(sprite, 55, 45, 70, 60, 1, 0);
}

bool MapsApp::onEvent(const Event& event)
{

    if (event.type != eEventType::TOUCH_EVENT) {
        return false;
    }

    if (w_header_.feed_event(event)) {
        return true;
    }

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));

    if (w_btn_less_details_.feed_event(event))
        return true;
    if (w_btn_more_details_.feed_event(event))
        return true;

    if ((touch->gesture == eGestureType::ONEF_DRAG) or (touch->gesture == eGestureType::ONEF_SWIPE_DOWN) or (touch->gesture == eGestureType::ONEF_SWIPE_UP) or (touch->gesture == eGestureType::ONEF_SWIPE_LEFT) or (touch->gesture == eGestureType::ONEF_SWIPE_RIGHT)) {

        int32_t pos_x = 540 / 2 - touch->deltaX; // 270
        int32_t pos_y = 960 / 2 - touch->deltaY; // 480

        Serial.printf("%d %d \n", pos_x, pos_y);

        calculator_.setNewCenterXY(pos_x, pos_y);
        Kernel::getDisplay()->setNeedRedraw();
    }

    if (touch->gesture == eGestureType::ONEF_DOUBLE_TAP) {
        calculator_.setNewCenterXY(touch->x, touch->y);
        calculator_.setNewZoom(calculator_.getZoom() / 2.);
        Kernel::getDisplay()->setNeedRedraw();
    }

    if (touch->gesture == eGestureType::ONEF_LONG_PRESS) {
        calculator_.setNewZoom(calculator_.getZoom() * 2.);
        Kernel::getDisplay()->setNeedRedraw();
    }

    // if (w_map_.feed_event(event)) {
    //     return true;
    // }

    return false;
}

void MapsApp::update(uint32_t deltaTime)
{
    if (w_header_.take_dirty_flag()) {
        Kernel::getDisplay()->setNeedRedraw();
    }
    // if (w_map_.take_dirty_flag()) {
    //     context_->getDisplay()->setNeedRedraw();
    // }

    if (w_btn_less_details_.is_pressed()) {
        calculator_.setNewDetailLevel(calculator_.getDetailLevel() - 1);
        Kernel::getDisplay()->setNeedRedraw();
        return;
    }

    if (w_btn_more_details_.is_pressed()) {
        calculator_.setNewDetailLevel(calculator_.getDetailLevel() + 1);
        Kernel::getDisplay()->setNeedRedraw();
        return;
    }
}

void MapsApp::render()
{
    Serial.println("DRAW");
    auto storage = Kernel::getStorage();
    auto display = Kernel::getDisplay();

    // w_map_.render(display);

    MapCalcResult r = calculator_.calculate();

    display->drawFillRect(0, 0, 540, 960, TFT_WHITE);
    for (auto x = 0; x < r.tilesX; x++) {
        for (auto y = 0; y < r.tilesY; y++) {

            LVFG::version_1::LVGFTileWorker::write_tile_to_pos(storage, display, r.tilesZ, r.startTileX + x, r.startTileY + y, r.offsetScreenX + x * r.tilePixelWidth, r.offsetScreenY + y * r.tilePixelHeight, r.tilePixelWidth, r.tilePixelHeight);
        }
    }

    w_btn_less_details_.render(display);
    w_btn_more_details_.render(display);
    w_header_.render(display);
}
