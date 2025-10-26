#include <Arduino.h>

#include <PaperS3/hal/PaperS3DisplayHAL.h>
#include <PaperS3/hal/PaperS3PowerHAL.h>
#include <PaperS3/hal/PaperS3RTCHAL.h>
#include <PaperS3/hal/PaperS3StorageHAL.h>
#include <PaperS3/hal/PaperS3TouchHAL.h>

#include <pda/sal/ConfigService.h>
#include <pda/sal/EventService.h>
#include <pda/sal/TimeService.h>

#include <pda/ApplicationManager.h>
#include <pda/ApplicationRegistry.h>

#include <pda/apps/menu/MenuApp.h>
#include <pda/apps/maps/MapsApp.h>


// Define HAL
PaperS3DisplayHAL displayHal;
PaperS3TouchHAL touchHal;
PaperS3StorageHAL storageHal;
PaperS3RTCHAL rtcHal;
PaperS3PowerHAL powerHal;

// Define serevices
EventService eventService;
ConfigService configService(&storageHal);
TimerService timerService;

// Define Application stuff
ApplicationContext appContext(&displayHal, &touchHal, &storageHal, &rtcHal, &powerHal, &eventService, &configService, &timerService);
ApplicationRegistry appRegistry;
ApplicationManager appManager(&appRegistry, &appContext);


void setup() {
    //M5.begin();
    
    // Initialize HAL
    displayHal.init();
    touchHal.init();
    storageHal.init();
    rtcHal.init();
    powerHal.init();
    
    // Register applications
    auto menuApp = new MenuApp(&appContext,&appManager);
    appRegistry.registerApp("Menu", "Application Launcher", menuApp);

    auto mapsApp = new MapsApp(&appContext, &appManager);
    appRegistry.registerApp("Maps", "Offline maps", mapsApp);

    // Initialize app manager
    appManager.init();
    appManager.launchApp(0);
}

void loop() {
    //M5.update();
    
    // Process hardware events
    if (touchHal.available()) {
        TouchPoint point = touchHal.getPoint();
        Event event;
        event.type = point.pressed ? EventType::TOUCH_PRESS : EventType::TOUCH_RELEASE;
        event.data = &point;
        event.timestamp = millis();
        eventService.postEvent(event);
    }
    
    // Update services
    timerService.update();
    eventService.processEvents();
    
    // Update and render app
    appManager.update();
    appManager.render();
    
    delay(10);
}
