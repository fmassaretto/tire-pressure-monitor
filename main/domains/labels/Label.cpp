#include "Label.h"

Label::Label(/* args */)
{
}

Label::~Label()
{
}

void Label::init()
{
    this->scr = lv_disp_get_scr_act(nullptr);
}

void Label::setLabel(lv_label_long_mode_t mode, unsigned int alignX, unsigned int alignY)
{
    this->label = lv_label_create(scr);
    lv_label_set_long_mode(label, mode);
    lv_label_set_text(label, " ");
    lv_obj_set_width(label, 128);
    lv_obj_align(label, LV_ALIGN_TOP_MID, alignX, alignY);
}

void Label::setTextFormated(const char *fmt, float value)
{
    lv_label_set_text_fmt(label, fmt, value);
}

void Label::clearScreen()
{
    lv_obj_clean(lv_scr_act());
}