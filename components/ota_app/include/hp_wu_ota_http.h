#ifndef _HP_WU_OTA_HTTP_
#define _HP_WU_OTA_HTTP_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"

#include "string.h"

#include "nvs.h"
#include "nvs_flash.h"

#include <sys/socket.h>

#define CONFIG_UPG_URL  "http://106.55.227.236:18884/zero_lib_idf.bin"

void ota_init(void);

#endif