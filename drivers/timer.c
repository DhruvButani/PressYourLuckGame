/**
 * @file timer.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "timer.h"
#include <complex.h>

void timer_init(cyhal_timer_t *timer_obj, cyhal_timer_cfg_t *timer_cfg, uint32_t ticks, void *Handler)
{
    cy_rslt_t rslt;

    timer_cfg->compare_value = 0;                   /* Comparison Value -- not used */
    timer_cfg->period = ticks - 1;                  /* Terminal Value used to generate interrupt*/
    timer_cfg->direction = CYHAL_TIMER_DIR_UP;      /* Timer Direction */
    timer_cfg->is_compare = false;                  /* Do not use compare mode */
    timer_cfg->is_continuous = true;                /* Continuous Mode */
    timer_cfg->value = 0;                           /* Current value of the timer*/

    /* Initialize a timer */
    rslt = cyhal_timer_init(timer_obj, NC, NULL);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Apply timer configuration such as period, count direction, run mode, etc. */
    rslt = cyhal_timer_configure(timer_obj, timer_cfg);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Set the frequency of timer*/
    rslt = cyhal_timer_set_frequency(timer_obj, 100000000);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Assign the ISR to execute on timer interrupt */
    cyhal_timer_register_callback(timer_obj, Handler, NULL);

    /* Set the event on which timer interrupt occurs and enable it */
    cyhal_timer_enable_event(timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT, 3, true);
}