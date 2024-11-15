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
    if((packet[0] == 0xA0) && (packet[1] == 0xB1) && (packet[6] == 0xA1)) {
        return true;
    }

    return false;
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
bool pyl_ipc_rx(game_info_msg_t *game_info) {

    uint8_t packet[7];
    
    if(circular_buffer_get_num_bytes(Rx_Circular_Buffer) != 7) {
        return false;
    }
    
    for(int i = 0; i < 7; i++) {
        packet[i] = circular_buffer_remove(Rx_Circular_Buffer);
    }

    if(pyl_packet_verify(packet)) {
        
        game_info->cmd = packet[1];
        game_info->score = ((packet[2] << 8) | packet[3]);
        game_info->spins = packet[4];
        game_info->passed = packet[5];

        return true;
    }

    return false;

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
    circular_buffer_add(Tx_Circular_Buffer, REMOTE_PACKET_START);  // 0xA0
    circular_buffer_add(Tx_Circular_Buffer, CMD_UPDATE_REMOTE_DATA); // 0xB1
    circular_buffer_add(Tx_Circular_Buffer, (uint8_t)((game_info->score & 0xFF00) >> 8));
    circular_buffer_add(Tx_Circular_Buffer, (uint8_t)(game_info->score & 0x00FF));
    circular_buffer_add(Tx_Circular_Buffer, game_info->spins);
    circular_buffer_add(Tx_Circular_Buffer, game_info->passed);
    circular_buffer_add(Tx_Circular_Buffer, REMOTE_PACKET_END);   // 0xA1

    for(int i = 0; i<7; i++) {
        printf("%d ",Tx_Circular_Buffer->data[i]);
    }
    printf("\n");

    // enable tx event 
    cyhal_uart_enable_event(&remote_uart_obj, (cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY, 7, true); //Transmit buffer is empty
    return true;

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

        /* Read in the current character */
        if(CY_RSLT_SUCCESS == cyhal_uart_getc(&remote_uart_obj, &c,0)) {

            /* If REMOTE_PACKET_END received, set the corresponding bit in ECE353_Event */
            if(c == REMOTE_PACKET_END) {
                ECE353_Events.ipc_rx = 1;
            }

            /* Add the character to the circular buffer */
            circular_buffer_add(Rx_Circular_Buffer, c);
        }

    }

    else if ((event & CYHAL_UART_IRQ_TX_EMPTY) == CYHAL_UART_IRQ_TX_EMPTY) //if empty tx_interrupt recieved then process tx buffer 
    {
        /* The UART finished transferring data, so check and see if
        * there is more data in the circular buffer to send*/
       if(!circular_buffer_empty(Tx_Circular_Buffer)) {

        // remove from tx buffer -> remote 
        uint32_t c = circular_buffer_remove(Tx_Circular_Buffer) ;
        remote_uart_tx_char_async(c);
        
       }

       else {
        cyhal_uart_enable_event(&remote_uart_obj,(cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY, 7, false);
       }

    }

}

 #endif