#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "driver/gpio.h"
#include "esp_timer.h"

enum ButtonState
{
    RELEASED,
    PRESSED
};

enum ButtonPressState
{
    NOT_PRESSED,
    SINGLE_PRESS,
    DOUBLE_PRESS,
    LONG_PRESS
};

class Button
{
private:
    gpio_num_t pin;

public:
    Button(gpio_num_t pin);
    ~Button();
    gpio_num_t getPin();
    bool getButtonState();
};

#endif