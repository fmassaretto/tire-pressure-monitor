#include "config/tire_pressure_monitor_config.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "esp_lvgl_port.h"
#include "./domains/sensors/pressure/Pressure.h"
#include "./domains/sensors/temperature/Temperature.h"
#include "./utils/util.cpp"
#include "ui/screens/ui_screen1.h"
#include "ui/screens/ui_screen2.h"
#include "domains/buttons/Button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
// freeRTOS Sergio Prado
#define BUTTON_PIN GPIO_NUM_17
#define LED_PIN GPIO_NUM_0

Button button(BUTTON_PIN);
Pressure pressure;
Temperature temperature;

// For Button Task
ButtonState buttonState = RELEASED;
ButtonPressState pressState = NOT_PRESSED;
uint32_t pressTime = 0;
uint32_t releaseTime = 0;

bool changeScreen = false;
bool changeScale = false;
int pressCount = 0;

bool isLedOn = false;

// Tasks
void ButtonTask(void *parameter);
void TaskScreen(void *parameter);
void TaskUpdatePressure(void *parameter);
void TaskUpdateTemperature(void *parameter);

// Handlers
TaskHandle_t taskButtonHandle = nullptr;
TaskHandle_t taskScreenHandle = nullptr;
TaskHandle_t taskUpdatePressureHandle = nullptr;
TaskHandle_t taskUpdateTemperatureHandle = nullptr;

void ButtonTask(void *pvParameters)
{
    while (true)
    {
        bool buttonPressed = button.getButtonState();

        switch (buttonState)
        {
        case RELEASED:
            if (buttonPressed)
            {
                buttonState = PRESSED;
                pressTime = esp_timer_get_time();
            }

            break;

        case PRESSED:
            if (!buttonPressed)
            {
                releaseTime = esp_timer_get_time();

                if ((releaseTime - pressTime) < 500000)
                {
                    pressState = SINGLE_PRESS;
                }
                else if ((releaseTime - pressTime) < 1000000)
                {
                    pressState = DOUBLE_PRESS;
                }
                else if (releaseTime - pressTime > 3000000)
                {
                    pressState = LONG_PRESS;
                }
                buttonState = RELEASED;
                pressCount++;
            }

            break;
        }

        switch (pressState)
        {
        case NOT_PRESSED:
        case SINGLE_PRESS:
        case DOUBLE_PRESS:
        case LONG_PRESS:
            if (pressState == SINGLE_PRESS)
            {
                changeScreen = !changeScreen;
            }
            else if (pressState == DOUBLE_PRESS)
            {
                isLedOn = !isLedOn;
                gpio_set_level(LED_PIN, isLedOn);
            }
            else if (pressState == LONG_PRESS)
            {
                changeScale = !changeScale;
                Util::changePressureScale(changeScale);
            }
            pressState = NOT_PRESSED;

            break;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

extern "C" void app_main()
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, isLedOn);

    pressure.init();
    temperature.init();

    tire_pressure_monitor_config_init();

    lvgl_port_lock(0);
    ui_init();
    lvgl_port_unlock();

    // Create tasks
    xTaskCreate(ButtonTask, "ButtonTask", 2048, nullptr, 5, &taskButtonHandle);
    xTaskCreate(TaskScreen, "Screen", 4096, nullptr, 3, &taskScreenHandle);
    xTaskCreate(TaskUpdatePressure, "UpdatePressure", 2048, nullptr, 2, &taskUpdatePressureHandle);
    xTaskCreate(TaskUpdateTemperature, "UpdateTemperature", 2048, nullptr, 2, &taskUpdateTemperatureHandle);
}

void TaskScreen(void *parameter)
{
    while (1)
    {
        if (changeScreen)
        {
            lv_scr_load(ui_Screen2);
        }
        else
        {
            lv_scr_load(ui_Screen1);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void TaskUpdatePressure(void *parameter)
{
    while (1)
    {
        if (changeScreen)
        {
            float recomendedPressureValue = pressure.getRecomendedPressure(changeScale);
            updatePressureTextScreen2(recomendedPressureValue);
        }
        else
        {
            float pressureValue = pressure.getPressure(changeScale);
            updatePressureTextScreen1(pressureValue);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void TaskUpdateTemperature(void *parameter)
{
    while (1)
    {
        if (changeScreen)
        {
            float tireTempValue = pressure.getTemperature();
            lv_scr_load(ui_Screen2);
            updateTireTemperatureTextScreen2(tireTempValue);
        }
        else
        {
            lv_scr_load(ui_Screen1);
            float ambientTempValue = temperature.getTemperature();
            updateAmbientTemperatureTextScreen1(ambientTempValue);
        }

        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}