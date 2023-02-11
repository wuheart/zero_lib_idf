idf_component_register(SRCS "zero_lib_idf.c"
                    INCLUDE_DIRS "." REQUIRES  adc_app ble_app gpio_app http_app mqtt_app ota_app timer_app uart_app
                                                wifi_app lvgl_port lvgl)
