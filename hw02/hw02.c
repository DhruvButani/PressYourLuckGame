/**
 * @file hw02.c
 * @author
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw02.h"


#if defined(HW02)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW02";
char TEAM[] = "Team28";
char STUDENTS[] = "Butani, Dhruv & Hern, Thomas";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/* Current Position of the Joystick */
joystick_position_t Joystick_Pos = JOYSTICK_POS_CENTER;

/* 50mS Timer Handles*/
cyhal_timer_t Hw_Timer_Obj; 
cyhal_timer_cfg_t Hw_Timer_Cfg;


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

    pwm_buzzer_init();

    joystick_init();

    /* Enable a timer peripheral that will interrupt every 50mS */
    timer_init(&Hw_Timer_Obj,&Hw_Timer_Cfg,5000000,handler_timer_050_ms);

    /* Start the timer */
    cyhal_timer_start(&Hw_Timer_Obj);

}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void main_app(void)
{




    image_t *pyl_images = malloc(14*sizeof(image_t));
    uint8_t active_index = 0; 
    game_info_msg_t local_info = {.cmd = CMD_UPDATE_LOCAL_DATA, .score = 0, .spins = 5, .passed = 0};


    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Team:%s\n\r", TEAM);
    printf("* Students:%s\n\r", STUDENTS);
    printf("**************************************************\n\r");


    /* Initialize the game board with a set of random images. The active square
     * should be located at square 0 (upper left hand square)
     */

    #define NUM_SQUARES 14

    bool sw1_pressed;
    bool sw2_pressed;

    image_t images[NUM_SQUARES]; 
    uint32_t reg_val = 0;

    /* Draw the 14 empty squares */
    /* Use the function pyl_draw_square() to draw an empty square*/
    for (int i = 0; i < NUM_SQUARES; i++)
    {
        pyl_draw_square(i);
    }
    
    bool sw1_prev_pressed = false;
    bool sw2_prev_pressed = false;


    for (;;)
    {
        /* Read the push button inputs */
        reg_val = REG_PUSH_BUTTON_IN;

        // set SW1 button correctly
        sw1_pressed = ((reg_val & SW1_MASK) == 0x00);
        sw2_pressed = ((reg_val & SW2_MASK) == 0x00);

        /* If the falling edge of SW1 is detected, randomize the 14 squares and display them on the LCD */
        
        if (sw1_prev_pressed && !sw1_pressed)  // Detect falling edge for SW1
        {
            pyl_images_randomize(images);

            for (int i = 0; i < NUM_SQUARES; i++)
            {
                images[i].square_id = i;
                pyl_draw_image(&(images[i]));
            }
        }

        /* If the falling edge of SW2 is detected, draw 14 empty squares */
        if (sw2_prev_pressed && !sw2_pressed)  // Detect falling edge for SW2
        {
            for (int i = 0; i < NUM_SQUARES; i++)
            {
                pyl_draw_square(i);
            }
        }

        /* Update the previous states for the next loop iteration */
        sw1_prev_pressed = sw1_pressed;
        sw2_prev_pressed = sw2_pressed;

        /* Delay for 50mS */
        cyhal_system_delay_ms(50);



        // sw1_pressed = (ECE353_Events.sw1==1);
        // sw2_pressed = (ECE353_Events.sw2==1);

        // /* If SW1 is pressed, update the scores and spins */

        // if (sw1_prev_pressed && !sw1_pressed)  // Detect falling edge for SW1
        // {
        //     pyl_images_randomize(images);

        //     for (int i = 0; i < NUM_SQUARES; i++)
        //     {
        //         images[i].square_id = i;
        //         pyl_draw_image(&(images[i]));
        //     }
        // }


        // /* If SW2 is pressed, randomize the 14 squares and display them on the LCD*/
        // if (sw2_prev_pressed && !sw2_pressed)  // Detect falling edge for SW2
        // {
        //     for (int i = 0; i < NUM_SQUARES; i++)
        //     {
        //         pyl_draw_square(i);
        //     }
        // }

        // sw1_prev_pressed = sw1_pressed;
        // sw2_prev_pressed = sw2_pressed;

        // /* Delay for 50mS */
        // cyhal_system_delay_ms(50);
        
        // /* If joystick is moved from the center, move the active square */
    }
}

#endif
