#pragma once

#include <string>
#include <vector>

#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>

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