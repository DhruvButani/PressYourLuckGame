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

      uint32_t reg_val = REG_PUSH_BUTTON_IN;
      joystick_position_t position = joystick_get_pos();

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


      if((reg_val & SW3_MASK) == 0x00) {
         ECE353_Events.sw3 = 1;
      }
      else {
         ECE353_Events.sw3 = 0;
      }


      if(position != JOYSTICK_POS_CENTER) {
         ECE353_Events.joystick = 1;
      }
      else {
         ECE353_Events.joystick = 0;
      }

 }
#endif
