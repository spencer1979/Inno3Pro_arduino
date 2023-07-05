/**	
	@file		Drv_Rtc.cpp
	
    @brief 		This is the source file containing the driver APIs 
                for Clock Signals.	

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
 
#include "Drv_Rtc.h"


uint16_t Inno3Pro_Rtc::clock_GetElapsedTimeMs(uint16_t u16TimeStamp)
{
	return(millis() - u16TimeStamp);
}


uint16_t Inno3Pro_Rtc::clock_GetTimeStampMs(void)
{
	return(millis());
}


bool Inno3Pro_Rtc::clock_HasTimeElapsedMs(uint16_t u16TimeStamp, uint16_t u16TimeDurationCheck)
{
	if(clock_GetElapsedTimeMs(u16TimeStamp) >= u16TimeDurationCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint16_t Inno3Pro_Rtc::clock_GetElapsedTimeUs(uint16_t u16TimeStamp)
{
	return(micros() - u16TimeStamp);
}


uint16_t Inno3Pro_Rtc::clock_GetTimeStampUs(void)
{
	return(micros());
}


bool Inno3Pro_Rtc::clock_HasTimeElapsedUs(uint16_t u16TimeStamp, uint16_t u16TimeDurationCheck)
{
	if(clock_GetElapsedTimeUs(u16TimeStamp) >= u16TimeDurationCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}