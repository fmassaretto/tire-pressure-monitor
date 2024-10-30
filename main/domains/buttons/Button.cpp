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

// press_type Button::getPressType() // TODO: return the right presstype
// {
//     buttonState = gpio_get_level(this->pin);
//     // TickType_t currentTime = pdTICKS_TO_MS(xTaskGetTickCount());

//     if (buttonState && !lastButtonState)
//     {
//         buttonPressTime = esp_timer_get_time();
//         printf("buttonPressTime: %lu \n", buttonPressTime);
//     }

//     if (!buttonState && lastButtonState)
//     {
//         buttonReleaseTime = esp_timer_get_time();
//         printf("buttonReleaseTime: %lu \n", buttonReleaseTime);
//         pressDuration = buttonReleaseTime - buttonPressTime;
//         printf("pressDuration: %lu \n", pressDuration);

//         // lastButtonState = buttonState;
//     }

//     lastButtonState = buttonState;

//     if (pressDuration >= longPressThreshold)
//     {
//         pressDuration = 0;
//         printf("pressDuration: %lu \n", pressDuration);

//         return LONG_PRESS;
//     }

//     pressDuration = 0;

//     return SINGLE_TAP;
// }

bool Button::buttonState()
{
    return gpio_get_level(this->pin);
}

press_type Button::getButtonEvent()
{
    static const uint32_t DOUBLE_GAP_MILLIS_MAX = 250;
    static const uint32_t LONG_MILLIS_MIN = 800;
    static uint32_t button_down_ts = 0;
    static uint32_t button_up_ts = 0;
    static bool double_pending = false;
    static bool long_press_pending = false;
    static bool button_down = false;

    press_type button_event = NO_TAP;
    uint32_t now = esp_timer_get_time();
    // uint32_t now = HAL_GetTick();

    // If state changed...
    if (button_down != buttonState())
    {
        button_down = !button_down;
        if (button_down)
        {
            // Timestamp button-down
            button_down_ts = now;
        }
        else
        {
            // Timestamp button-up
            button_up_ts = now;

            // If double decision pending...
            if (double_pending)
            {
                button_event = DOUBLE_TAP;
                double_pending = false;
            }
            else
            {
                double_pending = true;
            }

            // Cancel any long press pending
            long_press_pending = false;
        }
    }

    // If button-up and double-press gap time expired, it was a single press
    if (!button_down && double_pending && now - button_up_ts > DOUBLE_GAP_MILLIS_MAX)
    {
        double_pending = false;
        button_event = SINGLE_TAP;
    }
    // else if button-down for long-press...
    else if (!long_press_pending && button_down && now - button_down_ts > LONG_MILLIS_MIN)
    {
        button_event = LONG_TAP;
        long_press_pending = false;
        double_pending = false;
    }

    return button_event;
}
