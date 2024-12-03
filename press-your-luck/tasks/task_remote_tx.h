#ifndef __TASK_REMOTE_TX_H__
#define __TASK_REMOTE_TX_H__

#include "main.h"

#if defined(HW05) || defined(HW06)
#include "ece353_tasks.h"

extern QueueHandle_t q_Remote_Tx;

void task_remote_tx_init(void);
void task_remote_tx(void *param);


#endif

#endif
