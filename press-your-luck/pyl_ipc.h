/**
 * @file pyl_ipc.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef __PYL_IPC_H__
 #define __PYL_IPC_H__

#include "main.h"

#if defined (HW03) || defined (HW04)

#include "pyl.h"

bool pyl_ipc_rx(game_info_msg_t *game_info);
bool pyl_ipc_tx(game_info_msg_t *game_info);

 void handler_ipc(void *callback_arg, cyhal_uart_event_t event);

#endif

 #endif