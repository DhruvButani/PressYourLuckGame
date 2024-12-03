/**
 * @file task_game_control.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_game_control.h"
#include "portmacro.h"
#include "task_io_expander.h"

#if defined(HW05)

#define DEFAULT_RANDOM_DELAY 1500
#define DEFAULT_ACTIVE_DELAY 400

#include "main.h"
#include "press-your-luck/pyl.h"
#include "press-your-luck/tasks/task_console.h"
#include "press-your-luck/tasks/task_eeprom.h"
#include "press-your-luck/tasks/ece353_tasks.h"

#include "press-your-luck/tasks/task_lcd_squares.h"
#include "press-your-luck/tasks/task_lcd_game_info.h"
#include "press-your-luck/tasks/task_remote_tx.h"

extern cyhal_trng_t trng_obj;

char STUDENTS[] = "Dhruv Butani, Thomas Hearn";
char TEAM[] = "Team28";


/* Event Groups */
extern EventGroupHandle_t eg_UI;

/* Semaphores */
extern SemaphoreHandle_t s_LCD;

/* Queues */
TaskHandle_t Task_Handle_Game_Control;
TimerHandle_t Timer_Handle_Randomize;
TimerHandle_t Timer_Handle_Active_Square;
QueueHandle_t q_Control_Rx_Data;
QueueHandle_t q_Control_EEPROM_Rx;

void timer_randomize_callback(TimerHandle_t xTimer)
{
  /* Set the  in the event group */
  xEventGroupSetBits(eg_UI, EVENT_TMR_RAND_SQUARES);
}

void timer_active_callback(TimerHandle_t xTimer)
{
  /* Set the  in the event group */
  xEventGroupSetBits(eg_UI, EVENT_TMR_RAND_ACTIVE);
}

/******************************************************************************/
/******************************************************************************/

void task_game_control(void *param)
{
  EventBits_t active_events;
  game_info_msg_t local_stats= {.cmd = CMD_UPDATE_LOCAL_DATA, .score = 1000, .spins = 1, .passed = 2};
  game_info_msg_t remote_stats= {.cmd = CMD_UPDATE_REMOTE_DATA, .score = 0, .spins = 0, .passed = 0};
  uint8_t num_whammies = 0;
  uint16_t hi_score_write = 0;
  uint16_t hi_score_read = 0;

  image_t *pyl_images = pvPortMalloc(14*sizeof(image_t));



  /* Suppress warning for unused parameter */
  (void)param;

    /* Send the Clear Screen Escape Sequence*/
    task_print("\x1b[2J\x1b[;H");
    task_print("**************************************************\n\r");
    task_print("* %s\n\r", APP_DESCRIPTION);
    task_print("* Date: %s\n\r", __DATE__);
    task_print("* Time: %s\n\r", __TIME__);
    task_print("* Team:%s\n\r", TEAM);
    task_print("* Students:%s\n\r", STUDENTS);
    task_print("**************************************************\n\r");

    /* Start the random image timer */
    xTimerStart(Timer_Handle_Randomize, portMAX_DELAY);

    /* Start the Random Square Timer*/
    xTimerStart(Timer_Handle_Active_Square, portMAX_DELAY);

  /* Repeatedly running part of the task */

  for (;;)
  {

    /* Clear events that may have occurred when not in the Active state */
    xEventGroupClearBits(eg_UI, 0xFFFFFF);

    xEventGroupSetBits(eg_UI, EVENT_START_GAME);


    /* Draw empty squares */
    for (int i = 0; i < 14; i++) {
        pyl_images[i].square_id = i;
        pyl_images[i].reset = true;
        xQueueSend(q_LCD_SQUARES, &pyl_images[i], portMAX_DELAY);
    }
   

    while (1)
    {
      /* Wait for the user to press SW1 or move move attempt to move the board */
      active_events = xEventGroupWaitBits(
          eg_UI,
          EVENT_UI_SW1 | 
          EVENT_UI_SW2 | 
          EVENT_UI_SW3 | 
          EVENT_TMR_RAND_SQUARES | 
          EVENT_TMR_RAND_ACTIVE |
          EVENT_IPC_RX_DATA |
          EVENT_START_GAME , 
          true,  /* Clear Events on Return*/
          false, /* Any Event Wakes up task*/
          portMAX_DELAY);

      /* Check to see which event is active */
      if( (active_events & EVENT_UI_SW1) == EVENT_UI_SW1)
      {
        task_print_info("SW1 Pressed");

        task_print_info("Update Local Stats");
        
        /* Increment all fields in the the local_stats by 1 */
        local_stats.score += 1;
        local_stats.spins += 1;
        local_stats.passed +=1;


        /* Update LCD with local stats */ 
        xQueueSend(q_LCD_Info, &local_stats, portMAX_DELAY);
    

        /* Send the local stats to the remote user */
        xQueueSend(q_Remote_Tx, &local_stats, portMAX_DELAY);
      }

      else if( (active_events & EVENT_UI_SW2) == EVENT_UI_SW2)
      {
        task_print_info("SW2 Pressed");


        /* Randomize the game board */
        pyl_images_randomize(pyl_images);
        
        //Activate task to draw board
        for (int i = 0; i < 14; i++) {
          pyl_images[i].square_id = i;
          pyl_images[i].reset = false;
          xQueueSend(q_LCD_SQUARES, &pyl_images[i], portMAX_DELAY);
        }
        
      }

      else if( (active_events & EVENT_UI_SW3) == EVENT_UI_SW3)
      {
        task_print_info("SW3 Pressed");

        //Increment whammies count
        num_whammies++;
        hi_score_write =  (uint16_t) cyhal_trng_generate(&trng_obj);


        /* Write the number of whammies to the IO Expander */
        xQueueSend(q_IO_Exp, &num_whammies, portMAX_DELAY);


        /* Write a random high score to the eeprom */ 
        eeprom_msg_t eepromSendWrite = {
          .operation = EEPROM_WRITE,
          .score = hi_score_write,
          .return_queue = q_Control_EEPROM_Rx
        };
        xQueueSend(q_EEPROM, &eepromSendWrite, portMAX_DELAY);


        /* Read the high score back*/ 
        eeprom_msg_t eepromSendRead = {
          .operation = EEPROM_READ,
          .score = hi_score_write,
          .return_queue = q_Control_EEPROM_Rx
        };
        xQueueSend(q_EEPROM, &eepromSendRead, portMAX_DELAY);

        eeprom_msg_t eepromRecieve;
        xQueueReceive(q_Control_EEPROM_Rx, &eepromRecieve, portMAX_DELAY);

        hi_score_read = eepromRecieve.score;

        /* Read the high score from the eeprom and verify its value */ 
        if(hi_score_write == hi_score_read)
        {
          task_print_info("EEPROM read/write verified");
        }
        else {
          task_print_info("EEPROM read/write failed");
        }

      }
      else if( (active_events & EVENT_IPC_RX_DATA) == EVENT_IPC_RX_DATA)
      {

        task_print_info("Revived Remote Packet");

        /* Receive Remote Data from Queue*/
        game_info_msg_t temp;
        xQueueReceive(q_Control_Rx_Data, &temp, portMAX_DELAY);
        remote_stats.score = temp.score;
        remote_stats.spins = temp.spins;
        remote_stats.passed = temp.passed;


        /* Display the local stats */
        xQueueSend(q_LCD_Info, &remote_stats, portMAX_DELAY);


      }
    }
  }
}

void task_game_control_init(void)
{
  q_Control_Rx_Data = xQueueCreate(1, sizeof(game_info_msg_t));
  q_Control_EEPROM_Rx = xQueueCreate(1, sizeof(eeprom_msg_t));

  /* Create a timer for randomizing the image */
  Timer_Handle_Randomize = xTimerCreate(
      "Randomize",
      DEFAULT_RANDOM_DELAY,
      true, (void *)0,
      timer_randomize_callback);

  /* Create a timer for randomizing the position of
     the active square */
  Timer_Handle_Active_Square = xTimerCreate(
      "Active Square",
      DEFAULT_ACTIVE_DELAY,
      true,
      (void *)0,
      timer_active_callback);

  xTaskCreate(
      task_game_control,
      "Task Game Control",
      10 * configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_Game_Control);
}

#endif
