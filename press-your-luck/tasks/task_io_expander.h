#ifndef __TASK_IO_EXPANDER_H__
#define __TASK_IO_EXPANDER_H__

#include "main.h"

#if defined(HW05) || defined(HW06)

#include "ece353_tasks.h"

extern QueueHandle_t q_IO_Exp;

void task_io_expander_init(void);
void task_io_expander(void *param);

#endif

#endif
