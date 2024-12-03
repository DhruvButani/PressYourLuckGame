/**
 * @file task_lcd_game_info.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TASK_LCD_GAME_INFO_H__
#define __TASK_LCD_GAME_INFO_H__

#include "main.h"

#if defined(HW05) || defined(HW06)
#include "ece353_tasks.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/* Semaphores */
extern SemaphoreHandle_t s_LCD;

/* Queues */
extern QueueHandle_t q_LCD_Info;

void task_lcd_game_info_init(void);
void task_lcd_game_info(void *param);

#endif

#endif