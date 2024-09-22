/**
 * @file pyl_ipc.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #include "pyl_ipc.h"

 #if defined (HW03) || defined (HW04)

/* Data Structure Used to store data being received from the remote UART */
remote_uart_data_t IPC_Rx_Data = {
    .num_bytes = 0, 
    .payload = {0,0,0,0,0,0,0,0,0,0}
};

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
static bool pyl_packet_verify(uint8_t *packet)
{
    /* ADD CODE */
}


/**
 * @brief 
 * This function will initialize game_info with the data found in the 
 * circular buffer.  If the data in the circular buffer is not valid, then 
 * this function will return false.  If the data is valid, return true.
 *
 * Rx Interrupts should be enabled and data should be received using the 
 * Rx_Circular_Buffer
 * @param game_info 
  * @return true 
  * @return false 
 */
bool pyl_ipc_rx(game_info_msg_t *game_info)
{
    /* ADD CODE */
}

/**
 * @brief 
 * This function will transmit the data in game_info to the remote uart. Your function
 * should only transmit 7 bytes of data.  DO NOT transmit a NULL character, \n, or \r
 *
 * Tx Interrupts should be enabled and data should be transmitted using the 
 * Tx_Circular_Buffer
 *@param game_info 
 */
bool pyl_ipc_tx(game_info_msg_t *game_info)
{
    /* ADD CODE */
}

/**
 * @brief 
 * Handler used to collect a packet of data from the remote board.
 * @param callback_arg 
 * @param event 
 */
void handler_ipc(void *callback_arg, cyhal_uart_event_t event)
{
    uint8_t c;

    /* remove compiler warnings */
    (void) callback_arg;
    (void) event;

    if ((event & CYHAL_UART_IRQ_TX_ERROR) == CYHAL_UART_IRQ_TX_ERROR)
    {
      /* An error occurred in Tx */
      /* Insert application code to handle Tx error */
    }
    else if ((event & CYHAL_UART_IRQ_RX_NOT_EMPTY) == CYHAL_UART_IRQ_RX_NOT_EMPTY)
    {
        /* ADD CODE */

        /* Read in the current character */

        /* Add the character to the circular buffer */

        /* If REMOTE_PACKET_END received, set the corresponding bit in ECE353_Event */

    }
    else if ((event & CYHAL_UART_IRQ_TX_EMPTY) == CYHAL_UART_IRQ_TX_EMPTY)
    {
        /* The UART finished transferring data, so check and see if
        * there is more data in the circular buffer to send*/

        /* ADD CODE */
    }

}

 #endif