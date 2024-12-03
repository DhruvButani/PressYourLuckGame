/**
 * @file task_lcd_game_info.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "task_lcd_game_info.h"

#if defined(HW05) || defined(HW06)

#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"
#include "pyl.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/* Semaphores */
extern SemaphoreHandle_t s_LCD;

QueueHandle_t q_LCD_Info;

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * @param param
 */
void task_lcd_game_info(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        // Wait for a message to be received
        game_info_msg_t game_info;
        xQueueReceive(q_LCD_Info, &game_info, portMAX_DELAY);

        // Take the semaphore
        xSemaphoreTake(s_LCD, portMAX_DELAY);

        // Update the LCD with the new data
        if(game_info.cmd == CMD_UPDATE_LOCAL_DATA)
        {
            pyl_print_digits_6(game_info.score, LOCATION_LOCAL_SCORE_X , LOCATION_LOCAL_SCORE_Y, COLOR_LOCAL_SCORE, ~COLOR_LOCAL_SCORE);
            pyl_print_digits_2(game_info.spins, LOCATION_LOCAL_SPINS_X, LOCATION_LOCAL_SPINS_Y, COLOR_LOCAL_SPINS, ~COLOR_LOCAL_SPINS);
            pyl_print_digits_2(game_info.passed, LOCATION_LOCAL_PASSED_X, LOCATION_LOCAL_PASSED_Y, COLOR_LOCAL_PASSED, ~COLOR_LOCAL_PASSED);    
        }
        else if(game_info.cmd == CMD_UPDATE_REMOTE_DATA) {
            pyl_print_digits_6(game_info.score, LOCATION_REMOTE_SCORE_X , LOCATION_REMOTE_SCORE_Y, COLOR_REMOTE_SCORE, ~COLOR_REMOTE_SCORE);
            pyl_print_digits_2(game_info.spins, LOCATION_REMOTE_SPINS_X, LOCATION_REMOTE_SPINS_Y, COLOR_REMOTE_SPINS, ~COLOR_REMOTE_SPINS);
            pyl_print_digits_2(game_info.passed, LOCATION_REMOTE_PASSED_X, LOCATION_REMOTE_PASSED_Y, COLOR_REMOTE_PASSED, ~COLOR_REMOTE_PASSED);
        }
       
        // Give the semaphore
        xSemaphoreGive(s_LCD);
    }
    
}

void task_lcd_game_info_init(void)
{

    q_LCD_Info = xQueueCreate(1,sizeof(game_info_msg_t));

    xTaskCreate(
        task_lcd_game_info,
        "Task LCD Game Info",
        5 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif
