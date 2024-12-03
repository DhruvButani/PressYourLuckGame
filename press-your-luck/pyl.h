/**
 * @file pyl.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __PYL_H__
#define __PYL_H__

#include "cyhal.h"
#include "pyl_images.h"

/*****************************************************************************/
/* Software Events */
/*****************************************************************************/
#define EVENT_UI_SW1                (1 << 0)
#define EVENT_UI_SW2                (1 << 1)
#define EVENT_UI_SW3                (1 << 2)
#define EVENT_TMR_RAND_SQUARES      (1 << 3)
#define EVENT_TMR_RAND_ACTIVE       (1 << 4)
#define EVENT_IPC_RX_DATA           (1 << 5)
#define EVENT_START_GAME            (1 << 6)

/*****************************************************************************/
/* Remote UART Packet Start/Stop bytes */
/*****************************************************************************/
#define REMOTE_PACKET_START         0xA0    /* Start of a 4-byte transaction */
#define REMOTE_PACKET_END           0xA1    /* End of a 4-byte transaction */

/*****************************************************************************/
/* Game Information Commands  */
/*****************************************************************************/

/*****************************************************************************/
/* Information used to display the location of information on the screen     */
/*****************************************************************************/
#define LOCATION_LOCAL_SCORE_X          120
#define LOCATION_LOCAL_SCORE_Y          75 
#define LOCATION_REMOTE_SCORE_X         120
#define LOCATION_REMOTE_SCORE_Y         100 

#define LOCATION_LOCAL_SPINS_X          80 
#define LOCATION_LOCAL_SPINS_Y          130 
#define LOCATION_REMOTE_SPINS_X         80 
#define LOCATION_REMOTE_SPINS_Y         155 

#define LOCATION_LOCAL_PASSED_X         225 
#define LOCATION_LOCAL_PASSED_Y         130 
#define LOCATION_REMOTE_PASSED_X        225 
#define LOCATION_REMOTE_PASSED_Y        155 

#define COLOR_LOCAL_SCORE               LCD_COLOR_WHITE
#define COLOR_LOCAL_SPINS               LCD_COLOR_WHITE
#define COLOR_LOCAL_PASSED              LCD_COLOR_WHITE

#define COLOR_REMOTE_SCORE              LCD_COLOR_GRAY
#define COLOR_REMOTE_SPINS              LCD_COLOR_GRAY
#define COLOR_REMOTE_PASSED             LCD_COLOR_GRAY

/******************************************************************************
 * The game is allowed to be in one of the following states
 *****************************************************************************/
typedef enum control_state_t
{
    STATE_START,
    STATE_WAITING,
    STATE_ACTIVE_PLAYER,
    STATE_PASSIVE_PLAYER,
    STATE_GAME_OVER,
} control_state_t;

/******************************************************************************
 * Data structure used to transmit a variable number of bytes to a remote 
 * board 
 *****************************************************************************/
typedef struct remote_uart_data_t
{
    uint8_t num_bytes;
    uint8_t payload[10];
} remote_uart_data_t;

/******************************************************************************
 * Supported commands that the FSM can use to determine what action to take 
 *****************************************************************************/
typedef enum game_info_cmd_t
{
    CMD_UPDATE_LOCAL_DATA   =   0xB0,    /* Update Local Data (score, spins, passed) */
    CMD_UPDATE_REMOTE_DATA  =   0xB1,    /* Update Remote Data (score, spins, passed) */
    CMD_PASS_SPINS          =   0xB3,    /* Pass the Active Player Token to the other board */
    CMD_GAME_OVER           =   0xB4,    /* Indicate the game is over */
    CMD_RESTART             =   0xB5,    /* Restart the game */
} game_info_cmd_t;

/******************************************************************************
 * Supported commands that the FSM can use to determine what action to take 
 *****************************************************************************/
typedef struct game_info_msg_t
{
    game_info_cmd_t cmd;
    uint16_t        score; 
    uint8_t         spins; 
    uint8_t         passed; 
} game_info_msg_t;

/* Global variables used for HW01 */
extern cyhal_trng_t trng_obj;
extern char STUDENTS[];

/******************************************************************************
 * Public functions in pyl.c that can be called from other files 
 *****************************************************************************/
void pyl_draw_square(uint8_t square_id);
void pyl_draw_image(image_t *image);
void pyl_images_randomize(image_t *images);



#endif
