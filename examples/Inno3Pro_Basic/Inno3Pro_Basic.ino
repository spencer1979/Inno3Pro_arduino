/**
	InnoSwitch3-Pro Example Application

	Company:    Power Integrations

	Summary:    This is to demonstrate the Basic usage of Inno3-Pro Arduino Library          
              
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
Inno3Pro_Application Inno3ProApp;

//Step 3 :  Write Initial Commands to Inno Pro
void setup() 
{
	Inno3ProApp.Inno3Pro_Initialization(); 
}

//Step 4 :  Call the Functions on the Main Loop 
void loop()
{
      //Control Functions Set-Up
      
      // 5V, 5.1A , Voltage and Constant Current
      Inno3ProApp.Inno3Pro_Write_VI(5 , 5.1);   

      // 300mV    , Cable Drop Compesation  
      Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300); 

      // 7V       , Constant Output Power Knee Voltage
      Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);  

      // ON       , Vbus Enable
      Inno3ProApp.Inno3Pro_Vbus_Switch_Control(1);                    
}