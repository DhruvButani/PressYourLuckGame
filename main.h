/**
 * @file ece353.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/* Include Infineon BSP Libraries */
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"


/* Include Stanard C Libraries*/
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

/* Include ECE353 Drivers */

#include "drivers/console.h"
#include "drivers/ece353_events.h"
#include "drivers/eeprom.h"
#include "drivers/io-sw.h"
#include "drivers/io-leds.h"
#include "drivers/io-lcd.h"
#include "drivers/joystick.h"
#include "drivers/remote_uart.h"
#include "drivers/systick.h"
#include "drivers/timer.h"
#include "drivers/pwm-buzzer.h"

/* SPI Includes */
#include "drivers/spi.h"
#include "drivers/lsm6dsm_reg.h"
#include "drivers/imu.h"
#include "drivers/eeprom.h"

/* I2C Includes */
#include "drivers/i2c.h"
#include "drivers/LM75.h"
#include "drivers/io-expander.h"
#include "drivers/ft6x06.h" 
#include "drivers/light-sensor.h"

/* Uncomment the line below to enable FreeRTOS in your applications*/
//#define ECE353_FREERTOS

#if defined(ECE353_FREERTOS)
/* FreeRTOS Includes */
#include <FreeRTOS.h>
#include <event_groups.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>
#endif


/* This macro is used to determine if we are building an executable for example code or ICE code.
 * Only a single line should be uncommented at one time.  
*/
//#define EX01         /* Example Code C Basics*/
//#define EX02         /* Example Code Memory Mapped IO*/
//#define EX03         /* Example Code PSoC6 IO Ports*/
//#define EX05         /* Example Code SysTick*/
//#define EX06         /* Example Code PWM */
//#define EX07         /* Example Code Timer Interrupts*/
//#define EX08         /* Example Code ADC*/
//#define EX13         /* Example Code SPI IMU*/
//#define EX14         /* Example Code I2C Temp Sensor*/
//#define EX15         /* Example Code FreeRTOS*/
//#define EX16         /* Example Code FreeRTOS Semaphores*/
//#define EX17         /* Example Code FreeRTOS Queues*/
//#define EX18         /* Example Code FreeRTOS Task Notifications*/

//#define ICE01       /* In-Class Exercise -- Intro to C */
//#define ICE02        /* In-Class Exercise -- Memory Mapped IO */
//#define ICE03        /* In-Class Exercise -- PSoC6 IO Ports */
//#define ICE04        /* In-Class Exercise -- GPIO LCD */
//#define ICE05        /* In-Class Exercise -- SysTick */
//#define ICE06        /* In-Class Exercise -- PWM */
//#define ICE07        /* In-Class Exercise -- Timer Interrupts */
//#define ICE08        /* In-Class Exercise -- ADC */
//#define ICE09        /* In-Class Exercise -- UART Polling */
//#define ICE10        /* In-Class Exercise -- Circular Buffers */
//#define ICE11        /* In-Class Exercise -- UART Rx Interrupts */
//#define ICE12        /* In-Class Exercise -- UART Tx Interrupts */
//#define ICE13        /* In-Class Exercise -- SPI EEPROM */
//#define ICE14        /* In-Class Exercise -- I2C IO Expander */
//#define ICE15        /* In-Class Exercise -- FreeRTOS*/
//#define ICE16        /* In-Class Exercise -- FreeRTOS Semaphores */
//#define ICE17        /* In-Class Exercise -- FreeRTOS Queues */
//#define ICE18        /* In-Class Exercise -- FreeRTOS Task Notifications */

//#define HW01
//#define HW02
#define HW03
//#define HW04
//#define HW05

extern volatile ece353_events_t ECE353_Events;
extern char NAME[];
extern char APP_DESCRIPTION[];

/**
 * @brief 
 * This function will initialize all of the hardware resources for
 * the ICE.  
 * 
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void);

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief 
 * This function implements the behavioral requirements for the ICE
 * 
 * This function is implemented in the iceXX.c file for the ICE you are 
 * working on.
 */
void main_app(void);

#endif