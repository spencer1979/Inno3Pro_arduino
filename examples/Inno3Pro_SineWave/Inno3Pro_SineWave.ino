/**
	InnoSwitch3-Pro Example Application

	Company:    Power Integrations

	Summary:    This demonstration sine wave patterns on Output Voltage 
        
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
#include <Wire.h>


//Step  2  :  Create the class instance
Inno3Pro_Rtc Inno3ProClk;
Inno3Pro_Application Inno3ProApp;


//Step 3 :  Write Initial Commands to Inno Pro
void setup() 
{
    Inno3ProApp.Inno3Pro_Initialization();        
    Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);           
    Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);             
    Inno3ProApp.Inno3Pro_Vbus_Switch_Control(1);         
}



//Step 4 :  Call the Functions on the Main Loop     
void loop()
{  

        static double fVoltInc = 5;                 //Initialize Voltage at 5V
        static uint16_t u16_Request_Timer = 0;      //Initialize Request Timer     
        static float VoltOutput = 0;
         
        static  float WaveTimerCount = 0;
       
        static float Resolution = 256;  //256,128,64,32,16
        static float PI_Timer = (PI*1000)/Resolution;        
        
        static float SineWaveOffset = 11.5;

        static float Phase = 0;
          
        static float Amplitude = 5;                
        static float AngularFreq = 6;              
      
                
        //Library Call in the Mainloop
                
        //Timer Routine For Automatic Activation of  Requests
        if(Inno3ProClk.clock_HasTimeElapsedMs(u16_Request_Timer,50))    
        {                       
          
           VoltOutput = SineWaveOffset + (Amplitude*sin((AngularFreq * WaveTimerCount) + Phase)); 
           
           WaveTimerCount = WaveTimerCount + (PI/Resolution);

            //2 PI
            if(WaveTimerCount > 6.28135)
            {
              WaveTimerCount = 0;

               //changes the phase and Amplitude of the wave slightly each loop.
               //Phase = Phase + 5;     
               //Amplitude = Amplitude + 0.2;         
            }            

            fVoltInc =constrain(VoltOutput,3,20);
            Inno3ProApp.Inno3Pro_Write_VI(fVoltInc,6);          //Set Voltage as variable and Set 6A current

            u16_Request_Timer = Inno3ProClk.clock_GetTimeStampMs();     //Reset Timer  
        }                   
}


