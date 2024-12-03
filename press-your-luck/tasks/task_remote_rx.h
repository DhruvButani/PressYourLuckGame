#ifndef __TASK_REMOTE_RX_H__
#define __TASK_REMOTE_RX_H__

#include "main.h"

#if defined(HW05) || defined(HW06)

#include "ece353_tasks.h"

void task_remote_rx_init(void);
void task_remote_rx_bottom_half(void *param);

#endif

#endif