/**
 * @file pwm-buzzer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "pwm-buzzer.h"

cyhal_pwm_t pwm_buzzer_obj;

void pwm_buzzer_init(void)
{
    // Initialize PWM on the supplied pin and assign a new clock

    // Set a duty cycle of 50% and frequency of 3.5KHz
}

void pwm_buzzer_start(void)
{
    /* (Re-)start the PWM output */
}

void pwm_buzzer_stop(void)
{

    /* Stop the PWM output */

}



