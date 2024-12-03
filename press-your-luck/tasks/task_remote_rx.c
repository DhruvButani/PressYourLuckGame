/**
 * @file task_remote_rx.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "task_remote_rx.h"

#if defined(HW05) || defined(HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

extern cyhal_uart_t remote_uart_obj;

QueueHandle_t q_Remote_Rx;
extern QueueHandle_t q_Control_Rx_Data;

/******************************************************************************
 * Static Functions
 *
 * These Functions should never be called outside of this file
 ******************************************************************************/

/**
 * @brief
 * Verifies that the data received is valid
 * @param packet
 * An array of 4 bytes received from the remote board
 * @return true
 * Packet is valid
 * @return false
 * Packet contained invalid data
 */
static bool staff_packet_verify(uint8_t *packet)
{
  /* Verify start of packet */
  if (packet[0] != REMOTE_PACKET_START)
  {
    return false;
  }

  /* Verify the command is a a value between 0xB0 and 0xB6*/
  if ((packet[1] < 0xB0) || (packet[1] > 0xB6))
  {
    return false;
  }

  /* Verify end of packet */
  if (packet[6] != REMOTE_PACKET_END)
  {
    return false;
  }

  return true;
}
/******************************************************************************
 * End of Static Functions
 ******************************************************************************/

/* This Global variable is used to store up to 7-bytes of data received on
 * the remote UART. As data is received, add the data to the payload and increment
 * the number of bytes received.
 *
 * Adding the next byte of data
 * Data_Remote_Rx.payload[Data_Remote_Rx.num_bytes] = c;
 *
 * Incrementing the number of bytes received
 * Data_Remote_Tx.num_bytes++;
 *
 */
static remote_uart_data_t Data_Remote_Rx = {.num_bytes = 0, .payload = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

/**
 * @brief
 * This is the interrupt handler for the remote UART. Data is transmitted to the bottom
 * half task using q_Remote_Rx.
 *
 * @param handler_arg
 * @param event
 */
void Handler_FreeRTOS_Remote_UART(void *handler_arg, cyhal_uart_event_t event)
{
  (void)handler_arg;
  uint8_t data;
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  if ((event & CYHAL_UART_IRQ_TX_ERROR) == CYHAL_UART_IRQ_TX_ERROR)
  {
    /* An error occurred in Tx */
    /* Should never get here */
  }
  else if ((event & CYHAL_UART_IRQ_RX_NOT_EMPTY) == CYHAL_UART_IRQ_RX_NOT_EMPTY)
  {
    // Read the data from the UART
    cyhal_uart_getc(&remote_uart_obj, &data,0);
    Data_Remote_Rx.payload[Data_Remote_Rx.num_bytes] = data;
    Data_Remote_Rx.num_bytes++;

    // If we have received all 7 bytes, send the data to the bottom half task, notify the bottom half task 
    if(Data_Remote_Rx.num_bytes == 7) {
      Data_Remote_Rx.num_bytes = 0;
      xQueueSendFromISR(q_Remote_Rx, &Data_Remote_Rx, portMAX_DELAY); 

      vTaskNotifyGiveFromISR(task_remote_rx_bottom_half,&xHigherPriorityTaskWoken);
    }

  }
  else if ((event & CYHAL_UART_IRQ_TX_EMPTY) == CYHAL_UART_IRQ_TX_EMPTY)
  {
    /* Should never get here because Tx Empty Interrupts will not be enabled*/
  }

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
 * @brief 
 * Parses the 7-byte packet.  If the packet is invalid, the packet is discarded
 * If the packet is valid, initialize a game_info_msg_t message with the data 
 * received and send it to the q_Control_Rx_Data queue.
 * @param param 
 */
void task_remote_rx_bottom_half(void *param)
{
  /* Suppress warning for unused parameter */
  (void)param;

  /* Repeatedly running part of the task */
  for (;;)
  {
    remote_uart_data_t packet;
    xQueueReceive(q_Remote_Rx, &packet, portMAX_DELAY);

    // Verify the packet and send/notify that data is recieved
    if (staff_packet_verify(packet.payload))
    {
      game_info_msg_t game_info;

      game_info.cmd = packet.payload[1];
      game_info.score = ((uint16_t)packet.payload[2] << 8) | packet.payload[3];
      game_info.spins = packet.payload[4];
      game_info.passed = packet.payload[5];

      xQueueSend(q_Control_Rx_Data, &game_info, portMAX_DELAY);
      xEventGroupSetBits(eg_UI, EVENT_IPC_RX_DATA);

    }

  }
}

/**
 * @brief
 * Initializes the Remote UART interface so that interrupts are generated when bytes of data
 * are received by the remote UART.  This function registers a handler and bottom half task
 * that will be used to verify the data received is valid.  As part of the initialization, a
 * FreeRTOS Queue is created so send data between the Interrupt Handler and the bottom half
 * task.
 */
void task_remote_rx_init(void)
{
  q_Remote_Rx = xQueueCreate(1, sizeof(remote_uart_data_t));

  /* Set the remote uart to 115200 8N1*/
  remote_uart_init();
  
  remote_uart_enable_interrupts(
    Handler_FreeRTOS_Remote_UART,
    true, 
    false);

  xTaskCreate(
      task_remote_rx_bottom_half,
      "Task Remote Rx Bottom",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_BOTTOM_HALF,
      NULL);
}

#endif
