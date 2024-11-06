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
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
// freeRTOS Sergio Prado
#define BUTTON_PIN GPIO_NUM_17
// #define LED_PIN GPIO_NUM_2

Button button(BUTTON_PIN);
Pressure pressure;
Temperature temperature;

QueueHandle_t interputQueue;
int pinState = 0;
unsigned int curr_screen;
bool changeScreen = false;
bool changeScale = false;

// For Button Task
ButtonState buttonState = RELEASED;
ButtonPressState pressState = NOT_PRESSED;
uint32_t pressTime = 0;
uint32_t releaseTime = 0;
int pressCount = 0;

/*
        TASKS
*/
// Prototypes
// void TaskButton(void *parameter);
void TaskScreen(void *parameter);
void TaskUpdatePressure(void *parameter);
void TaskUpdateTemperature(void *parameter);

// Handlers
TaskHandle_t taskButtonHandle = nullptr;
TaskHandle_t taskScreenHandle = nullptr;
TaskHandle_t taskUpdatePressureHandle = nullptr;
TaskHandle_t taskUpdateTemperatureHandle = nullptr;

void buttonTask(void *pvParameters)
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
                // print("releaseTime: %llu", releaseTime);
                // print("pressTime: %llu", pressTime);

                if ((releaseTime - pressTime) < 500000)
                {
                    pressState = SINGLE_PRESS;
                    printf("1\n");
                }
                else if ((releaseTime - pressTime) < 1000000)
                {
                    pressState = DOUBLE_PRESS;
                    printf("2\n");
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
            // Handle the button event based on the state
            // printf("pressCount = %d\n", pressCount);
            if (pressState == SINGLE_PRESS)
            {
                printf("Single click\n");
                changeScreen = !changeScreen;
            }
            else if (pressState == DOUBLE_PRESS)
            {
                printf("DOUBLE click\n");
            }
            else if (pressState == LONG_PRESS)
            {
                changeScale = !changeScale;
                printf("Long press %d\n", changeScale);
                Util::changePressureScale(changeScale);
            }
            pressState = NOT_PRESSED;

            break;
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Adjust delay as needed
    }
}

extern "C" void app_main()
{
    // pinMode(17, INPUT_PULLUP);
    // gpio_set_direction(17, GPIO_MODE_DEF_INPUT, GPIO_PULLUP_ENABLE);
    // esp_rom_gpio_pad_select_gpio(LED_PIN);
    // gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    pressure.init();
    temperature.init();

    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON_PIN);
    gpio_pullup_dis(BUTTON_PIN);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_POSEDGE);

    interputQueue = xQueueCreate(10, sizeof(int));
    // xTaskCreate(LED_Control_Task, "LED_Control_Task", 2048, NULL, 20, NULL);

    gpio_install_isr_service(0);
    // gpio_isr_handler_add(BUTTON_PIN, gpio_interrupt_handler, (void *)BUTTON_PIN);

    tire_pressure_monitor_config_init();

    lvgl_port_lock(0);
    ui_init();
    lvgl_port_unlock();

    // Create tasks
    xTaskCreatePinnedToCore(buttonTask, "ButtonTask", 2048, NULL, 5, &taskButtonHandle, 0);
    // xTaskCreate(TaskButton, "Button", 2048, nullptr, 20, &taskButtonHandle);
    xTaskCreate(TaskScreen, "Screen", 2048, nullptr, 3, &taskScreenHandle);
    xTaskCreate(TaskUpdatePressure, "UpdatePressure", 2048, nullptr, 2, &taskUpdatePressureHandle);
    xTaskCreate(TaskUpdateTemperature, "UpdateTemperature", 2048, nullptr, 2, &taskUpdateTemperatureHandle);
}

void TaskScreen(void *parameter)
{
    while (1)
    {
        // lvgl_port_lock(0);

        // lv_disp_load_scr(ui_Screen1);
        if (changeScreen)
        {
            // printf("True %d\n", recomendationScreenActive);
            lv_scr_load(ui_Screen2);
        }
        else
        {
            // printf("False %d\n", recomendationScreenActive);
            lv_scr_load(ui_Screen1);
        }
        // printf("TaskScreen: ui_Screen1\n");
        // lvgl_port_unlock();
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
            updatePressureTextScreen2(recomendedPressureValue); // TODO: show recomended pressure
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