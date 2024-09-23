/**
 * @file hw01a.c
 * @author
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */


#include "hw01.h"


#if defined(HW01)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW01";
char STUDENTS[] = "LastName1, FirstName1 & LastName2, FirstName2";

 cyhal_trng_t trng_obj;


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Enable printf */
    console_init();

    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

    /* Enable the push buttons*/
    push_buttons_init(false);

    ece353_enable_lcd();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for HW01 
 */
void main_app(void)
{

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    
    /* Add any local variables required to implement the requirements for HW01*/
    #define NUM_SQUARES 14

    bool sw1_pressed = false;
    bool sw2_pressed = false;

    image_t images[NUM_SQUARES]; 
    uint32_t reg_val = 0;

    /* Draw the 14 empty squares */
    /* Use the function pyl_draw_square() to draw an empty square*/
    for (int i = 0; i < NUM_SQUARES; i++)
    {
        pyl_draw_square(i);
    }
   

    /* Main application loop */
    for (;;)
    {

        /* Read the push button inputs */
        reg_val = REG_PUSH_BUTTON_IN;

        // set SW1 button correctly 
        if ((reg_val & SW1_MASK) == 0x00)
        {
            sw1_pressed = true;
        }
        else
        {
            sw1_pressed = false;
        }   

        // set SW2 button correctly 
        if ((reg_val & SW2_MASK) == 0x00)
        {
            sw2_pressed = true;
        }
        else{
            sw2_pressed = false;
        } 

        /* If the falling edge of SW1 is detected, randomize the 14 squares and display them on the LCD*/
        /* Use the function pyl_images_randomize() to randomize the 14 square */
        /* Use the function pyl_draw_image() to display an individual image */
        if (sw1_pressed)
        {
            pyl_images_randomize(images);

            for (int i = 0; i < NUM_SQUARES; i++)
            {
                images[i].square_id = i;
                pyl_draw_image(&(images[i]));

            }
        }

        /* If the falling edge of SW2 is detected, draw 14 empty squares */
        /* Use the function pyl_draw_square() to draw an empty square*/
        if (sw2_pressed)
        {
            for (int i = 0; i < NUM_SQUARES; i++)
            {
                pyl_draw_square(i);
            }
        } 

        /* Delay for 50mS*/
        cyhal_system_delay_ms(50);
    }
}

#endif
