/**
 * @file pyl_handler_tmr_050_ms.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef __PYL_HANDLER_TMR_050_MS_H__
 #define __PYL_HANDLER_TMR_050_MS_H__

#include "main.h"

#if defined(HW02) || defined (HW03) || defined (HW04)

void handler_timer_050_ms(void *callback_arg, cyhal_timer_event_t event);

 #endif

 #endif