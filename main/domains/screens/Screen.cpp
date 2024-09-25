#include "Screen.h"
#include <stdexcept>

screen_type Screen::currentScreen;

Screen::Screen()
{
    printf("From contructor Screen.cpp");
}

Screen::~Screen()
{
}

// void Screen::show(screen_type screen)
// {
//     if (MAIN_SCREEN == screen)
//     {
//         printf("\n MAIN_SCREEN \n");
//     }
//     else if (MENU_SCREEN == screen)
//     {
//         printf("\n MENU_SCREEN \n");
//     }
//     else if (CAR_SELECT_SCREEN == screen)
//     {
//         printf("\n CAR_SELECT_SCREEN \n");
//     }
//     else if (NOTIFICATION_SCREEN == screen)
//     {
//         printf("\n NOTIFICATION_SCREEN \n");
//     }
//     else
//     {
//         printf("\n Invalid screen type \n");
//         throw std::invalid_argument("Invalid screen type");
//     }

//     this->currentScreen = screen;
// }

void Screen::init()
{
    // label.init();
    // label2.init();
    // label3.init();
    // label4.init();

    // label.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 0);
    // label2.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 16);
    // label3.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 32);
    // label4.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 48);
}

// void Screen::setTextFormatted(const char *fmt, float value)
// {
//     label.setTextFormated(fmt, value);
// }

void Screen::create() {}

void Screen::setCurrentScreen(screen_type screen)
{
    this->currentScreen = screen;
}

screen_type Screen::getCurrentScreen()
{
    return this->currentScreen;
}