/**
 * @file ice16.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE18)

char APP_DESCRIPTION[] = "ECE353: ICE 18 - FreeRTOS Task Notifications";

typedef struct LCD_Coordinates_t{
    uint16_t x;
    uint16_t y;
} LCD_Coordinates_t;

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
/* ADD CODE */
/* Create two TaskHandle_T variables for the Cap Touch and LCD tasks */


/* ADD CODE */
/* Create a QueueHandle_t for the CapTouch position queue */

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_cap_touch(void *pvParameters);
void task_lcd(void *pvParameters);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
cyhal_gpio_callback_data_t cap_touch_callback_data;

/*****************************************************************************/
/* Interrupt Handlers                                                        */
/*****************************************************************************/
/* Interrupt handler callback function */
void cap_touch_handler(void *handler_arg, cyhal_gpio_event_t event)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* ADD CODE */
    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */

    /* ADD CODE */
    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
}

/*****************************************************************************/
/* Peripheral Initialization                                                 */
/*****************************************************************************/
void cap_touch_irq_enable(void)
{
    cyhal_gpio_init(PIN_IO_CAP_TOUCH_INT,CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    cap_touch_callback_data.callback = cap_touch_handler;
    cyhal_gpio_register_callback(PIN_IO_CAP_TOUCH_INT, &cap_touch_callback_data);
    cyhal_gpio_enable_event(PIN_IO_CAP_TOUCH_INT, CYHAL_GPIO_IRQ_FALL, 3, true);
}

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the i2C bus */
    i2c_init();

    ece353_enable_lcd();

    cap_touch_irq_enable();
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
     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* ADD CODE */
    /* Initialize the LCD queue that will be used to send the coordinates of where
     * the user is touching the LCD screen
     */

    /* ADD CODE */
    /* Create the LCD Task */

    /* ADD CODE */
    /* Create the Cap Touch Task */

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

#define CURSOR_SIZE     5

/**
 * @brief 
 * This task is a bottom half task for the IO pin that generates an interrupt when the user
 * touches the LCD screen.  This task will wait indefinitely for a task notification from the 
 * IO pins handler.  Once the task notification is received, the task will determine the 
 * coordinates where the user is making contact with the LCD using the I2C bus. You will need
 * to make use of the functions defined in  ft6x06.c
 * @param pvParameters 
 */
void task_cap_touch(void *pvParameters)
{
    /* ADD CODE */
    uint8_t td_status;
    LCD_Coordinates_t coordinates;
    while (1)
    {
        /* ADD CODE */
        /* Wait for the Cap Touch IO Interrupt Handler to send
         * a task notification
         */

        /* Check to see if the TD status is equal to 1 or 2*/
        td_status = ft6x06_read_td_status();

        if(td_status == 1 || td_status == 2)
        {
            /* ADD CODE */
            /* Read the X and Y coordinates */
            
            printf("X: %d Y: %d \n\r",coordinates.x, coordinates.y);

            /* ADD CODE */
            /* Send the message to the LCD Task */
        }
    }
}

/**
 * @brief 
 * This Task will wait indefinitely for a message to be received on a Queue. The data in 
 * the queue will contain the coordinates of where the user is making contact with the 
 * LCD screen.  Using this information, the task will then draw a rectangle on the LCD screen 
 * @param pvParameters 
 */
void task_lcd(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    uint16_t cursor_color = LCD_COLOR_GREEN;
    LCD_Coordinates_t coordinates;

    while (1)
    {
        /* ADD CODE */
        /* Wait to receive a message with the coordinates to draw the cursor*/

        /* Draw a rectangle on the LCD*/
        lcd_draw_rectangle_centered(coordinates.x, coordinates.y, CURSOR_SIZE, CURSOR_SIZE, cursor_color);
    }
}


//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    // Handle FreeRTOS Stack Overflow
    while (1)
    {
    }
}

#endif