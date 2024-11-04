#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "driver/gpio.h"
#include "esp_timer.h"
#include "stdio.h"

enum
{
    NO_TAP = 0,
    LONG_TAP,
    SINGLE_TAP,
    DOUBLE_TAP
};
typedef unsigned int press_type;

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
    press_type pressState;
    gpio_num_t pin;
    const unsigned long longPressThreshold = 4000000;
    // bool buttonState = false;
    bool lastButtonState = false;
    unsigned long buttonPressTime = 0;
    unsigned long buttonReleaseTime = 0;
    unsigned long pressDuration = 0;

public:
    Button(gpio_num_t pin);
    ~Button();
    gpio_num_t getPin();
    // press_type getPressType();
    press_type getButtonEvent(int pinState);
    bool getButtonState();
};

#endif