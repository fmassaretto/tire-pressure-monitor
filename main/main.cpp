#include "config/tire_pressure_monitor_config.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "esp_lvgl_port.h"
#include "ui/screens/ui_screen1.h"
#include "ui/screens/ui_screen2.h"
#include "domains/buttons/Button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
// #include <semphr.h>
// freeRTOS Sergio Prado
#define BUTTON_PIN GPIO_NUM_17
// #define LED_PIN GPIO_NUM_2

Button button(GPIO_NUM_17);
// PinButton myButton(BUTTON_PIN, 2);

QueueHandle_t interputQueue;
int pinState = 0;
unsigned int curr_screen;
bool changeScreen = false;

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

// static void IRAM_ATTR gpio_interrupt_handler(void *args)
// {
//     int pinNumber = (int)args;
//     xQueueSendFromISR(interputQueue, &pinNumber, NULL);
// }

// void LED_Control_Task(void *params)
// {

//     // while (true)
//     // {
//     //     myButton.update();

//     //     if (myButton.isClick())
//     //     {
//     //         printf("\n isClick \n");
//     //     }
//     //     if (myButton.isSingleClick())
//     //     {
//     //         printf("\n isSingleClick \n");
//     //     }
//     //     if (myButton.isDoubleClick())
//     //     {
//     //         printf("\n isDoubleClick \n");
//     //     }
//     //     if (myButton.isLongClick())
//     //     {
//     //         printf("\n isLongClick \n");
//     //     }
//     //     vTaskDelay(1000 / portTICK_PERIOD_MS);
//     // }
//     int pinNumber, count = 0;

//     while (true)
//     {
//         printf("button level: %d  ____ ", gpio_get_level(BUTTON_PIN));
//         if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
//         {
//             pinState = gpio_get_level(BUTTON_PIN);

//             printf("GPIO %d was pressed %d times. The state is %d and pin value: %d\n", pinNumber, count++, gpio_get_level(BUTTON_PIN), pinState);
//             switch (button.getButtonEvent(pinState))
//             {
//             case NO_TAP:
//             {
//                 // printf("NO_PRESS\n");
//             }
//             break;
//             case SINGLE_TAP:
//             {
//                 printf("SINGLE_PRESS - Recomendacao Screen\n");
//             }
//             break;
//             case LONG_TAP:
//             {
//                 printf("LONG_PRESS - Change scale\n");
//                 changeScreen = !changeScreen;
//             }
//             break;
//             case DOUBLE_TAP:
//             {
//                 printf("DOUBLE_PRESS - switch LED\n");
//             }
//             break;
//             }
//             vTaskDelay(100 / portTICK_PERIOD_MS);
//             // gpio_set_level(LED_PIN, gpio_get_level(BUTTON_PIN));
//         }
//     }
// }

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
                //// Ate Aqui 22222

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
                printf("Long press\n");
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
        // lvgl_port_lock(0);
        updatePressureTextScreen1();
        updatePressureTextScreen2();
        // lvgl_port_unlock();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // printf("\n %lu \n", (1000 / portTICK_PERIOD_MS));
    }
}

void TaskUpdateTemperature(void *parameter)
{
    while (1)
    {
        // lvgl_port_lock(0);
        updateAmbientTemperatureTextScreen1();
        updateTireTemperatureTextScreen2();
        // lvgl_port_unlock();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

// Button press timing thresholds (in milliseconds)
// #define DEBOUNCE_TIME 50000      // Debounce time for button press (50 ms)
// #define SINGLE_PRESS_TIME 700000  // Max time for single press (700 ms)
// #define DOUBLE_PRESS_TIME 1000000 // Max time for double press (1000 ms)
// #define LONG_PRESS_TIME 3000000   // Time for long press (3000 ms)

// // Button states
// enum ButtonState
// {
//     BUTTON_IDLE,
//     BUTTON_PRESSED,
//     BUTTON_SINGLE_PRESS,
//     BUTTON_DOUBLE_PRESS,
//     BUTTON_LONG_PRESS
// };

// ButtonState buttonState = BUTTON_IDLE;
// int pressCount = 0;
// int64_t pressStartTime = 0;
// int64_t lastPressTime = 0;

// void TaskButton(void *pvParameters)
// {
//     // pinMode(BUTTON_PIN, INPUT_PULLUP);

//     while (true)
//     {
//         bool buttonPressed = gpio_get_level(BUTTON_PIN) == 1; // Active-high button
//         int64_t currentTime = esp_timer_get_time();

//         // printf("buttonPressed = %d \n", buttonPressed);
//         // printf("buttonState = %d \n", buttonState);

//         if ((buttonPressed == 1) && (buttonState == BUTTON_IDLE))
//         {
//             printf("1 \n");
//             buttonState = BUTTON_PRESSED;
//             pressStartTime = currentTime;
//             pressCount++;
//         }
//         else if ((buttonPressed == 0) && (buttonState == BUTTON_PRESSED))
//         {
//             printf("2 \n");
//             // Check for single, double, or long press
//             int64_t pressDuration = currentTime - pressStartTime;
//             // printf("pressDuration = %llu\n", pressDuration);

//             if (pressDuration >= LONG_PRESS_TIME)
//             {
//                 printf("3 \n");
//                 buttonState = BUTTON_LONG_PRESS;
//                 pressCount = 0;
//                 printf("Long press detected\n");
//             }
//             else if (pressDuration < SINGLE_PRESS_TIME)
//             {
//                 printf("4  \n");
//                 buttonState = BUTTON_SINGLE_PRESS;
//             }
//             lastPressTime = currentTime;
//         }

//         if (buttonPressed == 0)
//         {
//             int64_t diff = lastPressTime - pressStartTime;
//             if ((diff <= SINGLE_PRESS_TIME) && pressCount == 1)
//             {
//                 printf("Single press detected\n");
//                 pressCount = 0;
//             }
//             else if ((diff <= DOUBLE_PRESS_TIME) && pressCount == 2)
//             {
//                 printf("Double press detected\n");
//                 pressCount = 0;
//             }
//             else if ((diff >= LONG_PRESS_TIME))
//             {
//                 printf("Long press detected\n");
//                 pressCount = 0;
//             }
//             buttonState = BUTTON_IDLE;
//         }

//         // // Handle button state after release
//         // printf("(currentTime) = %llu\n", (currentTime));
//         // printf("(lastPressTime) = %llu\n", (lastPressTime));
//         // if ((buttonPressed == 0) && ((currentTime - lastPressTime) > DOUBLE_PRESS_TIME))
//         // {
//         //     printf("5 - pressCount = %d \n", pressCount);
//         //     if (pressCount == 1)
//         //     {
//         //         printf("Single press detected\n");
//         //     }
//         //     else if (pressCount == 2)
//         //     {
//         //         printf("Double press detected\n");
//         //     }

//         //     printf("\n");
//         //     pressCount = 0;
//         //     buttonState = BUTTON_IDLE;
//         // }

//         // // Reset button state if it was a long press
//         // if ((buttonState == BUTTON_LONG_PRESS) && (buttonPressed == 0))
//         // {
//         //     printf("6 \n");
//         //     buttonState = BUTTON_IDLE;
//         //     pressCount = 0;
//         // }

//         vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to avoid busy-looping
//     }
// }

// void TaskButton(void *pvParameters)
// {
//     // pinMode(BUTTON_PIN, INPUT_PULLUP);

//     while (true)
//     {
//         bool buttonPressed = gpio_get_level(BUTTON_PIN) == 1; // Active-high button
//         int64_t currentTime = esp_timer_get_time();

//         // printf("buttonPressed = %d \n", buttonPressed);
//         // printf("buttonState = %d \n", buttonState);

//         if ((buttonPressed == 1) && (buttonState == BUTTON_IDLE))
//         {
//             printf("1 \n");
//             buttonState = BUTTON_PRESSED;
//             pressStartTime = currentTime;
//             pressCount++;
//         }
//         else if ((buttonPressed == 0) && (buttonState == BUTTON_PRESSED))
//         {
//             printf("2 \n");
//             // Check for single, double, or long press
//             int64_t pressDuration = currentTime - pressStartTime;
//             // printf("pressDuration = %llu\n", pressDuration);

//             if (pressDuration >= LONG_PRESS_TIME)
//             {
//                 printf("3 \n");
//                 buttonState = BUTTON_LONG_PRESS;
//                 pressCount = 0;
//                 printf("Long press detected\n");
//             }
//             else if (pressDuration < SINGLE_PRESS_TIME)
//             {
//                 printf("4  \n");
//                 buttonState = BUTTON_SINGLE_PRESS;
//             }
//             lastPressTime = currentTime;
//         }

//         // Handle button state after release
//         printf("(currentTime) = %llu\n", (currentTime));
//         printf("(lastPressTime) = %llu\n", (lastPressTime));
//         if ((buttonPressed == 0) && ((currentTime - lastPressTime) > DOUBLE_PRESS_TIME))
//         {
//             printf("5 - pressCount = %d \n", pressCount);
//             if (pressCount == 1)
//             {
//                 printf("Single press detected\n");
//             }
//             else if (pressCount == 2)
//             {
//                 printf("Double press detected\n");
//             }

//             printf("\n");
//             pressCount = 0;
//             buttonState = BUTTON_IDLE;
//         }

//         // Reset button state if it was a long press
//         if ((buttonState == BUTTON_LONG_PRESS) && (buttonPressed == 0))
//         {
//             printf("6 \n");
//             buttonState = BUTTON_IDLE;
//             pressCount = 0;
//         }

//         vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to avoid busy-looping
//     }
// }

// int lastState = 0;
// int tapCounter = 0;
// bool buttonReleased = false;
// bool isSingleDouble = false;
// uint32_t pressed_time;
// uint32_t released_time;
// uint32_t diff;
// void TaskButton(void *parameter)
// {
//     while (1)
//     {
//         pinState = gpio_get_level(BUTTON_PIN);
//         printf("pinState: %d \n", pinState);
//         if (pinState == 1 && lastState == 0) // aqui apertou o botao
//         {
//             pressed_time = esp_timer_get_time();
//             lastState = 1;
//             buttonReleased = false;
//             printf("pressed_time: %lu - lastState: %d\n", pressed_time, lastState);
//         }
//         else if (pinState == 0 && lastState == 1)
//         {
//             released_time = esp_timer_get_time();
//             lastState = 0;
//             buttonReleased = true;
//             printf("released_time: %lu - lastState: %d\n", released_time, lastState);
//         }

//         if (buttonReleased)
//         {
//             diff = released_time - pressed_time;
//             printf("Diff: %lu\n", diff);

//             if (diff > 0 && diff <= 3000000)
//             {
//                 // single tap
//                 tapCounter++;
//                 printf("tap counter: %d\n", tapCounter);
//                 isSingleDouble = true;
//             }

//             if (isSingleDouble && tapCounter == 1)
//             {
//                 printf("Single - Change screen\n");
//             }
//             else if (isSingleDouble && tapCounter > 1)
//             {
//                 printf("Double - switch led\n");
//             }

//             if (diff >= 5000000 && !isSingleDouble)
//             {
//                 // long tap
//                 printf("LONG - Change Scale\n");
//             }
//             printf("\n\n");
//             tapCounter = 0;
//             isSingleDouble = false;
//             released_time = 0;
//             pressed_time = 0;
//         }
//         vTaskDelay(500 / portTICK_PERIOD_MS);
//     }
// }

// void TaskButton(void *parameter)
// {
//     while (1)
//     {
//         pinState = gpio_get_level(BUTTON_PIN);
//         printf("pin state: %d\n", pinState);

//         switch (button.getButtonEvent(pinState))
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
//         vTaskDelay(900 / portTICK_PERIOD_MS);
//     }
// }