#include "Screen.h"
#include <stdexcept>
screen_type Screen::currentScreen;

Screen::Screen()
{
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

void Screen::setCurrentScreen(screen_type screen)
{
    this->currentScreen = screen;
}

screen_type Screen::getCurrentScreen()
{
    return this->currentScreen;
}
