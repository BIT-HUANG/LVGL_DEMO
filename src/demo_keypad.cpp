#include "demo_keypad.h"

void keypad_init()
{
    pinMode(KEY_UP,INPUT_PULLUP);
    pinMode(KEY_DOWN,INPUT_PULLUP);
    pinMode(KEY_LEFT,INPUT_PULLUP);
    pinMode(KEY_RIGHT,INPUT_PULLUP);
    pinMode(KEY_A,INPUT_PULLUP);
    pinMode(KEY_B,INPUT_PULLUP);
}

uint8_t key_state()
{
    if(digitalRead(KEY_UP) == LOW)
    {
        return 1; // 上键按下
    }
    else if (digitalRead(KEY_DOWN) == LOW)
    {
        return 2; // 下键按下
    }
    else if (digitalRead(KEY_LEFT) == LOW)
    {
        return 3; // 左键按下
    }
    else if (digitalRead(KEY_RIGHT) == LOW)
    {
        return 4; // 右键按下
    }
    else if (digitalRead(KEY_A) == LOW)
    {
        return 5; // A键按下
    }
    else if (digitalRead(KEY_B) == LOW)
    {
        return 6; // B键按下
    }
    else
    {
        return 0; // 没有按键按下
    }
}