#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "driver/gpio.h"

enum
{
    LONG_PRESS = 0,
    SINGLE_TAP,
    DOUBLE_TAP
};
typedef unsigned int press_type;

class Button
{
private:
    press_type pressState;
    gpio_num_t pin;

public:
    Button(gpio_num_t pin);
    ~Button();
    press_type getPressType();
};

#endif