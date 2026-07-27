#ifndef DEMO_ENCODER_H
#define DEMO_ENCODER_H

#include<Arduino.h>

// ===================== 编码器引脚定义（按你实际接线修改） =====================
#define ENCODER_A     33    // 编码器A相引脚
#define ENCODER_B     32    // 编码器B相引脚
#define ENCODER_C     26    // 编码器中间按压按键引脚

// ===================== 对外函数声明（.cpp里实现的函数必须在这里声明） =====================
void encoder_init();                // 编码器初始化
uint8_t encoder_press();           // 读取编码器按键
int16_t encoder_rotate();           // 获取旋转增量值

#endif // DEMO_ENCODER_H