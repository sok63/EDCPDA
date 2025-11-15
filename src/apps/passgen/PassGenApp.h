#pragma once

#include <string>
#include <vector>

#include <pda/ApplicationManager.h>
#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>

#include "./ui/Button.h"
#include "./ui/ToggleButton.h"
#include "./ui/CharMatrix.h"
#include "./ui/Edit.h"
#include "./ui/Header.h"
#include "./ui/Keyboard.h"
#include "./ui/WidgetAppManager.h"

class PassGenApp : public AApplication
{
public:
    PassGenApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~PassGenApp() = default;

    void onStart() override;
    void onStop() override;


    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;

    WidgetAppManager wm_;

    Header w_header_;
    Keyboard w_keyboard_;

    char alphabet_buffer[256];
    char matrix_[100];

    char secret_str_[15];
    uint32_t secret_str_pos_ = 0;
    Edit w_edit_secret_;

    char site_str_[15];
    uint32_t site_str_pos_ = 0;
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