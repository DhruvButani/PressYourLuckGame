/**
 * @file io-sw.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io-sw.h"

/*****************************************************************************/
/* Public Global Variables */
/*****************************************************************************/

/*****************************************************************************/
/* Static Function Declarations */
/*****************************************************************************/
static void Handler_Timer_Buttons(void *handler_arg, cyhal_timer_event_t event);
static void push_buttons_timer_init(void);

/*****************************************************************************/
/* ICE 02 START */
/*****************************************************************************/
void push_buttons_init(bool enable_timer_irq)
{
    
    cy_rslt_t rsltOne;
    cy_rslt_t rsltTwo;
    cy_rslt_t rsltThree;

    /* Initialize the IO Pins connected to the push buttons as inputs */
    rsltOne = cyhal_gpio_init(PIN_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    rsltTwo = cyhal_gpio_init(PIN_SW2, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    rsltThree = cyhal_gpio_init(PIN_SW3, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);

    /* ADD CODE */
    if(enable_timer_irq)
    {
        push_buttons_timer_init();
    }
} 
/*****************************************************************************/
/* ICE 02 END */
/*****************************************************************************/

/*****************************************************************************/
/* ICE 06 START */
/*****************************************************************************/

/*
 * Handler used to debounce the push buttons
*/
static void Handler_Timer_Buttons(void *handler_arg, cyhal_timer_event_t event)
{
    /* Static Vars */
    
    uint32_t reg_val = PORT_BUTTONS->IN;

    /* Many mechanical buttons will bounce when they are pressed.
    *  The signal may oscillate between 0 and 1 for several milliseconds.
    *
    * We will debounce a button by sampling the button and detecting the first
    * 50mS interval of time when the button is low.  When that period of time is
    * detected, we will alert the main application using ECE353_Events.
    */

   /* ADD CODE */

}

/* ADD CODE */
/* Allocate static variables for a cyhal_timer_t and cyhal_timer_cfg_t that will be used
 * to configure the button timer*/

static void push_buttons_timer_init(void)
{
    /*ADD CODE*/
    /*
     * Use timer_init() to configure a timer that generates an interrupt every 10mS
     * This timer will be used to debounce the push buttons  on the ECE353 Dev Board
     */
}
/*****************************************************************************/
/* ICE 06 END */
/*****************************************************************************/