 /**	
	@file		Drv_i2C.h
	
    @brief 		This is the header file containing the driver APIs for I2C
	
    @author     CS - PIPH Applications
     
    @date 	    August 3, 2018
      
    Copyright (C) 2018 Power Integrations. All rights reserved.

    DISCLAIMER: YOU AGREE AND ACKNOWLEDGE THE SOFTWARE CODE LIBRARIES ARE
    PROVIDED ON AN "AS IS" BASIS AND THAT YOUR USE OR RELIANCE UPON THE SOFTWARE 
    IS AT YOUR OWN RISK AND DISCRETION. POWER INTEGRATIONS HEREBY DISCLAIM ANY 
    AND ALL REPRESENTATIONS, WARRANTIES AND GUARANTIES REGARDING THE SOFTWARE. 
    POWER INTEGRATIONS MAKES NO WARRANTY HEREIN AND SPECIFICALLY DISCLAIMS ALL 
    WARRANTIES INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT 
    TO THIRD PARTIES. FURTHERMORE, POWER INTEGRATIONS MAKES NO WARRANTY THAT 
 
    1) THE SOFTWARE CODE LIBRARIES WILL MEET YOUR REQUIREMENTS 
    2) THE SOFTWARE CODE LIBRARIES WILL BE ACCURATE, RELIBALE, OR ERROR-FREE. 

    DAMAGES DISCLAIMER: POWER INTEGRATIONS, WILL NOT UNDER ANY CIRCUMSTANCES, 
    BE LIABLE TO ANY USER FOR ANY DIRECT, INDIRECT, CONSEQUENTIAL, SPECIAL, 
    PUNITIVE, INCIDENTAL DAMAGES, LOST PROFITS OR LOSS OF BUSINESS, WHETHER 
    FORESEEABLE OR UNFORESEEABLE EVEN IF POWER INTEGRATIONS HAS BEEN ADVISED 
    OF THE POSSIBILITY OF SUCH DAMAGES ARISING OUT OF OR RELATED TO USE OF 
    THIS SOFTWARE CODE LIBRARY.
    
 */
 
#ifndef DRV_I2C_H
#define	DRV_I2C_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

 #include <Wire.h>

// library interface description
class Inno3Pro_I2C
{
  // user-accessible "public" interface
  public:
  
	/**
		@brief
			Handles one i2c master write transaction with the
			supplied parameters.

		@details 
			This Writes 1 to 2 Bytes of data to the Slave Device        
		
		@param
			slaveAddress - The address of the i2c Device to be accessed
						   Uses 7 Bit Address Scheme
						   
		@param
			dataAddress - The Register Address to be accessed
			
		@param
			*dataBuffer - A pointer to the block of data to be sent			
			 
		@param
			buflen - The length of the data block to be sent		
			
		@returns
			None
	*/
	void I2C_Write16(uint8_t slaveAddress, uint8_t dataAddress, uint8_t *dataBuffer, uint8_t buflen);
	
	
	
	/**
		@brief
			Handles one i2c master read transaction with the
			supplied parameters.

		@details 
			This Reads 1  Byte of data from the Slave Device        
		
		@param
			slaveAddress - The address of the i2c Device to be accessed
						   Uses 7 Bit Address Scheme
	 
		@param
			dataAddress - The Register Address to be accessed			
			
		@returns
			1 Byte of Data from the Slave Device
	*/	
	uint8_t I2C_Read8(uint8_t slaveAddress, uint8_t dataAddress) ;
	
	/**
		@brief
			Handles one i2c master read transaction with the
			supplied parameters.

		@details 
			This Reads 2  Bytes of data from the Slave Device        
		
		@param
			slaveAddress - The address of the i2c Device to be accessed
						   Uses 7 Bit Address Scheme
	 
		@param
			dataAddress - The Register Address to be accessed			
			
		@returns
			Merged LSB and MSB  from the Slave Device
			
	*/		
	uint16_t I2C_Read16(uint8_t slaveAddress, uint8_t dataAddress) ;
	

};
#endif	/* DRV_I2C_H */

