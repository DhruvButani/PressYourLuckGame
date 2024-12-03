#ifndef __TASK_EEPROM_H__
#define __TASK_EEPROM_H__

#include "main.h"

#if defined(HW05) || defined(HW06)

#include "ece353_tasks.h"

extern QueueHandle_t q_EEPROM;

typedef enum {
    EEPROM_READ,
    EEPROM_WRITE
} eeprom_operation_t;

typedef struct {
    eeprom_operation_t operation;
    uint16_t score;
    QueueHandle_t return_queue;
} eeprom_msg_t;

void task_eeprom_init(void);
void task_eeprom(void *param);

#endif

#endif
