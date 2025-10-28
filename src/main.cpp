#include <Arduino.h>
#include <PaperS3/PaperS3.h>

#include <pda/sal/ConfigService.h>
#include <pda/sal/EventService.h>
#include <pda/sal/TimeService.h>

#include <pda/ApplicationManager.h>
#include <pda/ApplicationRegistry.h>

#include <pda/apps/menu/MenuApp.h>
#include <pda/apps/maps/MapsApp.h>


PaperS3 pda;

void setup() {
    pda.init();
   
    // Start adding apps to our pda
    pda.registerApplication(new MenuApp(pda.getApplicationContext(), pda.getApplicationManager()));
    pda.registerApplication(new MapsApp(pda.getApplicationContext(), pda.getApplicationManager()));
}

void loop() {
    pda.update();
}
