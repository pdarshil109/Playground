#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "common.h"
#include "wifi_manager.h"
#include "mqtt_client.h"
#include "sensor.h"
#include <stdio.h>
#ifdef PWM_TEST
#include "driver/ledc.h"
#endif
#include "esp_err.h"
static const char *TAG = "APP_MAIN";

//#define PWM_TEST
//#define GPIO_TEST

#ifdef GPIO_TEST
#define LED_GPIO GPIO_NUM_2
#endif

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (18) // Use GPIO18 (choose your pin!)
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_FREQUENCY          (5000) // Frequency in Hz


void app_main(void)
{
    ESP_LOGI(TAG, "ESP Playground Project Started!");
#ifdef GPIO_TEST    
    /* Configure the pin as output */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),   // select pin
        .mode = GPIO_MODE_OUTPUT,             // set as output
        .pull_up_en = GPIO_PULLUP_DISABLE,    // disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE,// disable pull-down
        .intr_type = GPIO_INTR_DISABLE        // disable interrupts
    };
    gpio_config(&io_conf);
#endif
#ifdef PWM_TEST
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 2. Configure the channel
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // start with 0% duty
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
#endif
    // 3. Fade duty cycle up and down
    while (1) {
        ESP_LOGI(TAG, "ESP Playground Running...");
        vTaskDelay(pdMS_TO_TICKS(500));
#ifdef PWM_TEST
        for (int duty = 0; duty < (1 << LEDC_DUTY_RES); duty += 100) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        for (int duty = (1 << LEDC_DUTY_RES) - 1; duty > 0; duty -= 100) {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
#endif //PWM_TEST
#ifdef GPIO_TEST
        gpio_set_level(LED_GPIO, 1);   // turn ON
        ESP_LOGI(TAG, "LED_GPIO GPIO_NUM_2 turn ON!");
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_GPIO, 0);   // turn OFF
        ESP_LOGI(TAG, "LED_GPIO GPIO_NUM_2 turn OFF!");
        vTaskDelay(pdMS_TO_TICKS(500));
#endif //GPIO_TEST
    }
}
