#include "demo_lvgl.h"

/*LVGL 刷新任务*/
void lvgl_task(void *pvParameters)
{
    while (1)
    {
        lv_tick_inc(20);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    
}

/*测试任务*/
void test_task(void *pvParameters)
{
    while (1)
    {
        Serial.println("Test Task ...");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
}

void setup()
{
    Serial.begin(115200);
 
    demo_lvgl_init();

    xTaskCreate(lvgl_task,"LVGL Task",16384,NULL,3,NULL);
    xTaskCreate(test_task,"Test Task",2048,NULL,2,NULL);

    vTaskStartScheduler();

}

 
void loop()
{
   
}