#include <Arduino.h>

#include <PaperS3/PaperS3.h>

#include "apps/menu/MenuApp.h"
#include "apps/maps/MapsApp.h"
#include "apps/reader/ReaderApp.h"
#include "apps/gallery/GalleryApp.h"
#include "apps/weather/WeatherApp.h"
#include "apps/device/DeviceApp.h"
#include "apps/calendar/CalendarApp.h"
#include "apps/safepass/SafePassApp.h"
#include "apps/passgen/PassGenApp.h"


PaperS3 pda;

void setup() {

    Serial.begin(115200);
    Serial.println("M5 Paper S3 Touch Gesture Demo");

    pda.init();
   
    // Start adding apps to our pda
    auto menu = new MenuApp(pda.getApplicationContext(), pda.getApplicationManager());
    pda.registerApplication(menu); // At first debug menu

    // First apps line
    pda.registerApplication(new MapsApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(1,2);

    pda.registerApplication(new ReaderApp(pda.getApplicationContext(), pda.getApplicationManager()));
    menu->setAppPosition(2,3);
    
    // Second apps line
    pda.registerApplication(new GalleryApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(3,4);

    pda.registerApplication(new WeatherApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(4,5);

    pda.registerApplication(new DeviceApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(5,6);

    pda.registerApplication(new CalendarApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(6,7);

    // Third apps line
    pda.registerApplication(new SafePassApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(7,8);

    pda.registerApplication(new PassGenApp(pda.getApplicationContext(), pda.getApplicationManager())); 
    menu->setAppPosition(8,9);

}

void loop() {
    pda.update();
}
