#pragma once
#ifndef _LABEL_H_
#define _LABEL_H_

#include "esp_lvgl_port.h"
#include "lvgl.h"

class Label
{
private:
    lv_obj_t *label;

public:
    Label(/* args */);
    ~Label();
    void init();
    void setLabel(lv_label_long_mode_t mode, unsigned int alignX, unsigned int alignY);
    void setTextFormated(const char *fmt, float value);
};

#endif