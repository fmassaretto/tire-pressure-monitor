#include "Button.h"

Button::Button(gpio_num_t pin)
{
    this->pin = pin;
    gpio_set_direction(pin, GPIO_MODE_INPUT);
}

Button::~Button()
{
}

press_type Button::getPressType() // TODO: return the right presstype
{
    int state = gpio_get_level(this->pin);

    if (state)
    {
        return LONG_PRESS;
    }

    return SINGLE_TAP;
}
