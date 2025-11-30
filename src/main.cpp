#include <Arduino.h>

#include "apps/maps/MapsApp.h"
#include "apps/menu/MenuApp.h"
#include "apps/passgen/PassGenApp.h"

#include <pda/core/Kernel.h>
#include <pda/core/PDA.h>

#include <pda/hal/implementations/FastEPD/FastEPDDisplayHAL.h>

#include <pda/hal/implementations/M5PaperS3/PaperS3DisplayHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3DisplaySpriteHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3LVRenderHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3PowerHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3RTCHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3StorageHAL.h>
#include <pda/hal/implementations/M5PaperS3/PaperS3TouchHAL.h>

static AppDescriptor g_apps[] = {
    {0, "Menu", &MenuApp::createInstance, nullptr},
    {1, "Maps", &MapsApp::createInstance, &MapsApp::drawIcon},
    {2, "PassGen", &PassGenApp::createInstance, &PassGenApp::drawIcon},

};

static AppFactory g_appFactory(g_apps, sizeof(g_apps) / sizeof(g_apps[0]));

static PDA* pda;

void setup()
{
    auto cfg = M5.config();
    cfg.clear_display = false;
    M5.begin(cfg);

    Serial.begin(115200);
    sleep(3);

    // Fill Kernel with implemenatations
    auto kernel = Kernel::getInstance();

    Kernel::setApplicationFactory(&g_appFactory);

    Kernel::setDisplay(new PaperS3DisplayHAL());
    Kernel::setRender(new PaperS3LVRenderHAL);
    Kernel::setTouch(new PaperS3TouchHAL());
    Kernel::setStorage(new PaperS3StorageHAL());
    Kernel::setRTC(new PaperS3RTCHAL());
    Kernel::setPower(new PaperS3PowerHAL());
    Kernel::setEventService(new EventService());

    Kernel::getDisplay()->init();
    Kernel::getTouch()->init();
    Kernel::getStorage()->init();
    Kernel::getRTC()->init();
    Kernel::getPower()->init();

    pda = new PDA;

    Kernel::setApplication(0);

}

void loop()
{
    pda->run_cycle();
}
