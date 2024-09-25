#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "stdio.h"
#include "./domains/labels/Label.h"

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

protected:
    Label label1;
    Label label2;
    Label label3;
    Label label4;

public:
    Screen();
    virtual ~Screen();
    // void show(screen_type screen);
    void show();
    void init();
    screen_type getCurrentScreen();
    void setCurrentScreen(screen_type screen);
    virtual void create();
};

#endif