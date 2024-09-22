/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"
#include "timer.h"

#if defined(EX07)

char APP_DESCRIPTION[] = "ECE353: Ex07 - Timer Interrupts";

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Ex07_TMR(void *handler_arg, cyhal_timer_event_t event) {

}

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void) {
  console_init();

  /* Initialize leds */
  leds_init();

  /* Enable a timer that generates an interrupt every 100 microseconds  */

  /* Start the timer */
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void) {

  printf("\x1b[2J\x1b[;H");
  printf("**************************************************\n\r");
  printf("* %s\n\r", APP_DESCRIPTION);
  printf("* Date: %s\n\r", __DATE__);
  printf("* Time: %s\n\r", __TIME__);
  printf("* Name:%s\n\r", NAME);
  printf("**************************************************\n\r");

  /* Enter Infinite Loop*/
  while (1) {
    /* Print out a message every 1 second */
  }
}
#endif