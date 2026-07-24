#include "demo_encoder.h"
#include "demo_lvgl.h"

/*定义分辨率为静态全局变量，常量不可修改*/
static const uint16_t screenWidth = TFT_WIDTH; // 宽度128
static const uint16_t screenHeight = TFT_HEIGHT; // 高度160

/*定义文件内静态 LVGL 显示缓冲区管理结构体对象 draw_buf，用于管理绘图缓存*/
static lv_disp_draw_buf_t draw_buf;
/*定义文件内静态 LVGL 像素颜色类型数组 buf，作为分块刷新的绘图像素缓存，容量为屏幕宽度乘以 10 行像素*/
static lv_color_t buf[screenWidth * 10];
/*调用 TFT_eSPI 显示屏驱动类构造函数，传入屏幕宽高，创建名为 tft 的屏幕驱动实例对象*/
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);



/*定义 LVGL 屏幕刷新回调函数disp_flush_cb，入参分别为显示驱动指针、刷新区域只读指针、待刷新像素颜色缓存指针*/
void disp_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_buf)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_buf->full, w * h, true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

/*定义静态LVGL编码器输入设备读取回调函数encoder_read，入参分别为输入设备驱动指针、输入设备数据存储指针*/
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    data -> enc_diff = encoder_rotate();

    if (encoder_press())
    {
        data -> state = LV_INDEV_STATE_RELEASED;
    }
    else
    {
        data -> state = LV_INDEV_STATE_PRESSED;
    }

}

/*LVGL与编码器整体初始化函数*/
void demo_lvgl_init()
{
    encoder_init(); // 初始化编码器
    
    lv_init(); // LVGL图形库底层初始化，分配内存、初始化内核
    tft.begin(); // TFT_eSPI屏幕硬件初始化，启动SPI屏幕驱动
    tft.setRotation(3); // 设置屏幕旋转参数3，调整屏幕画面显示方向

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10); // 初始化LVGL绘图缓冲区

    static lv_disp_drv_t disp_drv; // 定义静态LVGL显示驱动结构体
    lv_disp_drv_init(&disp_drv);  // 对显示驱动结构体进行默认参数初始化

    disp_drv.hor_res = screenWidth; // 给显示驱动配置屏幕横向分辨率宽度
    disp_drv.ver_res = screenHeight;  // 给显示驱动配置屏幕纵向分辨率高度
    disp_drv.flush_cb = disp_flush_cb; // 绑定屏幕刷新回调函数
    disp_drv.draw_buf = &draw_buf; // 将之前初始化好的绘图缓冲区绑定到显示驱动
    lv_disp_drv_register(&disp_drv); // 将配置完成的显示驱动注册进LVGL内核，正式启用屏幕输出

    /*串口输出初始化信息*/
    String LVGL_Vesion = String("V") + lv_version_major() + "." + lv_version_minor() + "." +lv_version_patch();
    Serial.println("Hello Arduino !"); 
    Serial.println(LVGL_Vesion); 

    /*初始化输入设备*/
    lv_indev_t *indev_encoder = NULL; // 定义LVGL输入设备指针并初始化为空
    static lv_indev_drv_t encoder_drv; // 定义静态LVGL输入设备驱动结构体
    lv_indev_drv_init(&encoder_drv); // 对输入设备驱动结构体填充默认初始化参数
    encoder_drv.type = LV_INDEV_TYPE_ENCODER; // 设置输入设备类型为编码器模式
    encoder_drv.read_cb = encoder_read; // 绑定编码器数据读取回调函数
    indev_encoder = lv_indev_drv_register(&encoder_drv); // 返回编码器设备指针保存为全局变量给group设置用

    /*初始化UI*/
    lv_group_t *group1; // 定义LVGL控件组指针group1，切换页面时绑定输入设备指针
    ui_init(); //ui初始化
    group1 = lv_group_create(); // 创建一个新的控件焦点组，分配内存并返回组句柄赋值给group1
    lv_indev_set_group(indev_encoder, group1); // 将编码器输入设备与控件组绑定，操作仅作用于该组内控件
    lv_group_add_obj(group1, ui_Arc1); // 将控件添加到焦点组
    lv_group_add_obj(group1, ui_Switch1); // 将控件添加到焦点组
    lv_group_add_obj(group1, ui_Slider1); // 将控件添加到焦点组
    lv_group_add_obj(group1, ui_Checkbox1); // 将控件添加到焦点组
}