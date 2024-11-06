#include "util.h"
#include "stdio.h"

bool Util::isChangePressureScale;

Util::Util(/* args */)
{
}

Util::~Util()
{
}

void Util::changePressureScale(bool changeScale)
{
    printf("%d \n", changeScale);
    isChangePressureScale = changeScale;
}

bool Util::getChangePressureScale()
{
    return isChangePressureScale;
}

void Util::updatePressureScale(lv_obj_t *label, bool changeScale)
{
    lv_label_set_text(label, changeScale ? "BAR" : "PSI");
}