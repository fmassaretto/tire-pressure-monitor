#include "Label.h"

Label::Label()
{
}

Label::~Label()
{
}

void Label::init()
{
    // lv_scr_load(this->scr);
    // this->scr = lv_disp_get_scr_act(nullptr);
}

void Label::setLabel(lv_obj_t *scr, lv_label_long_mode_t mode, unsigned int alignX, unsigned int alignY)
{
    lvgl_port_lock(0);
    // lv_obj_t *scr1 = lv_obj_create(NULL);
    // this->label = lv_label_create(scr1);
    this->label = lv_label_create(scr);
    lv_label_set_long_mode(label, mode);
    lv_label_set_text(label, " ");
    lv_obj_set_width(label, 128);
    lv_obj_align(label, LV_ALIGN_TOP_MID, alignX, alignY);
    // lv_obj_clean(lv_scr_act());
    lvgl_port_unlock();
}

void Label::setTextFormated(const char *fmt, float value)
{
    lvgl_port_lock(0);
    lv_label_set_text_fmt(label, fmt, value);
    lvgl_port_unlock();
}

void Label::setText(char const *text)
{
    lvgl_port_lock(0);
    lv_label_set_text(label, text);
    lvgl_port_unlock();
}

void Label::clearScreen()
{
    lvgl_port_lock(0);
    lv_obj_clean(lv_scr_act());
    lvgl_port_unlock();
}