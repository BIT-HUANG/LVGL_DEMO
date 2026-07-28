#ifndef LVGL_GLOBAL_H
#define LVGL_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// 1. 输入设备全局句柄 外部声明
extern lv_indev_t *indev_encoder;
extern lv_indev_t *indev_keypad;

// 2. 焦点组全局句柄 外部声明
extern lv_group_t *group1;
extern lv_group_t *group2;

// 3. 跨文件可用的切换焦点组工具函数声明
void switch_input_group(lv_group_t *target_group);

#ifdef __cplusplus
}
#endif

#endif