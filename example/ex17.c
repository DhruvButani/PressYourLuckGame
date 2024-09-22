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

#if defined(EX17)

char APP_DESCRIPTION[] = "ECE353: Example 17 - FreeRTOS Message Queues";

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
/* ADD CODE */
/* Create a Message Queue for the Joystick */

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_print(void *pvParameters);
void task_joystick(void *pvParameters);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

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

    /* Initialize the RGB LEDs */
    joystick_init();
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
    Queue_Joystick = xQueueCreate(1, sizeof(joystick_position_t));

    xTaskCreate(task_print,
                "Print Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                NULL);

    xTaskCreate(task_joystick,
                "Joystick",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                NULL);

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

void task_print(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    joystick_position_t pos;

    while (1)
    {
        /* ADD CODE */
        /* Receive a message from the Joystick Queue, wait forever */
        
        printf("Joystick now in ");
        joystick_print_pos(pos);
        printf(" position\n\r");
    }
}

void task_joystick(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    joystick_position_t prev_pos = JOYSTICK_POS_CENTER;
    joystick_position_t cur_pos = JOYSTICK_POS_CENTER;

    while (1)
    {
        vTaskDelay(100);

        /* Get the current position of the joystick */
        cur_pos = joystick_get_pos();

        /* If the position of the joystick has changed, send a message to the joystick queue*/
        if (cur_pos != prev_pos)
        {
            /* ADD CODE */
            /* Send a message to the joystick queue */
        }

        /* Update the previous joystick position */
        prev_pos = cur_pos;
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
