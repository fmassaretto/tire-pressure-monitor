#include "MainScreen.h"

MainScreen::MainScreen() : Screen()
{
    printf("*From contructor MainScreen.cpp* ");
    new Temperature();
    new Pressure();

    // if (!lv_obj_is_valid(scr))
    // {
    // scr = lv_disp_get_scr_act(nullptr);

    // MainScreen::init();
    // }
}

MainScreen::~MainScreen() {}

void MainScreen::init(lv_obj_t *scr)
{
    temperature.init();
    pressure.init();

    label1.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 0);
    label2.setLabel(scr, LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 16);

    // labelMain3.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 32);
    // labelMain4.setLabel(LV_LABEL_LONG_SCROLL_CIRCULAR, 0, 48);
}

void MainScreen::create()
{
    printf("*From create() MainScreen.cpp* ");
    setCurrentScreen(MAIN_SCREEN);

    label1.setTextFormated("%4.2f psi", pressure.getPressureInPsi());
    // label1.setTextFormated("%6.2fC", temperature.getTemperature());
    label2.setTextFormated("%2.0f bar", pressure.getPressureInBar());
}

void MainScreen::show()
{
    setCurrentScreen(MAIN_SCREEN);
    printf("From MainScreen.cpp");

    // labelMain1.clearScreen();

    // MainScreen::setTextFormatted("Teste 1", 1.0);

    label1.setTextFormated("%6.2fC", temperature.getTemperature());
    label2.setTextFormated("%6.0fPa", pressure.getPressureInPsi());
    // labelMain3.setTextFormated("Teste 3", 1.0);
    // labelMain4.setTextFormated("Teste 4", 1.0);
    // label.setTextFormated("%6.0fPa", BMP280.getPressure());
    // label2.setTextFormated("%6.2fC", BMP280.getTemperature());
    // label3.setTextFormated("%6.0fPa", SMP3011.getPressure());
    // label4.setTextFormated("%6.2fC", SMP3011.getTemperature());
}
