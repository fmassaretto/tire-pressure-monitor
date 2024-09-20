#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_

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
    screen_type currentScreen;

public:
    Screen();
    ~Screen();
    void show(screen_type screen);
    screen_type getCurrentScreen();
};

#endif