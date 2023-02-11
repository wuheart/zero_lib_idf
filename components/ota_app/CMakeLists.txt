idf_component_register(SRCS "hp_wu_ota_http.c"
                    INCLUDE_DIRS "include" REQUIRES nvs_flash esp_https_ota app_update)

