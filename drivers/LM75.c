/**
 * @file LM75.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "i2c.h"
#include "LM75.h"

/** Read a register on the LM75AIMME/NOPB
 *
 * @param reg The reg address to read
 *
 */
static int16_t LM75_read_reg(uint8_t reg)
{
	int16_t return_value = 0;
    cy_rslt_t rslt = CY_RSLT_SUCCESS;


	/* Use cyhal_i2c_master_write to write the required data to the device. 
	 * Send the register address and then generate a stop condition 
	 */
	
	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* If the write failed, halt the CPU */

	/* Use cyhal_i2c_master_read to read the required data from the device. 
	 * The register address has already been set in the write above, so read two bytes
	 * of data.
	 */
	
	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* If the read failed, halt the CPU */

	/* Return an 16-bit signed number that represents the temp. */
	
	return return_value;
}

/** Read the value of the input port
 *
 * @param reg The reg address to read
 *
 */
float LM75_get_temp(void)
{
	int16_t raw_value = LM75_read_reg(LM75_TEMP_REG);
	float temp = (double)raw_value / 2;
	return temp;
}
