/**
 * @file ice03.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE03)

char APP_DESCRIPTION[] = "ECE353: ICE 03 - PSoC6 IO Ports";

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    push_buttons_init(false);

    leds_init();
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    button_state_t sw1_curr_state = BUTTON_RELEASED;
    button_state_t sw1_prev_state = BUTTON_RELEASED;
    
    button_state_t sw2_curr_state = BUTTON_RELEASED;
    button_state_t sw2_prev_state = BUTTON_RELEASED;
   
    button_state_t sw3_curr_state = BUTTON_RELEASED;
    button_state_t sw3_prev_state = BUTTON_RELEASED;

    uint32_t button_value = 0;

     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

     for (;;)
    {
        /* Read in the current state of the push buttons into button_value */
        button_value = REG_PUSH_BUTTON_IN;



        /* If SW1 is pressed, set sw1_curr_state to     BUTTON_PRESSED
         * If SW1 is not pressed, set sw1_curr_state to BUTTON_RELEASED
         */
        if((PORT_BUTTONS->IN & SW1_MASK) == 0)
        {
            sw1_curr_state = BUTTON_PRESSED;
        }
        else
        {
            sw1_curr_state = BUTTON_RELEASED;
        }

        /* If SW2 is pressed, set sw2_curr_state to     BUTTON_PRESSED
         * If SW2 is not pressed, set sw2_curr_state to BUTTON_RELEASED
         */
         if((PORT_BUTTONS->IN & SW2_MASK) == 0)
        {
            sw2_curr_state = BUTTON_PRESSED;
        }
        else
        {
            sw2_curr_state = BUTTON_RELEASED;
        }
       
        /* If SW3 is pressed, set sw3_curr_state to     BUTTON_PRESSED
         * If SW3 is not pressed, set sw3_curr_state to BUTTON_RELEASED
         */

         if((PORT_BUTTONS->IN & SW3_MASK) == 0)
        {
            sw3_curr_state = BUTTON_PRESSED;
        }
        else
        {
            sw3_curr_state = BUTTON_RELEASED;
        }

        /* If the current state of SW1 is BUTTON_PRESSED and the previous state is BUTTON_RELEASED 
         * turn the red LED on.
         */

        if((sw1_curr_state == BUTTON_PRESSED) && (sw1_prev_state == BUTTON_RELEASED)) {
            PORT_RGB_RED->OUT &= MASK_RGB_RED;
        }

        /* If the current state of SW1 is BUTTON_RELEASED and the previous state is BUTTON_PRESSED 
         * turn the red LED off
         */
         if((sw1_curr_state == BUTTON_RELEASED) && (sw1_prev_state == BUTTON_PRESSED)) {
            PORT_RGB_RED->OUT &= ~MASK_RGB_RED;
        }
        /* If the current state of SW2 is BUTTON_PRESSED and the previous state is BUTTON_RELEASED 
         * turn the green LED on
         */
        if((sw1_curr_state == BUTTON_PRESSED) && (sw1_prev_state == BUTTON_RELEASED)) {
            PORT_RGB_GRN->OUT &= MASK_RGB_GRN;
        }

        /* If the current state of SW2 is BUTTON_RELEASED and the previous state is BUTTON_PRESSED 
         * turn the green LED off
         */
         if((sw1_curr_state == BUTTON_RELEASED) && (sw1_prev_state == BUTTON_PRESSED)) {
            PORT_RGB_GRN->OUT &= ~MASK_RGB_GRN;
        }

        /* If the current state of SW3 is BUTTON_PRESSED and the previous state is BUTTON_RELEASED 
         * turn the blue LED on
         */
        
        if((sw1_curr_state == BUTTON_PRESSED) && (sw1_prev_state == BUTTON_RELEASED)) {
            PORT_RGB_BLU->OUT &= MASK_RGB_BLU;
        }
        /* If the current state of SW3 is BUTTON_RELEASED and the previous state is BUTTON_PRESSED 
         * turn the blue LED off
         */
        if((sw1_curr_state == BUTTON_PRESSED) && (sw1_prev_state == BUTTON_RELEASED)) {
            PORT_RGB_BLU->OUT &= MASK_RGB_BLU;
        }
        /* For each button, set local variable that holds the previous state to the current state of the button */
        
        /* Delay for 50 mS*/
        cyhal_system_delay_ms(50);
    }
}
#endif