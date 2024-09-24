#include "MenuScreen.h"

void MenuScreen::init()
{
    // Label::init();
    // Label::init();
    // Label::init();
    // Label::init();
    this->label.init();
    this->label2.init();
    this->label3.init();
    this->label4.init();

    this->label.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 0);
    this->label2.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 16);
    this->label3.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 32);
    this->label4.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 48);
}

void MenuScreen::show()
{
    setCurrentScreen(MENU_SCREEN);
    printf("From MenuScreen.cpp");

    // this->label.clearScreen();

    this->label.setTextFormated("Teste 5", 1.0);
    this->label2.setTextFormated("Teste 6", 1.0);
    this->label3.setTextFormated("Teste 7", 1.0);
    this->label4.setTextFormated("Teste 8", 1.0);
}
