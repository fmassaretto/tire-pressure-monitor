#pragma once
#ifndef _MENUSCREEN_H
#define _MENUSCREEN_H

#include "./domains/screens/Screen.h"
#include "./domains/labels/Label.h"

class MenuScreen : Screen
{
private:
    Label label;
    Label label2;
    Label label3;
    Label label4;

public:
    void init();
    void show();
};

#endif
