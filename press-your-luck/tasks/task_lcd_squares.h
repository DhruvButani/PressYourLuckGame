/**
 * @file task_lcd_squares.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TASK_LCD_SQUARES_H__
#define __TASK_LCD_SQUARES_H__

#include "main.h"

#if defined(HW05) || defined(HW06)

#include "ece353_tasks.h"

extern QueueHandle_t q_LCD_SQUARES;

void task_lcd_squares_init(void);
void task_lcd_squares(void *param);

#endif

#endif
