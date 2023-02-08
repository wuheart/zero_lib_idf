idf_component_register(SRCS "hp_wu_ble.c"
                        INCLUDE_DIRS "include" REQUIRES nvs_flash bt soc freertos mbedtls json)

