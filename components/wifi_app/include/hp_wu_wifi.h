/*
 * @Author “Zero” “zero_bbx@qq.com”
 * @Date 2023-01-28 15:30:09
 * @LastEditors “Zero” “zero_bbx@qq.com”
 * @LastEditTime 2023-01-28 15:31:45
 * @FilePath \esp32idf_gpio\include\hp_wu_wifi.h
 * @Description 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _HP_WU_WIFI_
#define _HP_WU_WIFI_

#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include <unistd.h>
#include "esp_timer.h"
#include "esp_sntp.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

void wu_wifi_init();

bool wifi_connect_state();

#endif // !
