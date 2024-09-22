/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX15)

char APP_DESCRIPTION[] = "ECE353: Example 15 - FreeRTOS";

/* ADD CODE */
/* Add Task Handles (TaskHandle_t) for Each Task */
TaskHandle_t Task_Handle_Led_Green = NULL;
TaskHandle_t Task_Handle_Led_Red = NULL;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_led_green(void *pvParameters);
void task_led_red(void *pvParameters);

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the LEDs that will be controlled by the FreeRTOS Tasks*/
    leds_init();
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
    /* Create the tasks that will toggle the Red and Green LEDs*/

    /* Start the Scheduler */
    vTaskStartScheduler();

    while(1){};
}

/**
 * @brief
 *  This task will blink the Green LED on/off at a rate of 0.5Hz
 * @param pvParameters
 */
void task_led_green(void *pvParameters)
{
    /* ADD CODE */
    /* Define behavior of the green LED Task */
}

/**
 * @brief
 *  This task will blink the Red LED on/off at a rate of 0.75Hz
 * @param pvParameters
 */

void task_led_red(void *pvParameters)
{
    /* ADD CODE */
    /* Define behavior of the red LED Task */
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
