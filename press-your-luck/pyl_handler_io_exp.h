/**
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef __PYL_HANDLER_IO_EXP_H__
 #define __PYL_HANDLER_IO_EXP_H__

#include "main.h"

#if defined (HW04) || defined (HW05)

void io_exp_initialize(void);
void handler_io_exp(void *callback_arg, cyhal_gpio_event_t event);

 #endif

 #endif