/******************************************************************************
 * File Name: uart_debug.c
 *
 * Description: This file contains the task that is used for thread-safe UART
 *              based debug.
 *
 * Related Document: See README.md
 *
 *******************************************************************************
 * (c) 2019-2020, Cypress Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 * This software, including source code, documentation and related materials
 * ("Software"), is owned by Cypress Semiconductor Corporation or one of its
 * subsidiaries ("Cypress") and is protected by and subject to worldwide patent
 * protection (United States and foreign), United States copyright laws and
 * international treaty provisions. Therefore, you may use this Software only
 * as provided in the license agreement accompanying the software package from
 * which you obtained this Software ("EULA").
 *
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software source
 * code solely for use in connection with Cypress's integrated circuit products.
 * Any reproduction, modification, translation, compilation, or representation
 * of this Software except as specified above is prohibited without the express
 * written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer of such
 * system or application assumes all risk of such use and in doing so agrees to
 * indemnify Cypress against all liability.
 *******************************************************************************/

/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "main.h"
#if defined(HW05)
#include "task_console.h"


//*******************************************************************************
// The console will be made up of the UART ISR along with two FreeRTOS
// tasks.
//
// The UART ISR will buffer data entered by the user into an array of characters.
// When the user presses the ENTER key, a Task Notification will be sent to the
// the task_console_rx task.  The only interrupt that will trigger the UART ISR
// will be CYHAL_UART_IRQ_RX_NOT_EMPTY.
//
// task_console_rx will parse the string entered by the user.  This will be
// accomplished using FreeRTOS-CLI.  Once the string has been parsed,
// CYHAL_UART_IRQ_RX_NOT_EMPTY interrupts will be re-enabled.
//
// task_console_tx will be used to print all messages to the console.  This task
// will wait for messages to arrive in its message queue.  It will then print
// out the messages in the order that they were received.  Transmitting data to
// the console will be accomplished using the retarget-io libraries supplied
// by the HAL.
//*******************************************************************************

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * External Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
cyhal_uart_t console_uart_obj;

/* Initialize the UART configuration structure */
const cyhal_uart_cfg_t console_uart_config =
    {
        .data_bits = DATA_BITS_8,
        .stop_bits = STOP_BITS_1,
        .parity = CYHAL_UART_PARITY_NONE,
        .rx_buffer = NULL,
        .rx_buffer_size = 0};

QueueHandle_t debug_message_q;

/*******************************************************************************
 * Function Name: task_console_tx
 ********************************************************************************
 * Summary:
 *  This task is responsible for printing ALL messages to the console.  It
 *  assumes that the retarget-io library is being utilized to send data
 *  to the UART
 *
 * Parameters:
 *  void *param : Task parameter defined during task creation (unused)
 *
 *******************************************************************************/
void task_console_tx(void *param)
{
    debug_message_data_t message_data;

    /* Variable used to store the return values of RTOS APIs */
    BaseType_t rtos_api_result;

    /* Remove warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        rtos_api_result = xQueueReceive(debug_message_q, &message_data,
                                        portMAX_DELAY);

        if (rtos_api_result == pdPASS)
        {
            switch (message_data.message_type)
            {
            case none:
            {
                Cy_SCB_UART_PutString(CONSOLE_SCB, (char *)message_data.str_ptr);
                break;
            }
            case info:
            {
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\033[0;32m[Info   ]\033[0m    : ");
                Cy_SCB_UART_PutString(CONSOLE_SCB, (char *)message_data.str_ptr);
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\n\r");
                break;
            }
            case warning:
            {
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\033[0;33m[WARNING]\033[0m    : ");
                Cy_SCB_UART_PutString(CONSOLE_SCB, (char *)message_data.str_ptr);
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\n\r");
                break;
            }
            case error:
            {
                
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\033[0;31m[ERROR  ]\033[0m    : ");
                Cy_SCB_UART_PutString(CONSOLE_SCB, (char *)message_data.str_ptr);
                Cy_SCB_UART_PutString(CONSOLE_SCB, "\n\r");
                break;
            }
            default:
            {
                break;
            }
            }

            /* free the message buffer allocated by the message sender */
            vPortFree((char *)message_data.str_ptr);
        }
        /* Task has timed out and received no commands during an interval of
         * portMAXDELAY ticks
         */
        else
        {
        }
    }
}

/*******************************************************************************
 * Function Name: task_debug_printf
 ********************************************************************************
 * Summary:
 *  This function sends messages to the debug Queue.
 *
 *******************************************************************************/
void task_debug_printf(debug_message_type_t message_type, char *str_ptr, ...)
{
    debug_message_data_t message_data;
    char *message_buffer;
    char *task_name;
    uint32_t length = 0;
    va_list args;

    /* Allocate the message buffer */
    message_buffer = pvPortMalloc(DEBUG_MESSAGE_MAX_LEN);

    if (message_buffer)
    {
        va_start(args, str_ptr);
        if (message_type != none)
        {
            task_name = pcTaskGetName(xTaskGetCurrentTaskHandle());
            length = snprintf(message_buffer, DEBUG_MESSAGE_MAX_LEN, "%-16s : ",
                              task_name);
        }

        vsnprintf((message_buffer + length), (DEBUG_MESSAGE_MAX_LEN - length),
                  str_ptr, args);

        va_end(args);

        message_data.message_type = message_type;
        message_data.str_ptr = message_buffer;

        /* The receiver task is responsible to free the memory from here on */
        if (pdPASS != xQueueSendToBack(debug_message_q, &message_data, 0u))
        {
            /* Failed to send the message into the queue */
            vPortFree(message_buffer);
        }
    }
    else
    {
        /* pvPortMalloc failed. Handle error */
    }
}

/*******************************************************************************
 * Function Name: task_console_init
 ********************************************************************************
 * Summary:
 *  Initializes the underlying Task and Queue used for printing debug
 *  messages.
 *
 *******************************************************************************/
void task_console_init(void)
{
    cy_rslt_t rslt;
    uint32_t actual_baud;

    rslt = cyhal_uart_init(
        &console_uart_obj,
        CONSOLE_TX_PIN,
        CONSOLE_RX_PIN,
        NC,
        NC,
        NULL,
        &console_uart_config);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    // Set the Baud Rate
    rslt = cyhal_uart_set_baud(&console_uart_obj, BAUD_RATE, &actual_baud);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    // Set up the Queue for task_console_tx
    debug_message_q = xQueueCreate(DEBUG_QUEUE_SIZE,
                                   sizeof(debug_message_data_t));

    // Create the transmit task
    xTaskCreate(
        task_console_tx,
        "Console Tx",
        15*configMINIMAL_STACK_SIZE,
        NULL,
        (tskIDLE_PRIORITY + 3u),
        NULL);

};

#endif