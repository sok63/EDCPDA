#include "Keyboard.h"

#include <M5Unified.h>
#include <pda/applications/ApplicationContext.h>

static std::vector<Key> row_1 = {
    {"Q", 1}, {"W", 1}, {"E", 1}, {"R", 1}, {"T", 1}, {"Y", 1}, {"U", 1}, {"I", 1}, {"O", 1}, {"P", 1}};

static std::vector<Key> row_2 = {
    {"A", 1}, {"S", 1}, {"D", 1}, {"F", 1}, {"G", 1}, {"H", 1}, {"J", 1}, {"K", 1.f}, {"L", 1.f}, {":", 1.f}};

static std::vector<Key> row_3 = {
    {" ", 1.f}, {"Z", 1}, {"X", 1}, {"C", 1}, {"V", 1}, {"B", 1}, {"N", 1}, {"M", 1}, {".", 1.f}, {"/", 1.f}};

static std::vector<std::vector<Key>> key_rows = {
    row_1,
    row_2,
    row_3};

Keyboard::Keyboard(EventService* event_service)
    : AWidget({0, 600, 540, 360})
    , event_service_(event_service)
{
}

void Keyboard::update()
{
}

void Keyboard::render(ADisplaySpriteHAL* to)
{
    to->drawLine(0, 700, 540, 700, 0);

    // Draw keyboard
    for (size_t row_idx = 0; row_idx < key_rows.size(); row_idx++)
        for (size_t idx = 0; idx < key_rows[row_idx].size(); ++idx) {
            calc_keyRectInfo(key_rows[row_idx], row_idx, idx);
            to->drawRect(key_rect_info_.x, key_rect_info_.y, key_rect_info_.w, key_rect_info_.h, 0);
            auto tw = to->getTextWidth(key_rows[row_idx][idx].label.c_str(), 4);
            auto th = to->getTextHeight(key_rows[row_idx][idx].label.c_str(), 4);
            to->drawText(key_rect_info_.x + key_rect_info_.w / 2 - tw / 2, key_rect_info_.y + key_rect_info_.h / 2 - th / 2, key_rows[row_idx][idx].label.c_str(), 0, 4);
        }
}

bool Keyboard::feed_event(const Event& event)
{

    if (event.type != eEventType::TOUCH_EVENT)
        return false;

    sTouchEvent* touch = (sTouchEvent*) (&(event.data));
    if ((touch->gesture != eGestureType::ONEF_TAP) and (touch->gesture != eGestureType::ONEF_DOUBLE_TAP))
        return false;

    // // Find cell (slow, need remake)
    bool flag = false;

    for (auto ridx = 0; ridx < key_rows.size(); ridx++) {
        if (flag)
            break;
        for (auto idx = 0; idx < key_rows[ridx].size(); idx++) {
            calc_keyRectInfo(key_rows[ridx], ridx, idx);

            if (!check_hit(key_rect_info_, touch->startX, touch->startY))
                continue;

            ch_ = key_rows[ridx][idx].label[0];
            post_event();
            if (touch->gesture == eGestureType::ONEF_DOUBLE_TAP)
                post_event(); // For double tap double post event
            return true;
        }
    }

    return false;
}

void Keyboard::calc_keyRectInfo(std::vector<Key>& row, uint32_t row_num, uint32_t cidx)
{
    uint32_t keyboard_y = 700;
    uint32_t keyboard_w = 540;

    int linePadding = 15;
    int keyGap = 4;
    int charW = 48;
    int charH = 63;

    // Precalc row_y
    uint32_t row_y = keyboard_y + linePadding;
    for (auto idx = 0; idx < row_num; idx++) {
        row_y += charH + linePadding;
    }

    // Precalc width of cells (to calc padding)
    auto cells_w = 0;
    for (auto idx = 0; idx < row.size(); idx++) {
        cells_w += (uint32_t) (charW * row[cidx].units);
        if (idx > 0)
            cells_w += keyGap;
    }

    key_rect_info_.y = row_y;
    key_rect_info_.w = (uint32_t) (charW * row[cidx].units);
    key_rect_info_.h = charH;

    // Calc true x position
    key_rect_info_.x = (keyboard_w - cells_w) / 2;
    for (auto idx = 0; idx < cidx; idx++) {
        key_rect_info_.x += (uint32_t) (charW * row[cidx].units);
        key_rect_info_.x += keyGap;
    }
}

char Keyboard::get_char()
{
    auto tmp = ch_;
    ch_ = '\0';
    return tmp;
}

void Keyboard::post_event()
{
    if (!event_service_)
        return;

    Serial.println("post2");
    Event event;
    event.type = eEventType::KEY_CHAR_EVENT;
    event.data[0] = ch_;
    event.timestamp = millis();

    event_service_->postEvent(event);
}
