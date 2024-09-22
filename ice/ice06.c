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
#include "io-leds.h"

#if defined(ICE06)

char APP_DESCRIPTION[] = "ECE353: ICE06 - PWM";

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* This function needs to be written as part of the Ex06 PWM video*/
    leds_pwm_init();
}
/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
static void ice06_update_duty_cycle(cyhal_pwm_t *pwm_obj, uint8_t duty_cycle)
{
    cy_rslt_t rslt = CY_RSLT_SUCCESS;

    /* ADD CODE */
    /* Stop the PWM generation */
    
    if( rslt != CY_RSLT_SUCCESS)
    {
        printf("Failed to stop PWM\n\r");
        while(1){};
    }

    /* ADD CODE */
    /* Change the Duty Cycle */
    
    if( rslt != CY_RSLT_SUCCESS)
    {
        printf("Failed to set duty cycle for PWM\n\r");
        while(1){};
    }


    /* ADD CODE */
    /* Start the PWM generation */
    
    if( rslt != CY_RSLT_SUCCESS)
    {
        printf("Failed to start PWM\n\r");
        while(1){};
    }


}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    uint8_t red_duty_cycle = 0;
    uint8_t green_duty_cycle = 0;
    uint8_t blue_duty_cycle = 0;

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    while (1)
    {
        while(red_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the red LED */

            cyhal_system_delay_ms(200);

            red_duty_cycle += 10;
        }

        /*ADD CODE Turn off the red LED by setting the duty cycle for the red LED to 0*/
        red_duty_cycle = 0;
        ice06_update_duty_cycle(&pwm_red_obj,red_duty_cycle);

        while(green_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the green LED */

            cyhal_system_delay_ms(200);

            green_duty_cycle += 10;
        }

        /*ADD CODE Turn off the green LED by setting the duty cycle for the green LED to 0*/
        green_duty_cycle = 0;
        ice06_update_duty_cycle(&pwm_green_obj,green_duty_cycle);

        while(blue_duty_cycle <= 100)
        {
            /* ADD CODE Set the duty cycle for the blue LED */

            cyhal_system_delay_ms(200);
            
            blue_duty_cycle += 10;
        }

        /*ADD CODE Turn off the blue LED by setting the duty cycle for the blue LED to 0*/

    }
}

#endif