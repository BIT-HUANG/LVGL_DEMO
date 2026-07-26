#ifndef DEMO_LVGL_H
#define DEMO_LVGL_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui/ui.h"
#include "demo_encoder.h"
#include "demo_keypad.h"

//extern lv_indev_t *indev_encoder;
void demo_lvgl_init();

#endif // DEMO_LVGL_H
