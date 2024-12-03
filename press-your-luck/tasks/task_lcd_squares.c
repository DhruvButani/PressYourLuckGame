/**
 * @file task_lcd_squares.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_lcd_squares.h"

#if defined(HW05) || defined(HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/* Semaphores */
extern SemaphoreHandle_t s_LCD;

QueueHandle_t q_LCD_SQUARES;

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * @param paramå
 */
void task_lcd_squares(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        // Wait for a message to be received
        image_t image;
        xQueueReceive(q_LCD_SQUARES, &image, portMAX_DELAY);
        
        // Take the semaphore
        xSemaphoreTake(s_LCD, portMAX_DELAY);

        // Update the LCD with the new data, if image draw or reset
        if(image.reset == true) {
            pyl_draw_square(0);
            } 
        else {
            pyl_draw_image(&image);
        }
        
        for (int i = 1; i < 14; i++) {
            xQueueReceive(q_LCD_SQUARES, &image, portMAX_DELAY);
            if(image.reset == true) {
                pyl_draw_square(i);
            } 
            else {
                pyl_draw_image(&image);
            }
            
        }
        
        xSemaphoreGive(s_LCD);

    }

}

void task_lcd_squares_init(void)
{

    /* Initialize the LCD hardware */
    ece353_enable_lcd();

    /* Create LCD Queues */
    q_LCD_SQUARES = xQueueCreate(14, sizeof(image_t));

    xTaskCreate(
        task_lcd_squares,
        "Task LCD Squares",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif
