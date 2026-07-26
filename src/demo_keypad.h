#ifndef DEMO_KEYPAD_H
#define DEMO_KEYPAD_H

#include<Arduino.h>

/*按键引脚定义*/
#define KEY_UP     2
#define KEY_DOWN   13
#define KEY_LEFT   27
#define KEY_RIGHT  35
#define KEY_A      34
#define KEY_B      12

void keypad_init(); // 按键初始化
uint8_t key_state(); // 读取按键状态，返回按键编号


#endif // DEMO_KEYPAD_H
