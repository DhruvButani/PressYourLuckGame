/**
 * @file remote_uart_rx.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "remote_uart.h"
/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern cyhal_uart_t remote_uart_obj;

Circular_Buffer *Rx_Circular_Buffer;

/**
 * @brief
 * Return a message from the circular buffer
 * @param msg
 * Starting address to place the message
 * @param max_size
 * Max number of characters to copy
 * @return true
 * Message copied successfully
 * @return false
 * No message was found in circular buffer
 */
bool remote_uart_rx_data_async(char *msg, uint16_t max_size)
{
    /* ADD CODE */

    /* If the msg pointer is NULL, return false*/

    /* If the circular buffer is empty, return false */

    /* Disable interrupts -- Disable NVIC */

    /* Grab characters from the circular buffer until the buffer
     *  is empty OR the maximum number of characters are copied*/

    /* Re-enable interrupts -- Enable NVIC */

    /* Return true */
    return true;
}

/**
 * @brief
 * Enables Rx Interrupts for the remote UART. 
 *  of data will utilize circular buffers to help minimize the amount
 * of time spent waiting for the UART interface.
 */
void remote_uart_rx_interrupts_init(void)
{
    /* ADD CODE */

    /* Initialize Rx_Circular_Buffer */

    /* Turn on Rx interrupts */
}

/**
 * @brief
 * Implements the Rx portion of the UART Handler
 */
void remote_uart_event_handler_process_rx(void)
{
    cy_rslt_t status;

    /* ADD CODE to receive a character using the HAL UART API */

    /* check for the end of a message to set the alert variable*/
    
    /* Add the character to the circular buffer if not the 
     * of the message
     */
}