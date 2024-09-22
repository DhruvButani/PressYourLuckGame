/**
 * @file ice04.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE04)

char APP_DESCRIPTION[] = "ECE353: ICE 04 - LCD";

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the LCD Screen */
    ece353_enable_lcd();
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    // Turn LCD On
    lcd_draw_image(
        160,
        120,
        wisconsinWidthPixels,
        wisconsinHeightPixels,
        wisconsinBitmaps,
        LCD_COLOR_RED,
        LCD_COLOR_BLACK);

    for (;;)
    {
    }
}
#endif