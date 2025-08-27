#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

void app_main(void)
{
    ESP_LOGI("HELLO", "Hello ESP32 Playground!");
    while (1) {
        printf("Hello from ESP32! Uptime: %lld ms\n", esp_timer_get_time()/1000);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
