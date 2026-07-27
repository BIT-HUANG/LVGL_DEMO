#include "demo_encoder.h"
#include <ESP32Encoder.h>

ESP32Encoder encoder;

/*编码器初始化函数*/
void encoder_init()
{
    pinMode(ENCODER_A,INPUT_PULLUP); // 编码器A相引脚
    pinMode(ENCODER_B,INPUT_PULLUP); // 编码器B相引脚
    pinMode(ENCODER_C,INPUT_PULLUP); // 编码器按键引脚

    encoder.attachSingleEdge(ENCODER_B,ENCODER_A); // 绑定编码器AB相引脚，单边沿采样

    encoder.setFilter(1023); // 设置硬件滤波，最大设置值1023

    encoder.clearCount(); // 清空编码器内部计数，初始值为0
}

/*编码器按下读取*/
uint8_t encoder_press()
{
    return digitalRead(ENCODER_C); // 未按下高电平返回1，按下低电平返回0
}

/*编码器旋转读取*/
int16_t encoder_rotate()
{
    int32_t diff = encoder.getCount(); // 获取本次累计旋转脉冲差值
    encoder.clearCount(); //读完立刻清零
    return diff; //返回正数为顺时针转，复数为逆时针转

}