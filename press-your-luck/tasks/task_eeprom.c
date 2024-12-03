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
#include "task_eeprom.h"
#include "ece353_tasks.h"
#include "portmacro.h"

#if defined(HW05) || defined (HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

QueueHandle_t q_EEPROM;

/**
 * @brief 
 * Displays the number of whammies that have been selected
 * @param param 
 * Not Used
 */
void task_eeprom(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        //Wait for data to be recieved
        uint16_t score;
        eeprom_msg_t recieved;
        xQueueReceive(q_EEPROM, &recieved, portMAX_DELAY);

        //If read operation, read the score from the eeprom and send it back
        if(recieved.operation == EEPROM_READ)
        {
            uint16_t scoreRead[2*sizeof(uint8_t)] = {eeprom_read_byte((uint16_t)(0x20)),eeprom_read_byte((uint16_t)(0x21))};
            score = ((uint16_t)scoreRead[1] << 8) | scoreRead[0];


            eeprom_msg_t send = {
                .operation = recieved.operation,
                .score = score,
                .return_queue = NULL
            };
            xQueueSend(recieved.return_queue, &send, portMAX_DELAY);

        }
        //If write operation, write the score to the eeprom
        else if(recieved.operation == EEPROM_WRITE)
        {
            score = recieved.score;
            eeprom_write_byte((uint16_t)(0x21), (uint8_t)(score >> 8));
            eeprom_write_byte((uint16_t)(0x20), (uint8_t)(score));
        }

    }
}

void task_eeprom_init(void)
{
    /* Enable the SPI interface */
    spi_init();

    /* Configure the IO pin used to control the chip select*/
    eeprom_cs_init();

    q_EEPROM = xQueueCreate(1, sizeof(eeprom_msg_t));

    xTaskCreate(
        task_eeprom,
        "Task EEPROM",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
