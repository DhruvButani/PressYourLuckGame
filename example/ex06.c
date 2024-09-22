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
#include "cy_result.h"
#include "cyhal_pwm.h"
#include "cyhal_system.h"
#include "io-leds.h"
#include "io-sw.h"
#include "psoc6_04_config.h"
#include <complex.h>

#if defined(EX06)

char APP_DESCRIPTION[] = "ECE353: Ex06 - PWM";

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
cyhal_pwm_t pwm_ex_blue_obj;

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void) {

  cy_rslt_t rslt = CY_RSLT_TYPE_ERROR;

  console_init();

  push_buttons_init(false);

  /* Configure the IO pin connected to the BLUE LED as a PWM pin */
  
  if(rslt != CY_RSLT_SUCCESS)
  {
    printf("Failed to initialize PWM\n\r");
    CY_ASSERT(0);
  }

  /* Set the Duty Cycle */
  
  if(rslt != CY_RSLT_SUCCESS)
  {
    printf("Failed to set PWM duty cycle \n\r");
    CY_ASSERT(0);
  }

  /* Start the PWM peripheral */
  
  if(rslt != CY_RSLT_SUCCESS)
  {
    printf("Failed to start PWM\n\r");
    CY_ASSERT(0);
  }


}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void) {

  uint8_t duty_cycle = 0;

  /* Variables used to determine if SW1 is pressed */
  uint32_t button_value = 0;
  button_state_t sw1_curr_state = BUTTON_RELEASED;
  button_state_t sw1_prev_state = BUTTON_RELEASED;

  printf("\x1b[2J\x1b[;H");
  printf("**************************************************\n\r");
  printf("* %s\n\r", APP_DESCRIPTION);
  printf("* Date: %s\n\r", __DATE__);
  printf("* Time: %s\n\r", __TIME__);
  printf("* Name:%s\n\r", NAME);
  printf("**************************************************\n\r");

  /* Enter Infinite Loop*/
  while (1) {

    /* Read in the current state of the push buttons into button_value */
    button_value = REG_PUSH_BUTTON_IN;

    /* If SW1 is pressed, set sw1_curr_state to     BUTTON_PRESSED
     * If SW1 is not pressed, set sw1_curr_state to BUTTON_RELEASED
     */
    if ((button_value & SW1_MASK) == 0) {
      sw1_curr_state = BUTTON_PRESSED;
    } else {
      sw1_curr_state = BUTTON_RELEASED;
    }

    /* Find the falling edge of SW1 */
    if ((sw1_curr_state == BUTTON_PRESSED) &&
        (sw1_prev_state == BUTTON_RELEASED)) {
      
      /* Increase the duty cycle */

      /* Any duty cycle greater than 100 gets set to 0*/

      printf("Duty Cycle: %d\n\r", duty_cycle);

      /* Stop the PWM peripheral*/

      /* Set the new duty cycle */

      /* Start the PWM peripheral */
    }

    /* Update the button states */
    sw1_prev_state = sw1_curr_state;

    /* delay for 50mS*/
    cyhal_system_delay_ms(50);
  }
}
#endif