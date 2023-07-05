/**
	InnoSwitch3-Pro Example Application

	Company:    Power Integrations

	Summary:    This is to demonstrate the Inno3-Pro Arduino Library
				Upon Upload initial voltage is set to 5V, then a random
				time will be gerated from 1sec to 10sec. This random time
				will dictate how fast the random voltage (3V to 20V) 
				will be generated. This is robust way to test the extreme
				capabilities of voltage updates.
			  
    Author  :   CS - PIPH Applications   
	
    Date    :   August 3, 2018
   
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


//Step  1  :  Add the Header Files
#include <Drv_Rtc.h>
#include <Drv_i2c.h>
#include <Inno3Pro.h>
#include <Config.h>

//Function Prototype
int rand(void);
float RandomFloat(const float min, const float max);
int16_t RandomInt(const int16_t min, const int16_t max);

//Step  2  :  Create the class instance
Inno3Pro_Rtc Inno3ProClk;
Inno3Pro_Application Inno3ProApp;



//Step 3 :  Write Initial Commands to Inno Pro
void setup() 
{
	Inno3ProApp.Inno3Pro_Initialization(); 
}



//Step 4 :  Call the Functions on the Main Loop     
void loop()
{
     
        // Main Loop Variables
        static uint16_t u16_Main_State = 0;                 //Main State Counter                                  
        static uint16_t u16_Request_Timer = 0;              //Initialize Request Timer 
        static uint16_t u16_Request_Timer_Delay = 3000;     //Initialize Request Timer Delay
        
        static float fRandomCV = 5;  
                    
    
        Inno3ProApp.Inno3Pro_Write_VI                (fRandomCV,6);          
        Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp   (300);           
        Inno3ProApp.Inno3Pro_Write_Volt_Peak         (7);             
        Inno3ProApp.Inno3Pro_Vbus_Switch_Control     (1);  
        
        //Timer Routine For Automatic Activation of  Requests
        if(Inno3ProClk.clock_HasTimeElapsedMs(u16_Request_Timer,u16_Request_Timer_Delay))     //Random Time Delay
        {                                 
            u16_Request_Timer = Inno3ProClk.clock_GetTimeStampMs();     //Reset Timer  
            fRandomCV = RandomFloat(3,20);                              //3V to 20V Random Number Generation
            u16_Request_Timer_Delay = RandomInt(1000,10000);            //1sec to 10sec Random Time
        }                                            
             

  }   
  
 float RandomFloat(const float min, const float max)
{
    if (max == min)
    {
        return min;
    }
    else if (min < max)
    {
        return (max - min) * ((float)rand() / 32767) + min;
    }
    // return 0 if min > max
    return 0;
}

int16_t RandomInt(const int16_t min, const int16_t max)
{
    return (rand()%(max-min) + min);
}
