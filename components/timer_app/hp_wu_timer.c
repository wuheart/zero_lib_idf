/*
 * @Author ��Zero�� ��zero_bbx@qq.com��
 * @Date 2022-12-13 17:06:21
 * @LastEditors “Zero” “zero_bbx@qq.com”
 * @LastEditTime 2023-01-30 11:29:13
 * @FilePath \mdf_meshc:\Users\Wu\Documents\PlatformIO\Projects\esp32idf_gpio\src\hp_wu_timer.c
 * @Description ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/timer.h"
#include "freertos/queue.h"

#define TIMER_DIVIDER         16  //  Ӳ����ʱ����Ƶ��
#define TIMER_FREQ           (TIMER_BASE_CLK / TIMER_DIVIDER)  // ��ʱ������Ƶ��

//count = TIMER_SCALE * time(second);
//time(second) = count / TIMER_SCALE;

static xQueueHandle queue;

static bool timer_callback(void *args){
    uint64_t val;
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    val = timer_group_get_counter_value_in_isr(0, 0);
    /*
     * ���д��룺
     * ����������������������������������������
     * ����ʱ����ֵ����һ������
     *�����ڱ�ʾ��ʹ�õ��Զ���װ��ģʽ��
     * �����ڱ�ʾ�������valֵ�����塣
     * ֻ��Ϊ��չʾ��isr callback�л�
     * ȡ��ʱ��ֵ������ʹ�á�����
     * ���ô���_in_isr�ĺ�������
     * ����������������������������������������
     */
    
    //ͨ�����н� val ��������
    xQueueSendFromISR(queue, (void*)&val, &pxHigherPriorityTaskWoken);

    return pxHigherPriorityTaskWoken;
}

static void task(void *arg){
    uint64_t counts = 0ull;
    while(1){
        printf("��һ�ν���!!\n");
        counts ++;
        uint64_t val;
        if(xQueueReceive(queue, &val, portMAX_DELAY)){
            printf("��ʱ���� %llu ���ж�-------------------------\n", counts);
            printf("��ʱֵ %llu \n", val);
        }
    }
}

static void task2(void *arg){
    uint64_t counts = 0ull;
    while(1){
        
        while (1)
        {
            //taskENTER_CRITICAL(0);
            printf("task2 runinging -----\n");

            //taskEXIT_CRITICAL(0);
            
        }
    }
}


#define TIM_HARE    1
#define TIM_WARE    
esp_timer_handle_t timer1;
void timer1Interrupt(void *args){
   
    printf("Timer1 Interrupt, state:periodic\n" );

}

void hp_timer_init(void)
{

#ifdef TIM_HARE

    queue = xQueueCreate(10, sizeof(uint64_t));
    timer_config_t config = {
        .alarm_en = 1,
        .counter_en = 0,
        .counter_dir = TIMER_COUNT_UP,
        .auto_reload = 1,
        .divider = 16,
    };

    timer_init(0, 0, &config);
    timer_set_counter_value(0, 0, 0x00ull);
    timer_set_alarm_value(0, 0, TIMER_FREQ * 3);
    timer_enable_intr(0, 0);
    
    timer_isr_callback_add(0, 0, timer_callback, NULL, ESP_INTR_FLAG_IRAM);

    xTaskCreate(task, "timer_test_task", 2048, NULL, 5, NULL);
    xTaskCreate(task2, "timer_test_task2", 2048, NULL, 4, NULL);
    timer_start(0, 0);
    printf("��ʱ�������ɹ���\n");

#elif  TIM_WARE ==1
    esp_timer_init();
    esp_timer_create_args_t args = {
        .callback = timer1Interrupt,
        .arg = (void*)1,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "Tiemr1",
        .skip_unhandled_events = false,
    };
    esp_timer_create(&args, &timer1);
    esp_timer_start_periodic(timer1, 500e3);

#endif // DEBUG

}
