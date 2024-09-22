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

#if defined(ICE08)

char APP_DESCRIPTION[] = "ECE353: ICE 08 - ADC";

#define TICKS_MS_100 (10000000)

/*****************************************************************************/
/*  Function Declaration                                                     */
/*****************************************************************************/
void Handler_ICE08_Timer_0100MS(void *handler_arg, cyhal_timer_event_t event);

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/* Timer object used */
cyhal_timer_t ice08_timer_obj;
cyhal_timer_cfg_t ice08_timer_cfg;

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_ICE08_Timer_0100MS(void *handler_arg, cyhal_timer_event_t event)
{
    /* ADD CODE*/
}

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

    /* ADD CODE */

    /* Initialize a timer to generate an interrupt every 100mS*/

    /* Start the timer */

    /* Initialize the X and Y directions of the joystick to be ADC pins*/

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
    joystick_position_t curr_position = JOYSTICK_POS_CENTER;
    joystick_position_t prev_position = JOYSTICK_POS_CENTER;

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    while (1)
    {
        if (ECE353_Events.tmr_0100_ms)
        {
            /* Acknowledge the event*/
            ECE353_Events.tmr_0100_ms = 0;

            /* Save the previous position */
            prev_position = curr_position;

            /* Get the current position */
            curr_position = joystick_get_pos();

            /* If the joystick was moved, print its new position*/
            if (curr_position != prev_position)
            {
                printf("Joystick now in ");
                joystick_print_pos(curr_position);
                printf(" position\n\r");
            }
        }
    }
}

#endif