/*
 * @Author “Zero” “zero_bbx@qq.com”
 * @Date 2023-02-07 10:18:18
 * @LastEditors “Zero” “zero_bbx@qq.com”
 * @LastEditTime 2023-02-07 10:22:41
 * @FilePath \esp32idf_gpio\include\hp_wu_ble.h
 * @Description 
 */

#ifndef _HP_WU_BLE_
#define _HP_WU_BLE_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Attributes State Machine */
enum
{
    IDX_SVC,
    IDX_CHAR_A,
    IDX_CHAR_VAL_A,


    IDX_CHAR_B,
    IDX_CHAR_VAL_B,

    IDX_CHAR_C,
    IDX_CHAR_VAL_C,

    IDX_CHAR_D,
    IDX_CHAR_VAL_D,

    HRS_IDX_NB,
};

void ble_servie_init();


#endif // !