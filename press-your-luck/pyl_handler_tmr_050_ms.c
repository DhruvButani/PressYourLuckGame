/**
 * @file pyl_handler_tmr_050_ms.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 
 #include "pyl.h"
 #include "pyl_handler_tmr_050_ms.h"

 #if defined(HW02) || defined (HW03) || defined (HW04)

 void handler_timer_050_ms(void *callback_arg, cyhal_timer_event_t event)
 {
   /*
   Detect the falling edge of SW1, SW2, and SW3 and set the corresponding bit-field in ECE353_Events
   Detect the when the joystick has been moved from the center position, set the value of Joystick_Pos, and set the corresponding bit-field in ECE353_Events
   */

      uint32_t reg_val = REG_PUSH_BUTTON_IN;

      if((reg_val & SW1_MASK) == 0x00) {
         ECE353_Events.sw1 = 1;
      }
      else {
         ECE353_Events.sw1 = 0;
      }


      if((reg_val & SW2_MASK) == 0x00) {
         ECE353_Events.sw2 = 1;
      }
      else{
         ECE353_Events.sw2 = 0;
      }



   //joystick info




    
 }
#endif
