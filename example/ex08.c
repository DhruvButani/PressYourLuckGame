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
#include "ece353_events.h"
#include "joystick.h"

#if defined(EX08)

char APP_DESCRIPTION[] = "ECE353: Ex08 - ADC";

#define TICKS_MS_100 10000000

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/* Timer object and timer_cfg object */
cyhal_timer_t ex08_timer_obj;
cyhal_timer_cfg_t ex08_timer_cfg;

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Ex08_Timer(void *handler_arg, cyhal_timer_event_t event) {
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

  /* Initialize a timer */
  timer_init(&ex08_timer_obj, &ex08_timer_cfg, TICKS_MS_100,
             Handler_Ex08_Timer);

  /* Start the timer */
  cyhal_timer_start(&ex08_timer_obj);

  /* Initialize the Joystick */
  joystick_init();
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
      /* Print the the X channel of the ADC every 100mS*/
    }
}
#endif
