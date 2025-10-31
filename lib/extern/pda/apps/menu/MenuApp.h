#include <pda/apps/AApplication.h>
#include <pda/apps/ApplicationContext.h>
#include <pda/ApplicationManager.h>


struct Position {
    int x;
    int y;
};


struct ApplicationRectInfo {
    uint32_t applicationIdx_;
    Position rect_;
    Position icon_;
    Position text_;
    uint32_t width;
    uint32_t height;
    uint32_t column;
    uint32_t row;
};


class MenuApp : public AApplication {
public:
    MenuApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~MenuApp() = default;
    
    void onCreate() override;
    void onStart() override;
    void onResume() override;
    void onPause() override;
    void onStop() override;
    
    void update(uint32_t deltaTime) override;
    void render(ADisplayHAL* display) override;
    
    const char* getName() const override;
    const char* getDescription() const override;
    const uint8_t* getIcon() const override;
    
    void onEvent(const Event& event) override;
    
    static AApplication* create(ApplicationContext* context);

private:
    void drawMenu();
    void handleTouch(int16_t x, int16_t y);
    
    void calculateApplicationRectInfo(uint32_t applicationIndex);

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;
    
    ApplicationRectInfo rect_;

    size_t selectedIndex_ = 0;
    size_t pageNum_ = 0;

};