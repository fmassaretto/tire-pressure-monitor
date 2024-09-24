#include "MainScreen.h"

// Temperature *temperature;

MainScreen::MainScreen()
{
    new Temperature();
    new Pressure();
}

MainScreen::~MainScreen() {}

void MainScreen::init()
{
    temperature.init();
    pressure.init();

    labelMain1.init();
    labelMain2.init();
    labelMain3.init();
    labelMain4.init();

    labelMain1.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 0);
    labelMain2.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 16);
    labelMain3.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 32);
    labelMain4.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 48);
}

void MainScreen::show()
{
    setCurrentScreen(MAIN_SCREEN);
    printf("From MainScreen.cpp");

    // labelMain1.clearScreen();

    // MainScreen::setTextFormatted("Teste 1", 1.0);

    labelMain1.setTextFormated("%6.2fC", temperature.getTemperature());
    labelMain2.setTextFormated("%6.0fPa", pressure.getPressure());
    // labelMain3.setTextFormated("Teste 3", 1.0);
    // labelMain4.setTextFormated("Teste 4", 1.0);
    // label.setTextFormated("%6.0fPa", BMP280.getPressure());
    // label2.setTextFormated("%6.2fC", BMP280.getTemperature());
    // label3.setTextFormated("%6.0fPa", SMP3011.getPressure());
    // label4.setTextFormated("%6.2fC", SMP3011.getTemperature());
}
