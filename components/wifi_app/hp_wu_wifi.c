/*
 * @Author “Zero” “zero_bbx@qq.com”
 * @Date 2023-01-28 15:29:35
 * @LastEditors “Zero” “zero_bbx@qq.com”
 * @LastEditTime 2023-01-30 11:17:56
 * @FilePath \esp32idf_gpio\src\hp_wu_wifi.c
 * @Description 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "hp_wu_wifi.h"

bool wifi_is_connect = false;
/**
 * @brief 用于初始化nvs 
 * @return {*}
 */
void nvs_init(){
    esp_err_t err = nvs_flash_init();
    if(err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND){
        // 初始化失败，检查错误，重新初始化
        nvs_flash_erase();
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}


void fun(struct timeval* tv) {
    time_t now = 0;
    struct tm timeinfo = {0};

    time(&now);
    localtime_r(&now, &timeinfo);

    char str[64];
    strftime(str, sizeof(str), "%c", &timeinfo);
    ESP_LOGI("TAG", "time updated: %s", str);
}

void tcp_client(){
    int _socket = 0;

createSocket:

    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    // AF_INET表示IPv4，AF_INET6表示IPv6

    // SOCK_STREAM表示TCP；
    // SOCK_DGRAM表示UDP；
    // SOCK_RAW表示RAW

    // protocol， 规定套接字发送和接送哪类型协议数据。
    // 最常见的是 IPPROTO_TCP, IPPROTO_UDP, IPPROTO_UDPLITE、IPPROTO_ICMP。
    // 如果 domain 和 type已经确定唯一的协议，“0（IPPROTO_IP）” 可以用来表示选择一个默认的协议。
 if(_socket < 0){
        printf("Socket 创建失败, 错误代码：%d\n", errno);
        vTaskDelete(NULL);
    }else{
        printf("Socket 创建成功");
    }

    struct sockaddr_in desk_addr = {
    // 下边这个IP 192.168.31.138和端口号8080是自己设置的，请按需要修改
        .sin_addr.s_addr = inet_addr("106.55.227.236"),	
        .sin_family = AF_INET,
        .sin_port = htons(18884),    // 小端模式转为大端模式
    };

    int err;
    while (1) {
        err = connect(_socket, (struct sockaddr*)&desk_addr, sizeof(desk_addr));
        if (err == 0){
            ESP_LOGI("CLIENT", "连接成功");
            break;
        }else{
            ESP_LOGI("CLIENT", "连接失败，错误代码：%d", errno);
            close(_socket);
            vTaskDelay(pdMS_TO_TICKS(200));
            
            goto createSocket; // goto标签
            
        }
    }
// API接口
// socket()
// bind()
// listen()
// connect()
// accept()
// send(), recv(), sendto(), recvfrom()
// close()
// gethostbyname()
// select()
// pool()
// getsockopt(), setsockopt()

}

void wifi_scan(){

    uint16_t num = 0;
    esp_wifi_scan_start( NULL, true);
    esp_wifi_scan_get_ap_num(&num);
    wifi_ap_record_t records[num];
    esp_wifi_scan_get_ap_records(&num, records);
    
    // 这个for循环是用来将RSSI信号强度，转换成信号等级。
	// 如 rssi_level == 5 时，表示WiFi满格
    for(int i = 0; i < num; i++){
        uint8_t rssi_level = 0;
        switch (records[i].rssi) {
            case -100 ... -88:
                rssi_level = 1; break;
            case -87 ... -77:
                rssi_level = 2; break;
            case -76 ... -66:
                rssi_level = 3; break;
            case -65 ... -55:
                rssi_level = 4; break;
            default:
                if(records[i].rssi < -100){
                    rssi_level = 0;
                }else{
                    rssi_level = 5;
                }
                break;
        }

	// 逐条打印扫描到的WiFi
        printf("—————【第 %2d 个WiFi】———————\n", i+1);
        printf("WiFi名称: %s\n", records[i].ssid);
        printf("信号强度: %d格\n", rssi_level);
        printf("WiFi: 安全类型: %d\n\n", records[i].authmode);
    }
    esp_wifi_scan_stop();
}

bool wifi_connect_state(){
    return wifi_is_connect;
}

/**
 * @brief 事件处理
 * @param {void*} arg 表示传递的参数
 * @param {esp_event_base_t} event_base 事件基
 * @param {int32_t} event_id 事件id
 * @param {void*} event_data 传递给事件的数据
 * @return {*}
 */
void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
    
    if(event_base == WIFI_EVENT){
        switch (event_id) {
            case WIFI_EVENT_STA_START:
                /* code */
                ESP_LOGI("WIFI", "wifi sta start");
                //wifi_scan();
                esp_wifi_connect();
                break;
            case WIFI_EVENT_STA_CONNECTED:
                ESP_LOGI("WIFI", "wifi connected");
                wifi_is_connect = true;
//              sntp_stop();
//              sntp_init();
                //tcp_client();
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                ESP_LOGI("WIFI", "wifi disconnected");
                ESP_LOGI("WIFI", "wifi reconnecting...");
                wifi_is_connect = false;
                esp_wifi_connect();
                break;
            case WIFI_EVENT_AP_START:
                ESP_LOGI("WIFI", "wifi ap start");
                break;
            case WIFI_EVENT_AP_STACONNECTED:
                ESP_LOGI("WIFI", "wifi sta connected");
                break;
            default:
                break;
        }
    }
    else if(event_base == IP_EVENT){
        switch (event_id)
        {
        case IP_EVENT_STA_GOT_IP:
            /* code */
            //ip_event_got_ip_t* ip_data = (ip_event_got_ip_t*) event_data;
            //ESP_LOGI("WIFI", "Got IP: ", IPSTR, IP2STR(&((ip_data->ip_info).ip)));
            break;
        case IP_EVENT_AP_STAIPASSIGNED:
            ESP_LOGI("WIFI", "AP 分配的 IP: ");
            break;
        default:
            break;
        }
    }

}

/**
 * @brief wifi 初始化
 * @return {*}
 */
void wu_wifi_init(){
    nvs_init();
    
    esp_netif_init();  //初始化网络接口
    esp_event_loop_create_default();   
    esp_netif_create_default_wifi_sta();
    //esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t cfg_sta = {
        // .ap = {
        // .ssid = "esp32_wifi",
        // .ssid_len = 11,
        // .channel = 11,
        // .password = "88888888",
        // .max_connection = 5,
        // .authmode = WIFI_AUTH_WPA_WPA2_PSK
        // }, 
        .sta = {
            .ssid = "HOPE",
            .password = "12347890",
        }
    };

    esp_wifi_set_config(WIFI_IF_STA, &cfg_sta);
    //esp_wifi_set_config(WIFI_IF_AP, &cfg_sta);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, NULL);
    esp_wifi_start();
    //sntp_set_time_sync_notification_cb(fun);

}