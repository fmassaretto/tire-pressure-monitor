#include "MenuScreen.h"

MenuScreen::MenuScreen() : Screen()
{
    printf("From contructor MenuScreen.cpp");
    // if (!lv_obj_is_valid(scr))
    // {
    // scr = lv_disp_get_scr_act(nullptr);
    // // }

    // this->init();
    // lv_obj_clean(lv_scr_act());
}

void MenuScreen::init(lv_obj_t *scr)
{
    label1.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 0);
    label2.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 16);
    label3.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 32);
    label4.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 48);

    // lv_obj_clean(scr);
}

void MenuScreen::create()
{
    printf("From create() MenuScreen.cpp");
    setCurrentScreen(MENU_SCREEN);

    // label1.clearScreen();

    label1.setText("");
    label2.setText("");
    label3.setText("");
    label4.setText("");
    label1.setText("Teste 5");
    label2.setText("Teste 6");
    label3.setText("Teste 7");
    label4.setText("Teste 8");
}

void MenuScreen::show()
{
    setCurrentScreen(MENU_SCREEN);
    printf("From MenuScreen.cpp");

    // this->label.clearScreen();

    this->label1.setTextFormated("Teste 5", 1.0);
    this->label2.setTextFormated("Teste 6", 1.0);
    this->label3.setTextFormated("Teste 7", 1.0);
    this->label4.setTextFormated("Teste 8", 1.0);
}
