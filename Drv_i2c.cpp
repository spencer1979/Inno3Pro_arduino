
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

// 寫入 16-bit 數據
void Inno3Pro_I2C::I2C_Write16(uint8_t slaveAddress, uint8_t dataAddress, uint8_t *dataBuffer, uint8_t buflen)
{
   Wire.beginTransmission(slaveAddress); // 開始傳輸
   Wire.write(dataAddress);             // 發送寄存器位址
   Wire.write(dataBuffer[0]);           // 寫入低位元組
   if (buflen == 3) {                   // 如果 buflen=3，表示有第二個位元組
       Wire.write(dataBuffer[1]);       // 寫入高位元組
   }
   Wire.endTransmission();              // 結束傳輸
   delayMicroseconds(150);             // 傳輸後延遲
}

// 讀取 8-bit 數據
uint8_t Inno3Pro_I2C::I2C_Read8(uint8_t slaveAddress, uint8_t dataAddress) 
{
   Wire.beginTransmission(slaveAddress); // 開始傳輸
   Wire.write(0x80);                    // PI Command Address (設備要求)
   Wire.write(dataAddress);             // 發送寄存器位址
   Wire.write(dataAddress);             // 再次發送寄存器位址 (設備要求)
   Wire.endTransmission(false);         // 重啟條件 (no STOP)

   Wire.requestFrom(slaveAddress, (uint8_t)1); // 請求 1 位元組
   return Wire.read();                  // 直接返回讀取到的數據
}

// 讀取 16-bit 數據
uint16_t Inno3Pro_I2C::I2C_Read16(uint8_t slaveAddress, uint8_t dataAddress) 
{
   Wire.beginTransmission(slaveAddress); // 開始傳輸
   Wire.write(0x80);                    // PI Command Address (設備要求)
   Wire.write(dataAddress);             // 發送寄存器位址
   Wire.write(dataAddress);             // 再次發送寄存器位址 (設備要求)
   Wire.endTransmission(false);         // 重啟條件 (no STOP)

   Wire.requestFrom(slaveAddress, (uint8_t)2); // 請求 2 位元組
   uint8_t u8Lsb = Wire.read();         // 讀取低位元組
   uint8_t u8Msb = Wire.read();         // 讀取高位元組
   return (uint16_t)(u8Msb << 8) | u8Lsb; // 合併並返回
}