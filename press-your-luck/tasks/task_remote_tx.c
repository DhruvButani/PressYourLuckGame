/**
 * @file task_remote_tx.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_remote_tx.h"

#if defined(HW05) || defined(HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

extern cyhal_uart_t remote_uart_obj;

QueueHandle_t q_Remote_Tx;


/**
 * @brief 
 * All data transmitted to the remote board MUST send the data to this task.  
 * 
 * The Remote Tx task is used to transmit data to the remote board. This task will use cyhal_uart_putc() to 
 * transmit each character using polling.
 *
 * Data is received by task_remote_tx using a remote_uart_data_t data struture.  This data structure contains 
 * the number of bytes to send (tx_data.num_bytes) and an array of up to 6 bytes to 
 * transmit (tx_data.payload[]). 
 * 
 * @param param 
 */
void task_remote_tx(void *param)
{
  /* Suppress warning for unused parameter */
  (void)param;

  /* Repeatedly running part of the task */
  for (;;)
  {
    // Wait for the game_info_msg_t to be received
    game_info_msg_t game_info;
    xQueueReceive(q_Remote_Tx, &game_info, portMAX_DELAY);

    // Transmit the data to the remote board by byte
    cyhal_uart_putc(&remote_uart_obj, REMOTE_PACKET_START);
    cyhal_uart_putc(&remote_uart_obj, CMD_UPDATE_REMOTE_DATA);
    cyhal_uart_putc(&remote_uart_obj, (uint8_t)(game_info.score >> 8));
    cyhal_uart_putc(&remote_uart_obj, (uint8_t)(game_info.score));
    cyhal_uart_putc(&remote_uart_obj, game_info.spins);
    cyhal_uart_putc(&remote_uart_obj, game_info.passed);
    cyhal_uart_putc(&remote_uart_obj, REMOTE_PACKET_END);

    task_print_info("Sending Stats to Remote Board");

  }
}


/**
 * @brief 
 * Used to create a FreeRTOS task that will manage all data being transmitted to the remote board.
 */
void task_remote_tx_init(void)
{
  
  q_Remote_Tx = xQueueCreate(1,sizeof(game_info_msg_t));

  xTaskCreate(
      task_remote_tx,
      "Task Remote Tx",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_OUTPUT,
      NULL);
}

#endif
