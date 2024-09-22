/**
 * @file ice16.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX18)

char APP_DESCRIPTION[] = "ECE353: Example 18 - FreeRTOS Task Notification";

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
/* ADD CODE */
/* Create Task Handles for the Console, Buzzer_Start, and Buzzer Stop Tasks*/

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_console(void *pvParameters);
void task_buzzer_start(void *pvParameters);
void task_buzzer_stop(void *pvParameters);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
cyhal_gpio_callback_data_t sw1_callback_data;
cyhal_gpio_callback_data_t sw2_callback_data;

/*****************************************************************************/
/* Interrupt Handlers                                                        */
/*****************************************************************************/
/* Interrupt handler callback function */
void sw1_handler(void *handler_arg, cyhal_gpio_event_t event)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* ADD CODE */
    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */

    /* ADD CODE */
    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
}

void sw2_handler(void *handler_arg, cyhal_gpio_event_t event)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* ADD CODE */
    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */

    /* ADD CODE */
    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
}

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

void sw1_irq_enable(void)
{
    sw1_callback_data.callback = sw1_handler;
    cyhal_gpio_register_callback(PIN_SW1, &sw1_callback_data);
    cyhal_gpio_enable_event(PIN_SW1, CYHAL_GPIO_IRQ_FALL, 3, true);
}

void sw2_irq_enable(void)
{
    sw2_callback_data.callback = sw2_handler;
    cyhal_gpio_register_callback(PIN_SW2, &sw2_callback_data);
    cyhal_gpio_enable_event(PIN_SW2, CYHAL_GPIO_IRQ_FALL, 3, true);
}

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    push_buttons_init(false);
    sw1_irq_enable();
    sw2_irq_enable();

    pwm_buzzer_init();

    ece353_enable_lcd();
    lcd_clear_screen(LCD_COLOR_GREEN);
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* ADD CODE */

    xTaskCreate(task_console,
                "Console Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_Console);

    xTaskCreate(task_buzzer_start,
                "Buzzer Start",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                &Task_Handle_Buzzer_Start);

    xTaskCreate(task_buzzer_stop,
                "Buzzer Stop",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                &Task_Handle_Buzzer_Stop);

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

void task_console(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    uint8_t msg[80];
    bool rx_status = false;
    memset(msg, 0, 80);

    while (1)
    {
        rx_status = console_rx_string(msg);

        if (rx_status)
        {

            if ((strcmp("buzzer_on\n", msg) == 0) || (strcmp("buzzer_on\r", msg) == 0))
            {
                /* ADD CODE */
                /* Send a Task Notification to start the buzzer */
                xTaskNotifyGive(Task_Handle_Buzzer_Start);
            }

            else if ((strcmp("buzzer_off\n", msg) == 0) || (strcmp("buzzer_off\r", msg) == 0))
            {
                /* ADD CODE */
                /* Send a Task Notification to stop the buzzer */
                xTaskNotifyGive(Task_Handle_Buzzer_Stop);
            }
            else
            {
                printf("Unknown command: %s\n\r", msg);
            }

            /* Clear the message buffer */
            memset(msg, 0, 80);
        }

        vTaskDelay(50);
    }
}

void task_buzzer_start(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    while (1)
    {
        /* ADD CODE */
        /* Wait indefinitely for a Task Notification */
        
        printf("Starting Buzzer\n\r");
        lcd_clear_screen(LCD_COLOR_RED);
        pwm_buzzer_start();
    }
}

void task_buzzer_stop(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    while (1)
    {
        /* ADD CODE */
        /* Wait indefinitely for a Task Notification */
        
        printf("Stopping Buzzer\n\r");
        lcd_clear_screen(LCD_COLOR_GREEN);
        pwm_buzzer_stop();
    }
}
//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    // Handle FreeRTOS Stack Overflow
    while (1)
    {
    }
}

#endif