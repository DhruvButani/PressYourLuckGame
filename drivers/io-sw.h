/**
 * @file io-sw.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __IO_SW_H__
#define __IO_SW_H__

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include <ctype.h>
#include <stdio.h>


/*****************************************************************************/
/* ICE 02 START */
/*****************************************************************************/

/* Push Button (SW) Pins */
#define PIN_SW1                 P6_3        // MODIFY
#define PIN_SW2                 P6_4        // MODIFY
#define PIN_SW3                 P6_5        // MODIFY

/* Bit Masks for Push Buttons */
#define SW1_MASK                (1 << 3)    // MODIFY
#define SW2_MASK                (1 << 4)    // MODIFY
#define SW3_MASK                (1 << 5)    // MODIFY

/* Memory address for Push Button IO Port IN register */
#define ADDR_REG_PUSH_BUTTON_IN     0x40310310      // MODIFY
#define REG_PUSH_BUTTON_IN          (*(volatile uint32_t *)(ADDR_REG_PUSH_BUTTON_IN))

#define PORT_BUTTONS                GPIO_PRT0       // MODIFY

typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED,
}button_state_t;

/*****************************************************************************/
/* Public Global Variables */
/*****************************************************************************/

/**
 * @brief 
 * Initializes the 3 push buttons on the ECE353 Dev Board 
 */
void push_buttons_init(bool enable_timer_irq);


/*****************************************************************************/
/* ICE 02 END */
/*****************************************************************************/

#endif