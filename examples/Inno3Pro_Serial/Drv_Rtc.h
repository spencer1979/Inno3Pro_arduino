/**	
	@file		Drv_Rtc.h
	
    @brief 		This is the header file containing the driver APIs 
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

#ifndef DRV_RTC_H
#define	DRV_RTC_H


#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Inno3Pro_Rtc{
 public:


 
	/**
		@brief
			Get the current timestamp in mSec

		@param
			None
	 
		@returns
			Current timestamp in milli Seconds
	*/
	uint16_t clock_GetTimeStampMs(void);
	

	
	
	/**
		@brief
			Used for Generating milli Seconds delay
			
		@param
			u16TimeStamp - milli second time stamp variable
			
		@param
			u16TimeDurationCheck - Duration to compare against the TimeStamp
			
		@returns
			TRUE after Delay Time has Elapsed
	*/
	bool clock_HasTimeElapsedMs(uint16_t u16TimeStamp, uint16_t u16TimeDurationCheck);

	
	/**
		@brief
			Get the current timestamp in uSec

		@param
			None
	 
		@returns
			Current timestamp in micro Seconds
	*/
	uint16_t clock_GetTimeStampUs(void);
	

	
	
	/**
		@brief
			Used for Generating micro Seconds delay
			
		@param
			u16TimeStamp - micro second time stamp variable
			
		@param
			u16TimeDurationCheck - Duration to compare against the TimeStamp
			
		@returns
			TRUE after Delay Time has Elapsed
	*/
	bool clock_HasTimeElapsedUs(uint16_t u16TimeStamp, uint16_t u16TimeDurationCheck);

		
	
 private:
 
 
	/** Clock Variables*/
	uint16_t 	u16ClockMSec = 0;

	
	
	/**
		@brief
			Used for calculating the elapsed time in milli seconds
			
		@param
			u16TimeStamp - milli second time stamp variable
			
		@returns
			Returns the Time that have elapsed since u16TimeStamp
	*/	
	uint16_t clock_GetElapsedTimeMs(uint16_t u16TimeStamp);
	
	
	
	/**
		@brief
			Used for calculating the elapsed time in micro seconds
			
		@param
			u16TimeStamp - micro second time stamp variable
			
		@returns
			Returns the Time that have elapsed since u16TimeStamp
	*/	
	uint16_t clock_GetElapsedTimeUs(uint16_t u16TimeStamp);	
};

#endif /* Drv_Rtc_h */







