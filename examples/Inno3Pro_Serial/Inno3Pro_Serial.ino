/**
	InnoSwitch3-Pro Serial Application Source File

	Company :   Power Integrations

	Summary :   This demonstration file uses SerialEvent Arduino Example and
	            Inno Pro Library. This Checks for the incoming Serial Data
	            (Command Codes) and Processes the user inputs to Control 
	            the InnoSwitch3-Pro via I2C

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


// Header Files
#include "Config.h"
#include "Drv_i2c.h"
#include "Drv_Rtc.h"
#include "Inno3Pro.h"



// Variables for grabbing the serial input
String Inno3ProString = "";
float inputFloat;

boolean stringComplete = false;
bool bVoltAndAmp = true;

// Main Loop Variable Initialization 
static float fVolts = 5.01;              //aInitialize Voltage at 5V
static float fAmps = 6.01;               //Initialize Constant Current at 6A 
static float fCableDropComp = 300;       //Initialize Cable Drop Compensation to 300mv
static float fVoltPeak = 7.01;           //Initialize Voltage Peak at 7V 
static float fVbusEn = 1;                //Initialize Vbus Enable to at ON        
static float fOverVolts = 6.2;           //Initialize Over Voltage at 6.2V
static float fUnderVolts = 3.6;          //Initialize Over Voltage at 3.6V


// Library Instance - Needed to call Classes
Inno3Pro_Application Inno3ProApp;
Inno3Pro_I2C Inno3ProTx;

//I2C Write Buffer - LSB, MSB
uint8_t u8_Buffer_Tx_Data[2]  ={0};
uint8_t u8_Inno3Pro_Reg_Address = 0;


void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
    
  // Initialize serial
  Serial.begin(9600);  

  // reserve 10 bytes for the inputString:
  Inno3ProString.reserve(10);
  
  // Initial Message
  Serial.println(F("Inno3Pro Serial Application"));   //F( ) -Stores Strings on the Flash Memory to Optimize SRAM
  Serial.print("\n");    
  Serial.println(F("Command Codes: INIT, VI, CV, CC, OV, UV, CDC, VKP, VBEN, RDVOLTS, RDAMPS, RD , WR")); 
  Serial.print("\n");    
  Serial.println(F("BLEEDER, VDIS, PSUOFF, CVO, OVL, UVL, ISSC, UVLTIMER, WATCHDOG, CVOL, CVOLTIMER, INT , OTP ,CVOPTI"));
  /*
   * User Instructions:
   
    PROCEDURE:
    Input the Command Code, then Input the Value(s)
    Command Codes are Case Sensitive

  
    EXAMPLE: (Voltage and Current)
    "Input VI and Send"
    "Input 5 and Send (This Means 5V)"
    "Input 3 and Send (This Means 3A)"
    
   */
  
  Serial.print("\n");  
  Serial.println(F("********************************************************************************"));
  Serial.print("\n");  

  //Run Initialization at Start Up
  Inno3ProApp.Inno3Pro_Initialization();   
 
  Inno3ProApp.Inno3Pro_Vbus_Switch_Control(fVbusEn);              //Set Vbus Enable

}

void loop()
{

      //Check for Serial Events
      serialEvent();

      //Commands Received
      if(stringComplete)
      {
        Inno3ProSerial_State();                    // Command States , Processes the Serial Inputs
   
        stringComplete = false;                   // Clear the input boolean               
        Inno3ProString = "";                       // Clear the input string              
      }    
      //Library Call in the Mainloop
      if(bVoltAndAmp)
      {
          Inno3ProApp.Inno3Pro_Write_VI(fVolts,fAmps);               //Set Voltage and current
      }

}



// Catch All Serial Commands
void serialEvent() 
{
  if (Serial.available()) {

     
     
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:vi
    Inno3ProString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}



//Process All Serial Commands and Configures Inno Pro based on the Inputs
void Inno3ProSerial_State (void)
{
         //Temporary  Variables
         uint16_t u16TempReadValue = 0;
         uint16_t u16TempReadLsb = 0;
         uint16_t u16TempReadMsb = 0;         
         static float fTempVolts = 5;   
         float fConvertedValue = 0;              
         uint16_t u16ReadCnt = 0; 
         uint16_t u16GenericReadValue = 0;          
         bool bflag = false;             
         static uint16_t u16Response = 0;
         static uint16_t u16Freq = 0;
         uint16_t u16Temp = 0;
         
         String ReadBit15 = "";
         String ReadBit14 = "";
         String ReadBit13 = "";
         String ReadBit12 = "";
         String ReadBit11 = "";
         String ReadBit10 = "";
         String ReadBit9 = "";
         String ReadBit8 = "";
         String ReadBit7 = "";
         String ReadBit6 = "";      
         String ReadBit5 = "";
         String ReadBit4 = "";
         String ReadBit3 = "";
         String ReadBit2 = "";                                            
         String ReadBit1 = "";
         String ReadBit0 = "";              
         
          //Inno Pro Command States
          static enum { STATE_CMD_CODE,
                        STATE_INIT,
                        STATE_READ,
                        STATE_WRITE,                                                
                        STATE_VBEN,
                        STATE_BLEEDER,
                        STATE_VDIS,
                        STATE_PSUOFF,
                        STATE_FASTVI,  
                        STATE_CVO, 
                        STATE_VOLTS,
                        STATE_OVA,  
                        STATE_UVA,  
                        STATE_CDC,  
                        STATE_AMPS, 
                        STATE_VKP,
                        STATE_OVL,                        
                        STATE_UVL,  
                        STATE_ISSC, 
                        STATE_ISSCFREQ,                       
                        STATE_UVLTIMER,
                        STATE_WATCHDOG,
                        STATE_CVOL,  
                        STATE_CVOLTIMER,  
                        STATE_INTERRUPT, 
                        STATE_OTP  ,
                        STATE_CVOPTI                                                                                       
                      }SerialState_e;
                        
          switch(SerialState_e)
          {
      
            case STATE_CMD_CODE:
                              
                  Serial.print(F("Inno Pro Command Code: "));                  // Print the data to serial    
      
                  if (Inno3ProString == "VI\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_VOLTS;   
                     bVoltAndAmp = true;                                          
                  } 
                  else if (Inno3ProString == "VBEN\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_VBEN;    
                     bVoltAndAmp = false;                                          
                  }  
                  else if (Inno3ProString == "BLEEDER\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_BLEEDER;    
                     bVoltAndAmp = false;                                          
                  } 
                  else if (Inno3ProString == "VDIS\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_VDIS;    
                     bVoltAndAmp = false;                                          
                  } 
                  else if (Inno3ProString == "PSUOFF\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_PSUOFF;    
                     bVoltAndAmp = false;                                          
                  } 
                  else if (Inno3ProString == "FASTVI\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_FASTVI;    
                     bVoltAndAmp = false;                                          
                  }   
                  else if (Inno3ProString == "CVO\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_CVO;    
                     bVoltAndAmp = false;                                          
                  }            
                  else if (Inno3ProString == "CV\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_VOLTS;   
                     bVoltAndAmp = false;                                          
                  } 
                  else if (Inno3ProString == "OV\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_OVA;    
                     bVoltAndAmp = false;                                          
                  }   
                  else if (Inno3ProString == "UV\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_UVA;    
                     bVoltAndAmp = false;                                          
                  }   
                  else if (Inno3ProString == "CDC\n")
                  {  
                     Serial.print(Inno3ProString);             
                     SerialState_e = STATE_CDC;  
                     bVoltAndAmp = false;                                            
                  }           
                  else if (Inno3ProString == "CC\n")
                  {  
                     Serial.print(Inno3ProString);                                    
                     SerialState_e = STATE_AMPS; 
                     bVoltAndAmp = false;                                          
                  }  
                  else if (Inno3ProString == "VKP\n")
                  {  
                     Serial.print(Inno3ProString);              
                     SerialState_e = STATE_VKP;  
                     bVoltAndAmp = false;                                            
                  }         
                  else if (Inno3ProString == "OVL\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_OVL;  
                     bVoltAndAmp = false;                                             
                  } 
                  else if (Inno3ProString == "UVL\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_UVL;   
                     bVoltAndAmp = false;                                         
                  }    
                  else if (Inno3ProString == "ISSC\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_ISSC;   
                     bVoltAndAmp = false;                                         
                  }   
                  else if (Inno3ProString == "ISSCFREQ\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_ISSCFREQ;   
                     bVoltAndAmp = false;                                         
                  }           
                  else if (Inno3ProString == "UVLTIMER\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_UVLTIMER;   
                     bVoltAndAmp = false;                                         
                  }   
                  else if (Inno3ProString == "WATCHDOG\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_WATCHDOG;   
                     bVoltAndAmp = false;                                         
                  } 
                  else if (Inno3ProString == "CVOL\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_CVOL;   
                     bVoltAndAmp = false;                                         
                  }           
                  else if (Inno3ProString == "CVOLTIMER\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_CVOLTIMER;   
                     bVoltAndAmp = false;                                         
                  }  
                      else if (Inno3ProString == "CVOPTI\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_CVOPTI ;   
                     bVoltAndAmp = false;                                         
                  }     
                  else if (Inno3ProString == "INT\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_INTERRUPT;   
                     bVoltAndAmp = false;                                         
                  } 
                  else if (Inno3ProString == "OTP\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_OTP;   
                     bVoltAndAmp = false;                                         
                  }           
                  else if (Inno3ProString == "INIT\n")
                  {  
                     Serial.print(Inno3ProString);    
                     Inno3ProApp.Inno3Pro_Vbus_Switch_Control(0);               //Turn OFF Vbus Switch   
                     delay(50);      
                     Inno3ProApp.Inno3Pro_Initialization();                     //Disable Watch Dog

                     //Set Values
                     fVolts = 5;
                     fAmps = 6;
                     fCableDropComp = 300;
                     fVoltPeak = 7;
                     fVbusEn = 3;
   
                     delay(50); 
                     Inno3ProApp.Inno3Pro_Vbus_Switch_Control(fVbusEn);         //Turn on Vbus
                     
                     //Send Value to Serial Monitor  
                     Serial.print(F("Voltage Setting: "));                       Serial.print(fVolts);             Serial.print(F(" V"));     Serial.print("\n");    
                     Serial.print(F("Constant Current Setting:: "));             Serial.print(fAmps);              Serial.print(F(" A"));     Serial.print("\n");   
                     Serial.print(F("Cable Drop Compensation: "));               Serial.print(fCableDropComp);     Serial.print(F(" mV"));    Serial.print("\n");    
                     Serial.print(F("Constant Output Power Knee Voltage: "));    Serial.print(fVoltPeak);          Serial.print(F(" V"));     Serial.print("\n");         
                     Serial.print(F("Series Bus Switch Control: "));             Serial.print(fVbusEn);            Serial.print(F(" ON"));    Serial.print("\n");   
                     Serial.print("\n");  

                     bVoltAndAmp = false;                                                  
                  }                      
                  else if (Inno3ProString == "RDVOLTS\n")
                  {  
                     Serial.print(Inno3ProString);
                     u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ9);                    // Read9, Reg_CV
                         
                     Serial.print(F("Measured Output Voltage: "));                     
                     Serial.print("\n");        
                     Serial.print(F("HEX       : "));             Serial.print(u16TempReadValue,HEX);         Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent 

                     Serial.print("\n");  
                     //Bit Manipulation:  Clear the Bit[15:12] , use Bit [11:0] 
                     u16TempReadValue = (u16TempReadValue & 0x0FFF);                   
                     Serial.print(F("Processed Hex : "));                                                          
                     Serial.print(u16TempReadValue,HEX);                      

                     Serial.print("\n");                
                     Serial.print(F("DECIMAL   : "));             Serial.print(u16TempReadValue,DEC);         // Print Decimal Equivalent                                                                                                              

                     fConvertedValue = (float) (u16TempReadValue / INNO3PRO_CV_SET_PT_MULT );                  // Implement CV multiplier
                       
                     Serial.print("\n");        
                     Serial.print(F("CONVERTED : "));            Serial.print(fConvertedValue,2);   Serial.print(F(" V"));// Print Converted Equivalent

                     
                     //Next Line
                     Serial.print("\n");                             
                     Serial.print("\n"); 

                     bVoltAndAmp = false;
                  }                  
                  else if (Inno3ProString == "RDAMPS\n")
                  {  
                     Serial.print(Inno3ProString);
                     u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ7);                       // Read7, Reg_MEASURED_I
                     
                     
                     Serial.print(F("Measured Output Current: "));                                            // Print the data to serial                      
                     Serial.print("\n");        
                     Serial.print(F("HEX       : "));             Serial.print(u16TempReadValue,HEX);          Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent                                                                


                     Serial.print("\n");  
                     //Bit Manipulation:  MSB- Clear the Bit [15:9]            LSB - Clear bit 7 (Parity)
                     u16TempReadValue = ((u16TempReadValue & 0x0100) >> 1) + (u16TempReadValue & 0x7F);               
                     Serial.print(F("Processed Hex : "));                                                           
                     Serial.print(u16TempReadValue,HEX);      

                     Serial.print("\n");                
                     Serial.print(F("DECIMAL   : "));             Serial.print(u16TempReadValue,DEC);         // Print Decimal Equivalent                     
                     
                    //Sensed Current Value = N (Decimal) x 32 / (Rsense * 128)
                    //Calculate Reading:  
                    //Sensed Current Value = (58 x 32) / (5 * 128 ) =  2.9 Amps                              
                     fConvertedValue = (float) ( (u16TempReadValue * INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE)/(INNO3PRO_RSENSE * INNO3PRO_ADC_FULL_RANGE) );                  // Implement  multiplier  
                       
                     Serial.print("\n");        
                     Serial.print(F("CONVERTED : "));            Serial.print(fConvertedValue,2);   Serial.print(F(" A"));// Print Converted Equivalent

                     
                     //Next Line
                     Serial.print("\n");                             
                     Serial.print("\n");  

                     bVoltAndAmp = false;                                                                                        
                  }   
                  else if (Inno3ProString == "RD\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_READ;  
                     bVoltAndAmp = false;                                            
                  }     
                  else if (Inno3ProString == "WR\n")
                  {  
                     Serial.print(Inno3ProString);            
                     SerialState_e = STATE_WRITE;   
                     bVoltAndAmp = false;                                           
                  }                                                                            
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }
                  break;
      
            case STATE_VOLTS: //Volts
                  Serial.print(F("Output Voltage Setting: "));                  // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  {
                      inputFloat = Inno3ProString.toFloat();               //Convert the inputted number to a float     
                      inputFloat = constrain(inputFloat,3,21);             //Set Limits - 20V for Now , Hardware Limitation
                      
                      fTempVolts = inputFloat + 0.001;                     //Store Output Voltage Setting , 1mv Offset Needed for ASCII conversion
                      Serial.print(inputFloat);                            //Send Value to Serial Monitor                         
                      Serial.print(F(" V"));                               //Print Unit 


                      //Next Line
                      Serial.print("\n");                             
                                                          
                      //Proceed to Amps if Write VI only
                      if(bVoltAndAmp)
                      {                      
                        SerialState_e = STATE_AMPS;                          //Proceed to Constant Current Setting
                      }
                      else
                      {
                        Serial.print("\n");     
                        fVolts = fTempVolts;                                 //Set Output Voltage In Volts
                        Inno3ProApp.Inno3Pro_Write_Volts(fVolts);            //Set Voltage   
                        SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                      }   

                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                  
                  break;      


            case STATE_VBEN: //VBEN

                  Serial.print(F("Series Bus Switch Control: "));                
                   
                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {

                    Inno3ProApp.Inno3Pro_Initialization();                //Re- Initialize to Disable Watchdog  

                    
                    inputFloat = Inno3ProString.toFloat();    
                    inputFloat = constrain(inputFloat,0,3);              //Set Limits - 0 to 3 Only             

                    if( inputFloat >= 1 )
                    {
                         fVbusEn =   1;                                  //Turn ON VBEN
                    } 
                    else
                    {
                         fVbusEn =   0;                                  //Turn OFF VBEN                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor

                    //Analyze and Print VBEN Setting
                    if(inputFloat == 0)
                    {
                       Serial.print(F(" OFF"));                          //Print Setting                          
                    }
                    else if( inputFloat >= 1)
                    {
                       Serial.print(F(" ON"));                           //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" OFF"));                          //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_Vbus_Switch_Control(fVbusEn);              //Set Vbus Enable
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                               
                  }                                                             
                  break;   
             // ADD BY SPENCER 

  case STATE_CVOPTI: //VBEN

                  Serial.print(F("Constant Voltage Load Optimal: 1 or 0 "));                
                   
                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {

                    Inno3ProApp.Inno3Pro_Initialization();                //Re- Initialize to Disable Watchdog  

                    
                    inputFloat = Inno3ProString.toFloat();    
                    inputFloat = constrain(inputFloat,0,3);              //Set Limits - 0 to 3 Only             
                   float fCVload_opti;
                    if( inputFloat >= 1 )
                    {
                       fCVload_opti =   0x80;                                  //Turn ON VBEN
                    } 
                    else
                    {
                          fCVload_opti =   0x20;                                  //Turn OFF VBEN                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor

                    //Analyze and Print VBEN Setting
                    if(inputFloat == 0)
                    {
                       Serial.print(F(" 0x20"));                          //Print Setting                          
                    }
                    else if( inputFloat >= 1)
                    {
                       Serial.print(F(" 0x80"));                           //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" 0x20"));                          //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_Write_CV_Load(fCVload_opti)  ;          //Set Vbus Enable
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                               
                  }                                                             
                  break;   
                  
            case STATE_BLEEDER: //Bleeder
                  Serial.print(F("Active Bleeder Setting: "));           // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              

                    if( inputFloat >= 1 )
                    {
                         bflag =   true;                                 //enable
                    } 
                    else
                    {
                         bflag =   false;                                //disable                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor

                    //Analyze and Print Setting
                    if( inputFloat >= 1)
                    {
                       Serial.print(F(" ENABLED"));                     //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" DISABLED"));                    //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_Bleeder_Enable(bflag);   //Implement Setting
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }  
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                     
                  break; 

            case STATE_VDIS: //Load Discharge
                  Serial.print(F("Load (VBUS) Discharge Setting: "));     // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              

                    if( inputFloat >= 1 )
                    {
                         bflag =   true;                                 //enable
                    } 
                    else
                    {
                         bflag =   false;                                //disable                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor

                    //Analyze and Print Setting
                    if( inputFloat >= 1)
                    {
                       Serial.print(F(" ENABLED"));                     //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" DISABLED"));                    //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_Load_Discharge(bflag);          //Implement Setting
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break; 

            case STATE_PSUOFF: //PSU off
                  Serial.print(F("Turn Off PSU Setting: "));            // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              

                    if( inputFloat >= 1 )
                    {
                         bflag =   true;                                 //enable
                    } 
                    else
                    {
                         bflag =   false;                                //disable                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor

                    //Analyze and Print Setting
                    if( inputFloat >= 1)
                    {
                       Serial.print(F(" ENABLED"));                     //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" DISABLED"));                    //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_TurnOff_PSU(bflag);             //Implement Setting
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }  
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                     
                  break;    

            case STATE_FASTVI: //Speed of CV/CC Update
                  Serial.print(F("Fast VI Command Setting: "));          // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              

                    if( inputFloat >= 1 )
                    {
                         bflag =   true;                                 //enable
                    } 
                    else
                    {
                         bflag =   false;                                //disable                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    
                    //Analyze and Print Setting
                    if( inputFloat >= 1)
                    {
                       Serial.print(F("  No Speed Limit"));              //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F("  10ms Update Limit Enabled"));   //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_FastVI_Disable(bflag);          //Implement Setting
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  } 
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                      
                  break;    

            case STATE_CVO: //Constant Voltage Only Mode
                  Serial.print(F("Constant Voltage Only Mode: "));       // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              

                    if( inputFloat >= 1 )
                    {
                         bflag =   true;                                 //enable
                    } 
                    else
                    {
                         bflag =   false;                                //disable                
                    }
   
                    
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                  
                    //Analyze and Print Setting
                    if( inputFloat >= 1)
                    {
                       Serial.print(F(" No CC"));                       //Print Setting                 
                    }
                    else
                    {
                       Serial.print(F(" CV/CC Enabled"));                //Print Setting    
                    }

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    Inno3ProApp.Inno3Pro_CVOnlyMode_Enable(bflag);       //Implement Setting
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }      
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                 
                  break;                                                 
                                    
            case STATE_AMPS: //Constant Current (Amps)

                  Serial.print(F("Constant Current Setting: "));         // Print the data to serial 
                   
                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {
                    inputFloat = Inno3ProString.toFloat();                // Convert the inputted number to a float    
                    inputFloat = constrain(inputFloat,0,6.4);             //Set Limits: 0 to 6.4A, depends on Rsense
                    
                    fAmps =   inputFloat;                                //Set Constant Current in Amps
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" A"));                               //Print Unit                     

                    if(bVoltAndAmp)
                    {
                      fVolts = fTempVolts;                               //Set Output Voltage In Volts                                                                
                    }
                    else
                    {
                      Inno3ProApp.Inno3Pro_Write_Amps(fAmps);  
                    }
                    
                    Serial.print("\n");     
                    Serial.print("\n");        
                      
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                               
                  }                                                             
                  break;     

            
            case STATE_OVA: //Over Voltage Setting
                  Serial.print(F("Over Voltage Setting: "));                  // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  {
                    inputFloat = Inno3ProString.toFloat();               //Convert the inputted number to a float     
                    inputFloat = constrain(inputFloat,6.2,25);          //Set Limits - 6.2V to 25V
                    
                    fTempVolts = inputFloat + 0.001;                     //Store Output Voltage Setting , 1mv Offset Needed for ASCII conversion
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor                         
                    Serial.print(F(" V"));                               //Print Unit 
                                  
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");   

                    fOverVolts = fTempVolts;                             //Set Over Voltage In Volts
                    Inno3ProApp.Inno3Pro_Write_Over_Volts(fOverVolts);   //Set Over Voltage                                        
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                 
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                  
                  break; 

            
            case STATE_UVA: //Under Voltage Setting
                  Serial.print(F("Under Voltage Setting: "));                  // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  {
                    inputFloat = Inno3ProString.toFloat();               //Convert the inputted number to a float     
                    inputFloat = constrain(inputFloat,3,20);             //Set Limits - 3V to 24V
                    
                    fTempVolts = inputFloat + 0.001;                     //Store Output Voltage Setting , 1mv Offset Needed for ASCII conversion
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor                         
                    Serial.print(F(" V"));                               //Print Unit 
                                  
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");   

                    fUnderVolts = fTempVolts;                             //Set Over Voltage In Volts
                    Inno3ProApp.Inno3Pro_Write_Under_Volts(fUnderVolts);  //Set Under Voltage                   
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                 
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                  
                  break;                   

                     
            case STATE_CDC: //CDC

                  Serial.print(F("Cable Drop Compensation: "));                
                   
                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {
                    inputFloat = Inno3ProString.toFloat();        
                    inputFloat = constrain(inputFloat,0,600);            //Set Limits: 0 to 600mv    
                    
                    fCableDropComp =   inputFloat;                       //Set Cable Drop Compensation
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor  
                    Serial.print(F(" mV"));                              //Print Unit                               
                                          
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");                        
                    Inno3ProApp.Inno3Pro_Write_Cable_Drop_Comp(fCableDropComp);     //Set Cable Drop Compesation    
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                                             
                  break;     

      
            case STATE_VKP: //VKP

                  Serial.print(F("Constant Output Power Knee Voltage: "));                
                   
                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {
                    inputFloat = Inno3ProString.toFloat(); 
                    inputFloat = constrain(inputFloat,5.3,24);           //Set Limits: 5.3 to 24V               
                    
                    fVoltPeak =   inputFloat;                            //Set Constant Power Knee Voltage
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" V"));                               //Print Unit                         
                                        
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");      
                      
                    Inno3ProApp.Inno3Pro_Write_Volt_Peak(fVoltPeak);                //Set Constant Output Power Knee Voltage
                    SerialState_e = STATE_CMD_CODE;                     //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                                             
                  break;    
 

            case STATE_OVL: //Over Voltage Fault Response
                  Serial.print(F("Over Voltage Fault Response: "));      // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                  
                    //Analyze and Print Setting
                    if( inputFloat == 0)
                    {
                       Inno3ProApp.Inno3Pro_Write_OVL_Fault_Response(INNO3PRO_OVL_FAULT_RESPONSE_NORESPONSE);
                       Serial.print(F(" No Response"));                  //Print Setting                                      
                    }
                    else if(inputFloat == 1)
                    {
                       Inno3ProApp.Inno3Pro_Write_OVL_Fault_Response(INNO3PRO_OVL_FAULT_RESPONSE_LATCHOFF);
                       Serial.print(F(" Latch-Off"));                    //Print Setting    
                    }
                    else if(inputFloat == 2)
                    {
                       Inno3ProApp.Inno3Pro_Write_OVL_Fault_Response(INNO3PRO_OVL_FAULT_RESPONSE_AUTORESTART); 
                       Serial.print(F(" Auto Restart"));                 //Print Setting      
                    }
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (0-NR , 1-LO, 2-AR )"));                                                                                      
                    }    
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  


            case STATE_UVL: //Under Voltage Fault Response
                  Serial.print(F("Over Voltage Fault Response: "));      // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                  
                    //Analyze and Print Setting
                    if( inputFloat == 2)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Response(INNO3PRO_UVL_FAULT_RESPONSE_NORESPONSE);
                       Serial.print(F(" No Response"));                  //Print Setting                                      
                    }
                    else if(inputFloat == 1)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Response(INNO3PRO_UVL_FAULT_RESPONSE_LATCHOFF);
                       Serial.print(F(" Latch-Off"));                    //Print Setting    
                    }
                    else if(inputFloat == 0)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Response(INNO3PRO_UVL_FAULT_RESPONSE_AUTORESTART); 
                       Serial.print(F(" Auto Restart"));                 //Print Setting   
                    }   
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (0-AR , 1-LO, 2-NR )"));                                                                                      
                    }   
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  


            case STATE_ISSC: //IS-pin Short Fault Response
                  Serial.print(F("IS-pin Short Fault Response: "));      // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                  
                    //Analyze and Print Setting
                    if( inputFloat == 0)
                    {
                        u16Response = INNO3PRO_ISSC_FAULT_RESPONSE_NORESPONSE;   
                        Serial.print(F(" No Response"));                  //Print Setting                                                   
                    }
                    else if(inputFloat == 1)
                    {
                        u16Response = INNO3PRO_ISSC_FAULT_RESPONSE_LATCHOFF;
                        Serial.print(F(" Latch-Off"));                    //Print Setting                            
                    }
                    else if(inputFloat == 2)
                    {
                        u16Response = INNO3PRO_ISSC_FAULT_RESPONSE_AUTORESTART;
                        Serial.print(F(" Auto Restart"));                 //Print Setting                           
                    }
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (0-NR , 1-LO, 2-AR )"));                                                                                      
                    }                        

                    //Next Line
                    Serial.print("\n");                               
                    SerialState_e = STATE_ISSCFREQ;                       //Got to ISSC Frequency Setting
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  

            case STATE_ISSCFREQ: //IS-pin Short Frequency
                  Serial.print(F("IS-pin Short Frequency: "));          // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 

                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" Khz"));
                     
                    //Analyze and Print Setting
                    if( inputFloat == 30) //Khz
                    {
                        u16Freq = INNO3PRO_ISSC_FREQ_THRESHOLD_30KHZ;    
                        Inno3ProApp.Inno3Pro_Write_ISSC_Fault_Response(u16Response,u16Freq);                                              
                    }
                    else if(inputFloat == 40) //Khz
                    {
                        u16Freq = INNO3PRO_ISSC_FREQ_THRESHOLD_40KHZ;  
                        Inno3ProApp.Inno3Pro_Write_ISSC_Fault_Response(u16Response,u16Freq);                     
                    }
                    else if(inputFloat == 60) //Khz
                    {
                        u16Freq = INNO3PRO_ISSC_FREQ_THRESHOLD_60KHZ; 
                        Inno3ProApp.Inno3Pro_Write_ISSC_Fault_Response(u16Response,u16Freq);                     
                    }                    
                    else if(inputFloat == 50) //Khz
                    {
                        u16Response = INNO3PRO_ISSC_FREQ_THRESHOLD_50KHZ;
                        Inno3ProApp.Inno3Pro_Write_ISSC_Fault_Response(u16Response,u16Freq);                   
                    }
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (30, 40, 50, 60)"));                                                                                       
                    } 
                                        
                   
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                      //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;                    


            case STATE_UVLTIMER: //Under Voltage Fault Timer
                  Serial.print(F("Under Voltage Fault Timer: "));       // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" ms"));
                  
                    //Analyze and Print Setting
                    if( inputFloat == 8)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Timer(INNO3PRO_UVL_FAULT_TIMER_8MS);                                 
                    }
                    else if(inputFloat == 16)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Timer(INNO3PRO_UVL_FAULT_TIMER_16MS);
                    }
                    else if(inputFloat == 32)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Timer(INNO3PRO_UVL_FAULT_TIMER_32MS);
                    }                    
                    else if(inputFloat == 64)
                    {
                       Inno3ProApp.Inno3Pro_Write_UVL_Fault_Timer(INNO3PRO_UVL_FAULT_TIMER_64MS);
                    }   
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (8, 16, 32, 64)"));                                                                                      
                    } 
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  

            case STATE_WATCHDOG: //Watchdog Timer
                  Serial.print(F("Watchdog Timer: "));                  // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" ms"));
                  
                    //Analyze and Print Setting
                    if( inputFloat == 500)
                    {
                       Inno3ProApp.Inno3Pro_Write_Watchdog_Timer(INNO3PRO_WATCHDOG_TIMER_500MS);                                 
                    }
                    else if(inputFloat == 1000)
                    {
                       Inno3ProApp.Inno3Pro_Write_Watchdog_Timer(INNO3PRO_WATCHDOG_TIMER_1000MS);
                    }
                    else if(inputFloat == 2000)
                    {
                       Inno3ProApp.Inno3Pro_Write_Watchdog_Timer(INNO3PRO_WATCHDOG_TIMER_2000MS);
                    }                    
                    else if(inputFloat == 0)
                    {
                       Inno3ProApp.Inno3Pro_Write_Watchdog_Timer(INNO3PRO_WATCHDOG_TIMER_NOWATCHDOG);  
                    }
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (0, 500, 1000, 2000)"));                                                                                      
                    }                     

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  


            case STATE_CVOL: //Constant Voltage Mode Fault Response
                  Serial.print(F("Constant Voltage Mode Fault Response: "));  // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                  
                    //Analyze and Print Setting
                    if( inputFloat == 0)
                    {
                        Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Response(INNO3PRO_CVOL_FAULT_RESPONSE_NORESPONSE);  
                        Serial.print(F(" No Response"));                  //Print Setting                                                   
                    }
                    else if(inputFloat == 1)
                    {
                        Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Response(INNO3PRO_CVOL_FAULT_RESPONSE_AUTORESTART); 
                        Serial.print(F(" Auto Restart"));                 //Print Setting                           
                    }
                    else if(inputFloat == 2)
                    {
                        Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Response(INNO3PRO_CVOL_FAULT_RESPONSE_LATCHOFF);                         
                        Serial.print(F(" Latch-Off"));                    //Print Setting                            
                    }                    
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (0-NR , 1-AR, 2-LO )"));                                                                                      
                    }                        

                    //Next Line
                    Serial.print("\n");                               
                    SerialState_e = STATE_CMD_CODE;                       //Got to ISSC Frequency Setting
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;                    

            case STATE_CVOLTIMER: //Constant Voltage Fault Timer

                  Serial.print(F("Constant Voltage Fault Timerr: "));       // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" ms"));
                  
                    //Analyze and Print Setting
                    if( inputFloat == 8)
                    {
                       Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Timer(INNO3PRO_CVOL_FAULT_TIMER_8MS);                                 
                    }
                    else if(inputFloat == 16)
                    {
                       Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Timer(INNO3PRO_CVOL_FAULT_TIMER_16MS);
                    }
                    else if(inputFloat == 32)
                    {
                       Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Timer(INNO3PRO_CVOL_FAULT_TIMER_32MS);
                    }                    
                    else if(inputFloat == 64)
                    {
                       Inno3ProApp.Inno3Pro_Write_CVOL_Fault_Timer(INNO3PRO_CVOL_FAULT_TIMER_64MS);
                    }   
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (8, 16, 32, 64)"));                                                                                      
                    } 
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break; 



            case STATE_INTERRUPT: //Interrupt
                  Serial.print(F("Interrupt Mask: "));   // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    u16Temp = Inno3ProString.toInt();              
                    Serial.print(u16Temp);                            //Send Value to Serial Monitor
                    Serial.print(F(" Decimal"));
                  

                     Inno3ProApp.Inno3Pro_Write_Interupt_Mask(u16Temp);

                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  
                  
            case STATE_OTP: //OTP
                  Serial.print(F("Secondary Over Temperature Hysteresis: "));   // Print the data to serial         

                  if (isDigit(Inno3ProString[0]))                        //Check If First Serial Command is a Number
                  { 
                    
                    inputFloat = Inno3ProString.toFloat();              
                    Serial.print(inputFloat);                            //Send Value to Serial Monitor
                    Serial.print(F(" Deg"));
                  
                    //Analyze and Print Setting
                    if( inputFloat == 40)
                    {
                       Inno3ProApp.Inno3Pro_Write_OTP_Hysteresis(INNO3PRO_OTP_FAULT_HYST_40DEG);                                 
                    }
                    else if(inputFloat == 60)
                    {
                       Inno3ProApp.Inno3Pro_Write_OTP_Hysteresis(INNO3PRO_OTP_FAULT_HYST_60DEG);
                    }
                    else
                    {
                       Serial.print("\n"); 
                       Serial.print(F("Invalid Input! (40 Deg, 60 Deg)"));                                                                                      
                    } 
                    
                    //Next Line
                    Serial.print("\n");                             
                    Serial.print("\n");    
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                  }    
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                   
                  break;  
                                                                                                                          
            case STATE_READ: //Generic Read Command


                  if (isDigit(Inno3ProString[0]))                         //Check If First Serial Command is a Number
                  {
  
                     u16ReadCnt = Inno3ProString.toInt();   

                      Serial.print(F("READ: ")); Serial.print(u16ReadCnt);         // Print Read Value Equivalent
                      Serial.print("\n"); 
                 

                    //CV Set Point                                                                
                    if( u16ReadCnt == 1)
                    {                              
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ1);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);                 
                          Serial.print(F("(MSB,LSB)"));            
                                               
                          Serial.print("\n");   
                          Serial.print(F("CV Set Point : "));                       
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_CV_SetPoint(),2); 
                          Serial.print(F(" V"));                                             
                    }
                    //UV Set Point 
                    else if( u16ReadCnt == 2  )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ2);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);                 
                          Serial.print(F("(MSB,LSB)"));          
                          
                          Serial.print("\n");
                          Serial.print(F("UV Threshold : "));                                                      
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_UV_Threshold(),2);           
                          Serial.print(F(" V"));                                              
                    } 
                    //OV Set Point 
                    else if(u16ReadCnt == 3 )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ3);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);                 
                          Serial.print(F("(MSB,LSB)"));     
                          
                          Serial.print("\n");
                          Serial.print(F("OV Threshold : "));           
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_OV_Threshold(),2);           
                          Serial.print(F(" V"));                                           
                    }             
                    else if(u16ReadCnt == 4 )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ4);  
                          Serial.print(F("HEX : "));       Serial.print(u16TempReadValue,HEX);              Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent      
                          Serial.print("\n");
                          Serial.print("\n");
                          
                          Serial.print(F("Bit 14 : "));        Inno3ProApp.Inno3Pro_Read_VbusSwitch()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_VBEN");     Serial.print("\n");
                          Serial.print(F("Bit 13 : "));        Inno3ProApp.Inno3Pro_Read_Bleeder()       ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_BLEEDER");  Serial.print("\n");
                          Serial.print(F("Bit 12 : "));        Inno3ProApp.Inno3Pro_Read_PsuOff()        ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_PSUOFF");   Serial.print("\n"); 
                          Serial.print(F("Bit 11 : "));        Inno3ProApp.Inno3Pro_Read_FastVI()        ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_FSTVIC");   Serial.print("\n");
                          Serial.print(F("Bit 10 : "));        Inno3ProApp.Inno3Pro_Read_CvoMode()       ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_CVO");      Serial.print("\n");          
                          Serial.print(F("Bit  9 : "));        Inno3ProApp.Inno3Pro_Read_OtpFaultHyst()  ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("     Reg_OTP");      Serial.print("\n");      

                          Serial.print(F("Bit 0-3: "));          
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_Cable_Drop_Comp(),2);        
                          Serial.print("  Reg_CDC (mv)");          
                          Serial.print("\n");                           
                                                                               
                    }                      
                    //CC and CP Set Point                                   
                    else if( u16ReadCnt == 5)
                    {       
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ5);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));    
                          Serial.print("\n");                                                                                   
                           
                          //MSB
                          Serial.print(F("CC Set Point: "));
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_CC_SetPoint(),2);   
                          Serial.print(F(" A"));           
                          Serial.print("\n"); 
                                
                          //LSB
                          Serial.print(F("CP Set Point: "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_CP_Threshold(),2);  
                          Serial.print(F(" V"));           
                          Serial.print("\n");                                       
                    }   

                                                   
                    else if( u16ReadCnt == 6)
                    {       
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ6);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));    
                          Serial.print("\n");                                                                                   
                           
                   
                          Serial.print(F("Overvoltage Fault Response    :   "));
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_OV_Fault_Response(),2);         
                          Serial.print("\n");                                 
                   
                          Serial.print(F("Undervoltage Fault Response   :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_UV_Fault_Response(),2);            
                          Serial.print("\n");       

                          Serial.print(F("IS-pin Short Fault Response   :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_IsPinShort_Fault_Response(),2);            
                          Serial.print("\n");      

                          Serial.print(F("Undervoltage Fault Timer      :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_UV_Fault_Timer(),2);            
                          Serial.print("\n");        

                          Serial.print(F("Watchdog Timer Timeout        :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_Watchdog_Timer(),2);            
                          Serial.print("\n");   

                          Serial.print(F("CV Mode Fault Response        :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_CvMode_Fault_Response(),2);            
                          Serial.print("\n"); 

                          Serial.print(F("CV Mode Fault Timer           :   "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_CvMode_Timer(),2);            
                          Serial.print("\n");                                                                                                                                                                    
                    }   
                    

                    //Measured CC                                  
                    else if( u16ReadCnt == 7)
                    {
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ7);  
                          Serial.print(F("HEX : "));       
                                            
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));    
                          Serial.print("\n");

                          //Bit Manipulation:  MSB- Clear the Bit [15:9]            LSB - Clear bit 7 (Parity)
                          u16TempReadValue = ((u16TempReadValue & 0x0100) >> 1) + (u16TempReadValue & 0x7F);                        
                          Serial.print(F("Processed Hex : "));                                                           
                          Serial.print(u16TempReadValue,HEX);                                                                                     
                          Serial.print("\n");                           
                                                                                                 
                          Serial.print(F("Measured Output Current: "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_Amps(),2);   
                          Serial.print(F(" A"));                                   
                    }                    
                    //Measured CV                                   
                    else if( u16ReadCnt == 9)
                    {  
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ9);  
                          Serial.print(F("HEX : "));                                                          
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));                                                                     
                          Serial.print("\n");   

                         //Bit Manipulation:  Clear the Bit[15:12] , use Bit [11:0] 
                          u16TempReadValue = (u16TempReadValue & 0x0FFF);                          
                          Serial.print(F("Processed Hex : "));                                                          
                          Serial.print(u16TempReadValue,HEX);                                                                                     
                          Serial.print("\n"); 
                                                         
                          Serial.print(F("Measured Output Voltage: "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_Volts(),2);   
                          Serial.print(F(" V")); 
                    }

                    else if(u16ReadCnt == 10 )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ10);  
                          Serial.print(F("HEX : "));       Serial.print(u16TempReadValue,HEX);              Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent      
                          Serial.print("\n");
                          Serial.print("\n");

                          Serial.print(F("Bit 15 : "));        Inno3ProApp.Inno3Pro_Read_Status_InterruptEnable ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_INTERRUPT_EN");     Serial.print("\n");
                          Serial.print(F("Bit 14 : "));        Inno3ProApp.Inno3Pro_Read_Status_SystemReady     ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_CONTROL_S");        Serial.print("\n");
                          Serial.print(F("Bit 13 : "));        Inno3ProApp.Inno3Pro_Read_Status_OutputDischarge ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_VDIS");             Serial.print("\n");
                          Serial.print(F("Bit 12 : "));        Inno3ProApp.Inno3Pro_Read_Status_HighSwitchFreq  ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_HIGH_FSW");         Serial.print("\n"); 
                          Serial.print(F("Bit  9 : "));        Inno3ProApp.Inno3Pro_Read_Status_OtpFault        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_OTP");              Serial.print("\n");
                          Serial.print(F("Bit  5 : "));        Inno3ProApp.Inno3Pro_Read_Status_Vout2pct        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_VOUT2PCT");         Serial.print("\n");          
                          Serial.print(F("Bit  4 : "));        Inno3ProApp.Inno3Pro_Read_Status_Vout10pct       ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_VOUT10PCT");        Serial.print("\n");      

                         
                          Serial.print(F("Bit  3 : "));        Inno3ProApp.Inno3Pro_Read_Status_IsPinShort      ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_ISSC");             Serial.print("\n"); 
                          Serial.print(F("Bit  1 : "));        Inno3ProApp.Inno3Pro_Read_Status_UV_Fault        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_VOUT_UV");          Serial.print("\n");
                          Serial.print(F("Bit  0 : "));        Inno3ProApp.Inno3Pro_Read_Status_OV_Fault        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_VOUT_OV");          Serial.print("\n");          
                                                  
                    }         
                    else if(u16ReadCnt == 11 )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ11);  
                          Serial.print(F("HEX : "));       Serial.print(u16TempReadValue,HEX);              Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent      
                          Serial.print("\n");
                          Serial.print("\n");
                          
                          Serial.print(F("Bit 15 : "));        Inno3ProApp.Inno3Pro_Read_Status_CvoMode_AR      ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_ar_CV");         Serial.print("\n");
                          Serial.print(F("Bit 12 : "));        Inno3ProApp.Inno3Pro_Read_Status_IsPinShort_AR   ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_ar_ISSC");       Serial.print("\n");
                          Serial.print(F("Bit 10 : "));        Inno3ProApp.Inno3Pro_Read_Status_OV_AR           ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_ar_VOUT_OV");    Serial.print("\n");
                          Serial.print(F("Bit  9 : "));        Inno3ProApp.Inno3Pro_Read_Status_UV_AR           ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_ar_VOUT_UV");    Serial.print("\n"); 
                          Serial.print(F("Bit  7 : "));        Inno3ProApp.Inno3Pro_Read_Status_LatchOff        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_LO");            Serial.print("\n");
                          Serial.print(F("Bit  6 : "));        Inno3ProApp.Inno3Pro_Read_Status_CvoMode_LO      ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_Lo_CVO");        Serial.print("\n");          
                          Serial.print(F("Bit  5 : "));        Inno3ProApp.Inno3Pro_Read_Status_PsuOffCmd       ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_PSUOFF");        Serial.print("\n");      

                         
                          Serial.print(F("Bit  4 : "));        Inno3ProApp.Inno3Pro_Read_Status_IsPinShort_LO   ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_Lo_ISSC");       Serial.print("\n"); 
                          Serial.print(F("Bit  2 : "));        Inno3ProApp.Inno3Pro_Read_Status_OV_LO           ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_Lo_VOUT_OV");    Serial.print("\n");
                          Serial.print(F("Bit  1 : "));        Inno3ProApp.Inno3Pro_Read_Status_UV_LO           ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_Lo_VOUT_UV");    Serial.print("\n");          
                          Serial.print(F("Bit  0 : "));        Inno3ProApp.Inno3Pro_Read_Status_BPS_LO          ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Reg_BPS_OV");        Serial.print("\n");          
                                                  
                    }                  

                    else if(u16ReadCnt == 12 )
                    {                            
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ12);  
                          Serial.print(F("HEX : "));       Serial.print(u16TempReadValue,HEX);              Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent      
                          Serial.print("\n");
                          Serial.print("\n");
                          
                          Serial.print(F("Bit 14 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_CntrlSecondary        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_CONTROL_S");     Serial.print("\n");
                          Serial.print(F("Bit 13 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_BpsCurrentLo          ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_LO_Fault");      Serial.print("\n");
                          Serial.print(F("Bit 12 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_CvoPkLoadTimer        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_CCAR");          Serial.print("\n");
                          Serial.print(F("Bit 11 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_IsPinShort            ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_ISSC");          Serial.print("\n");
                          Serial.print(F("Bit  9 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_UV                    ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_VOUT_UV");       Serial.print("\n"); 
                          Serial.print(F("Bit  8 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Mask_OV                    ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("    Mask  Reg_VOUT_OV");       Serial.print("\n");
                         
                          Serial.print(F("Bit  6 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Stat_CntrlSecondary        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_CONTROL_S");     Serial.print("\n");          
                          Serial.print(F("Bit  5 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Stat_BpsCurrentLo          ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_LO_Fault");      Serial.print("\n");                               
                          Serial.print(F("Bit  4 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Stat_CvoPkLoadTimer        ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_CCAR");          Serial.print("\n"); 
                          Serial.print(F("Bit  3 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Stat_IsPinShort            ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_ISSC");          Serial.print("\n");
                          Serial.print(F("Bit  1 : "));        Inno3ProApp.Inno3Pro_Read_Interrupt_Stat_UV                    ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_VOUT_UV");       Serial.print("\n");          
                          Serial.print(F("Bit  0 : "));        Inno3ProApp. Inno3Pro_Read_Interrupt_Stat_OV                   ()    ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print("  Status  Reg_VOUT_OV");       Serial.print("\n");          
                                                  
                    }                                           
                    //Average Measured CC                                  
                    else if( u16ReadCnt == 13)
                    {
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ13);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));    
                          Serial.print("\n");    
                                                                                                                 
                          Serial.print(F("Average Output Current: "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_AmpsAverage(),2);   
                          Serial.print(F(" A"));                                    
                    }                    
                    //Average Measured CV                                   
                    else if( u16ReadCnt == 14)
                    {  
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ14);  
                          Serial.print(F("HEX : "));       
                          Serial.print(u16TempReadValue,HEX);             
                          Serial.print(F("(MSB,LSB)"));    
                          Serial.print("\n");    
                                                                                                                 
                          Serial.print(F("Average Output Voltage: "));            
                          Serial.print((float)Inno3ProApp.Inno3Pro_Read_VoltsAverage(),2);   
                          Serial.print(F(" V")); 
                    }    
                   else if( u16ReadCnt == 15)
                    {  

                       u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ15);            
                        Serial.print(F("HEX : "));       
                        Serial.print(u16TempReadValue,HEX);             
                        Serial.print(F("(MSB,LSB)"));    
                        Serial.print("\n");  
                                                 
                        Serial.print(F("Voltage DAC: "));            
                        Serial.print((float)Inno3ProApp.Inno3Pro_Read_Voltage_DAC(),2);   
                        Serial.print(F(" V")); 
                    } 
                   else if( u16ReadCnt == 16)
                    {  

                       u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ_LOOP_SPEED_1);            
                       
                       Serial.print(F("Loop Speed 1: "));                     
                       Serial.print("\n");        
                       Serial.print(F("HEX       : "));             Serial.print(u16TempReadValue,HEX);         Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent            
                    }   
                   else if( u16ReadCnt == 17)
                    {  

                       u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(INNO3PRO_READ_LOOP_SPEED_2);            
                       
                       Serial.print(F("Loop Speed 2: "));                      
                       Serial.print("\n");        
                       Serial.print(F("HEX       : "));             Serial.print(u16TempReadValue,HEX);         Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent            
                    }                                                           
                    else
                    {
                          u16TempReadValue = Inno3ProApp.Inno3Pro_Telemetry(u16GenericReadValue);  
                          Serial.print(F("HEX : "));       Serial.print(u16TempReadValue,HEX);                 Serial.print(F("(MSB,LSB)"));  // Print Hex Equivalent   
                          Serial.print("\n"); 
                          Serial.print("\n"); 
                          
                         //MSB 
                         Serial.print(F("MSB    : 0x"));     Serial.print((u16TempReadValue & 0xFF00)>>8,HEX);                                                                                                                                       
                         Serial.print("\n"); 
                         
                         Serial.print(F("Bit 15 : "));        bitRead(u16TempReadValue,15) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit15);  Serial.print("\n");                          
                         Serial.print(F("Bit 14 : "));        bitRead(u16TempReadValue,14) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit14);  Serial.print("\n");
                         Serial.print(F("Bit 13 : "));        bitRead(u16TempReadValue,13) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit13);  Serial.print("\n");
                         Serial.print(F("Bit 12 : "));        bitRead(u16TempReadValue,12) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit12);  Serial.print("\n"); 
                         Serial.print(F("Bit 11 : "));        bitRead(u16TempReadValue,11) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit11);  Serial.print("\n");
                         Serial.print(F("Bit 10 : "));        bitRead(u16TempReadValue,10) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit10);  Serial.print("\n");          
                         Serial.print(F("Bit  9 : "));        bitRead(u16TempReadValue,9) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );      Serial.print(ReadBit9);  Serial.print("\n"); 
                         Serial.print(F("Bit  8 : "));        bitRead(u16TempReadValue,8) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );      Serial.print(ReadBit8);  Serial.print("\n");                                                                                                      
                         Serial.print("\n");   
    
    
                         //LSB  
                         Serial.print(F("LSB    : 0x"));       Serial.print(u16TempReadValue & 0x00FF,HEX);                                                                                                                                         
                         Serial.print("\n");                  
                                         
                         Serial.print(F("Bit  7 : "));        bitRead(u16TempReadValue,7) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit7);  Serial.print("\n");                          
                         Serial.print(F("Bit  6 : "));        bitRead(u16TempReadValue,6) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit6);  Serial.print("\n"); 
                         Serial.print(F("Bit  5 : "));        bitRead(u16TempReadValue,5) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit5);  Serial.print("\n"); 
                         Serial.print(F("Bit  4 : "));        bitRead(u16TempReadValue,4) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit4);  Serial.print("\n");
                         Serial.print(F("Bit  3 : "));        bitRead(u16TempReadValue,3) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit3);  Serial.print("\n"); 
                         Serial.print(F("Bit  2 : "));        bitRead(u16TempReadValue,2) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit2);  Serial.print("\n");           
                         Serial.print(F("Bit  1 : "));        bitRead(u16TempReadValue,1) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit1);  Serial.print("\n"); 
                         Serial.print(F("Bit  0 : "));        bitRead(u16TempReadValue,0) ? ( Serial.print(F("1")) ) : ( Serial.print(F("0")) );     Serial.print(ReadBit0);  Serial.print("\n"); 
        
                    }                                                  

                    Serial.print("\n"); 
                    Serial.print("\n"); 
                                       
                    SerialState_e = STATE_CMD_CODE;                     //Return to Inno Pro Command Code
                  }
                  else
                  {
                     Serial.print(F("Invalid"));    
                     Serial.print("\n");                                                                
                  }                                                             
                  break;  

            
            case STATE_WRITE: //Register Write

                    Serial.print(F("Register Address: "));                            
                    u8_Inno3Pro_Reg_Address = (Ascii_to_Hex(Inno3ProString[0])<<4) + Ascii_to_Hex(Inno3ProString[1]);  
                    Serial.print(u8_Inno3Pro_Reg_Address,HEX);                  
                    Serial.print("\n");                        
                     
                    //LSB
                    Serial.print(F("LSB: "));   
                    u8_Buffer_Tx_Data[0] = (Ascii_to_Hex(Inno3ProString[3])<<4) + Ascii_to_Hex(Inno3ProString[4]);
                    Serial.print(u8_Buffer_Tx_Data[0],HEX); 
                    Serial.print("\n");                        
                    

                    //MSB
                    Serial.print(F("MSB: "));    
                    u8_Buffer_Tx_Data[1] = (Ascii_to_Hex(Inno3ProString[6])<<4) + Ascii_to_Hex(Inno3ProString[7]);
                    Serial.print(u8_Buffer_Tx_Data[1],HEX); 
                    Serial.print("\n");                        
  


                    //Next Line                         
                    Serial.print("\n");   
                   
                    //Execute I2C Command Write                     
                    Inno3ProTx.I2C_Write16(INNO3PRO_ADDRESS,u8_Inno3Pro_Reg_Address,u8_Buffer_Tx_Data,2);                                                        
                    SerialState_e = STATE_CMD_CODE;                       //Return to Inno Pro Command Code
                 
                       
                  break;                                                                                                         

          }
}

 unsigned char Ascii_to_Hex (unsigned char data)
 { 
    if (data > '9') 
    { 
      data += 9;
    }
    return (data &= 0x0F);
 }
