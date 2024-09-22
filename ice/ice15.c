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

#if defined(ICE15)

char APP_DESCRIPTION[] = "ECE353: ICE 15 - FreeRTOS";

TaskHandle_t Task_Handle_Button_SW1 = NULL;
TaskHandle_t Task_Handle_Button_SW2 = NULL;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_button_sw1(void *pvParameters);
void task_button_sw2(void *pvParameters);

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

    /* Initialize the buttons */
    push_buttons_init(false);

    /* Initialize the Buzzer */
    pwm_buzzer_init();
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
    /* Create SW1 Task */

    /* ADD CODE */
    /* Create SW1 Task */

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

/**
 * @brief
 * This task will turn the buzzer on/off by detecting when SW1 has been pressed. This task
 * should sleep for 50mS.  When it is active, check the current state of SW1 and compare it with
 * the previous value of SW1.  If you detect that the button has been pressed, then toggle the
 * buzzer On/Off
 * @param pvParameters
 */
void task_button_sw1(void *pvParameters)
{
    /* ADD CODE */
    /* Allocate any local variables used in this task */

    while (1)
    {
        /* ADD CODE */
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */

        /* ADD CODE */
        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW1_MASK) == 0x00)
        {
        }
        else
        {
        }

        /* ADD CODE */
        /* Detect if the button has been pressed */
        if (0 /*Check the current and previous states of the button*/)
        {
            /* ADD CODE */
            /* Determine if the buzzer should be started or stopped*/
        }

        /* ADD CODE */
        /* Update the previous button state */
    }
}

/**
 * @brief
 * This task will turn the green on/off by detecting when SW2 has been pressed. This task
 * should sleep for 50mS.  When it is active, check the current state of SW1 and compare it with
 * the previous value of SW2.  If you detect that the button has been pressed, then toggle the
 * Green LED On/Off
 * @param pvParameters
 */

void task_button_sw2(void *pvParameters)
{
    /* ADD CODE */
    /* Allocate any local variables used in this task */

    while (1)
    {
        /* ADD CODE */
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */

        /* ADD CODE */
        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW2_MASK) == 0x00)
        {
        }
        else
        {
        }

        /* ADD CODE */
        /* Detect if the button has been pressed */
        if (0 /*Check the current and previous states of the button*/)
        {
            /* ADD CODE */
            /* Toggle the Green LED */
        }

        /* ADD CODE */
        /* Update the previous button state */
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