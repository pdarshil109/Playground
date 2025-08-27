#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "common.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensor.h"

static const char *TAG = "APP_MAIN";

#define LED_GPIO GPIO_NUM_2

void app_main(void)
{
    ESP_LOGI(TAG, "ESP Playground Project Started!");
    /* Configure the pin as output */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),   // select pin
        .mode = GPIO_MODE_OUTPUT,             // set as output
        .pull_up_en = GPIO_PULLUP_DISABLE,    // disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE,// disable pull-down
        .intr_type = GPIO_INTR_DISABLE        // disable interrupts
    };
    gpio_config(&io_conf);
    
    while (1) {
        gpio_set_level(LED_GPIO, 1);   // turn ON
        ESP_LOGI(TAG, "LED_GPIO GPIO_NUM_2 turn ON!");
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_GPIO, 0);   // turn OFF
        ESP_LOGI(TAG, "LED_GPIO GPIO_NUM_2 turn OFF!");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
