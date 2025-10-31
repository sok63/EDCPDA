#include <Arduino.h>

#include <PaperS3/PaperS3.h>
#include <pda/apps/menu/MenuApp.h>
#include <pda/apps/maps/MapsApp.h>

PaperS3 pda;

void setup() {
    pda.init();
   
    // Start adding apps to our pda
    pda.registerApplication(new MenuApp(pda.getApplicationContext(), pda.getApplicationManager())); // At first debug menu
    pda.registerApplication(new MapsApp(pda.getApplicationContext(), pda.getApplicationManager())); // Minimal one "true" app to debug menu
}

void loop() {
    pda.update();
    delay(100);
}
