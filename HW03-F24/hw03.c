/**
 * @file hw03.c
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw03.h"

#if defined(HW03)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: HW03";
char TEAM[] = "Team28";
char STUDENTS[] = "Butani Dhruv, Hern, Thomas2";



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

    /* Configure the remote UART for 115200, 8N1*/
    remote_uart_init();

    /* Enable Rx interrupts for the remote.  Use the handler defined in pyl_ipc.c */
    remote_uart_enable_interrupts(handler_ipc, true, true);

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

    pyl_images_randomize(pyl_images);
    
    for (int i = 0; i < 14; i++) {
        pyl_images[i].square_id = i;
        pyl_draw_image(&(pyl_images[i]));
    }

    bool gameOver = false;

    bool sw1_pressed;
    bool sw2_pressed;


    bool sw1_prev_pressed = false;
    bool sw2_prev_pressed = false;

    pyl_images[active_index].invert_colors = true;

    pyl_draw_image(&pyl_images[active_index]);

    pyl_print_digits_6(local_info.score, LOCATION_LOCAL_SCORE_X , LOCATION_LOCAL_SCORE_Y, COLOR_LOCAL_SCORE, ~COLOR_LOCAL_SCORE);
    pyl_print_digits_2(local_info.spins, LOCATION_LOCAL_SPINS_X, LOCATION_LOCAL_SPINS_Y, COLOR_LOCAL_SPINS, ~COLOR_LOCAL_SPINS);
    pyl_print_digits_2(local_info.passed, LOCATION_LOCAL_PASSED_X, LOCATION_LOCAL_PASSED_Y, COLOR_LOCAL_PASSED, ~COLOR_LOCAL_PASSED);



    for (;;) {
        
        if(gameOver) {
            break;
        }

        sw1_pressed = (ECE353_Events.sw1==1);
        sw2_pressed = (ECE353_Events.sw2==1);


        /* If SW1 is pressed, update the scores and spins */
        if (sw1_prev_pressed && !sw1_pressed) 
        {

            if(pyl_images[active_index].image_type == IMG_TYPE_WHAMMY) {
                local_info.score = 0;
                local_info.spins--;
            }

            else if(pyl_images[active_index].image_type >= 7) {
                local_info.score += pyl_images[active_index].value;
            }

            else {
                local_info.score += pyl_images[active_index].value;
                local_info.spins--;
            }


            pyl_print_digits_6(local_info.score, LOCATION_LOCAL_SCORE_X , LOCATION_LOCAL_SCORE_Y, COLOR_LOCAL_SCORE, ~COLOR_LOCAL_SCORE);
            pyl_print_digits_2(local_info.spins, LOCATION_LOCAL_SPINS_X, LOCATION_LOCAL_SPINS_Y, COLOR_LOCAL_SPINS, ~COLOR_LOCAL_SPINS);
            pyl_print_digits_2(local_info.passed, LOCATION_LOCAL_PASSED_X, LOCATION_LOCAL_PASSED_Y, COLOR_LOCAL_PASSED, ~COLOR_LOCAL_PASSED);


            pyl_ipc_tx(&local_info);

            if(local_info.spins == 0) {
                gameOver = true;
            }

        }

        /* If SW2 is pressed, randomize the 14 squares and display them on the LCD*/
        if (sw2_prev_pressed && !sw2_pressed)  
        {
            pyl_images_randomize(pyl_images);
    
            for (int i = 0; i < 14; i++) {
                pyl_images[i].square_id = i;
                pyl_draw_image(&(pyl_images[i]));
            }

            pyl_images[active_index].invert_colors = true;
            pyl_draw_image(&pyl_images[active_index]);

        }

        sw1_prev_pressed = sw1_pressed;
        sw2_prev_pressed = sw2_pressed;

        /* Delay for 50mS */
        cyhal_system_delay_ms(50);

        /* If joystick is moved from the center, move the active square */
        if(ECE353_Events.joystick == 1) {

            Joystick_Pos = joystick_get_pos();
            
            pyl_images[active_index].invert_colors = false;
            pyl_draw_image(&pyl_images[active_index]);

            if(Joystick_Pos == JOYSTICK_POS_UP) {
                if(active_index == 13) {
                    active_index = 0;
                }
                else{
                    active_index++;
                }  
            }

            if(Joystick_Pos == JOYSTICK_POS_DOWN) {
                if(active_index == 0) {
                    active_index = 13;
                }
                else {
                    active_index--;
                }  
            }
            
            pyl_images[active_index].invert_colors = true;
            pyl_draw_image(&pyl_images[active_index]);

            ECE353_Events.joystick = 0;

        }

        cyhal_system_delay_ms(75);

    }

}


#endif
