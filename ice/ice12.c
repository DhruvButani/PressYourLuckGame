/**
 * @file ice07.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"
#include <string.h>

#if defined(ICE12)

char APP_DESCRIPTION[] = "ECE353: ICE 12 - UART Tx Interrupts";

extern cyhal_uart_t cy_retarget_io_uart_obj;

/*****************************************************************************/
/*  Function Declarations                                                    */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
const char RX_MSG[] = "\033[0;32mAsync Rx Msg <-\033[0m";
const char TX_MSG[] = "\033[0;31mAsync Tx Msg ->\033[0m";
/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    // Initialize the remote UART port
    remote_uart_init();

    // Enable interrupts and circular buffers from remote board.
    remote_uart_enable_interrupts(remote_uart_event_handler, true, true);
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    uint8_t console_msg[80];
    uint8_t remote_rx_message[80];

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* Clear out the array holding the message */
    memset(remote_rx_message, 0, 80);

    cyhal_uart_putc(&cy_retarget_io_uart_obj, '\r');

    while (1)
    {
        /* Check to see if the user has entered a string into the console*/
        if (console_rx_string(console_msg))
        {
            /* Print out the message received on the console*/
            printf("%s %s\n\r", TX_MSG, console_msg);

            /* Send the String to the remote board */
            remote_uart_tx_data_async(console_msg, strlen(console_msg));

            /* Need to send a \r or \n to indicate the end of a string*/
            remote_uart_tx_char_async('\n');
        }
        if (ECE353_Events.ipc_rx)
        {
            /* Set the alert back to 0*/
            ECE353_Events.ipc_rx = 0;

            /* Initialize the array to all 0*/
            memset(remote_rx_message, 0, 80);

            if (remote_uart_rx_data_async(remote_rx_message, 80))
            {
                /* print out the message received from the remote uart */
                printf("%s %s\n\r", RX_MSG, remote_rx_message);
            }
        }
    }
}

#endif