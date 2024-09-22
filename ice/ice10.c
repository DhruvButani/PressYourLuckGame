/**
 * @file ice07.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE10)

#define ICE_BUFFER_SIZE 8

char APP_DESCRIPTION[] = "ECE353: ICE 10 - Circular Buffers";
typedef enum
{
    CB_SUCCESS,
    CB_ERROR_ADD_FAILED,
    CB_ERROR_REMOVE_FAILED,
    CB_ERROR_VALUE_MISMATCH,
    CB_ERROR_BUFFER_OVERFLOW,
    CB_ERROR_BUFFER_UNDERFLOW,
    CB_ERROR_BUFFER_NOT_FULL,
    CB_ERROR_BUFFER_NOT_EMPTY
} Circular_Buffer_Status;

const char *CB_MESSAGES[] = {
    "\033[0;32mSUCCESS:\033[0m Circular Buffer passed validation test",
    "\033[0;31mERROR  :\033[0m Failed to add data to circular buffer",
    "\033[0;31mERROR  :\033[0m Failed to remove data from circular buffer",
    "\033[0;31mERROR  :\033[0m Value returned from circular buffer is incorrect",
    "\033[0;31mERROR  :\033[0m Added data to a full circular buffer",
    "\033[0;31mERROR  :\033[0m Removed data from an empty circular buffer",
    "\033[0;31mERROR  :\033[0m Circular buffer should be full",
    "\033[0;31mERROR  :\033[0m Circular buffer should be empty",
};


/*****************************************************************************/
/*  Function Declarations                                                    */
/*****************************************************************************/
Circular_Buffer_Status test_circular_buffer(Circular_Buffer *buffer, char *values, uint16_t buf_size, uint8_t test_number);

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
cyhal_trng_t trng_obj;

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    char *values;
    Circular_Buffer *ice_buffer;
    Circular_Buffer_Status status = CB_SUCCESS;

     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");


    printf("Allocating space for random values\n\r");
    values = malloc(ICE_BUFFER_SIZE);

    printf("Initializing Circular Buffer\n\r\n\r");
    ice_buffer = circular_buffer_init(ICE_BUFFER_SIZE);

    status = test_circular_buffer(ice_buffer, values, ICE_BUFFER_SIZE, 1);
    printf("%s\n\r", CB_MESSAGES[status]);

    if (status != CB_SUCCESS)
    {
        /* Halt the program*/
        while (1)
        {
        };
    }

    status = test_circular_buffer(ice_buffer, values, ICE_BUFFER_SIZE, 2);
    printf("%s\n\r", CB_MESSAGES[status]);

    if (status != CB_SUCCESS)
    {
        /* Halt the program*/
        while (1)
        {
        };
    }

    printf("\n\rDeleting circular buffer\n\r");
    circular_buffer_delete(ice_buffer);

    printf("Return memory for random numbers to the heap\n\r");
    free(values);

    while (1)
    {
    };
}

/**
 * @brief
 *
 * @param buffer
 *  A pointer to a circular buffer object
 * @param values
 *  A pointer to an array of numbers that will be added to the circular buffer
 * @param buf_size
 *  The size of the circular buffer AND values
 * @param test_number
 *  Used to print out a debug message
 * @return true
 *  The circular buffer implementation passed
 * @return false
 *  The circular buffer implementation failed
 */
Circular_Buffer_Status test_circular_buffer(Circular_Buffer *buffer, char *values, uint16_t buf_size, uint8_t test_number)
{
    uint16_t i;

    printf("\n\rStarting Test Run %d\n\r", test_number);

    /* Generate Random Number */
    for (i = 0; i < buf_size; i++)
    {
        values[i] = cyhal_trng_generate(&trng_obj);
    }

    /* ADD CODE In a for loop, fill the circular buffer with the values found in 'values'
     * If any of the values cannot be added, return CB_ERROR_ADD_FAILED
     */

    /* ADD CODE verify that the circular buffer is full.  If the circular buffer does not
     * indicate that it is full, return CB_ERROR_BUFFER_NOT_FULL.
     */

    /* ADD CODE Return CB_ERROR_BUFFER_OVERFLOW if you are able to add a value to the circular
     * buffer when it is full
     */

    /* ADD CODE in a for loop, empty the circular buffer.  Verify that each value returned
     * from the circular buffer matches the value found in 'values[i]'.  If any of the values
     * returned from the circular buffer do not match the corresponding value is 'values',
     * return CB_ERROR_VALUE_MISMATCH
     */

    /* ADD CODE Return CB_ERROR_BUFFER_NOT_EMPTY false if the circular buffer is not empty */

    /* ADD CODE Return CB_ERROR_BUFFER_UNDERFLOW if you are able to remove a value to a
     * circular buffer that is empty
     */

    return CB_SUCCESS;
}

#endif