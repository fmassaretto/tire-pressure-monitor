#pragma once
#ifndef _MENUSCREEN_H
#define _MENUSCREEN_H

#include "./domains/screens/Screen.h"
// #include "./domains/labels/Label.h"

class MenuScreen : Screen
{
private:
    // Label label1;
    // Label label2;
    // Label label3;
    // Label label4;
    // lv_obj_t *scr;

public:
    MenuScreen();
    void init(lv_obj_t *scr);
    void show();
    void create();
};

#endif
