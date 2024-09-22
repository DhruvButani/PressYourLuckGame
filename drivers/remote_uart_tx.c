/**
 * @file remote_uart_tx.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-09-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "remote_uart_tx.h"
#include "cy_syslib.h"
#include <sys/types.h>
/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
extern cyhal_uart_t remote_uart_obj;

/*******************************************************************************
 * Function Declarations
 ******************************************************************************/

Circular_Buffer *Tx_Circular_Buffer;

/**
 * @brief
 * Send a character to the remote UART
 * @param
 * Character to Send
 */
void remote_uart_tx_char_async(char c)
{
    /* ADD CODE */

    /* Wait while the circular buffer is full*/

    /* Disable interrupts -- Disable NVIC */
    
    /* Add the current character*/

    /* Re-enable interrupts */
    
    /* Enable the Transmit Empty Interrupts*/
}

/**
 * @brief
 * Prints out a NULL terminated string to the remote UART
 * @param msg
 * String to print
 */
void remote_uart_tx_data_async(char *msg, uint16_t num_bytes)
{
    /* ADD CODE */

    /* check to see that msg pointer is not equal to NULL*/

    /* Add characters to the circular buffer until we reach the NULL character*/
    while (num_bytes > 0)
    {
        /* Wait while the circular buffer is full*/

        /* Disable interrupts -- Disable NVIC */

        /* Add the current character*/

        /* Re-enable interrupts */

        /* Go to the next character*/

        /* Decrement the number of bytes left to transfer */
        num_bytes--;
    }

    /* Enable the Transmit Empty Interrupts*/
}

/**
 * @brief
 * Initializes the Circular Buffer used for transmitting characters to the remote UART
 * and will disable Tx Empty interrupts.
 */
void remote_uart_tx_interrupts_init(void)
{
    /* Initialize the Tx Circular Buffer */

    /* Turn Off Tx Interrupts*/
}

/**
 * @brief
 * Implements the Tx portion of the UART Handler
 */
void remote_uart_event_handler_process_tx(void)
{
    /* The UART finished transferring data, so check and see if
     * the circular buffer is empty*/
    if (1 /* ADD CODE */)
    {
        /* No More data to send, so disable Tx Empty Interrupts
         * to avoid the UART handler from constantly being
         * called
         */

        /* Disable the Transmit Empty Interrupts*/
    }
    else
    {
        /* Transmit the next character in the circular buffer */
    }
}
