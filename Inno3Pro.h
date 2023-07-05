/**	
	@file		Inno3Pro.h
	
    @brief 		This is the header file containing the InnoSwitch3-Pro  I2C Settings and Control.
				Includes API for computations related to configuring InnoSwitch3-Pro  Registers 
				and Functions to Control the InnoSwitch3-Pro  IC.	

    @author     CS - PIPH Applications
     
	@date 	    August 3, 2018  

    Copyright (C) 2018 Power Integrations. All rights reserved.

    This software, including source code, documentation and related materials, is owned 
    by Power Integrations.You may use this software, and any derivatives created 
    by any person or entity by or on your behalf, exclusively with Power Integrations' 
    products. Power Integrations reserves the right to make changes to the Software 
    without notice.Power Integrations does not assume any liability arising 
    out of the use of the Software.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    - Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY POWER INTEGRATIONS "AS IS" AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
    BUT NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,INTELLECTUAL 
    PROPERTY RIGHTS; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
     
 */
 
#ifndef INNO3PRO_H
#define	INNO3PRO_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

 #include <Wire.h>
 #include <Config.h>



// library interface details 
class Inno3Pro_Application
{
  // user-accessible "public" interface
  public:
	     /** @name InnoSwitch3-Pro  Flags
		  
		  @brief
		  Example Flags Used for Application specific routines

		  @details 
		  Used for Specific InnoSwitch3-Pro  Routines

		 */
		///@{

		bool b_Lock_Timer_Is_Running  = false;   	//Sample Flag Used In Main Application Code - Can be used For Buttons
		bool b_Lock_Enable            = false;   	//Sample Flag Used in Main Application Code - Can be used For Buttons
        bool b_Setting_Update         = false;   	//Sample Flag for Updating the Buffers        
        bool b_Request_Enable         = false;   	//Sample Flag for Updating the Buffers
		
		///@}	// end of InnoSwitch3-Pro Application specific Flags

			
        /** 
            @name   API Write Functions
            @brief	Application Programming Interface to control InnoSwitch3-Pro
         */
        ///@{ 

        
		/**
			@brief
				Handles all Common I2C Configurations to be				
				written to InnoSwitch3-Pro  as initialization

			@details 
				This Reads the InnoSwitch3-Pro System Ready Signal to check
				if InnoSwitch3-Pro  is ready to communicate. Once InnoSwitch3-Pro  
				is ready ,This function configures the Initial registers needed
                for operation.        
			
			@details 
				Needs to be called on the beginning to Initialize InnoSwitch3-Pro  
                Settings			
		 
			@param
				None
		 
			@returns
				None
		*/
		void Inno3Pro_Initialization(void);

        
		/**
			@brief
				 Vbus Switch Control (VBEN Control)

			@details 
				Used to Enable or Disable Vbus Switch By Writing a value to 
                VBEN Register. This also Contains computations for VBEN settings             
         		 
			@note
                When VBEN is Disabled, Watchdog is Enabled As Default
				so Watchdog Timer is needed to be Disabled again							
				
                Before Disabling the Vbus Switch,  UV is set to 3V and
                then CV is programmed  to 5V to avoid inadvertent 
                triggering of OV fault.
         
			@param
				fEnableVben - Value to Enable VBEN          
         
                <b> Input Values: </b>
                    - False:   Disable VBEN  
                    - True :   Enable VBEN
		 
			@returns
				None				
		
		*/
		void Inno3Pro_Vbus_Switch_Control(bool bEnableVben);
      
        
		/**
			@brief
				Handles Bleeder Setting

			@details 
				This function Writes to bleeder  register.
                The BLEEDER register must not be enabled for extended period of
                time to prevent excessive power dissipation in the controller
				
			@param
				bEnable - Value to Enable Bleeder
     
                <b> Input Values: </b>
                    - False:   Disable Bleeder  
                    - True :   Enable Bleeder  
         
			@returns
                None
		*/			        
        void Inno3Pro_Bleeder_Enable(bool bEnable);
        
        
		/**
			@brief
                Activates Vbus Load Discharge 

			@details 
				This function Writes to Load Discharge  register.

            @note
                 Enabling the VDIS register will automatically disable the VBEN
                 register
         
			@param
				bEnable - Value to Enable Load Discharge
         
                <b> Input Values: </b>
                    - False:   Disable Load Discharge  
                    - True :   Enable Load Discharge       
             
			@returns
                None
		*/			        
        void Inno3Pro_Load_Discharge(bool bEnable);   

        
		/**
			@brief
                Turns off the power supply

			@details 
				This function puts the device into latch off

            @note
                 AC power cycling is required to restart the
                 power supply.
         
			@param
				bEnable - Value to Turn off the power supply
         
                <b> Input Values: </b>
                    - False:   Disable Turn Off    
                    - True :   Enable Turn Off     
             
			@returns
                None
		*/        
        void Inno3Pro_TurnOff_PSU(bool bEnable);
        
        
		/**
			@brief
                CV and CC Commands speed limit

			@details 
				This function limits the maximum speed (10ms) in which CV
                and CC commands can be sent to the device.

            @note
                Speed limit can be removed as needed
         
			@param
				bEnable - Value to Set the Speed Limit
         
                <b> Input Values: </b>
                    - False:   10ms Update Limit Enabled   
                    - True :   No Speed Limit    
             
			@returns
                None
		*/             
        void Inno3Pro_FastVI_Disable(bool bDisable);
        
        
		/**
			@brief
                Constant voltage only mode

			@details 
				This function sets the device to constant voltage
                only and have no constant current regulation mode.

                Once the load current exceeds the programmed current, 
                fault setting is activated after CVOL timer expires
         
			@param
				bEnable - Value to  enable CVO mode
         
                <b> Input Values: </b>
                    - False:   CV and CC Enabled
                    - True :   CV Only Mode/No CC     
             
			@returns
                None
		*/          
        void Inno3Pro_CVOnlyMode_Enable(bool bEnable);
        
                
		/**
			@brief
				Output Voltage Control without Bleeder Control

			@details 				
				Used to update the Value of CV Register  
         
			@param
				fSetPtCV - Output Voltage Set Point Value
         
            <b> CV Range:  </b>
			 -  3 to 24 V (in 10mv Step)
						
            @returns
				None
		*/        
		void Inno3Pro_Write_Volts(float fSetPtCV);
               
                
		/**
			@brief
				Over Voltage Protection 

			@details 				
				Used to update the Value of OVA Register  													
			
			@param
				fSetPtOVA - Over Voltage (OVA) Set Point Value
          
            <b> OVA Range:  </b>
			 -  6.2V to 25 V (in 100mv Step)        
         						
            @returns
				None
		*/         
		void Inno3Pro_Write_Over_Volts(float fSetPtOVA);
        
        
		/**
			@brief
				Under Voltage Protection 

			@details 				
				Used to update the Value of UVA Register  													
			
			@param
				fSetPtUVA - Over Voltage (UVA) Set Point Value
          
            <b> UVA Range:  </b>
			 -  3V to 24 V (in 100mv Step)           
         						
            @returns
				None
		*/               
		void Inno3Pro_Write_Under_Volts(float fSetPtUVA); 
        
        
		/**
			@brief
				Cable Drop Compensation (CDC) Control

			@details 
				Used to update the Value of CDC Register.
                Contains computations for CDC settings
         
			@param	
					fSetPtCDC - Cable Drop Compensation (CDC) Set Point Value
         
            <b> CDC Range:  </b>
			 -  0 to 600 mv (in 50mv Step)  
         		 
			@returns
				None
		*/
		void Inno3Pro_Write_Cable_Drop_Comp(float fSetPtCDC);


		/**
			@brief
				Constant Current (CC) Control

			@details 				
				Used to update the Value of CC Register  													

			@param
				fSetPtCC - Constant Current (CC) Set Point Value
          
            <b> CC Range:  </b>
			 -  20% to 100%       
        
            @returns
				None
		*/        
		void Inno3Pro_Write_Amps(float fSetPtCC);

        
		/**
			@brief
				Constant Output Power Voltage Threshold (VKP) Control

			@details 
				Used to update the Value of VKP Register.
                Contains computations for VKP settings
				
			@param
				fSetPtVpk - Value to Enable VBEN
				VKP Range:  
		 
            <b> VKP Range:  </b>
			 -  5.3V  to  24V  (in 100mV step)
                  
			@returns
				None
		*/
		void Inno3Pro_Write_Volt_Peak(float fSetPtVpk);
		        
        
		/**
			@brief
                Over Voltage Fault Response Setting

			@details 
                Defines how the device will respond to 
                Over Voltage fault condition 
				
			@param
				u16Response - Fault Response setting of the Device
		 
			@returns
				None                  
		*/        
		void Inno3Pro_Write_OVL_Fault_Response(uint16_t u16Response);
        
                
		/**
			@brief
                Under Voltage Fault Response Setting

			@details 
                Defines how the device will respond to 
                Under Voltage fault condition 
				
			@param
				u16Response - Fault Response setting of the Device
		 
			@returns
				None
		*/           
        void Inno3Pro_Write_UVL_Fault_Response(uint16_t u16Response);
                
        
		/**
			@brief
                IS Pin Short Fault Response Setting

			@details 
                Defines how the device will respond to 
                IS pin Short fault condition                                          
        	
            @note                  			
                ISSC fault is annunciated in the event the IS pin voltage
                does not exceed approximately 50% of the full constant-current 
                threshold (ISV(TH)) with a switching frequency exceeding a 
                programmed threshold. The switching frequency can be selected 
                in a range from 30 to 60 kHz.

			@param
				u16Response  - Fault Response setting of the Device
                u16Frequency - Switching frequency threshold
		 
			@returns
				None
		*/           
        void Inno3Pro_Write_ISSC_Fault_Response(uint16_t u16Response, uint16_t u16Frequency);

        /**
         * @brief 
		 * 	Output Short-Circuit Fault Detection
		 * 
		 * @details
		 * 	The CCSC register can be programmed to have
		 * 	response of a (a.) No Fault or (b.) Auto-Restart. The default response
		 *	for this command register is Auto-restart.  
         * @note
		 * 
         * @param 
		 * 		u16Response - Fault Response setting of the Device
         */
        void Inno3Pro_Write_CCSC_Fault_Response(uint16_t u16Response);
		/**
			@brief
                Under Voltage Fault Timer Setting

			@details 
                Defines the duration of how long the device will
                continue to operate before triggering UVL fault 
				
			@param
				u16Timer - Delay Time before fault is asserted
		 
			@returns
				None
		*/            
        void Inno3Pro_Write_UVL_Fault_Timer(uint16_t u16Timer);
                
        
		/**
			@brief
                Watchdog Timer Setting

			@details 
                Defines the duration of how long the device will
                continue to operate before triggering Watchdog fault 
				
			@param
				u16Timer - Delay Time before fault is asserted
		 
			@returns
				None
		*/             
        void Inno3Pro_Write_Watchdog_Timer(uint16_t u16Timer);
                
        
		/**
			@brief
               CV Only Fault Response Setting

			@details 
                Defines how the device will respond to 
                CV Only fault condition 
				
			@param
				u16Response - Fault Response setting of the Device
		 
			@returns
				None
		*/           
        void Inno3Pro_Write_CVOL_Fault_Response(uint16_t u16Response);
        
                
		/**
			@brief
                CV Only Fault Timer Setting

			@details 
                Defines the duration of how long the device will
                continue to operate before triggering CVOL fault 
				
			@param
				u16Timer - Delay Time before fault is asserted
		 
			@returns
				None
		*/        
        void Inno3Pro_Write_CVOL_Fault_Timer(uint16_t u16Timer);
        
        
		/**
			@brief
                Interrupt Mask Setting

			@details 
                This defines the setting of the Active 
                interrupt reporting scheme on the SCL Pin.
                 
			@note
                The Interrupt Mask Register  must be enabled for each of the 
                individual fault conditions to activate this feature. \n
         
                Once a fault occurs, the Interrupt Mask is reset and the
                particular faults of interest must be re-enabled to activate 
                the SCL reporting scheme.     
         	
			@param
				u16IntMask - Interrupt Bit Mask Settings
		 
			@returns
				None
		*/                            
        void Inno3Pro_Write_Interupt_Mask(uint16_t u16IntMask);
        
                
		/**
			@brief
                Over Temperature Setting

			@details 
                Defines the temperature when bleeder can be re-enabled
		
            @note 		
                As secondary controller die temperature increases 
                beyond ~125 Degrees Celsius, the active VOUT pin bleeder 
                function will be turned off. The bleeder will not be permitted 
                to be re-enabled until the controller temperature falls
                below the programmable hysteresis value.         
         
			@param
				u16Otp - Over Temperature Hysteresis Setting
		          
			@returns
				None
		*/         
        void Inno3Pro_Write_OTP_Hysteresis(uint16_t u16Otp);
        
        
		/**
			@brief
                Constant Voltage Load setting

			@details 
                Optimization feature for CV type of Load
		
            @note 		
                The constant current regulation mode in the InnoSwitch3-Pro 
                can be optimized for constant voltage (CV) type load required
                by the end application. Enabling this command register reduces 
                the output current ripple for CV load only. This setting should 
                only be used if CV load must be supported.      
         
			@param
				u16Load - Value of CV load Register
		          
			@returns
				None
		*/            
        void Inno3Pro_Write_CV_Load(uint16_t u16Load);
        
                
		/**
			@brief
                Loop Speed 1 Setting

			@details 
                Optimization feature for Transient Response
		
            @note 		
                If faster transient response is required in the application the
                InnoSwitch3-Pro includes command registers to reduce the time
                for low to high output voltage transitions. \n
         
                Using values other than the default or recommended settings 
                could lead to oscillatory behavior.  
                 
			@param
				u16LoopSpeed - Value of u16Loop Speed 1
		          
			@returns
				None
		*/         
        void Inno3Pro_Write_Loop_Speed1(uint16_t u16LoopSpeed);        
        
        
		/**
			@brief
                Loop Speed 2 Setting

			@details 
                Optimization feature for Transient Response
		
            @note 		
                If faster transient response is required in the application the
                InnoSwitch3-Pro includes command registers to reduce the time
                for low to high output voltage transitions. \n
         
                Using values other than the default or recommended settings 
                could lead to oscillatory behavior.  
                 
			@param
				u16LoopSpeed - Value of u16Loop Speed 2
		          
			@returns
				None
		*/                
        void Inno3Pro_Write_Loop_Speed2(uint16_t u16LoopSpeed);
                
        
		/**
			@brief
				Output Voltage Control with Bleeder Control and  
                Constant Current (CC) Control
                
			@details 	
				Used to update the Value of CV and CC Register. \n  
				Automatically computes for UVA and OVA settings 
                - OVA  is 124% of CV Setpoint
                - UVA is Fixed to 3V setting
               
         	@details 
                UVL is set to "No Response" by this function when CV setting is 
                lesser than 3.6V and UVL is set back to "Auto Restart" when CV 
                setting crosses 3.6V. This UVL feature is optional and currently 
                commented on the code.
         													
				This function stores the old values it received. 
				If the Input parameters is the same with the previous 
				it will not execute the I2C Commands		
			
            @note
                Transition time of High voltage to Low voltage (e.g 20V to 5V at No load)
                may take some time(in ms). It is recommended that voltage updates using 
                this function must only be done after the update request was finished.
                When this function is used but the voltage transition is not yet complete
                the incoming update will not be processed.
         
			@param
				fSetPtCV - Output Voltage Set Point Value
         
            <b> CV Range:  </b>
			 -  3 to 24 V (in 10mv Step)          
				
			@param
				fSetPtCC - Constant Current (CC) Set Point Value
         
            <b> CC Range:  </b>
			 -  20% to 100%              
			
            @returns
                True   - Update process complete \n
                False  - Update process not yet complete
		*/
		bool Inno3Pro_Write_VI(float fSetPtCV, float fSetPtCC);
        

		/**
			@brief
				Handles Command Sequences for Voltage Increment/Decrement 

			@details 
				This function follows a certain sequence of commands in order to
                avoid inadvertent triggering of UV or OV faults				
		 
			@param
				bVoltIncrease - True or False Value to Increase or Decrease Voltage
                fSetPtCV - Output Voltage Set Point Value
         
			@returns
				True  - I2C commands are successfully written 
		*/
		bool Inno3Pro_Process_Voltage(bool bVoltIncrease,  float fSetPtCV); 
			
        ///@}	// end of InnoSwitch3-Pro  API Write Functions  
        
        
        
        /** 
           @name   Common API Telemetry Functions
        */
        ///@{  
        
  		/**
			@brief
				Handles InnoSwitch3-Pro Common I2C Read Back Telemetry

			@details 
				This function Reads the Specific  InnoSwitch3-Pro  Telemetry register

			@pre 				
				I2C_Read16()   Driver should be already Configured and is  able to Read I2C commands
		 
			@param
				ReadBack_Address - Read Back Register Address
		 
			@returns
				Register Reading 
		*/
		uint16_t Inno3Pro_Telemetry(uint8_t ReadBack_Address);
				
        
  		/**
			@brief
				Handles InnoSwitch3-Pro I2C Read Bit 

			@details 
				This function Reads the Specific  Bit of each  Telemetry register

			@pre 				
				I2C_Read16()   Driver should be already Configured and is  able to Read I2C commands
		 
			@param
				ReadBack_Address - Read Back Register Address
                Bit - Bit Count of the Register to Read
		 
			@returns
				Bit Reading 
		*/        
        bool Inno3Pro_Read_Bit(uint8_t ReadBack_Address, uint8_t Bit);
		
        
  		/**
			@brief
				Handles InnoSwitch3-Pro I2C Read Byte 

			@details 
				This function Reads the LSB or MSB of each  Telemetry register

			@pre 				
				I2C_Read16()   Driver should be already Configured and is  able to Read I2C commands
		 
			@param
				ReadBack_Address - Read Back Register Address
                bHighByte - Selects the LSB or MSB of the Register to Read
		 
			@returns
				Byte Reading 
		*/           
        uint8_t Inno3Pro_Read_Byte(uint8_t ReadBack_Address, bool bHighByte);
		
           
  		/**
			@brief
				Handles InnoSwitch3-Pro I2C Read 2 Bitss 

			@details 
				This function Reads to 2 Bits of each  Telemetry register 

			@pre 				
				I2C_Read16()   Driver should be already Configured and is  able to Read I2C commands
		 
			@param
				ReadBack_Address - Read Back Register Address
                u8ShiftCnt -Number of Right Shift applied to the reading
		 
			@returns
				Byte Reading 
		*/            
        uint8_t Inno3Pro_Read_2Bits(uint8_t ReadBack_Address, uint8_t u8ShiftCnt);
        
        
  		/**
			@brief
				Handles InnoSwitch3-Pro I2C Set Point and Threshold 

			@details 
				This function is used for CV,OV,UV Thresholds and Set-Point

			@pre 				
				I2C_Read16()   Driver should be already Configured and is  able to Read I2C commands
		 
			@param
				ReadBack_Address - Read Back Register Address
                fMultiplier - Factor to be used for the Set Point computation
		 
			@returns
				Byte Reading 
		*/            
        float Inno3Pro_Read_SetPoint(uint16_t ReadBack_Address , float fMultiplier);
        
        ///@}	// end of InnoSwitch3-Pro  Common Telemetry Functions

        
        
        /** 
           @name    Main API Telemetry Functions
        */
        ///@{         
       
  		/**                     
			@brief
                Reads the Telemetry register
                Read1  - Output Voltage Set-Point

			@details 
				This function provides the output voltage setting
                that was programmed on the CV Register

			@param
				None
		 
			@returns
				The Output Voltage Set Point in Volts
		*/		        
        float Inno3Pro_Read_CV_SetPoint(void);
        
        
  		/**
			@brief
                Reads the Telemetry register          
				Read2 - Under Voltage Threshold 

			@details 
				This function provides the Under Voltage setting
                that was programmed on the UVA Register
        
			@param
				None
		 
			@returns
				Under Voltage Threshold in Volts
		*/		        
        float Inno3Pro_Read_UV_Threshold(void);
        
        
  		/**
			@brief
                Reads the Telemetry register          
				Read3 - Over Voltage Threshold 

			@details 
				This function provides the Over Voltage setting
                that was programmed on the OVA Register
         
			@param
				None
		 
			@returns
				Over Voltage Threshold in Volts
		*/		        
        float Inno3Pro_Read_OV_Threshold(void);
        
        
  		/**
			@brief
                Reads bit 14 on Telemetry register          
				Read4 - VBUS Switch Enable

			@details 
				This function provides the current status of the VBUS Switch
         
			@param
				None
		 
			@returns
				True  - Vbus Switch is Enabled  (Closed) \n
                False - Vbus Switch is Disabled (Open)
		*/		        
        bool Inno3Pro_Read_VbusSwitch(void);
        
        
  		/**
			@brief
                Reads bit 13 on Telemetry register          
				Read4 - Minimum Load (Bleeder)

			@details 
				This function provides the current status of the Bleeder
         
			@param
				None
		 
			@returns
				True  - Bleeder is ON  \n
                False - Bleeder is OFF  
		*/		        
        bool Inno3Pro_Read_Bleeder(void);        
        
        
  		/**
			@brief
                Reads bit 12 on Telemetry register           
				Read4 - Turn PSU Off (Latch Off Device)

			@details 
				This function provides the current setting of the PSU
         
			@param
				None
		 
			@returns
				True  - Latch Off Device is Enabled \n
				False - Latch Off Device is Disabled
		*/		        
        bool Inno3Pro_Read_PsuOff(void);  
        
        
  		/**
			@brief
                Reads bit 11 on Telemetry register           
				Read4 - Fast VI Commands

			@details 
                This function provides the current setting of
                the Fast VI Command Register
         
			@param
				None
		 
			@returns
				True  - No Speed Limit (10ms update limit is disabled) \n
				False - 10ms Update Limit must be observed
		*/		        
        bool Inno3Pro_Read_FastVI(void);  
        
        
  		/**
			@brief
                Reads bit 10 on Telemetry register           
				Read4 - Constant-Voltage Mode Only 

			@details 
                This function tells if InnoSwitch3-Pro is operating on
                Constant Voltage Only Mode or both constant voltage
                and  constant current regulation mode is running
         
			@param
				None
		 
			@returns
				True  - CV Only Mode/No CC Regulation \n
				False - CV and CC Mode Enabled
		*/		        
        bool Inno3Pro_Read_CvoMode(void);          
        
        
  		/**
			@brief
                Reads bit 9 on Telemetry register           
				Read4 - Over-Temperature Protection

			@details 
                This function provides the current setting of
                the Secondary Over Temperature Fault Hysteresis
                or OTP Register
         
			@param
				None
		 
			@returns
				True  - 60 Degrees \n
				False - 40 Degrees
		*/		        
        bool Inno3Pro_Read_OtpFaultHyst(void);  

                
        /**
			@brief
                Reads the Telemetry register           
				Read4 - Cable Drop Compensation

			@details 
				This function provides the current Cable Drop Compensation
                that was programmed on the CDC Register
         
			@param
				None
		 
			@returns
                Cable Drop Compensation in millivolts (mV)
		*/	
        float Inno3Pro_Read_Cable_Drop_Comp(void);
        
               
  		/**
			@brief
                Reads the Telemetry register          
				READ5 - Constant Current Set-Point

			@details 
				This function provides the Constant Current setting
                that was programmed on the CC Register
        
			@param
				None
		 
			@returns
				Constant Current Set-Point in Amperes
		*/		        
        float Inno3Pro_Read_CC_SetPoint(void);  
                
        
  		/**
			@brief
                Reads the Telemetry register          
				READ5 - Constant Power Threshold

			@details 
				This function provides the Constant Power setting
                that was programmed on the VKP Register
        
			@param
				None
		 
			@returns
				Constant Power Threshold in Volts
		*/		        
        float Inno3Pro_Read_CP_Threshold(void);          
                
        
  		/**
			@brief
                Reads the Telemetry register          
				READ6 - Overvoltage Fault Response

			@details 
				This function provides the Overvoltage Fault Response setting
                that was programmed on the OVL Register
        
                This determines the action that InnoSwitch3-Pro 
                will take in response to an output Overvoltage fault
        
			@param
				None
		 
			@returns
				Overvoltage Fault Response in Byte
		*/		        
        uint8_t Inno3Pro_Read_OV_Fault_Response(void);
        

  		/**
			@brief
                Reads the Telemetry register          
				READ6 - Under voltage Fault Response

			@details 
				This function provides the Undervoltage Fault Response setting
                that was programmed on the UVL Register
        
                This determines the action that InnoSwitch3-Pro 
                will take in response to an output Undervoltage fault
        
			@param
				None
		 
			@returns
				Under voltage Fault Response in Byte
		*/		        
        uint8_t Inno3Pro_Read_UV_Fault_Response(void);
        
        
  		/**
			@brief
                Reads the Telemetry register          
				READ6 - IS-pin Short Fault Response

			@details 
				This function provides the IS-pin Short Fault Response setting
                that was programmed on the 1st 2 bits of the ISSC Register
        
                This determines the action that InnoSwitch3-Pro 
                will take in response to the IS-pin Short Fault  
                         
			@param
				None
		 
			@returns
				IS-pin Short Fault Response in Byte
		*/		        
        uint8_t Inno3Pro_Read_IsPinShort_Fault_Response(void);
        
            
  		/**
			@brief
                Reads the Telemetry register          
				READ6 - Undervoltage Timer 

			@details 
				This function provides the Under voltage Timer setting
                that was programmed on the UVL Timer Register  
                  
			@param
				None
		 
			@returns
				Under voltage Timer in Byte
		*/		        
        uint8_t Inno3Pro_Read_UV_Fault_Timer(void);

        
  		/**
			@brief
                Reads the Telemetry register          
				READ6 - Watchdog Timer 

			@details 
				This function provides the Watchdog Timer Timeout setting
                that was programmed on the Watchdog Timer Register
        
			@param
				None
		 
			@returns
				Watchdog Timer Timeout in Byte
		*/		        
        uint8_t Inno3Pro_Read_Watchdog_Timer(void);
        
                
  		/**
			@brief
                Reads the Telemetry register          
				READ6 -  Constant Voltage Mode Fault Response

			@details 
				This function provides the Constant Voltage Mode Response 
                setting that was programmed on the CVOL Register
        
                This determines the action that InnoSwitch3-Pro 
                will take in response to a Constant Voltage Mode Fault  
                         
			@param
				None
		 
			@returns
				Constant Voltage Mode Fault Response in Byte
		*/		        
        uint8_t Inno3Pro_Read_CvMode_Fault_Response(void);

        
  		/**
			@brief
                Reads the Telemetry register          
				READ6 - Constant Voltage Mode Timer 

			@details 
				This function provides the Constant Voltage Mode Timeout setting
                that was programmed on the CVOL Timer Register
        
			@param
				None
		 
			@returns
				Watchdog Timer Timeout in Byte
		*/		        
        uint8_t Inno3Pro_Read_CvMode_Timer(void);

        
    	/** 		
			@brief
                Reads the Telemetry register                 
				Read7 - Measured Output Current

			@details 
				This function provides the measured output current. \n
         
                The output current measurement ADC full range is 128.  \n
         
                This function removes the Odd parity on bit 15 and bit 7
                and process it to actual measurements.
                         
			@param
				None
		 
			@returns
				Current Reading in Amps
		*/		
		float Inno3Pro_Read_Amps(void);
        
        
  		/**
			@brief
                Reads the Telemetry register           
				Read9 - Measured Output Voltage

			@details 
                This function provides the actual measured output voltage. \n
         
                The output voltage report back is in 12-bit format but the 
                resolution depends on the output voltage range.
         
			@param
				None
		 
			@returns
				Voltage Reading in Volts
		*/		
		float Inno3Pro_Read_Volts(void);
    
  
  		/**
			@brief
                Reads bit 15 on Telemetry register          
				Read10 - Interrupt Enable

			@details 
				This function provides the current status of the Active 
                interrupt reporting scheme on the SCL Pin 
		          
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - Interrupt is Enabled   \n
                False - Interrupt is Disabled 
		*/		
        bool Inno3Pro_Read_Status_InterruptEnable(void);        

		        
    	/**
			@brief
                Reads bit 14 on Telemetry register          
				Read10 - System Ready Signal        

			@details 
				This function provides the current status when 
                InnoSwitch3-Pro is ready to receive I2C commands        
		          
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
                True  - System is Ready  
		*/		
		bool Inno3Pro_Read_Status_SystemReady(void);
        
        
  		/**
			@brief
                Reads bit 13 on Telemetry register          
				Read10 - Output Discharge

			@details 
				This function tells the load(VBUS) has been discharged
		          
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - Discharge is Enabled \n  
                False - Discharge is Disabled 
		*/	        
        bool Inno3Pro_Read_Status_OutputDischarge(void);
        
        
        /**
			@brief
                Reads bit 12 on Telemetry register          
				Read10 - Switching Frequency High        

			@details 
				This function tells if InnoSwitch3-Pro is operating at 
                High Switching Frequency
		          
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - High Switching Frequency \n 
                False - Low Switching Frequency  
		*/
		bool Inno3Pro_Read_Status_HighSwitchFreq(void);
        
        
        /**
			@brief
                Reads bit 9 on Telemetry register          
				Read10 - Over-Temperature Protection     

			@details 
				This function tells that Over-Temperature Protection 
                was triggered
		          
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - Over-Temperature Protection Enabled \n
                False - Over-Temperature Protection Disabled 
		*/        
        bool Inno3Pro_Read_Status_OtpFault(void);

        
    	/**
			@brief
                Reads bit 5 on Telemetry register          
				Read10 - 2% Bleeder Enabled    

			@details 
				This function monitors the VOUT2PCT status
                to detect when to disable the Active bleeder.
                when the BLEEDER function is being used to bleed 
                the output voltage from high to low set point
                  
                The InnoSwitch3-Pro automatically activates a weak current
                bleeder (>5mA) on the VOUT pin until the output voltage settles 
                to less than 2% of the set regulation threshold.
         
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  -  2% Bleeder Enabled \n
                False -  2% Bleeder Disabled
		*/				
        bool Inno3Pro_Read_Status_Vout2pct(void);		
        
        
    	/**
			@brief
                Reads bit 4 on Telemetry register          
				Read10 - VOUTADC > 1.1*Vout   

			@details 
				This function monitors the VOUT10PCT status
                to detect when to disable the Active bleeder
                when the BLEEDER function is being used to bleed 
                the output voltage from high to low set point
         
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  -  2% Bleeder Enabled \n
                False -  2% Bleeder Disabled
		*/			
        bool Inno3Pro_Read_Status_Vout10pct(void);	
        
		
        /**
			@brief
                Reads bit 3 on Telemetry register          
				Read10 - IS-pin Short Circuit Detected    

			@details 
				This function tells that IS-pin Short Circuit 
                was triggered 
         
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - IS-pin Short Circuit Detected \n
                False - No IS-pin Short Circuit 
		*/  	       
        bool Inno3Pro_Read_Status_IsPinShort(void);
        
        
        /**
			@brief
                Reads bit 1 on Telemetry register          
				Read10 - Output Voltage UV Fault Comparator    

			@details 
				This function tells that Output Voltage has crossed 
                the UV Fault Threshold Limit 
         
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.	
         	 
			@param
				None
		 
			@returns
				True  - Output Voltage UV Fault Detected \n
                False - No Output Voltage UV Fault 
		*/  	        
        bool Inno3Pro_Read_Status_UV_Fault(void);
        
        
        /**
			@brief
                Reads bit 0 on Telemetry register          
				Read10 - Output Voltage OV Fault Comparator    

			@details 
				This function tells that Output Voltage has crossed 
                the OV Fault Threshold Limit 
         
                The READ10 telemetry registers are instantaneous and 
                are cleared whenever the condition is no longer valid.
       
			@param
				None
		 
			@returns
				True  - Output Voltage OV Fault Detected \n
                False - No Output Voltage OV Fault 
		*/  	         
        bool Inno3Pro_Read_Status_OV_Fault(void);
        
        
        /**
			@brief
                Reads bit 15 on Telemetry register          
				Read11 - CVO Mode Auto Restart(AR)   

			@details 
				This function tells that an Auto Restart happened
                while InnoSwitch3-Pro is operating in Constant Voltage
                Mode Only
        
			@param
				None
		 
			@returns
				True  - CVO Mode Auto Restart Occurred \n
                False - No Fault 
		*/          
        bool Inno3Pro_Read_Status_CvoMode_AR(void);
        
        
        /**
			@brief
                Reads bit 12 on Telemetry register          
				Read11 - IS-pin Short Circuit Auto Restart(AR)   

			@details 
				This function tells that an Auto Restart happened
                because of IS-pin Short Circuit
        
			@param
				None
		 
			@returns
				True  - IS-pin Short Circuit AR Occurred \n
                False - No Fault 
		*/         
        bool Inno3Pro_Read_Status_IsPinShort_AR(void);
        
        
        /**
			@brief
                Reads bit 10 on Telemetry register          
				Read11 - Output Voltage OV Auto Restart(AR)   

			@details 
				This function tells that an Auto Restart happened
                because of Output Voltage Overvoltage
        
			@param
				None
		 
			@returns
				True  - Output Voltage Overvoltage AR Occurred \n
                False - No Fault 
		*/           
        bool Inno3Pro_Read_Status_OV_AR(void);
        
        
        /**
			@brief
                Reads bit 9 on Telemetry register          
				Read11 - Output Voltage UV Auto Restart(AR)   

			@details 
				This function tells that an Auto Restart happened
                because of Output Voltage Undervoltage
        
			@param
				None
		 
			@returns
				True  - Output Voltage Undervoltage AR Occurred \n
                False - No Fault 
		*/          
        bool Inno3Pro_Read_Status_UV_AR(void);
        
        
        /**
			@brief
                Reads bit 7 on Telemetry register          
				Read11 - Latch-Off (LO) Occurred   

			@details 
				This function tells that the power supply is in Latch-Off
                mode. 

                An AC Input Reset is needed to bring back normal 
                operation if the fault is no longer present.
         
			@param
				None
		 
			@returns
				True  - Latch-Off (LO) Occurred \n 
                False - No Fault 
		*/           
        bool Inno3Pro_Read_Status_LatchOff(void);
        
        
        /**
			@brief
                Reads bit 6 on Telemetry register          
				Read11 - CVO Mode Latch Off (LO)  

			@details 
				This function tells that Latch-Off mode happened while 
                InnoSwitch3-Pro is operating in Constant Voltage Mode Only
        
			@param
				None
		 
			@returns
				True  - CVO Mode Latch Off Occurred \n
                False - No Fault 
		*/         
        bool Inno3Pro_Read_Status_CvoMode_LO(void);
        
        
        /**
			@brief
                Reads bit 5 on Telemetry register          
				Read11 - PSU Turn-Off Command Received  

			@details 
				This function tells that PSU was Turned off since PSU Turn-Off 
                CMD was received
         
			@param
				None
		 
			@returns
				True  - PSU Turn-Off Command Received \n
                False - No Fault 
		*/          
        bool Inno3Pro_Read_Status_PsuOffCmd(void);
        
        
        /**
			@brief
                Reads bit 4 on Telemetry register          
				Read11 - IS-pin Short Circuit Latch Off (LO) 

			@details 
				This function tells that Latch-Off mode happened
                because of IS-pin Short Circuit
        
			@param
				None
		 
			@returns
				True  - IS-pin Short Circuit LO Occurred \n
                False - No Fault 
		*/             
        bool Inno3Pro_Read_Status_IsPinShort_LO(void);
        
        
        /**
			@brief
                Reads bit 2 on Telemetry register          
				Read11 - Output Voltage OV Latch Off (LO)  

			@details 
				This function tells that Latch-Off mode happened
                because of Output Voltage Overvoltage
        
			@param
				None
		 
			@returns
				True  - Output Voltage Overvoltage LO Occurred \n
                False - No Fault 
		*/          
        bool Inno3Pro_Read_Status_OV_LO(void);
        
        
        /**
			@brief
                Reads bit 1 on Telemetry register          
				Read11 - Output Voltage UV Latch Off (LO)  

			@details 
				This function tells that Latch-Off mode happened
                because of Output Voltage Undervoltage
        
			@param
				None
		 
			@returns
				True  - Output Voltage Undervoltage LO Occurred \n
                False - No Fault 
		*/           
        bool Inno3Pro_Read_Status_UV_LO(void);
        
        
        /**
			@brief
                Reads bit 0 on Telemetry register          
				Read11 - BPS-pin Latch Off (LO)  

			@details 
				This function tells that Latch-Off mode happened
                because of Overvoltage was detected on the BPS Pin 
        
			@param
				None
		 
			@returns
				True  - Output Voltage Overvoltage LO Occurred \n
                False - No Fault 
		*/          
        bool Inno3Pro_Read_Status_BPS_LO(void);

        
        /**
			@brief
                Reads bit 14 on Telemetry register          
				Read12 - Interrupt Mask Control Secondary

			@details 
				This function provides the bit setting of the Control Secondary
                that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for Control Secondary is Enabled \n
                False -  Interrupt for Control Secondary is Disabled
		*/
        bool Inno3Pro_Read_Interrupt_Mask_CntrlSecondary(void);
        
        
        /**
			@brief
                Reads bit 13 on Telemetry register            
				Read12 - Interrupt Mask BPS Current Latch-off

			@details 
				This function provides the bit setting of the BPS Current 
                Latch-off that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for BPS Current Latch-off is Enabled \n
                False -  Interrupt for BPS Current Latch-off Disabled
		*/        
        bool Inno3Pro_Read_Interrupt_Mask_BpsCurrentLo(void);
        
        
        /**
			@brief
                Reads bit 12 on Telemetry register           
				Read12 - Interrupt Mask BPS Current Latch-off

			@details 
				This function provides the bit setting of the CVO Mode Peak 
                load timer that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for CVO Mode Peak load Timer is Enabled \n
                False -  Interrupt for CVO Mode Peak load Timer is Disabled
		*/            
        bool Inno3Pro_Read_Interrupt_Mask_CvoPkLoadTimer(void);
        
        
        /**
			@brief
                Reads bit 11 on Telemetry register           
				Read12 - Interrupt Mask IS-pin Short

			@details 
				This function provides the bit setting of the Interrupt Mask
                IS-pin Short that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for IS-pin Short is Enabled \n
                False -  Interrupt for IS-pin Short is Disabled
		*/          
        bool Inno3Pro_Read_Interrupt_Mask_IsPinShort(void);
        
        
        /**
			@brief
                Reads bit 9 on Telemetry register            
				Read12 - Interrupt Mask Vout Undervoltage(UV)

			@details 
				This function provides the bit setting of the Interrupt Mask
                Vout(UV) that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for Vout (UV) is Enabled \n
                False -  Interrupt for Vout (UV) is Disabled
		*/          
        bool Inno3Pro_Read_Interrupt_Mask_UV(void);
        
        
        /**
			@brief
                Reads bit 8 on Telemetry register         
				Read12 - Interrupt Mask Vout Overvoltage(OV)

			@details 
				This function provides the bit setting of the Interrupt Mask
                Vout(OV) that was programmed on the Interrupt Register
         
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -  Interrupt for Vout (OV) is Enabled \n
                False -  Interrupt for Vout (OV) is Disabled
		*/        
        bool Inno3Pro_Read_Interrupt_Mask_OV(void);
        
        
        /**
			@brief
                Reads bit 6 on Telemetry register          
				Read12 - Interrupt Status Control Secondary

			@details 
				This function tells that Control Secondary fault has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   Control Secondary fault has occurred \n
                False -   No Fault
		*/        
        bool Inno3Pro_Read_Interrupt_Stat_CntrlSecondary(void);
        
        
        /**
			@brief
                Reads bit 6 on Telemetry register          
				Read12 - Interrupt Status for Control Secondary

			@details 
				This function tells that Control Secondary fault has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   Control Secondary fault has occurred \n
                False -   No Fault
		*/         
        bool Inno3Pro_Read_Interrupt_Stat_BpsCurrentLo(void);
        
        
        /**
			@brief
                Reads bit 5 on Telemetry register          
				Read12 - Interrupt Status for CVO Mode Peak load timer

			@details 
				This function tells that CVO fault has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   Constant Voltage Mode Fault has occurred \n
                False -   No Fault
		*/         
        bool Inno3Pro_Read_Interrupt_Stat_CvoPkLoadTimer(void);
        
        
        /**
			@brief
                Reads bit 3 on Telemetry register          
				Read12 - Interrupt Status for Status IS-pin Short

			@details 
				This function tells that IS-pin Short has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   IS-pin Short has occurred \n
                False -   No Fault
		*/         
        bool Inno3Pro_Read_Interrupt_Stat_IsPinShort(void);
        
        
        /**
			@brief
                Reads bit 1 on Telemetry register          
				Read12 - Interrupt Status for Status Vout(UV)

			@details 
				This function tells that Vout Undervoltage Fault has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and 
                must be re-enabled to activate the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   Vout Undervoltage(UV) Fault has occurred \n
                False -   No Fault
		*/         
        bool Inno3Pro_Read_Interrupt_Stat_UV(void);
        
        
        /**
			@brief
                Reads bit 0 on Telemetry register          
				Read12 - Interrupt Status for Status Vout(OV)

			@details 
				This function tells that Vout Overvoltage Fault has occurred
                and an Interrupt on the SCL was generated
          
            @note
                Once a fault occurs, the Interrupt Mask is reset and the
                particular faults of interest must be re-enabled to activate 
                the SCL reporting scheme.
         
			@param
				None
		 
			@returns
				True  -   Vout Overvoltage(OV) Fault has occurred \n
                False -   No Fault
		*/          
        bool Inno3Pro_Read_Interrupt_Stat_OV(void);


    	/** 		
			@brief
                Reads the Telemetry register                 
				Read13 - Average Output Current

			@details 
				This function provides the average measured output current. \n
         
                The average output current measurement is simply 16-samples 
                rolling average of the READ7 (measured output current)
                and the ADC full range is 128 and with No Odd-Parity.
         
			@param
				None
		 
			@returns
				Current Reading in Amps
		*/		
		float Inno3Pro_Read_AmpsAverage(void);
        
        
  		/**
			@brief
                Reads the Telemetry register           
				Read14 - Average Output Voltage 

			@details 
                This function provides the average measured output voltage. \n
         
                The average output voltage measurement is simply 16-samples 
                rolling average of the READ9 (measured output voltage). \n
                
                The output voltage report back is in 12-bit format but the 
                resolution depends on the output voltage range.
         
			@param
				None
		 
			@returns
				Voltage Reading in Volts
		*/		
		float Inno3Pro_Read_VoltsAverage(void);
        
        
  		/**
			@brief
                Reads the Telemetry register           
				Read15 - Voltage DAC

			@details 
                This function is useful in determining if InnoSwitch3-Pro 
                is operating in CC or CV Mode

			@param
				None
		 
			@returns
				DAC Voltage Reading in Volts
		*/        
        float Inno3Pro_Read_Voltage_DAC(void);
        ///@}	// End of Main API Telemetry Functions
        
        
		/** @name InnoSwitch3-Pro I2C Register Buffers
		
			@brief
				Individual Array Buffers Used for I2C Communication
				Each Corresponds to an InnoSwitch3-Pro  I2C register

			@details 
				These Array Buffers needs to be filled with LSB and MSB values.
				These are used directly for Writing values to InnoSwitch3-Pro  via I2C.			
				These values are Initialize with InnoSwitch3-Pro  Default Values.
				
		 	@details 
				Buffer[0]  - LSB
				Buffer[1]  - MSB
			
		 */
		///@{
        
        uint8_t u8_Buffer_VBEN[2]                  ={0};			 
		uint8_t u8_Buffer_BLEEDER[2]               ={0};
		uint8_t u8_Buffer_VDIS[2]                  ={0};
		uint8_t u8_Buffer_TURN_OFF_PSU[2]          ={0};
		uint8_t u8_Buffer_FAST_VI_CMD[2]           ={0};     
		uint8_t u8_Buffer_CVO[2]                   ={0};           
		 
		uint8_t u8_Buffer_CV[2]                    ={0};
		uint8_t u8_Buffer_OVA[2]                   ={0};
		uint8_t u8_Buffer_UVA[2]                   ={0};
		uint8_t u8_Buffer_CDC[2]                   ={0};
		uint8_t u8_Buffer_CC[2]                    ={0};
		uint8_t u8_Buffer_VKP[2]                   ={0};

		uint8_t u8_Buffer_OVL[2]                   ={0};
		uint8_t u8_Buffer_UVL[2]                   ={0};
		uint8_t u8_Buffer_ISSC[2]                  ={0};
		uint8_t u8_Buffer_CCSC[2]                  ={0};
		uint8_t u8_Buffer_UVL_TIMER[2]             ={0};
		uint8_t u8_Buffer_WATCHDOG_TIMER[2]        ={0};
		
        uint8_t u8_Buffer_CVOL[2]                  ={0};
		uint8_t u8_Buffer_CVOL_TIMER[2]            ={0};
		uint8_t u8_Buffer_INTERRUPT[2]             ={0};
        uint8_t u8_Buffer_OTP[2]                   ={0};
		
	    uint8_t u8_Buffer_CVLOAD[2]            	   ={0};
        uint8_t u8_Buffer_LoopSpeed1[2]            ={0};
        uint8_t u8_Buffer_LoopSpeed2[2]            ={0};

		///@}	// end of  InnoSwitch3-Pro  I2C Buffers
		
	
	
		/** @name InnoSwitch3-Pro Setter Functions
		
            @brief
				API for Setting Individual Register Variables that needs to be configured 		   
		 */
		///@{
		  
        inline void Inno3Pro_Set_Register_CV(float fVout);
        
		inline void Inno3Pro_Set_Register_OVA(float fOva);
		
		inline void Inno3Pro_Set_Register_UVA(float fUva);

        inline void Inno3Pro_Set_Register_CC(float fCc);

        inline void Inno3Pro_Set_Register_CDC(float fCdc);

        inline void Inno3Pro_Set_Register_VKP(float fVkp);

        inline void Inno3Pro_Set_Register_VBEN(float fVben);
        
        inline void Inno3Pro_Set_Register_UVL(float fUvl);
       
		///@}	// end of  InnoSwitch3-Pro Setter Functions

        
        
		/** @name InnoSwitch3-Pro Getter Functions
		
            @brief
				API Getting the value of Individual Register Variables		   
		 */
		///@{
		  
        inline float Inno3Pro_Get_Register_CV(void);
        
		inline float Inno3Pro_Get_Register_OVA(void);
		
		inline float Inno3Pro_Get_Register_UVA(void);

        inline float Inno3Pro_Get_Register_CC(void);

        inline float Inno3Pro_Get_Register_CDC(void);

        inline float Inno3Pro_Get_Register_VKP(void);

        inline float Inno3Pro_Get_Register_VBEN(void);
        
        inline float Inno3Pro_Get_Register_UVL(void);
		///@}	// end of  InnoSwitch3-Pro Getter Functions


		 

  	/** @name InnoSwitch3-Pro  Registers
		
		  @brief
				Individual Register Values that needs to be configured 

		  @details 
				After these values have been set, it is converted
				to appropriate MSB and LSB needed for Filling Up the
				Inno3-Pro  I2C buffers  
		   
		 */
		///@{
		  
        float fInno3Pro_CV                   =INNO3PRO_DEFAULT_CV_SET_PT_LEVEL;
		float fInno3Pro_OVA                  =INNO3PRO_DEFAULT_OVA_SET_PT_LEVEL;
		float fInno3Pro_UVA                  =INNO3PRO_DEFAULT_UVA_SET_PT_LEVEL;
        float fInno3Pro_CDC                  =INNO3PRO_DEFAULT_CDC_ASSERT_LEVEL;
        float fInno3Pro_CC                   =INNO3PRO_DEFAULT_CC_ASSERT_LEVEL;
        float fInno3Pro_VKP                  =INNO3PRO_DEFAULT_VKP_ASSERT_LEVEL;
        float fInno3Pro_VBEN                 =INNO3PRO_DEFAULT_VBEN_CONTROL_LOGIC;
        float fInno3Pro_UVL                  =INNO3PRO_DEFAULT_UVL_CONTROL_LOGIC;
		 
		///@}	// end of  InnoSwitch3-Pro  Registers
	

	
  // library-accessible "private" interface
  private:
  
		/** @name InnoSwitch3-Pro  Computations
		
            @brief
				Individual Functions Used to Compute values for the InnoSwitch3-Pro Registers
		   
		 */
		///@{  
				
			/**
				@brief
					InnoSwitch3-Pro  Computation for Output Voltage (CV)

				@details 
				   Calculates the value based on 10mV/LSB Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    300 to 2400  (3V to 24V)			
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed CV Value
			*/	 		
			 float Inno3Pro_Compute_CV( float fSetPt);
			 			 
			 
			/**
				@brief
					InnoSwitch3-Pro  Computation for Over-Voltage Threshold (OVA)

				@details 
				   Calculates the value based on 100mV/LSB Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    62 to 250  (6.2V to 25V)					
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed OVA Value
			*/	 				 
			float Inno3Pro_Compute_OV( float fSetPt);
			
			            
			/**
				@brief
					InnoSwitch3-Pro  Computation for Under-Voltage Threshold (UVA)

				@details 
				   Calculates the value based on 100mV/LSB Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    30 to 240  (3V to 24V)					
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed UVA Value
			*/				
			float Inno3Pro_Compute_UV( float fSetPt);
						
            
			/**
				@brief
					InnoSwitch3-Pro  Computation for Cable Drop Compensation (CDC)

				@details 
				   Calculates the value based on 50mV/LSB Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    0 to 12  (0V to 600mV)					
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed CDC Value
			*/				
			float Inno3Pro_Compute_CDC( float fSetPt);
			            
            
			/**
				@brief
					InnoSwitch3-Pro  Computation for Constant Current Regulation (CC)

				@details 
				   Calculates the value based on 0.25mV/Step/Rsense Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    25 to 128  (20% to 100% of CC)					
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed CC Value
			*/				
			float Inno3Pro_Compute_CC( float fSetPt);
		
		
			/**
				@brief
					InnoSwitch3-Pro  Computation for Output Power Knee Voltage (VKP)

				@details 
				   Calculates the value based on 100mV/LSB Resolution.	
				   
				@note
				   This Function Applies Range Limits  to the Set Point Value				   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    53 to 240  (5.3V to 24V)				
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					Computed VKP Value
			*/					
			float Inno3Pro_Compute_VKP( float fSetPt);
			
            			
			/**
				@brief
					InnoSwitch3-Pro  Computation for Series Bus Switch Control (VBEN)
				   
				@note
				   This function Doesn't have any computation, Only Applies Range limits			   
				   
				@pre 
					None
					
				@post
				    Returned Value Range:    0 or 3  ( 0: Disabled or Bus SW Open  , 3: Enabled or Bus SW Closed )				
			 
				@param
					fSetPt - Set Point Value
			 
				@returns
					 VBEN Value
			*/					
			float Inno3Pro_Compute_VBEN( float fSetPt);	
		 
		///@}	// end of  InnoSwitch3-Pro  Computations

		
			
		/** @name InnoSwitch3-Pro  Buffer Conversion
		
            @brief
				Prepares the LSB and MSB values to be used on I2C buffers
		   
		 */
		///@{ 	 
			
			/**
				@brief
					InnoSwitch3-Pro  Conversion for I2C buffers
				   
				@note
				   This function Converts the Data Input to Hexadecimal
                   LSB and MSB  that will be stored on the I2C write buffers.
				   
				@pre 
					None
							 
				@param
					u16Temp - Value to be converted
					
				@param
					*u8WriteBuffer - A pointer to the memory location 
					 where the converted data will be stored				
			 
				@returns
					 None
			*/				
			void Inno3Pro_Encode_Buffer( uint16_t u16Temp, uint8_t *u8WriteBuffer);			
            
                        
			/**
				@brief
					InnoSwitch3-Pro  Conversion for I2C buffers
				   
				@note
				   This function Converts the Data Input to Hexadecimal
                   LSB and MSB. After parity is added the hex equivalent will be 
                   stored on the I2C write buffers.
				   
				@pre 
					None
							 
				@param
					u16Temp - Value to be converted
					
				@param
					*u8WriteBuffer - A pointer to the memory location 
					 where the converted data will be stored				
			 
				@returns
					 None
			*/	            
            void Inno3Pro_Encode_Buffer_Parity( uint16_t u16Temp, uint8_t *u8WriteBuffer);
            
                        
			/**
				@brief
					InnoSwitch3-Pro  Odd Parity Bit Detection
				   
				@note
				   This function Detects the No of 1s in a Byte
				   
				@pre 
					None
							 
				@param
					u8OddParity - Byte to be Evaluated with Parity
					
				@returns
                    True  - If the no 1s is Odd number
			*/	            
            bool Inno3Pro_OddParity(uint8_t u8OddParity);                        
	 	 	 	            
		///@}	// end of  InnoSwitch3-Pro  Buffer Conversion
										        
};
#endif	/* INNO3PRO_H */

