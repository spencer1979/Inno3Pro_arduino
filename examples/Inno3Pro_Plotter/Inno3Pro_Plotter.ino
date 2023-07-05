/**
	InnoSwitch3-Pro Example Application

	Company:    Power Integrations

	Summary:    This demonstration Uses the Read Volts and Read Amps library
				functions of Inno3-Pro and combine it with the Serial Plotter
				to show voltage and current active graphs.
        
				Upon Upload initial voltage is set to 5V, then every 100ms
				the voltage will ramp Up by 200mV until it Reaches 20V.
				Once 20V was reached, the voltage will ramp down by 200mV every
				after 100ms until in goes to 5V. And then Process Repeats

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
  // initialize the serial communication:
  Serial.begin(9600);
    
  Inno3ProApp.Inno3Pro_Initialization(); 
}



//Step 4 :  Call the Functions on the Main Loop     
void loop()
{
  
        // Main Loop Variables    
        static double fVoltInc = 5;                 //Initialize Voltage at 5V
        static bool bVoltIncrease = true;           //Initialize Voltage to Increment        
        static uint16_t u16_Request_Timer = 0;      //Initialize Request Timer     
        
        //Read Variables
        static float fReadVolt = 0;                 // Temporary Variable for Voltage Reading
        static float fReadAmps = 0;                 // Temporary Variable for Current Reading

        
        //Timer Routine For Automatic Activation of  Requests
        if(Inno3ProClk.clock_HasTimeElapsedMs(u16_Request_Timer,100)) 	  //Delay Time 100ms
        {             
          
            Inno3ProApp.b_Request_Enable = true;      					          //Activate Voltage Change

            
            fReadVolt = Inno3ProApp.Inno3Pro_Read_Volts();                //Read Volts
            Serial.print(fReadVolt);                                      //Print Voltage Reading
            
            Serial.print("\t");                                           //For Multiple Graph 
            
            fReadAmps = Inno3ProApp.Inno3Pro_Read_Amps();                 //Read Amps
            Serial.println(fReadAmps);                                    //Print Current Reading
            
            u16_Request_Timer = Inno3ProClk.clock_GetTimeStampMs(); 	   //Reset Timer  
        }        


        
        //Increment/Decrement Process
        if(Inno3ProApp.b_Request_Enable)
        {
            if(bVoltIncrease)//Increase Voltage
            {
                fVoltInc = fVoltInc + 0.200;        //Increment by 200mV
                sig_max(fVoltInc,20);               //20V Max Saturation
                if(fVoltInc == 20)                  //if 20V reached,
                {
                    bVoltIncrease = false;          //Activate Decrement Process 
                }
            }
            else  //Decrease Voltage
            {
                fVoltInc = fVoltInc -0.200;         //Decrement by 200mV
                sig_min(fVoltInc,5);                //5V Min Saturation
                if(fVoltInc == 5)                   //if 5V reached,
                {
                    bVoltIncrease = true;           //Activate Increment Process 
                }                                
            }                             

            Inno3ProApp.b_Request_Enable = false;
        }     


		//Library Call in the Mainloop
        Inno3ProApp.Inno3Pro_Write_VI(fVoltInc,5.1);          //Set Voltage as variable and Set 5.1A current
        Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(300);           
        Inno3ProApp.Inno3Pro_Write_Volt_Peak(7);             
        Inno3ProApp.Inno3Pro_Vbus_Switch_Control(1);   
                       
}