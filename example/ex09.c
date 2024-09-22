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

#if defined(EX09)

char APP_DESCRIPTION[] = "ECE353: Example 09 - UART Polling";

/* This is the handle to access the UART used to print message to the 
* serial terminal 
*/
extern cyhal_uart_t cy_retarget_io_uart_obj;

/*****************************************************************************/
/*  Function Declarations                                                    */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

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

    /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* Clear out the arrays holding the messages */
    memset(console_msg, 0, 80);

    while (1)
    {

        /*
         * Check if the user has entered a string at the console.
         * A string is any string of characters that ends with
         * a '\n'  or '\r'
         */
        if (console_rx_string(console_msg))
        {
            /* Print the string back out to the console */
            printf("Tx message -> %s\n\r", console_msg);

            /* clear the array for the next message */
            memset(console_msg, 0, 80);
        }
    }
}

#endif