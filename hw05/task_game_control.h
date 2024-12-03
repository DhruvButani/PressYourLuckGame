#ifndef __TASK_GAME_CONTROL_H__
#define __TASK_GAME_CONTROL_H__

#include "hw05.h"

#if defined(HW05)
extern TaskHandle_t Task_Handle_Game_Control;
extern QueueHandle_t q_Control_Rx_Data;

void task_game_control(void *param);
void task_game_control_init(void);

#endif

#endif