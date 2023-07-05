
/**	
	@file		Inno3Pro.cpp
	
    @brief 		This is the source file containing the InnoSwitch3-Pro APIs.	

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
#include <Config.h>
#include <Drv_Rtc.h>
#include <Drv_i2c.h>
#include "Inno3Pro.h"

 /** 
	@brief	Class instance Declaration
 */
Inno3Pro_I2C Inno3ProSend;
Inno3Pro_Rtc Inno3ProTimer;



 /** 
	@name 	Setter Functions
	@brief	Functions for Setting the values of the Register Variables 
 */
///@{ 
inline void Inno3Pro_Application::Inno3Pro_Set_Register_CV(float fVout)
{
    fInno3Pro_CV = fVout;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_OVA(float fOva)
{
    fInno3Pro_OVA = fOva;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_UVA(float fUva)
{
    fInno3Pro_UVA = fUva;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_CC(float fCc)
{
    fInno3Pro_CC = fCc;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_CDC(float fCdc)
{
    fInno3Pro_CDC = fCdc;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_VKP(float fVkp)
{
    fInno3Pro_VKP = fVkp;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_VBEN(float fVben)
{
    fInno3Pro_VBEN = fVben;
}

inline void Inno3Pro_Application::Inno3Pro_Set_Register_UVL(float fUvl)
{
    fInno3Pro_UVL = fUvl;
}
///@}	// end of InnoSwitch3-Pro Setter Functions



 /** 
	@name 	Getter Functions
	@brief	Functions for Getting the contents of the Register Variables 
 */
///@{ 
inline float Inno3Pro_Application::Inno3Pro_Get_Register_CV(void)
{
    return fInno3Pro_CV;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_OVA(void)
{
    return fInno3Pro_OVA;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_UVA(void)
{
    return fInno3Pro_UVA;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_CC(void)
{
    return fInno3Pro_CC;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_CDC(void)
{
    return fInno3Pro_CDC;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_VKP(void)
{
    return fInno3Pro_VKP;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_VBEN(void)
{
    return fInno3Pro_VBEN;
}

inline float Inno3Pro_Application::Inno3Pro_Get_Register_UVL(void)
{
    return fInno3Pro_UVL;
}
///@}	// end of InnoSwitch3-Pro Getter Functions



 /** 
	@name 	Computation Functions
	@brief	Threshold Calculations and Adjustment Range for specific Registers
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Compute_CV( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt * INNO3PRO_CV_SET_PT_MULT);
    sig_minmax(fTemp,300,2400);  	
    return fTemp;
}

float Inno3Pro_Application::Inno3Pro_Compute_OV( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt * INNO3PRO_OV_SET_PT_MULT);
    sig_minmax(fTemp,62,250);       //Set Limits
    return fTemp;
}

float Inno3Pro_Application::Inno3Pro_Compute_UV( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt * INNO3PRO_UV_SET_PT_MULT);
    sig_minmax(fTemp,30,240);       //Set Limits
    return fTemp;
}

float Inno3Pro_Application::Inno3Pro_Compute_CDC( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt / INNO3PRO_CDC_SET_PT_DIV);
    sig_minmax(fTemp,0,12);         //Set Limits
    return fTemp;
}

float Inno3Pro_Application::Inno3Pro_Compute_CC( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt * INNO3PRO_CC_SET_PT_MULT);
    sig_minmax(fTemp,25,128);       //Set Limits
    return fTemp;
}


float Inno3Pro_Application::Inno3Pro_Compute_VKP( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt * INNO3PRO_VKP_SET_PT_MULT);
    sig_minmax(fTemp,53,240);       //Set Limits
    return fTemp;
}

float Inno3Pro_Application::Inno3Pro_Compute_VBEN( float fSetPt)
{
    float fTemp = 0;
    fTemp = (float)(fSetPt);
    sig_minmax(fTemp,0,3);       //Set Limits
    return fTemp;
}
///@}	// end of InnoSwitch3-Pro Computation Functions


/***** Buffer Related Functions *****/
 /** 
	@name 	Buffer Related  Functions
	@brief	Buffer and Parity Handling  
 */
///@{ 
void Inno3Pro_Application::Inno3Pro_Encode_Buffer( uint16_t u16Temp, uint8_t *u8WriteBuffer)
{
    //Litte Endian
    u8WriteBuffer[0] = (u16Temp & 0xFF);               //LSB
    u8WriteBuffer[1] = (u16Temp & 0xFF00) >> 8;        //MSB
}

void Inno3Pro_Application::Inno3Pro_Encode_Buffer_Parity( uint16_t u16Temp, uint8_t *u8WriteBuffer)
{
    uint16_t u16TempMsb = 0;
    uint8_t u8ConvertedMsb = 0;
    uint8_t u8ConvertedLsb = 0;

    // Clears Bit 0-6  and Shift the remaining to left by 1
    // The 7th Bit is used for Parity Purposes
    // Example for 5V :  01F4 Hex (500 in decimal) ,  Returns 0x300
    u16TempMsb = (u16Temp & 0xFF80) << 1;
   
    // Begin MSB Extraction
    // From 0x300 , Returns 0x03
    u8ConvertedMsb = (u16TempMsb & 0xFF00) >> 8;          
   

    // Check Odd Parity and Fill the MSB buffer
    if(Inno3Pro_OddParity(u8ConvertedMsb))      
    {
        // No of Zero is Odd
        u8WriteBuffer[1] = u8ConvertedMsb;             
    }
    else   
    {
        // No of Zero is Even
        u8WriteBuffer[1] = set_bit(u8ConvertedMsb,7);  
    }


    // Clears 7th Bit, This is used for parity purposes
    // Example for 5V :  01F4 Hex (500 in decimal) ,  Returns 0x74    
    u8ConvertedLsb = (u16Temp & 0x7F);
    
    
    // Check Odd Parity and Fill the LSB buffer
    if(Inno3Pro_OddParity(u8ConvertedLsb))  
    {
        // No of Zero is Odd
        u8WriteBuffer[0] = u8ConvertedLsb;              
    }
    else    
    {
        // No of Zero is Even
        u8WriteBuffer[0] = set_bit(u8ConvertedLsb,7);   
    }
}


bool Inno3Pro_Application::Inno3Pro_OddParity(uint8_t u8OddParity)
{    
    u8OddParity ^= (u8OddParity >> 4);
    u8OddParity ^= (u8OddParity >> 2); 
    u8OddParity ^= (u8OddParity >> 1); 
    return u8OddParity & 1; 
}


///@}	// end of InnoSwitch3-Pro Buffer Related Functions



 /** 
	@name   API Write Functions
	@brief	Application Programming Interface to control InnoSwitch3-Pro
 */
///@{ 

void Inno3Pro_Application::Inno3Pro_Initialization(void)
{
	
	//Set  I2C to 400Khz
 	Wire.setClock(400000); 
	
    //InnoSwitch3-Pro is ready to receive I2C commands?
    if(Inno3Pro_Read_Status_SystemReady())
    {    
        
        /******************  Example Configuration for boolean functions  ******************/ 
        
        // Inno3Pro_Vbus_Switch_Control         (true);
        // Inno3Pro_Bleeder_Enable              (false);
        // Inno3Pro_Load_Discharge              (false);
        // Inno3Pro_TurnOff_PSU                 (false);
           Inno3Pro_FastVI_Disable              (true);
        // Inno3Pro_CVOnlyMode_Enable           (false);    

           
           
        /********************** Example of Basic functions Configuration  *******************/ 
           
        // Inno3Pro_Write_Volts                 (INNO3PRO_DEFAULT_CV_SET_PT_LEVEL);
        // Inno3Pro_Write_Over_Volts            (INNO3PRO_DEFAULT_OVA_SET_PT_LEVEL);
        // Inno3Pro_Write_Under_Volts           (INNO3PRO_DEFAULT_UVA_SET_PT_LEVEL);
        // Inno3Pro_Write_Cable_Drop_Comp       (INNO3PRO_DEFAULT_CDC_ASSERT_LEVEL);
        // Inno3Pro_Write_Amps                  (INNO3PRO_DEFAULT_CC_ASSERT_LEVEL);
        // Inno3Pro_Write_Volt_Peak             (INNO3PRO_DEFAULT_VKP_ASSERT_LEVEL);

           
           
        /******************  Example Configuration for OVL Fault Response  ******************/ 
           
        // Inno3Pro_Write_OVL_Fault_Response    (INNO3PRO_OVL_FAULT_RESPONSE_NORESPONSE);
        // Inno3Pro_Write_OVL_Fault_Response    (INNO3PRO_OVL_FAULT_RESPONSE_LATCHOFF);
        // Inno3Pro_Write_OVL_Fault_Response    (INNO3PRO_OVL_FAULT_RESPONSE_AUTORESTART);        
           
           
        
        /******************  Example Configuration for UVL Fault Response  ******************/
           
        // Inno3Pro_Write_UVL_Fault_Response    (INNO3PRO_UVL_FAULT_RESPONSE_AUTORESTART);
        // Inno3Pro_Write_UVL_Fault_Response    (INNO3PRO_UVL_FAULT_RESPONSE_LATCHOFF);
        // Inno3Pro_Write_UVL_Fault_Response    (INNO3PRO_UVL_FAULT_RESPONSE_NORESPONSE);                   
           
           
           
        /*****************  Example Configuration for ISSC Fault Response  ******************/  
           
        // Inno3Pro_Write_ISSC_Fault_Response   (INNO3PRO_ISSC_FAULT_RESPONSE_NORESPONSE,
        //                                       INNO3PRO_ISSC_FREQ_THRESHOLD_50KHZ );
           
        // Inno3Pro_Write_ISSC_Fault_Response   (INNO3PRO_ISSC_FAULT_RESPONSE_LATCHOFF,
        //                                       INNO3PRO_ISSC_FREQ_THRESHOLD_30KHZ );

        // Inno3Pro_Write_ISSC_Fault_Response   (INNO3PRO_ISSC_FAULT_RESPONSE_AUTORESTART,
        //                                       INNO3PRO_ISSC_FREQ_THRESHOLD_40KHZ );           
        
        // Inno3Pro_Write_ISSC_Fault_Response   (INNO3PRO_ISSC_FAULT_RESPONSE_AUTORESTART,
        //                                       INNO3PRO_ISSC_FREQ_THRESHOLD_60KHZ );            
           
           
           
        /*****************  Example Configuration for UVL Fault Timer  ******************/  
           
        // Inno3Pro_Write_UVL_Fault_Timer       (INNO3PRO_UVL_FAULT_TIMER_8MS);
        // Inno3Pro_Write_UVL_Fault_Timer       (INNO3PRO_UVL_FAULT_TIMER_16MS);           
        // Inno3Pro_Write_UVL_Fault_Timer       (INNO3PRO_UVL_FAULT_TIMER_32MS); 
           Inno3Pro_Write_UVL_Fault_Timer       (INNO3PRO_UVL_FAULT_TIMER_64MS);            
           
           
           
        /*****************  Example Configuration for Watchdog Timer  ******************/  
           
           Inno3Pro_Write_Watchdog_Timer        (INNO3PRO_WATCHDOG_TIMER_NOWATCHDOG);
        // Inno3Pro_Write_Watchdog_Timer        (INNO3PRO_WATCHDOG_TIMER_500MS);
        // Inno3Pro_Write_Watchdog_Timer        (INNO3PRO_WATCHDOG_TIMER_1000MS);
        // Inno3Pro_Write_Watchdog_Timer        (INNO3PRO_WATCHDOG_TIMER_2000MS);           
           
           
           
        /*****************  Example Configuration for CVOL Fault Response  ******************/   
           
        // Inno3Pro_Write_CVOL_Fault_Response   (INNO3PRO_CVOL_FAULT_RESPONSE_NORESPONSE);
        // Inno3Pro_Write_CVOL_Fault_Response   (INNO3PRO_CVOL_FAULT_RESPONSE_AUTORESTART);
        // Inno3Pro_Write_CVOL_Fault_Response   (INNO3PRO_CVOL_FAULT_RESPONSE_LATCHOFF);

           
           
        /*****************  Example Configuration for CVOL Fault Timer  ******************/     
           
        // Inno3Pro_Write_CVOL_Fault_Timer      (INNO3PRO_CVOL_FAULT_TIMER_8MS);
        // Inno3Pro_Write_CVOL_Fault_Timer      (INNO3PRO_CVOL_FAULT_TIMER_16MS);
        // Inno3Pro_Write_CVOL_Fault_Timer      (INNO3PRO_CVOL_FAULT_TIMER_32MS);
        // Inno3Pro_Write_CVOL_Fault_Timer      (INNO3PRO_CVOL_FAULT_TIMER_64MS);           
           
           
           
        /*****************  Example Configuration of SCL Interrupt  ******************/ 
           
        // Inno3Pro_Write_Interupt_Mask         (INNO3PRO_INTERRUPT_CONTROL_S_MASK          |
        //                                       INNO3PRO_INTERRUPT_BPS_CURR_LO_FAULT_MASK  |
        //                                       INNO3PRO_INTERRUPT_CVO_PKLOAD_TIMER_MASK   |
        //                                       INNO3PRO_INTERRUPT_ISSC_MASK               |
        //                                       INNO3PRO_INTERRUPT_VOUT_UV_MASK            |
        //                                       INNO3PRO_INTERRUPT_VOUT_OV_MASK );                   


           
        /*****************  Example Configuration for OTP Hysteresis ******************/ 
           
        // Inno3Pro_Write_OTP_Hysteresis        (INNO3PRO_OTP_FAULT_HYST_40DEG);
        // Inno3Pro_Write_OTP_Hysteresis        (INNO3PRO_OTP_FAULT_HYST_60DEG);

           
           
        /*****************  Example Configuration for CV Load  ******************/   
           
        // Inno3Pro_Write_CV_Load               (INNO3PRO_CVLOAD_DEFAULT);
        // Inno3Pro_Write_CV_Load               (INNO3PRO_CVLOAD_RECOMMENDED);           

           
           
        /*****************  Example Configuration for Loop Speed 1 ******************/   
          
        // Inno3Pro_Write_Loop_Speed1           (INNO3PRO_LOOPSPEED1_DEFAULT);                           
           Inno3Pro_Write_Loop_Speed1           (INNO3PRO_LOOPSPEED1_RECOMMENDED);
           
           
           
        /*****************  Example Configuration for Loop Speed 2 ******************/      
           
        // Inno3Pro_Write_Loop_Speed2           (INNO3PRO_LOOPSPEED2_DEFAULT);       
           Inno3Pro_Write_Loop_Speed2           (INNO3PRO_LOOPSPEED2_RECOMMENDED);                
    }        
}


void Inno3Pro_Application::Inno3Pro_Vbus_Switch_Control(bool bEnableVben)
{
    float fEnableVben = 0;
    
    if(bEnableVben)
    {
        fEnableVben = 3; //Vbus ON
    }
    else
    {
        //Set UV to 3V to avoid UV Fault     
        Inno3Pro_Write_Under_Volts(3);
        
        //Set CV to 5V before Opening the VBUS
	    Inno3Pro_Write_Volts(5);
        
        fEnableVben = 0; //Vbus OFF
    }      
    
    Inno3Pro_Encode_Buffer_Parity((uint32_t)Inno3Pro_Compute_VBEN(fEnableVben) ,u8_Buffer_VBEN);		

    //Needed Since When VBEN is OFF, Watchdog is Enabled as Default so  Watchdog must be Re-Disabled
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_WATCHDOG_TIMER  ,u8_Buffer_WATCHDOG_TIMER   ,WR_BYTE);   

    //Initiate VBEN Command
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_VBEN ,u8_Buffer_VBEN ,WR_BYTE); 	
}	


void Inno3Pro_Application::Inno3Pro_Bleeder_Enable(bool bEnable)
{
    uint16_t u16BleederLogic = 0;
    
    if(bEnable)
    {
        u16BleederLogic = 0x01;    //Enable Bleeder   
    }
    else
    {
        u16BleederLogic = 0x00;    //Disable Bleeder   
    }

    //Write the I2C Settings
    Inno3Pro_Encode_Buffer((uint16_t)(u16BleederLogic)  ,u8_Buffer_BLEEDER); 
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS,INNO3PRO_BLEEDER,u8_Buffer_BLEEDER,WR_BYTE); 
}


void Inno3Pro_Application::Inno3Pro_Load_Discharge(bool bEnable)
{
    uint16_t u16VdisLogic = 0;
    
    if(bEnable)
    {
        u16VdisLogic = 0x83;    //Enable 
    }
    else
    {
        u16VdisLogic = 0x8C;    //Disable  
    }

    //Write the I2C Settings
    Inno3Pro_Encode_Buffer((uint16_t)(u16VdisLogic)  ,u8_Buffer_VDIS); 
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS,INNO3PRO_VDIS,u8_Buffer_VDIS,WR_BYTE); 
}


void Inno3Pro_Application::Inno3Pro_TurnOff_PSU(bool bEnable)
{
    uint16_t u16PsuLogic = 0;
    
    if(bEnable)
    {
        u16PsuLogic = 0x01;    //Enable 
    }
    else
    {
        u16PsuLogic = 0x00;    //Disable  
    }

    //Write the I2C Settings
    Inno3Pro_Encode_Buffer((uint16_t)(u16PsuLogic)  ,u8_Buffer_TURN_OFF_PSU); 
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS,INNO3PRO_TURN_OFF_PSU,u8_Buffer_TURN_OFF_PSU,WR_BYTE); 
}


void Inno3Pro_Application::Inno3Pro_FastVI_Disable(bool bDisable)
{
    uint16_t u16FastVI_Logic = 0;
    
    if(bDisable)
    {
        u16FastVI_Logic = 0x01;    //Disable 
    }
    else
    {
        u16FastVI_Logic = 0x00;    //Enable  
    }

    //Write the I2C Settings
    Inno3Pro_Encode_Buffer((uint16_t)(u16FastVI_Logic)  ,u8_Buffer_FAST_VI_CMD); 
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS,INNO3PRO_FAST_VI_CMD,u8_Buffer_FAST_VI_CMD,WR_BYTE); 
}


void Inno3Pro_Application::Inno3Pro_CVOnlyMode_Enable(bool bEnable)
{
    uint16_t u16CvoLogic = 0;
    
    if(bEnable)
    {
        u16CvoLogic = 0x01;    //Disable 
    }
    else
    {
        u16CvoLogic = 0x00;    //Enable  
    }

    //Write the I2C Settings
    Inno3Pro_Encode_Buffer((uint16_t)(u16CvoLogic)  ,u8_Buffer_CVO); 
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS,INNO3PRO_CVO,u8_Buffer_CVO,WR_BYTE); 
}

void Inno3Pro_Application::Inno3Pro_Write_Volts(float fSetPtCV)
{	
    Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_CV(fSetPtCV)   ,u8_Buffer_CV);	
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS   ,INNO3PRO_CV    ,u8_Buffer_CV   ,WR_WORD);   
}	

void Inno3Pro_Application::Inno3Pro_Write_Over_Volts(float fSetPtOVA)
{			
	Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_OV(fSetPtOVA)   ,u8_Buffer_OVA);
	Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS   ,INNO3PRO_OVA    ,u8_Buffer_OVA   ,WR_WORD);   
}

void Inno3Pro_Application::Inno3Pro_Write_Under_Volts(float fSetPtUVA)
{				
	Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_UV(fSetPtUVA)   ,u8_Buffer_UVA);
	Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS   ,INNO3PRO_UVA    ,u8_Buffer_UVA   ,WR_WORD);   
}

void Inno3Pro_Application::Inno3Pro_Write_Cable_Drop_Comp(float fSetPtCDC)
{
    Inno3Pro_Encode_Buffer((uint16_t)Inno3Pro_Compute_CDC(fSetPtCDC) ,u8_Buffer_CDC);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_CDC, u8_Buffer_CDC, WR_WORD);  		
}

void Inno3Pro_Application::Inno3Pro_Write_Amps(float fSetPtCC)
{			
    Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_CC(fSetPtCC)   ,u8_Buffer_CC);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS   ,INNO3PRO_CC    ,u8_Buffer_CC   ,WR_WORD);   
}

void Inno3Pro_Application::Inno3Pro_Write_Volt_Peak(float fSetPtVpk)
{			
    Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_VKP(fSetPtVpk) ,u8_Buffer_VKP);		
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_VKP, u8_Buffer_VKP, WR_WORD);  		
}

void Inno3Pro_Application::Inno3Pro_Write_OVL_Fault_Response(uint16_t u16Response)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Response ,u8_Buffer_OVL);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_OVL, u8_Buffer_OVL, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_UVL_Fault_Response(uint16_t u16Response)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Response ,u8_Buffer_UVL);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_UVL, u8_Buffer_UVL, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_ISSC_Fault_Response(uint16_t u16Response, uint16_t u16Frequency)
{			
    Inno3Pro_Encode_Buffer((uint16_t)(u16Response|(u16Frequency << 2 )),u8_Buffer_ISSC);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_ISSC, u8_Buffer_ISSC, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_CCSC_Fault_Response(uint16_t u16Response)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Response ,u8_Buffer_CCSC);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_CCSC, u8_Buffer_CCSC, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_UVL_Fault_Timer(uint16_t u16Timer)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Timer ,u8_Buffer_UVL_TIMER);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_UVL_TIMER, u8_Buffer_UVL_TIMER, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_Watchdog_Timer(uint16_t u16Timer)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Timer ,u8_Buffer_WATCHDOG_TIMER);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_WATCHDOG_TIMER, u8_Buffer_WATCHDOG_TIMER, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_CVOL_Fault_Response(uint16_t u16Response)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Response ,u8_Buffer_CVOL);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_CVOL, u8_Buffer_CVOL, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_CVOL_Fault_Timer(uint16_t u16Timer)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Timer ,u8_Buffer_CVOL_TIMER);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_CVOL_TIMER, u8_Buffer_CVOL_TIMER, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_Interupt_Mask(uint16_t u16IntMask)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16IntMask ,u8_Buffer_INTERRUPT);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_INTERRUPT, u8_Buffer_INTERRUPT, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_OTP_Hysteresis(uint16_t u16Otp)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Otp ,u8_Buffer_OTP);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_OTP, u8_Buffer_OTP, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_CV_Load(uint16_t u16Load)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16Load ,u8_Buffer_CVLOAD);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_CV_LOAD, u8_Buffer_CVLOAD, WR_BYTE);  		
}

void Inno3Pro_Application::Inno3Pro_Write_Loop_Speed1(uint16_t u16LoopSpeed)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16LoopSpeed ,u8_Buffer_LoopSpeed1);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_LOOP_SPEED_1, u8_Buffer_LoopSpeed1, WR_WORD);  		
}

void Inno3Pro_Application::Inno3Pro_Write_Loop_Speed2(uint16_t u16LoopSpeed)
{			
    Inno3Pro_Encode_Buffer((uint16_t)u16LoopSpeed ,u8_Buffer_LoopSpeed2);
    Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS, INNO3PRO_LOOP_SPEED_2, u8_Buffer_LoopSpeed2, WR_WORD);  		
}

bool Inno3Pro_Application::Inno3Pro_Write_VI(float fSetPtCV, float fSetPtCC)
{    
    //Variable for Controlling the Updates
	static bool bInno3Pro_Allow_Change = false;
    
    //Indicates that Update Process was successful
    static bool bInno3Pro_UpdateDone = false;
    
    //Used for Voltage Direction (Increase or Decrease)    
    static bool b_Volt_Setting    = true; 
  	
    //Initialize CV 
    static float fPrevious_CV = 0;   	  
    
    //Do Not Process Voltage Change Requests Until 
    //the Voltage Transition is Complete
    if(!bInno3Pro_Allow_Change)
    {    	  
        //Check if Voltage Has Changed due to a new CV Request
        //This Determines the Direction of the Voltage Transition
        if (fSetPtCV!= fPrevious_CV)
        {
            //Compare New CV setting to Previous Setting
            if(fSetPtCV > fPrevious_CV)
            {
                b_Volt_Setting = true;   //Increase Voltage
            }
            else
            {
                b_Volt_Setting = false;  //Decrease Voltage
            }        

            //Save the current CV Value
            fPrevious_CV = fSetPtCV;		
        }    
     
        //Start Conversion to Split the Value to LSB and MSB , Implement Parity and Fill up the I2C Buffers  
        Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_CV(   fSetPtCV  )   ,u8_Buffer_CV);
        Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_CC(   fSetPtCC  )   ,u8_Buffer_CC);  

        //Set Over Voltage to 124% of CV
        Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_OV(   fSetPtCV * INNO3PRO_OV_PERCENTAGE_MULT )   ,u8_Buffer_OVA);

        //Set Under Voltage  to 3V
        Inno3Pro_Encode_Buffer_Parity((uint16_t)Inno3Pro_Compute_UV(INNO3PRO_DEFAULT_UVA_SET_PT_LEVEL)   ,u8_Buffer_UVA);   

        //Proceed to New VI Settings, Since Buffers are already Filled           
        bInno3Pro_Allow_Change = true;         
    }
     
    //Implement New VI Settings
	if(bInno3Pro_Allow_Change)		
	{        
        //Auto Disable UVL when less than 3.6V operation
        if(fSetPtCV <= 3.6 )
        {
            //No Response
            Inno3Pro_Encode_Buffer((uint16_t)INNO3PRO_UVL_FAULT_RESPONSE_NORESPONSE ,u8_Buffer_UVL);      
        }
        else
        {
            //Auto Restart
            Inno3Pro_Encode_Buffer((uint16_t)INNO3PRO_UVL_FAULT_RESPONSE_AUTORESTART,u8_Buffer_UVL);  
        }    
	            
        //Voltage Transition was Finished?
		if(Inno3Pro_Process_Voltage(b_Volt_Setting,fSetPtCV) == true)
		{	
            //Accept New Requests
            bInno3Pro_Allow_Change = false;
            
            //Update process complete
            bInno3Pro_UpdateDone = true;            
		}
	}
    
    // Return Status 
    if(bInno3Pro_UpdateDone)
    {
        return true;
    }
    else
    {
        return false;
    }
}



bool Inno3Pro_Application::Inno3Pro_Process_Voltage(bool bVoltIncrease,  float fSetPtCV) 
{
    //Control Variables
    static bool bControlFlag_Increase = false;
    static bool bVoutpct_Ok_Increase = false;
    
    static bool bControlFlag_Decrease= false;
    static bool bVoutpct_Ok_Decrease = false;
    
    //Voltage Increase Routine
    if(bVoltIncrease)
    {
        //Initial Command Sequence
        if(!bControlFlag_Increase)
        {
          //Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_UVL ,u8_Buffer_UVL ,WR_BYTE);  			
            Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_CC  ,u8_Buffer_CC  ,WR_WORD); 
            Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_OVA ,u8_Buffer_OVA ,WR_WORD);
            Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_CV  ,u8_Buffer_CV  ,WR_WORD);     

            //Debug Pin 
            //digitalWrite(LED_BUILTIN, 0); 
            
            bControlFlag_Increase = true;
        }
        
        if(bControlFlag_Increase)
        {
            //Check If Vout already reached 90% of the desired Set Point
            if(Inno3Pro_Read_Volts() >(fSetPtCV * 0.9))
            {
                //Debug Pin  
				//digitalWrite(LED_BUILTIN, 1);                    

                //UVA must be written only after New Voltage Setpoint was reached
                Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_UVA ,u8_Buffer_UVA  ,WR_WORD);

                bVoutpct_Ok_Increase = true;                 
            }  
        }
        
        //New Set Point Was Reached
        if(bVoutpct_Ok_Increase) 
        {
            //Reset all variables
            bControlFlag_Increase = false;
            bVoutpct_Ok_Increase = false;
            return true;
        }          
		else
		{
			return false;
		}               
    }
    else //Voltage Decrease Routine
    {
        if(!bControlFlag_Decrease)
        {
          //Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_UVL ,u8_Buffer_UVL  ,WR_BYTE);			
	        Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_CC  ,u8_Buffer_CC   ,WR_WORD);    
	        Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_UVA ,u8_Buffer_UVA  ,WR_WORD);             
	        Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_CV  ,u8_Buffer_CV   ,WR_WORD);    

	        // Immediately Executed after CV                                   
	        // Turn on Bleeder
	        Inno3Pro_Bleeder_Enable(true);  
            
            bControlFlag_Decrease = true;
			 
            //Debug Pin 
            //digitalWrite(LED_BUILTIN, 0);    			 
        }
        
        //Bleeder Turn Off Control
        if(bControlFlag_Decrease)
        {  
            if(!Inno3Pro_Read_Status_Vout2pct())
            {
                //Debug Pin  
				//digitalWrite(LED_BUILTIN, 1);                    

                //Disable Bleeder 
                Inno3Pro_Bleeder_Enable(false); 

                //OVA must be after Bleeder Turn Off to avoid OVP trigger
                Inno3ProSend.I2C_Write16(INNO3PRO_ADDRESS  ,INNO3PRO_OVA ,u8_Buffer_OVA ,WR_WORD); 

                bVoutpct_Ok_Decrease = true;            
            }
        }    

        //New Set Point Was Reached
        if(bVoutpct_Ok_Decrease) 
        {
            //Reset all variables
            bControlFlag_Decrease = false;
            bVoutpct_Ok_Decrease = false;
            return true;
        }  
		else
		{
			return false;
		}   		
    }                         
}


///@}	// end of InnoSwitch3-Pro  API Write Functions




 /** 
	@name   Common API Telemetry Functions
	@brief	These functions are used as base for
            the main API Read functions
 */
///@{ 
uint16_t Inno3Pro_Application::Inno3Pro_Telemetry(uint8_t ReadBack_Address)
{
	uint16_t u16TempRead = 0;
	u16TempRead = Inno3ProSend.I2C_Read16(INNO3PRO_ADDRESS,ReadBack_Address);
	return u16TempRead;
}

bool Inno3Pro_Application::Inno3Pro_Read_Bit(uint8_t ReadBack_Address, uint8_t Bit)
{
	uint16_t u16TempRead = 0;
	u16TempRead = Inno3ProSend.I2C_Read16(INNO3PRO_ADDRESS,ReadBack_Address);
    
    if(test_bit(u16TempRead,Bit))
    {
        return true;
    }
    else
    {
        return false;
    }        
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_Byte(uint8_t ReadBack_Address, bool bHighByte)
{
	uint16_t u16TempRead = 0;
	u16TempRead = Inno3ProSend.I2C_Read16(INNO3PRO_ADDRESS,ReadBack_Address);
       
    if(bHighByte)
    {
        return (u16TempRead & 0xFF00)>>8;
    }
    else
    {
        return (u16TempRead & 0xFF);
    }        
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_2Bits(uint8_t ReadBack_Address, uint8_t u8ShiftCnt)
{
	uint16_t u16TempRead = 0;
	u16TempRead = Inno3ProSend.I2C_Read16(INNO3PRO_ADDRESS,ReadBack_Address);       

    return ((u16TempRead >> u8ShiftCnt)& 0x03) ;     
}

float Inno3Pro_Application::Inno3Pro_Read_SetPoint(uint16_t ReadBack_Address , float fMultiplier)
{
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;    

    u16TempReadValue = Inno3Pro_Telemetry(ReadBack_Address); 
                        //MSB                             //LSB
    u16ConvertedValue = ((u16TempReadValue & 0x7F00)>>1) + (u16TempReadValue & 0x7F);
   
    return (float) (u16ConvertedValue / fMultiplier);   
}

///@}	// end of InnoSwitch3-Pro  Common Telemetry Functions


 /** 
	@name   Read1 - Main API Telemetry Functions
	@brief	Telemetry API for Read1 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_CV_SetPoint(void)
{
    // Read1, Output Voltage Set-Point
    return (float)(Inno3Pro_Read_SetPoint(INNO3PRO_READ1,INNO3PRO_CV_SET_PT_MULT));
}
///@}	// End of Read1 API Telemetry Functions


 /** 
	@name   Read2 - Main API Telemetry Functions
	@brief	Telemetry API for Read2 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_UV_Threshold(void)
{
    // Read2, Under Voltage Threshold
    return (float)(Inno3Pro_Read_SetPoint(INNO3PRO_READ2,INNO3PRO_UV_SET_PT_MULT)); 
}
///@}	// End of Read2 API Telemetry Functions


 /** 
	@name   Read3 - Main API Telemetry Functions
	@brief	Telemetry API for Read3 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_OV_Threshold(void)
{
    // Read3, Over Voltage Threshold
    return (float)(Inno3Pro_Read_SetPoint(INNO3PRO_READ3,INNO3PRO_OV_SET_PT_MULT));    
}
///@}	// End of Read3 API Telemetry Functions



 /** 
	@name   Read4 - Main API Telemetry Functions
	@brief	Telemetry API for Read4 
 */
///@{ 
bool Inno3Pro_Application::Inno3Pro_Read_VbusSwitch(void)
{
    // Read4, VBUS Switch Enable
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_VBEN);
}

bool Inno3Pro_Application::Inno3Pro_Read_Bleeder(void)
{
    // Read4, Minimum Load (Bleeder)
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_BLEEDER);
}

bool Inno3Pro_Application::Inno3Pro_Read_PsuOff(void)
{
    // Read4, Turn PSU Off   
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_PSUOFF);
}

bool Inno3Pro_Application::Inno3Pro_Read_FastVI(void)
{
    // Read4, Fast VI Commands 
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_FSTVIC);
}

bool Inno3Pro_Application::Inno3Pro_Read_CvoMode(void)
{
    // Read4, Constant-Voltage Mode Only   
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_CVO);
}

bool Inno3Pro_Application::Inno3Pro_Read_OtpFaultHyst(void)
{
    // Read4, Secondary Over-Temperature Protection Fault Hysteresis
    return Inno3Pro_Read_Bit(INNO3PRO_READ4,READ4_Reg_OTP);
}

float Inno3Pro_Application::Inno3Pro_Read_Cable_Drop_Comp(void)
{
    // Read4, Cable Drop Compensation
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;    

    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ4); 
    
    //Get Lower Nibble of LSB
    u16ConvertedValue = (u16TempReadValue & 0x000F);
   
    return (float) (u16ConvertedValue * INNO3PRO_CDC_SET_PT_DIV);       
}
///@}	// End of Read4 API Telemetry Functions



 /** 
	@name   Read5 - Main API Telemetry Functions
	@brief	Telemetry API for Read5 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_CC_SetPoint(void)
{
    // Read5, Constant Current Set-Point
    uint16_t u16TempReadValue = 0; 
    
    u16TempReadValue = Inno3Pro_Read_Byte(INNO3PRO_READ5,RD_MSB);  
    
    return (float)( (u16TempReadValue * INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE)/(INNO3PRO_RSENSE * INNO3PRO_ADC_FULL_RANGE) ); 
}

float Inno3Pro_Application::Inno3Pro_Read_CP_Threshold(void)
{
    // Read5, Constant Power Threshold 
    uint16_t u16TempReadValue = 0; 
    
    u16TempReadValue = Inno3Pro_Read_Byte(INNO3PRO_READ5,RD_LSB);  
    
    return (float) (u16TempReadValue / INNO3PRO_VKP_SET_PT_MULT );             
}
///@}	// End of Read5 API Telemetry Functions



 /** 
	@name   Read6 - Main API Telemetry Functions
	@brief	Telemetry API for Read6 
 */
///@{ 
uint8_t Inno3Pro_Application::Inno3Pro_Read_OV_Fault_Response(void)
{
    // Read6, Over Voltage Fault Response
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_OV_FAULT_BITSHIFT);    
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_UV_Fault_Response(void)
{
    // Read6, Under Voltage Fault Response
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_UV_FAULT_BITSHIFT);    
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_IsPinShort_Fault_Response(void)
{
    // Read6, IS-pin Short Fault Response and Detection Frequency
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_ISSC_SHORT_BITSHIFT);   
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_UV_Fault_Timer(void)
{
    // Read6, Under Voltage Timer
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_UVL_TIMER_BITSHIFT);   
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_Watchdog_Timer(void)
{
    // Read6, Watchdog Timer
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_WATCHDOG_TIMER_BITSHIFT);  
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_CvMode_Fault_Response(void)
{
    // Read6, Constant Voltage Mode Fault Response
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_CV_MODE_BITSHIFT);     
}

uint8_t Inno3Pro_Application::Inno3Pro_Read_CvMode_Timer(void)
{
    // Read6, CV Mode Timer
    return Inno3Pro_Read_2Bits(INNO3PRO_READ6,INNO3PRO_READ_CV_MODE_TIMER_BITSHIFT);    
}
///@}	// End of Read6 API Telemetry Functions



 /** 
	@name   Read7 - Main API Telemetry Functions
	@brief	Telemetry API for Read7 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_Amps(void)
{
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;
    
    // Read7, Measured Output Current
    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ7); 

    //Bit Manipulation:  MSB- Clear the Bit [15:9]            LSB - Clear bit 7 (Parity)
    u16ConvertedValue = ((u16TempReadValue & 0x0100) >> 1) + (u16TempReadValue & 0x7F);
            
    //Sensed Current Value = N (Decimal) x 32 / (Rsense * 128)
    //Calculate Reading:  
    //Sensed Current Value = (58 x 32) / (5 * 128 ) =  2.9 Amps
    return (float)  (  (u16ConvertedValue * INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE)/
                       (INNO3PRO_RSENSE * INNO3PRO_ADC_FULL_RANGE)
                    );   
}
///@}	// End of Read7 API Telemetry Functions


 /** 
	@name   Read9 - Main API Telemetry Functions
	@brief	Telemetry API for Read9 
 */
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_Volts(void)
{
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;

    // Read9, Measured Output Voltage
    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ9); 
	 
    //Bit Manipulation:  Clear the Bit[15:12] , use Bit [11:0] 
    u16ConvertedValue = (u16TempReadValue & 0x0FFF);
            
    //Calculate Reading - 1F4 Hex -> 500 Decimal , 500 / 100 = 5V
    return (float) (u16ConvertedValue / INNO3PRO_CV_SET_PT_MULT);   
}
///@}	// Read8 API Telemetry Functions



 /** 
	@name   Read10 - Main API Telemetry Functions
	@brief	Telemetry API for Read10 
 */
///@{ 
bool Inno3Pro_Application::Inno3Pro_Read_Status_InterruptEnable(void)
{
    // Read10, Interrupt Enable
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_INTERRUPT_EN);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_SystemReady(void)
{
    // Read10, System Ready Signal
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_CONTROL_S);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_OutputDischarge(void)
{
    // Read10, Output Discharge
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_VDIS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_HighSwitchFreq(void)
{
    // Read10, System Ready Signal
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_HIGH_FSW);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_OtpFault(void)
{
    // Read10, Secondary Over-Temperature Protection Fault 
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_OTP);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_Vout2pct(void)
{
    // Read10, 2% Bleeder Enabled
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_VOUT2PCT);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_Vout10pct(void)
{
    // Read10, VOUTADC > 1.1*Vout
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_VOUT10PCT);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_IsPinShort(void)
{
    // Read10, IS-pin Short Circuit Detected
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_ISSC);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_UV_Fault(void)
{
    // Read10, Output Voltage UV Fault
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_VOUT_UV);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_OV_Fault(void)
{
    // Read10, Output Voltage OV Fault
    return Inno3Pro_Read_Bit(INNO3PRO_READ10,READ10_Reg_VOUT_OV);
}
///@}	// End of Read10 API Telemetry Functions



 /** 
	@name   Read11 - Main API Telemetry Functions
	@brief	Telemetry API for Read11 
 */
///@{ 
bool Inno3Pro_Application::Inno3Pro_Read_Status_CvoMode_AR(void)
{
    // Read11, CVO Mode Auto Restart
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_ar_CV);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_IsPinShort_AR(void)
{
    // Read11, IS-pin Short Circuit Auto Restart
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_ar_ISSC);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_OV_AR(void)
{
    // Read11, Output Voltage OV Auto Restart
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_ar_CCSC);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_UV_AR(void)
{
    // Read11, Output Voltage UV Auto Restart
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_ar_VOUT_OV);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_LatchOff(void)
{
    // Read11, Latch-Off (LO) Occurred
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_LO);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_CvoMode_LO(void)
{
    // Read11, CVO Mode Latch Off 
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_Lo_CVO);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_PsuOffCmd(void)
{
    // Read11, PSU Turn-Off CMD Received
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_PSUOFF);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_IsPinShort_LO(void)
{
    // Read11, IS-pin Short Circuit Latch Off
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_Lo_ISSC);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_OV_LO(void)
{
    // Read11, Output Voltage OV Latch Off
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_Lo_VOUT_OV);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_UV_LO(void)
{
    // Read11, Output Voltage UV Latch Off
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_Lo_VOUT_UV);
}

bool Inno3Pro_Application::Inno3Pro_Read_Status_BPS_LO(void)
{
    // Read11, BPS-pin Latch Off
    return Inno3Pro_Read_Bit(INNO3PRO_READ11,READ11_Reg_BPS_OV);
}
///@}	// End of Read11 API Telemetry Functions


/** 
   @name    Read12 - Main API Telemetry Functions
   @brief	Telemetry API for Read12 
*/
///@{ 
bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_CntrlSecondary(void)
{
    // Read12, Interrupt Mask Control Secondary
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_CONTROL_S_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_BpsCurrentLo(void)
{
    // Read12, Interrupt Mask BPS Current Latch-off
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_LO_Fault_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_CvoPkLoadTimer(void)
{
    // Read12, Interrupt Mask CVO Mode Peak load timer
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_CCAR_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_IsPinShort(void)
{
    // Read12, Interrupt Mask IS-pin Short
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_ISSC_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_UV(void)
{
    // Read12, Interrupt Mask Vout(UV)
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_VOUT_UV_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Mask_OV(void)
{
    // Read12, Interrupt Mask Vout(OV)
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_VOUT_OV_MASK);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_CntrlSecondary(void)
{
    // Read12, Interrupt Status Control Secondary
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_CONTROL_S_STATUS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_BpsCurrentLo(void)
{
    // Read12, Interrupt Status BPS Current Latch-off
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_LO_FAULT_STATUS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_CvoPkLoadTimer(void)
{
    // Read12, Interrupt Status CVO Mode Peak load timer
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_CCAR_STATUS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_IsPinShort(void)
{
    // Read12, Interrupt Status IS-pin Short
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_ISSC_STATUS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_UV(void)
{
    // Read12, Interrupt Status Vout(UV)
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_VOUT_UV_STATUS);
}

bool Inno3Pro_Application::Inno3Pro_Read_Interrupt_Stat_OV(void)
{
    // Read12, Interrupt Status Vout(OV)
    return Inno3Pro_Read_Bit(INNO3PRO_READ12,READ12_Reg_VOUT_OV_STATUS);
}
///@}	// End of Read12 API Telemetry Functions


/** 
   @name    Read13 - Main API Telemetry Functions
   @brief	Telemetry API for Read13 
*/
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_AmpsAverage(void)
{
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;
    
    //Read13, Average Output Current
    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ13); 

    //Bit Manipulation:  Clear the MSB , use LSB only - Bit[7:0]  
    u16ConvertedValue = (u16TempReadValue & 0x00FF);
            
    //Sensed Current Value = N (Decimal) x 32 / (Rsense * 128)
    //Calculate Reading:  
    //Sensed Current Value = (58 x 32) / (5 * 128 ) =  2.9 Amps
    return (float)  (  (u16ConvertedValue * INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE)/
                       (INNO3PRO_RSENSE * INNO3PRO_ADC_FULL_RANGE)
                    );   
}
///@}	// End of Read13 API Telemetry Functions


/** 
   @name    Read14 - Main API Telemetry Functions
   @brief   Telemetry API for Read14 
*/
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_VoltsAverage(void)
{
    uint16_t u16TempReadValue = 0;
    uint16_t u16ConvertedValue = 0;

    //Read14, Average Output Voltage
    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ14); 
	 
    //Bit Manipulation:  Clear high nibble of MSB - Bit[15:12] , use Bit [11:0]             
    u16ConvertedValue = (u16TempReadValue & 0x0FFF);
            
    //Calculate Reading - 1F4 Hex -> 500 Decimal , 500 / 100 = 5V
    return (float) (u16ConvertedValue / INNO3PRO_CV_SET_PT_MULT);       
}
///@}	// End of Read14 API Telemetry Functions


/** 
   @name    Read15 - Main API Telemetry Functions
   @brief	Telemetry API for Read15 
*/
///@{ 
float Inno3Pro_Application::Inno3Pro_Read_Voltage_DAC(void)
{
    uint16_t u16TempReadValue = 0;
    float fVoutConvValue = 0;
    
    // Read15, Voltage DAC, DAC_100mV[15:8],DAC_10mV[7:0]
    //VOUT = 5 V + (MSB * 100 mV) ? (LSB * 10 mV).
    //READ15 (0x5C): MSB = 0x00, LSB = 0x0E
    //VOUT = 5 ? (14 * 10 mV) = 4.86 V
    u16TempReadValue = Inno3Pro_Telemetry(INNO3PRO_READ15); 

    //                    //CV Set Point   //MSB                             //LSB
    fVoutConvValue =       5   +  (((u16TempReadValue & 0xFF00)>>8)*0.1)  - ((u16TempReadValue & 0xFF)*0.01);

    return (float)  (fVoutConvValue);   
}
///@}	// End of Read15 API Telemetry Functions


