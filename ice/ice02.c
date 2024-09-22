/**
 * @file ice02.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE02)

char APP_DESCRIPTION[] = "ECE353: ICE 02 - Memory Mapped IO";

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
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    bool sw1_pressed = false;
    bool sw2_pressed = false;
    bool sw3_pressed = false;

    /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");


    uint32_t reg_val = 0;

    while (1)
    {
        /* ADD CODE */
        /* Read the IO Port that is connected to the buttons */
        reg_val = REG_PUSH_BUTTON_IN;
        

        /* ADD CODE */
        /* if the SW1 is pressed, set sw1_pressed to true.*/
        /* if the SW1 is NOT pressed, set sw1_pressed to false.*/
        if ((reg_val & SW1_MASK) == 0x00)
        {
            sw1_pressed = true;
        }
        else
        {
            sw1_pressed = false;
        }   

        /* ADD CODE */
        /* if the SW2 is pressed, set sw2_pressed to true.*/
        /* if the SW2 is NOT pressed, set sw2_pressed to false.*/
         if ((reg_val & SW2_MASK) == 0x00)
        {
            sw2_pressed = true;
        }
        else{
            sw2_pressed = false;
        }  

        /* ADD CODE */
        /* if the SW3 is pressed, set sw3_pressed to true.*/
        /* if the SW3 is NOT pressed, set sw3_pressed to false.*/
        if ((reg_val & SW3_MASK) == 0x00)
        {
            sw3_pressed = true;
        }
        else
        {
            sw3_pressed = false;
        }



        if (sw1_pressed)
        {
            printf("SW1 is pressed\n\r");
        }

        if (sw2_pressed)
        {
            printf("SW2 is pressed\n\r");
        }

        if (sw3_pressed)
        {
            printf("SW3 is pressed\n\r");
        }

        /* Delay 100mS before checking the buttons again*/
        cyhal_system_delay_ms(100);
    }
}
#endif