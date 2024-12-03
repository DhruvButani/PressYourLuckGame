/**
 * @file task_sw.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "task_sw.h"

#if defined(HW05) || defined(HW06)
#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/**
 * @brief
 * Function used to detect when SW1, SW2, and SW3 are been pressed.  
 * The task should detect the initial button press by debouncing 
 * the push button for 50mS.  Pressing the button for longer than 50mS 
 * should only result in a single button event.
 * 
 * @param param
 *  Unused
 */
void task_switches(void *param)
{
  bool sw1_pressed;
  bool sw2_pressed;
  bool sw3_pressed;


  bool sw1_prev_pressed = false;
  bool sw2_prev_pressed = false;
  bool sw3_prev_pressed = false;

  // Monitor the push buttons/keep track of the previous state
  while (1)
  {
    if((REG_PUSH_BUTTON_IN & SW1_MASK) == 0x00) {
      sw1_pressed = true;
    }
    else {
      sw1_pressed = false;
    }

    if((REG_PUSH_BUTTON_IN & SW2_MASK) == 0x00) {
      sw2_pressed = true;
    }
    else {
      sw2_pressed = false;
    }
    if((REG_PUSH_BUTTON_IN & SW3_MASK) == 0x00) {
      sw3_pressed = true;
    }
    else {
      sw3_pressed = false;
    }

    // Detect falling edge for SW1,SW2,SW3

    if(sw1_prev_pressed && !sw1_pressed)  
    {
      xEventGroupSetBits(eg_UI, EVENT_UI_SW1);
    }
    if(sw2_prev_pressed && !sw2_pressed)  
    {
      xEventGroupSetBits(eg_UI, EVENT_UI_SW2);
    }
    if(sw3_prev_pressed && !sw3_pressed)  
    {
      xEventGroupSetBits(eg_UI, EVENT_UI_SW3);
    }

    sw1_prev_pressed = sw1_pressed;
    sw2_prev_pressed = sw2_pressed;
    sw3_prev_pressed = sw3_pressed;

    // Delay for 50mS
    vTaskDelay(50);    

  }
}

/**
 * @brief
 * Initializes User Push Buttons and creates the corresponding FreeRTOS tasks for SW1 and SW2
 */
void task_sw_init(void)
{
  push_buttons_init(false);

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_switches,
      "Task Switches",
      configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_INPUT,
      NULL);
}

#endif
