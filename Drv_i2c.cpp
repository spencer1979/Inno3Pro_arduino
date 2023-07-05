
 /**	
	@file		Drv_i2C.cpp
	
    @brief 		This is the source file containing the driver APIs for I2C
	
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
 
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
#include "Drv_i2c.h"


void Inno3Pro_I2C::I2C_Write16(uint8_t slaveAddress, uint8_t dataAddress, uint8_t *dataBuffer, uint8_t buflen)
{
    //150us Delay On Every I2C Transaction
    delayMicroseconds(150); 
	Wire.beginTransmission((uint8_t)slaveAddress);

  #if ARDUINO >= 100
	Wire.write((uint8_t)dataAddress); // send address	
	Wire.write((uint8_t)dataBuffer[0]); 
	if(buflen == 3)
	{
		Wire.write((uint8_t)dataBuffer[1]);  
	}
  #else
	Wire.send((uint8_t)dataAddress); // send address	
	Wire.send((uint8_t)dataBuffer[0]); 
	if(buflen == 3)
	{
		Wire.send((uint8_t)dataBuffer[1]);  
	}
  #endif
  
  Wire.endTransmission();
}




uint8_t Inno3Pro_I2C::I2C_Read8(uint8_t slaveAddress, uint8_t dataAddress) 
{
  //150us Delay On Every I2C Transaction
   delayMicroseconds(150); 	
  uint8_t ret;

 Wire.beginTransmission(slaveAddress); // start transmission to device 
 
#if (ARDUINO >= 100)
  Wire.write(0x80); 			// PI Command Address
  Wire.write(dataAddress); 		// sends register address to read from
  Wire.write(dataAddress); 		// sends register address to read from  
#else
  Wire.write(0x80); 			// PI Command Address
  Wire.send(dataAddress); 		// sends register address to read from
  Wire.send(dataAddress); 		// sends register address to read from  
#endif
  Wire.endTransmission(); 		// end transmission
  
  
  Wire.beginTransmission(slaveAddress); // start transmission to device 
  Wire.requestFrom(slaveAddress, (uint8_t)0x01);	// send data n-bytes read
  
#if (ARDUINO >= 100)
  ret = Wire.read(); 		// receive DATA
#else
  ret = Wire.receive(); 	// receive DATA
#endif
  Wire.endTransmission(); 	// end transmission

  return ret;
}




uint16_t Inno3Pro_I2C::I2C_Read16(uint8_t slaveAddress, uint8_t dataAddress) 
{
    //150us Delay On Every I2C Transaction
	delayMicroseconds(150); 
    uint8_t u8Lsb;                //Storage Variable for LSB Reading
    uint8_t u8Msb;                //Storage Variable for MSB Reading

 Wire.beginTransmission(slaveAddress); // start transmission to device 
 
#if (ARDUINO >= 100)
  Wire.write(0x80); 			// PI Command Address
  Wire.write(dataAddress); 		// sends register address to read from
  Wire.write(dataAddress); 		// sends register address to read from  
#else
  Wire.send(0x80); 				// PI Command Address
  Wire.send(dataAddress); 		// sends register address to read from
  Wire.send(dataAddress); 		// sends register address to read from  
#endif
  Wire.endTransmission(); 		// end transmission
  
  //150us Delay On Every I2C Transaction
  delayMicroseconds(150); 
  
  Wire.beginTransmission(slaveAddress); // start transmission to device 
  Wire.requestFrom(slaveAddress,(uint8_t)0x02);	// send data n-bytes read
  
  
#if (ARDUINO >= 100)
    //Example  5V,  Returns F4 
    u8Lsb =  Wire.read(); 		// receive DATA
   
    //Example  5V,  Returns 01
    u8Msb =  Wire.read();        // receive DATA 

#else
   //Example  5V,  Returns F4 
    u8Lsb =  Wire.receive(); 		// receive DATA
   
    //Example  5V,  Returns 01
    u8Msb = Wire.receive();        // receive DATA 
    
  
#endif
  
	//Wire.endTransmission(); 		// end transmission
    //Returns 01F4    
    return ((u8Msb<<8)|(u8Lsb));   
}

