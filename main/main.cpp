#include "config/tire_pressure_monitor_config.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "esp_lvgl_port.h"
#include "ui/screens/ui_screen1.h"
#include "domains/buttons/Button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
// #include <semphr.h>
// freeRTOS Sergio Prado
#define BUTTON_PIN GPIO_NUM_17
#define LED_PIN GPIO_NUM_2
SemaphoreHandle_t interruptSemaphore;

Button button(GPIO_NUM_17);

QueueHandle_t interputQueue;
int state = 0;
unsigned int curr_screen;
bool recomendationScreenActive = false;

/*
        TASKS
*/
// Prototypes
void TaskButton(void *parameter);
void TaskScreen(void *parameter);
void TaskUpdatePressure(void *parameter);
void TaskUpdateTemperature(void *parameter);

// Handlers
TaskHandle_t taskButtonHandle = nullptr;
TaskHandle_t taskScreenHandle = nullptr;
TaskHandle_t taskUpdatePressureHandle = nullptr;
TaskHandle_t taskUpdateTemperatureHandle = nullptr;

static void IRAM_ATTR gpio_interrupt_handler(void *args)
{
    int pinNumber = (int)args;
    xQueueSendFromISR(interputQueue, &pinNumber, NULL);
}

void LED_Control_Task(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(BUTTON_PIN));
            switch (button.getButtonEvent())
            {
            case NO_TAP:
            {
                // printf("NO_PRESS\n");
            }
            break;
            case SINGLE_TAP:
            {
                printf("SINGLE_PRESS - Recomendacao Screen\n");
            }
            break;
            case LONG_TAP:
            {
                printf("LONG_PRESS - Change scale\n");
                recomendationScreenActive = !recomendationScreenActive;
            }
            break;
            case DOUBLE_TAP:
            {
                printf("DOUBLE_PRESS - switch LED\n");
            }
            break;
            }
            vTaskDelay(800 / portTICK_PERIOD_MS);
            // gpio_set_level(LED_PIN, gpio_get_level(BUTTON_PIN));
        }
    }
}

extern "C" void app_main()
{
    // pinMode(17, INPUT_PULLUP);
    // gpio_set_direction(17, GPIO_MODE_DEF_INPUT, GPIO_PULLUP_ENABLE);
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    esp_rom_gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON_PIN);
    gpio_pullup_dis(BUTTON_PIN);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_POSEDGE);

    interputQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(LED_Control_Task, "LED_Control_Task", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, gpio_interrupt_handler, (void *)BUTTON_PIN);

    tire_pressure_monitor_config_init();

    lvgl_port_lock(0);
    ui_init();
    lvgl_port_unlock();

    // Create tasks
    // xTaskCreate(TaskButton, "Button", 2048, nullptr, 0, &taskButtonHandle);
    xTaskCreate(TaskScreen, "Screen", 2048, nullptr, tskIDLE_PRIORITY, &taskScreenHandle);
    xTaskCreate(TaskUpdatePressure, "UpdatePressure", 2048, nullptr, 2, &taskUpdatePressureHandle);
    xTaskCreate(TaskUpdateTemperature, "UpdateTemperature", 2048, nullptr, 2, &taskUpdateTemperatureHandle);
}

void TaskScreen(void *parameter)
{
    while (1)
    {
        // lvgl_port_lock(0);

        // lv_disp_load_scr(ui_Screen1);
        if (recomendationScreenActive)
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
        // lvgl_port_lock(0);
        updatePressure();
        // lvgl_port_unlock();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("\n %lu \n", (1000 / portTICK_PERIOD_MS));
    }
}

void TaskUpdateTemperature(void *parameter)
{
    while (1)
    {
        // lvgl_port_lock(0);
        updateAmbientTemperature();
        // lvgl_port_unlock();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

// void TaskButton(void *parameter)
// {
//     while (1)
//     {
//         switch (button.getButtonEvent())
//         {
//         case NO_TAP:
//         {
//             // printf("NO_PRESS\n");
//         }
//         break;
//         case SINGLE_TAP:
//         {
//             printf("SINGLE_PRESS - Recomendacao Screen\n");
//         }
//         break;
//         case LONG_TAP:
//         {
//             printf("LONG_PRESS - Change scale\n");
//         }
//         break;
//         case DOUBLE_TAP:
//         {
//             printf("DOUBLE_PRESS - switch LED\n");
//         }
//         break;
//         }
//         vTaskDelay(800 / portTICK_PERIOD_MS);
//     }
// }