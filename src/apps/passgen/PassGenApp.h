#pragma once

#include <string>
#include <vector>

#include <pda/applications/AApplication.h>

#include <pda/ui/widgets/Button.h>
#include <pda/ui/widgets/CharMatrix.h>
#include <pda/ui/widgets/Edit.h>
#include <pda/ui/widgets/Header.h>
#include <pda/ui/widgets/Keyboard.h>
#include <pda/ui/widgets/ToggleButton.h>
#include <pda/ui/widgets/WidgetAppManager.h>

class PassGenApp : public AApplication
{
public:
    static AApplication* createInstance();
    PassGenApp();
    virtual ~PassGenApp() = default;

    void update(uint32_t deltaTime) override;
    void render() override;

    static void drawIcon(ADisplaySpriteHAL*);

    bool onEvent(const Event& event) override;

private:
    WidgetAppManager wm_;

    Header w_header_;
    Keyboard w_keyboard_;

    char alphabet_buffer[256];
    char matrix_[100];

    Edit w_edit_secret_;
    Edit w_edit_site_;

    Button w_btn_sw_;

    ToggleButton w_btn_chd_;
    ToggleButton w_btn_chb_;
    ToggleButton w_btn_chs_;
    ToggleButton w_btn_chs1_;

    ToggleButton w_btn_chs2_;
    ToggleButton w_btn_chs3_;
    ToggleButton w_btn_chs4_;
    ToggleButton w_btn_chs5_;

    bool is_secret_selected = true;
};