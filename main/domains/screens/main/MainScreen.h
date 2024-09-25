#pragma once
#ifndef _MAINSCREEN_H
#define _MAINSCREEN_H

#include "./domains/screens/Screen.h"
// #include "./domains/labels/Label.h"
#include "./domains/sensors/temperature/Temperature.h"
#include "./domains/sensors/pressure/Pressure.h"

class MainScreen : Screen
{
private:
    Temperature temperature;
    Pressure pressure;

public:
    MainScreen();
    ~MainScreen();
    void init(lv_obj_t *scr);
    void show();
    void create();
};

#endif
