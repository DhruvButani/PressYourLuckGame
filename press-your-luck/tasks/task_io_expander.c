/**
 * @file task_io_expander.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_io_expander.h"
#include "ece353_tasks.h"

#if defined(HW05) || defined (HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

QueueHandle_t q_IO_Exp;

/**
 * @brief 
 * Displays the number of whammies that have been selected
 * @param param 
 * Not Used
 */
void task_io_expander(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    io_expander_set_configuration(0x80); // Set bit 7 as input, bits 6-0 as outputs
    io_expander_set_output_port(0x00);   // Turn OFF all LEDs

    /* Repeatedly running part of the task */
    for (;;)
    {

        // Wait for the number of whammies to be updated
        uint8_t whammyCount = 0;
        xQueueReceive(q_IO_Exp, &whammyCount, portMAX_DELAY);

        // Update the LEDs on the IO Expander
        if(whammyCount == 1) {
            io_expander_set_output_port(0xF8);
        }
        if(whammyCount == 2) {
            io_expander_set_output_port(0xFC);
        }
        if(whammyCount == 3) {
            io_expander_set_output_port(0xFE);
        }
        if(whammyCount == 4) {
            io_expander_set_output_port(0xFF);
        }

    }
}

void task_io_expander_init(void)
{
    i2c_init();

    q_IO_Exp = xQueueCreate(1, sizeof(uint8_t));

    xTaskCreate(
        task_io_expander,
        "Task IO Exp",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
