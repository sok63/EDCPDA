#include <Arduino.h>

#include <PaperS3/PaperS3.h>

#include "apps/header/HeaderApplication.h"
#include "apps/menu/MenuApp.h"
#include "apps/maps/MapsApp.h"
#include "apps/reader/ReaderApp.h"

PaperS3 pda;

void setup() {

    Serial.begin(115200);
    Serial.println("M5 Paper S3 Touch Gesture Demo");

    pda.init();
   
    // Start adding apps to our pda
    pda.getApplicationRegistry()->setHeaderApplication(new HeaderApplication(pda.getApplicationContext(), pda.getApplicationManager()));

    pda.registerApplication(new MenuApp(pda.getApplicationContext(), pda.getApplicationManager())); // At first debug menu
    pda.registerApplication(new MapsApp(pda.getApplicationContext(), pda.getApplicationManager())); // Minimal one "true" app to debug menu
    pda.registerApplication(new ReaderApp(pda.getApplicationContext(), pda.getApplicationManager())); // Minimal one "true" app to debug menu

}

void loop() {
    pda.update();
    //delay(100);
}
