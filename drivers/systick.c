/**
 * @file systick.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-06-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "systick.h"
#include <complex.h>

/**
 * @brief 
 *  Initializes the SysTick Timer for a configurable interval of time. 
 * @param ticks 
 *  The Number clock cycles 
 */
bool systick_start(uint32_t ticks)
{
    if(ticks > 0xFFFFFF)
    {
        // SysTick Timer is only 24-bits, so return an error
        return false;
    }

    // Turn off the SysTick Timer

    // Set the current value to 0

    // Set the period

    // Set the clock source to the main CPU clock and turn 
    // the timer on.

    return true;
}

/**
 * @brief 
 * Disables the SysTick Timer
 */
void systick_stop(void)
{
    SysTick->CTRL &= ~SYSTICK_CTRL_ENABLE ;
}

/**
 * @brief 
 * Determine if the SysTick timer has expired since the last time the CTRL register
 * was read
 * @return true 
 * @return false 
 */
bool systick_expired(void)
{
    /* ADD CODE */
}