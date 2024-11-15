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

    if(c == NULL) {
        return;
    }

    /* Wait while the circular buffer is full*/
    while(circular_buffer_full(Tx_Circular_Buffer))
    {


    }

    /* Disable interrupts -- Disable NVIC */
    __disable_fault_irq();

    /* Add the current character*/
    cyhal_uart_putc(&remote_uart_obj, c);

    /* Re-enable interrupts */
    __enable_fault_irq();
    /* Enable the Transmit Empty Interrupts*/
    cyhal_uart_enable_event(
        &remote_uart_obj,
        (cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY,
        7,
        true
    );
   
}

/**
 * @brief
 * Prints out a NULL terminated string to the remote UART
 * @param msg
 * String to print
 */
void remote_uart_tx_data_async(char *msg, uint16_t num_bytes)
{

    /* check to see that msg pointer is not equal to NULL*/
     if(msg == NULL){
        return false;
    }


    /* Add characters to the circular buffer until we reach the NULL character*/
    while (num_bytes > 0)
    {
        /* Wait while the circular buffer is full*/
        uint8_t i = 0;
        // while(circular_buffer_full(Tx_Circular_Buffer))
        // {
        
        // }

        /* Disable interrupts -- Disable NVIC */
        __disable_fault_irq();
        
        /* Add the current character*/
        circular_buffer_add(Tx_Circular_Buffer, msg[i]);


        /* Re-enable interrupts */
       __enable_fault_irq();


        /* Go to the next character*/
        msg++;

        /* Decrement the number of bytes left to transfer */
        num_bytes--;
    }

    /* Enable the Transmit Empty Interrupts*/
    cyhal_uart_enable_event(
            &remote_uart_obj,
            (cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY,
            7,
            true
        );
}

/**
 * @brief
 * Initializes the Circular Buffer used for transmitting characters to the remote UART to 
 * and will disable Tx Empty interrupts.
 */
void remote_uart_tx_interrupts_init(void)
{   uint8_t max_size = 7;
    /* Initialize the Tx Circular Buffer */
    Tx_Circular_Buffer = circular_buffer_init(max_size); //remote: 7 as buffer operates properly

    /* Turn Off Tx Interrupts*/
    cyhal_uart_enable_event(
        &remote_uart_obj,
        (cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY,
        7,
        false
    );

}




/**
 * @brief
 * Implements the Tx portion of the UART Handler
 */
void remote_uart_event_handler_process_tx(void)
{   
    char c;
    /* The UART finished transferring data, so check and see if
     * the circular buffer is empty*/
    if (1 == circular_buffer_empty(Tx_Circular_Buffer))
    {
        /* No More data to send, so disable Tx Empty Interrupts
         * to avoid the UART handler from constantly being
         * called
         */

        /* Disable the Transmit Empty Interrupts*/
        cyhal_uart_enable_event(
            &remote_uart_obj,
            (cyhal_uart_event_t)CYHAL_UART_IRQ_TX_EMPTY,
            7,
            false);
    }
    else
    {
        /* Transmit the next character in the circular buffer */
        cyhal_uart_putc(&remote_uart_obj, circular_buffer_remove(Tx_Circular_Buffer));
    }
}