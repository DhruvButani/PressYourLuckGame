/**
 * @file eeprom.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-10-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "eeprom.h"

/** Initializes the IO pins used to control the CS of the
 *  EEPROM
 *
 * @param
 *
 */
void eeprom_cs_init(void)
{
   	cy_rslt_t rslt = CY_RSLT_SUCCESS;

	/* ADD CODE */
	/* Initialize EEPROM Chip Select IO pins as an output*/

	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if init fails*/
}

/** Determine if the EEPROM is busy writing the last
 *  transaction to non-volatile storage
 *
 * @param
 *
 */
void eeprom_wait_for_write(void)
{
	/* ADD CODE */
	//uint8_t transmit_data[?] 	= {?, ?, ?, ....};
	//uint8_t receive_data[?] 	= {?, ?, ?, ....};
   	cy_rslt_t rslt = CY_RSLT_SUCCESS;

	// Check to see if the eeprom is still updating
	// the data from the last write
	do
	{
		/* ADD CODE */
		/* Set the CS Low */

		// Starts a data transfer

		CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

		// Set the CS High

		// If the address was not ACKed, try again.
	} while (1 /* Check the data returned from the EEPROM */);
}

/** Enables Writes to the EEPROM
 *
 * @param
 *
 */
void eeprom_write_enable(void)
{
	/* ADD CODE */
	//uint8_t transmit_data[?] 	= {?, ?, ?, ....};
	//uint8_t receive_data[?] 	= {?, ?, ?, ....};
   	cy_rslt_t rslt = CY_RSLT_SUCCESS;

	// Set the CS Low

	// Starts a data transfer

	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High
}

/** Disable Writes to the EEPROM
 *
 * @param
 *
 */
void eeprom_write_disable(void)
{
	/* ADD CODE */
	//uint8_t transmit_data[?] 	= {?, ?, ?, ....};
	//uint8_t receive_data[?] 	= {?, ?, ?, ....};
   	cy_rslt_t rslt = CY_RSLT_SUCCESS;

	// Set the CS Low

	// Starts a data transfer

	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High
}

/** Writes a single byte to the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 * @param data    -- value to write into memory
 *
 */
void eeprom_write_byte(uint16_t address, uint8_t data)
{
	/* ADD CODE */
	//uint8_t transmit_data[?] 	= {?, ?, ?, ....};
	//uint8_t receive_data[?] 	= {?, ?, ?, ....};
   	cy_rslt_t rslt = CY_RSLT_SUCCESS;


	// Wait for any outstanding writes to complete
	eeprom_wait_for_write();

	// Enable writes to the eeprom
	eeprom_write_enable();

	// Set the CS Low

	// Starts a data transfer

	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High

	// Disable writes to the eeprom
	eeprom_write_disable();
}

/** Reads a single byte to the specified address
 *
 * @param address -- 16 bit address in the EEPROM
 *
 */
uint8_t eeprom_read_byte(uint16_t address)
{
	/* ADD CODE */
	//uint8_t transmit_data[?] 	= {?, ?, ?, ....};
	//uint8_t receive_data[?] 	= {?, ?, ?, ....};
    cy_rslt_t rslt = CY_RSLT_SUCCESS;


	// Wait for any outstanding writes to complete
	eeprom_wait_for_write();

	// Enable writes to the eeprom
	eeprom_write_enable();

	// Set the CS Low
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 0);

	// Starts a data transfer

	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 1);

	// Disable writes to the eeprom
	eeprom_write_disable();

	// Return the value from the EEPROM to the user
}