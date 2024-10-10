#include "Button.h"

Button::Button(gpio_num_t pin)
{
    this->pin = pin;

    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_intr_type(pin, GPIO_INTR_NEGEDGE);
}

Button::~Button()
{
}

gpio_num_t Button::getPin()
{
    return this->pin;
}

press_type Button::getPressType() // TODO: return the right presstype
{
    buttonState = gpio_get_level(this->pin);
    // TickType_t currentTime = pdTICKS_TO_MS(xTaskGetTickCount());

    if (buttonState && !lastButtonState)
    {
        buttonPressTime = esp_timer_get_time();
        printf("buttonPressTime: %lu \n", buttonPressTime);
    }

    if (!buttonState && lastButtonState)
    {
        buttonReleaseTime = esp_timer_get_time();
        printf("buttonReleaseTime: %lu \n", buttonReleaseTime);
        pressDuration = buttonReleaseTime - buttonPressTime;
        printf("pressDuration: %lu \n", pressDuration);

        // lastButtonState = buttonState;
    }

    lastButtonState = buttonState;

    if (pressDuration >= longPressThreshold)
    {
        pressDuration = 0;

        return LONG_PRESS;
    }

    pressDuration = 0;

    return SINGLE_TAP;
    // return SINGLE_TAP;
}
