/**
	InnoSwitch3-Pro Example Application

	Company:    Power Integrations

	Summary:    This is to demonstrate the Inno3-Pro Arduino Library
				Upon Upload initial voltage is set to 5V, then every 5 Seconds
				the voltage state will change (5V , 8V, 15V, 20V) And then Process Repeats.
              
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
		static uint16_t u16_Main_State = 0;                 	//Initialize Main State
		static uint16_t u16_Request_Timer = 0;           	  	//Initialize Request Timer  



		//Timer Routine For Automatic Activation of  Requests
		if(Inno3ProClk.clock_HasTimeElapsedMs(u16_Request_Timer,5000)) 		//Delay Time
		{
    
		  u16_Main_State++; 												//Change State	
      
		  u16_Request_Timer = Inno3ProClk.clock_GetTimeStampMs();			//Reset Timer
		}



		// Main Loop States
		switch(u16_Main_State)
		{
			
			case 0:   
					  u16_Main_State = 1;  
					                                                                                
					  break;
			  
			
			case 1:   //Activate 5V Configuration                 
					  Inno3ProApp.Inno3Pro_Write_VI(5,5.1);          		// CV = 5V and CC = 5.1A
					  Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);      // CDC  = 300mV    
					  Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);             	// VKP  = 7V
					  Inno3ProApp.Inno3Pro_Vbus_Switch_Control(1);          // VBEN = ON          
					  break;

		  case 2: 	  //Activate 8V Configuration
					  Inno3ProApp.Inno3Pro_Write_VI(8,5.1);                  
					  Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);    
					  Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);                   
					  break;
		  
		  case 3:	  //Activate 15V Configuration
					  Inno3ProApp.Inno3Pro_Write_VI(15,2,76);                  
					  Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);     
					  Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);                       
					  break;                   

		  case 4:     //Activate 20V Configuration
					  Inno3ProApp.Inno3Pro_Write_VI(20,2.1);                  
					  Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);     
					  Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);                       
					  break;    
                                  
		  default:   
					  u16_Main_State = 1;                       
					  break;  
		}
              
 
}