#include "PaperS3TouchHAL.h"
#include <cmath>
#include <esp32-hal.h>

#include <M5Unified.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

static QueueHandle_t events_q;

void task_touch(void* arg)
{
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(8));
        M5.update();
        size_t cnt = M5.Touch.getCount();
        for (size_t i = 0; i < cnt; ++i) {
            auto t = M5.Touch.getDetail(i);
            sTouchInput input;

            input.n = i;
            input.x = t.x;
            input.y = t.y;
            input.isPressed = t.isPressed();
            input.justPressed = t.wasPressed();
            input.justReleased = t.wasReleased();
            input.timestamp = millis();

            xQueueSend(events_q, &input, 0);
        }
    }
}

void PaperS3TouchHAL::init()
{
    Serial.println("Start touch thread");
    events_q = xQueueCreate(32, sizeof(sTouchInput));
    xTaskCreatePinnedToCore(task_touch, "touch", 4096, nullptr, 3, nullptr, 0);
}

sTouchEvent PaperS3TouchHAL::getNext()
{
    sTouchEvent event;
    touchDriver_.getNextEvent(event);
    return event;
}

void PaperS3TouchHAL::update()
{
    sTouchInput input;
    if (xQueueReceive(events_q, &input, 0) == pdTRUE) {
        touchDriver_.update(input);
    } else {
        input.n = 0;
        input.x = 0;
        input.y = 0;
        input.isPressed = false;
        input.justPressed = false;
        input.justReleased = false;
        input.timestamp = millis();
        // Update touch driver
        touchDriver_.update(input);
    }
}
