#include <pda/applications/ApplicationManager.h>
#include <pda/applications/AApplication.h>
#include <pda/applications/ApplicationContext.h>

#include <pda/ui/widgets/Header.h>

#define MINIMAL_SPACING 10
#define HEADER_SPACING 30

#define CELLS_IN_ROW 4
#define CELLS_IN_COLUMN 7

#define CELL_SIZE 110
#define CELL_SPACING 20

#define ICON_SIZE 80

struct Position
{
    int x;
    int y;
};

struct CellRectInfo
{
    uint32_t idx;
    uint32_t column;
    uint32_t row;

    uint32_t width;
    uint32_t height;
    uint32_t x;
    uint32_t y;
};

struct CellAppInfo
{
    int8_t app;
    int8_t row;
    int8_t column;
};

class MenuApp : public AApplication
{
public:
    MenuApp(ApplicationContext* context, ApplicationManager* appManager);
    virtual ~MenuApp() = default;

    void onStart() override;
    void onStop() override;

    void update(uint32_t deltaTime) override;
    void render() override;

    const char* getName() const override;
    void drawIconTo(ADisplaySpriteHAL*) override;

    bool onEvent(const Event& event) override;

    void setAppPosition(uint32_t appNum, uint32_t position);

private:
    void drawMenu();
    void handleTouch(int16_t x, int16_t y);

    void calculateCellRect(uint32_t position);
    void calculateCellRect(uint32_t row, uint32_t column);

    // Draw widgets section
    void drawDateTimeBlock();
    void drawSliderBlock();
    void drawFastAccessBlock();
    void drawAppAtCell(uint32_t appNum, uint32_t position);

private:
    ApplicationContext* context_;
    ApplicationManager* appManager_;

    CellAppInfo apps_[32];

    ADisplaySpriteHAL* icon_;
    CellRectInfo rect_;

    size_t selectedIndex_ = 0;
    size_t pageNum_ = 0;

    // Widgets
    Header w_header_;
};