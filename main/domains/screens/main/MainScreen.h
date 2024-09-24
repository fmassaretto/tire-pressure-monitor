#pragma once
#ifndef _MAINSCREEN_H
#define _MAINSCREEN_H

#include "./domains/screens/Screen.h"
#include "./domains/labels/Label.h"
#include "domains/sensors/temperature/Temperature.h"

class MainScreen : Screen
{
private:
    Label labelMain1;
    Label labelMain2;
    Label labelMain3;
    Label labelMain4;
    Temperature temperature;

public:
    MainScreen();
    ~MainScreen();
    void init();
    void show();
};

#endif
