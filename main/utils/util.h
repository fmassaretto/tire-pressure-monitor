#pragma once

#ifndef _UTIL_H
#define _UTIL_H

#include "ui/ui.h"

class Util
{
private:
    static bool isChangePressureScale;

public:
    Util(/* args */);
    ~Util();
    static bool getChangePressureScale();
    static void changePressureScale(bool changeScale);
    static void updatePressureScale(lv_obj_t *label, bool changeScale);
};

#endif