#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "soc/gpio_reg.h"

#include "hp_wu_gpio.h"
#include "hp_wu_adc.h"
#include "hp_wu_timer.h"
#include "hp_wu_uart.h"
#include "hp_wu_wifi.h"
#include "hp_wu_mqtt.h"
#include "hp_wu_httpclient.h"
#include "hp_wu_ble.h"

void app_main(void) {
    //gpio_Init();
    //xTaskCreate(xTaskOne, "xTask1", 1000, NULL, 1, NULL );
    //adc_init();
    //hp_timer_init();
//     app_uart_init(print_free_ram);
    ble_servie_init();
    wu_wifi_init();
    //wu_mqtt_start();
    while (1) {
        //gpio_set_level(GPIO_NUM_19,1);
        //gpio_set_level(GPIO_NUM_18,0);
        printf("main is running ! \n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
//        http_native_request();

    }

}
