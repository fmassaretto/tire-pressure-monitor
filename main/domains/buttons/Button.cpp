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

bool Button::getButtonState()
{
    return gpio_get_level(this->pin);
}