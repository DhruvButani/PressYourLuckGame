/**
 * @file hw01a.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

//
#include "main.h"
#if defined(HW05)
#include "hw05.h"
#include "tasks/task_console.h"
#include "tasks/task_io_expander.h"
#include "tasks/task_eeprom.h"
#include "tasks/task_lcd_game_info.h"
#include "tasks/task_lcd_squares.h"
#include "tasks/task_remote_rx.h"
#include "tasks/task_remote_tx.h"
#include "tasks/task_sw.h"
#include "task_game_control.h"

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW05";

 cyhal_trng_t trng_obj;

/* Event Groups Shared by all of the states*/
EventGroupHandle_t eg_UI;

/* Queues */
QueueHandle_t q_Dir;

/*Semaphores*/
SemaphoreHandle_t s_LCD;

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

}

// Task - initializes peripherals 
void tasks_peripheral_init(void)
{
    /* Initialize the Console Task */
    task_console_init();

    /* Initialize the LCD Task */
    task_lcd_squares_init();

    /* Initialize the Task used to print the score, number of turns, etc */
    task_lcd_game_info_init();

    /* Initialize the Buttons Tasks*/
    task_sw_init();

    /* Initialize the Remote UART Tasks*/
    task_remote_rx_init();
    task_remote_tx_init();

    /* Initialize the IO Expander */
    task_io_expander_init();

    /* Initialize eeprom task*/
    task_eeprom_init();

}

void tasks_states_init(void)
{
    /* Initialize the Event Groups*/
    eg_UI = xEventGroupCreate();

    /* Initialize the LCD Semaphore */
    s_LCD = xSemaphoreCreateBinary();
    xSemaphoreGive(s_LCD);

    /* Initialize State Tasks */
    task_game_control_init();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void main_app(void)
{
    tasks_peripheral_init();

    tasks_states_init();

    // Start the scheduler
    vTaskStartScheduler();

    /* RTOS scheduler exited */
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);

    for (;;)
    {
    }
}

#endif