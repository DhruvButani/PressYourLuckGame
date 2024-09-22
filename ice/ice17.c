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

#if defined(ICE17)

#define CURSOR_SIZE 5

char ICE_DESCRIPTION[] = "ECE353: ICE 17 - FreeRTOS Message Queues";

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
QueueHandle_t Queue_Stylus_Position;
QueueHandle_t Queue_Stylus_Color;

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_joystick(void *pvParameters);
void task_lcd(void *pvParameters);
void task_button_sw1(void *pvParameters);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Peripheral Initialization                                          */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the RGB LEDs */
    joystick_init();

    ece353_enable_lcd();

    push_buttons_init(false);
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
    /* Create the Queue for the Stylus Position */

    /* ADD CODE */
    /* Create the Queue for Stylus Color  */

    xTaskCreate(task_joystick,
                "Joystick",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                NULL);

    xTaskCreate(task_lcd,
                "LCD Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                3,
                NULL);

    xTaskCreate(task_button_sw1,
                "SW1 Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                2,
                NULL);

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

/**
 * @brief 
 * This function will monitor the current position of the joystick.  If the joystick
 * if not in the center postion, send a message to the LCD task with the current postion
 * of the joystick.  This will be done using a queue. 
 * @param pvParameters 
 */
void task_joystick(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    joystick_position_t cur_pos = JOYSTICK_POS_CENTER;

    while (1)
    {
        vTaskDelay(5);

        cur_pos = joystick_get_pos();

        /* Check to see what the current position of the
         * joystick is.  If it is not in the center, send a message
         * to the stylus position queue
         */
        if (cur_pos != JOYSTICK_POS_CENTER)
        {
            /* ADD CODE */
            /* Send the current joystick position to the stylus position queue */
        }
    }
}

/**
 * @brief
 * This task monitors SW1.  When SW1 is pressed, it update the color of the
 * stylus.  The new color of the stylus will be sent using a queue.
 * 
 * The color of the stylus should go from GREEN->ORANGE->RED->BLUE->GREEN...
 * @param pvParameters
 */
void task_button_sw1(void *pvParameters)
{
    /* ADD CODE */
    /* Allocate any local variables used in this task */
    bool state_button_prev = false;
    bool state_button_curr = false;
    uint16_t current_color = LCD_COLOR_GREEN;
    uint16_t color_lut[] = {LCD_COLOR_GREEN, LCD_COLOR_ORANGE, LCD_COLOR_RED, LCD_COLOR_BLUE};

    uint8_t color_index = 0;

    while (1)
    {
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */
        vTaskDelay(50);

        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW1_MASK) == 0x00)
        {
            state_button_curr = true;
        }
        else
        {
            state_button_curr = false;
        }

        /* If the button was pressed, update the current color
         * of the stylus and send this information to the LCD
         * task
         */
        if (state_button_curr && !state_button_prev)
        {
            /* ADD CODE */
            /* Determine the next color so send */

            /* ADD CODE */
            /* Send the updated color to the LCD Task using
             * the stylus color queue
             */
        }

        /* Update the previous button state */
        state_button_prev = state_button_curr;
    }
}
#define LCD_MIN_X (2)
#define LCD_MAX_X (319 - 2)
#define LCD_MIN_Y (2)
#define LCD_MAX_Y (240 - 2)

/**
 * @brief 
 * This function will monitor the Stylus Position and Stylus Color queues. 
 * 
 * If a valid message is received ont he Stylus Position queue, update the coordinates of the cursor
 * and draw a new rectangle at that location.  Wait up to 5mS for a message to arrive on the Position 
 * queue.  Be sure to check the return status to see if a valid message was received.
 * 
 * If a valid message is received ont he Stylus Color queue, update the color of the cursor
 * and draw a new rectangle at the current location.  Wait up to 5mS for a message to arrive on the Stylus Color 
 * queue.  Be sure to check the return status to see if a valid message was received.
 * 
 * @param pvParameters 
 */
void task_lcd(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    uint16_t x = (320 / 2) - 1;
    uint16_t y = (240 / 2) - 1;
    BaseType_t joystick_status;
    BaseType_t sw_status;
    uint16_t cursor_color = LCD_COLOR_GREEN;
    uint16_t new_color = LCD_COLOR_GREEN;

    joystick_position_t pos = JOYSTICK_POS_CENTER;

    /* Draw the cursor's initial position */
    lcd_draw_rectangle_centered(x, y, CURSOR_SIZE, CURSOR_SIZE, cursor_color);

    while (1)
    {
        /* ADD CODE */
        /* Receive the current position of the joystick from the Stylus Position Queue 
         * Timeout after 5mS. 
        */


        /* ADD CODE */
       /* Check to see if a valid message was received */
        if (0)
        {
            /* ADD CODE */
            /* Based on the information received, determine where to move the cursor to*/
            /* This implementation does NOT support diagonal movements*/
            switch (0)
            {
            case JOYSTICK_POS_LEFT:
            case JOYSTICK_POS_UPPER_LEFT:
            case JOYSTICK_POS_LOWER_LEFT:
            {
                if (x > LCD_MIN_X)
                {
                    x--;
                }

                break;
            }
            case JOYSTICK_POS_LOWER_RIGHT:
            case JOYSTICK_POS_UPPER_RIGHT:
            case JOYSTICK_POS_RIGHT:
            {
                if (x < LCD_MAX_X)
                {
                    x++;
                }
                break;
            }
            case JOYSTICK_POS_UP:
            {
                if (y > LCD_MIN_Y)
                {
                    y--;
                }
                break;
            }
            case JOYSTICK_POS_DOWN:
            {
                if (y < LCD_MAX_Y)
                {
                    y++;
                }
                break;
            }
            }

            /* Draw the new location of the cursor */
            lcd_draw_rectangle_centered(x, y, CURSOR_SIZE, CURSOR_SIZE, cursor_color);
        }

        /* ADD CODE */
        /* Receive a message from the Stylus Color Queue.  Wait 5mS for a message
         * to arrive.
        */
       
        /* ADD CODE */
        /* Check to see if a valid message was received */
        if (0)
        {
            /* ADD CODE */
            /* Set the new color based on the data received from the message queue */

            /* Re-draw the current position of the stylus*/
            lcd_draw_rectangle_centered(x, y, CURSOR_SIZE, CURSOR_SIZE, cursor_color);
        }
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