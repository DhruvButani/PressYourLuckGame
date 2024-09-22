/**
 * @file pwm-buzzer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ECE353_PWM_BUZZER_H_
#define ECE353_PWM_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

#define PIN_IO_BUZZER           P6_2

#define PWM_BUZZER_FREQ			3500
#define PWM_BUZZER_DUTY			50

extern cyhal_pwm_t pwm_buzzer_obj;

void pwm_buzzer_init(void);
void pwm_buzzer_start(void);
void pwm_buzzer_stop(void);

#endif /* ECE353_PWM_BUZZER_H_ */
