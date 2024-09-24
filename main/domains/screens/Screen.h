#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "stdio.h"
// #include "./domain/label/Label.h"

enum
{
    MAIN_SCREEN = 0,
    MENU_SCREEN,
    NOTIFICATION_SCREEN,
    CAR_SELECT_SCREEN
};
typedef unsigned int screen_type;

class Screen
{
private:
    static screen_type currentScreen;

public:
    Screen();
    ~Screen();
    // Label label;
    // Label label2;
    // Label label3;
    // Label label4;
    // void show(screen_type screen);
    void show();
    void init();
    screen_type getCurrentScreen();
    void setCurrentScreen(screen_type screen);
    // void setTextFormatted(const char *fmt, float value);
};

#endif