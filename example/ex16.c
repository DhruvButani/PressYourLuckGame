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

#if defined(EX16)

char APP_DESCRIPTION[] = "ECE353: Example 16 - FreeRTOS Semaphores";

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
TaskHandle_t Task_Handle_Print1 = NULL;
TaskHandle_t Task_Handle_Print2 = NULL;

/* ADD CODE */
/* Allocate a semaphore that will be used to control the RGB LED */
SemaphoreHandle_t Sem_Console;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_print1(void *pvParameters);
void task_print2(void *pvParameters);

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
    /* Initialize the RGB LEDs */
    leds_init();

    /* Initialize the buttons */
    push_buttons_init(false);
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
    /* Create Semaphores */

    /* ADD CODE */
    /* Give the Semaphore to initialize its state */

    xTaskCreate(task_print1,
                "Print1 Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_Print1);

    xTaskCreate(task_print2,
                "Print2 Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                &Task_Handle_Print2);

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

void task_print1(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    char msg[] = "task_print1 01234567890123456789012345\n\r";
    char *msg_ptr;

    while (1)
    {
        vTaskDelay(150);
        msg_ptr = msg;

        /* ADD CODE */
        /* Take Console Semaphore */

        /* Print out the entire string by directly accessing the TX_FIFO_WR */ 
        while (*msg_ptr != 0)
        {
            while ((CONSOLE_PORT->TX_FIFO_STATUS & SCB_TX_FIFO_STATUS_SR_VALID_Msk) != 0)
            {
                /* Wait for previous byte to finish transmitting */
            }
            CONSOLE_PORT->TX_FIFO_WR = *msg_ptr;
            msg_ptr++;
        }

        /* ADD CODE */ 
        /* Give the Console Semaphore */
    }
}

void task_print2(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    char msg[] = "task_print2 ABCDEFGHIJKLMNOPQRSTUVWZYZ\n\r";
    char *msg_ptr;

    while (1)
    {
        vTaskDelay(100);
        msg_ptr = msg;

        /* ADD CODE */
        /* Take Console Semaphore */

        while (*msg_ptr != 0)
        {
            while ((CONSOLE_PORT->TX_FIFO_STATUS & SCB_TX_FIFO_STATUS_SR_VALID_Msk) != 0)
            {
                /* Wait for previous byte to finish transmitting */
            }
            CONSOLE_PORT->TX_FIFO_WR = *msg_ptr;
            msg_ptr++;
        }
        
        /* ADD CODE */ 
        /* Give the Console Semaphore */
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
