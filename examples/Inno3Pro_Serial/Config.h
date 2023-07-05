 /**	
	@file		Config.h
	
    @brief 	    This is the header file containing all the Library Macros
                and configuration for InnoSwitch3-Pro
	
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

#ifndef CONFIG_H
#define	CONFIG_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


/** 
	@name 	Firmware Revision Macro
	@brief	Defines the revision number of <b> InnoSwitch3-Pro Code Library </b>
            to track changes on each release
			
	@note	<b> Version Format:	  v00.00.00 
 */
///@{ 

/** Firmware Version for Major Code Changes */
#define	INNO3PRO_FW_VERSION_MAJOR   '0','1'   

 /** Firmware Version for Minor Code Changes */
#define	INNO3PRO_FW_VERSION_MINOR   '0','0'	

/** Firmware Version for Test Codes */
#define	INNO3PRO_FW_VERSION_TEST    '0','0'	  
///@}


/** 
	@name 	Saturation Macros	
	@brief	Used for Setting limits to a certain parameter
 */
///@{ 

/** Constrain the parameter up to Minimum and Maximum Value Only */
#define	sig_minmax(sig, min, max) ((sig < min) ? sig = min : (sig > max) ? sig = max : 0)

/** Constrain the parameter up to Minimum Value Only */
#define	sig_max( sig, max )	((sig > max) ? sig = max : 0)				

/** Constrain the parameter up to Maximum Value Only */
#define	sig_min( sig, min )	((sig < min) ? sig = min : 0)									
///@}
	
	
	
	
/** 
	@name 	Bit Manipulation Macros	
	@brief	Used for Manipulating bits in a certain byte
 */
///@{ 	

/** Set a bit in a byte  */
#define set_bit(ADDRESS,BIT)        (ADDRESS |= (1<<BIT))	

/** Clear a bit in a byte  */
#define clear_bit(ADDRESS,BIT)      (ADDRESS &= ~(1<<BIT))		

/** Toggle a bit in a byte  */
#define toggle_bit(ADDRESS,BIT)     (ADDRESS ^= (1<<BIT))	

/** Test a bit in a byte if it Set */
#define test_bit(ADDRESS,BIT)       (ADDRESS & (1<<BIT))	

///@}



/** 
	@name 	InnoSwitch3-Pro I2C Macros
	
	@brief	Defines the Slave address of InnoSwitch3-Pro  and I2C Write Sizes
	@note	
			0011000 (0x18) - 7bit Address Scheme
 */
///@{ 

/** InnoSwitch3-Pro I2C 7-bit Slave Address  */
#define INNO3PRO_ADDRESS     0x18		

/** InnoSwitch3-Pro I2C Buffer Length (Address, LSB, MSB) */
#define WR_WORD              0x03 	

/** InnoSwitch3-Pro I2C Buffer Length (Address, LSB) */
#define WR_BYTE              0x02	

/** InnoSwitch3-Pro Read MSB */
#define RD_MSB               1		

/** InnoSwitch3-Pro Read LSB */
#define RD_LSB               0

///@}


/** 
	@name 	InnoSwitch3-Pro Read Register BitShift Count Macros
	
	@brief	Defines the Register BitShift position used in Reading 
            Register Values
 */
///@{ 

/** Overvoltage Fault Bit Shift Count  */
#define INNO3PRO_READ_OV_FAULT_BITSHIFT             14	

/** Undervoltage Fault Bit Shift Count  */
#define INNO3PRO_READ_UV_FAULT_BITSHIFT             12	

/** IS-Pin Short Fault Bit Shift Count  */
#define INNO3PRO_READ_ISSC_SHORT_BITSHIFT           8	

/** Undervoltage Fault Timer Bit Shift Count  */
#define INNO3PRO_READ_UVL_TIMER_BITSHIFT            6	

/** Watchdog Timer Bit Shift Count  */
#define INNO3PRO_READ_WATCHDOG_TIMER_BITSHIFT       4	

/** Constant Voltage Only Mode Bit Shift Count  */
#define INNO3PRO_READ_CV_MODE_BITSHIFT              2	

/** Constant Voltage Only Mode Timer Bit Shift Count  */
#define INNO3PRO_READ_CV_MODE_TIMER_BITSHIFT        0		

///@}


/** 
	@name 	InnoSwitch3-Pro Response and Timer Macros
	
	@brief	Used for Response and Timer settings of registers
    @note   Use these MACROS for updating the PI Command register settings
 */
///@{ 

/** Series Bus Switch Enable  */
#define INNO3PRO_VBUS_ENABLE                        true

/** Series Bus Switch Disable  */
#define INNO3PRO_VBUS_DISABLE                       false		



/** Active Bleeder Enable  */
#define INNO3PRO_BLEEDER_ENABLE                     true	

/** Active Bleeder Disable  */
#define INNO3PRO_BLEEDER_DISABLE                    false		



/** Load Discharge Enable  */
#define INNO3PRO_LOAD_DISCHARGE_ENABLE              true	

/** Load Discharge Enable  */
#define INNO3PRO_LOAD_DISCHARGE_DISABLE             false		



/** Latch Off Device Enable  */
#define INNO3PRO_TURN_OFF_PSU_ENABLE                true	

/** Latch Off Device Disable  */
#define INNO3PRO_TURN_OFF_PSU_DISABLE               false	



/** Fast VI Command Enable  */
#define INNO3PRO_FASTVI_UPDATE_LIMIT_ENABLE         false	

/** Fast VI Command Disable  */
#define INNO3PRO_FASTVI_UPDATE_LIMIT_DISABLE        true		



/** Overvoltage Fault Response Set to No Response */
#define INNO3PRO_OVL_FAULT_RESPONSE_NORESPONSE      0

/** Overvoltage Fault Response Set to Latch-Off */
#define INNO3PRO_OVL_FAULT_RESPONSE_LATCHOFF        1	

/** Overvoltage Fault Response Set to Auto-Restart */
#define INNO3PRO_OVL_FAULT_RESPONSE_AUTORESTART     2		



/** Undervoltage Fault Response Set to Auto-Restart */
#define INNO3PRO_UVL_FAULT_RESPONSE_AUTORESTART     0	

/** Undervoltage Fault Response Set to Latch-Off */
#define INNO3PRO_UVL_FAULT_RESPONSE_LATCHOFF        1	

/** Undervoltage Fault Response Set to No Response */
#define INNO3PRO_UVL_FAULT_RESPONSE_NORESPONSE      2		



/** IS-Pin Short Fault Response Set to No Response */
#define INNO3PRO_ISSC_FAULT_RESPONSE_NORESPONSE     0

/** IS-Pin Short Fault Response Set to Latch-Off */
#define INNO3PRO_ISSC_FAULT_RESPONSE_LATCHOFF       1	

/** IS-Pin Short Fault Response Set to Auto-Restart */
#define INNO3PRO_ISSC_FAULT_RESPONSE_AUTORESTART    2		



/** IS-Pin Short Frequency Detection Threshold at 50Khz */
#define INNO3PRO_ISSC_FREQ_THRESHOLD_50KHZ          0	

/** IS-Pin Short Frequency Detection Threshold at 30Khz */
#define INNO3PRO_ISSC_FREQ_THRESHOLD_30KHZ          1		

/** IS-Pin Short Frequency Detection Threshold at 40Khz */
#define INNO3PRO_ISSC_FREQ_THRESHOLD_40KHZ          2		

/** IS-Pin Short Frequency Detection Threshold at 60Khz */
#define INNO3PRO_ISSC_FREQ_THRESHOLD_60KHZ          3		



/** Undervoltage Fault Timer Set to 8ms */
#define INNO3PRO_UVL_FAULT_TIMER_8MS                0	

/** Undervoltage Fault Timer Set to 16ms */
#define INNO3PRO_UVL_FAULT_TIMER_16MS               1	

/** Undervoltage Fault Timer Set to 32ms */
#define INNO3PRO_UVL_FAULT_TIMER_32MS               2	

/** Undervoltage Fault Timer Set to 64ms */	
#define INNO3PRO_UVL_FAULT_TIMER_64MS               3	



/** Watchdog Timer Set to 0 sec (No-Watchdog) */
#define INNO3PRO_WATCHDOG_TIMER_NOWATCHDOG          0	

/** Watchdog Timer Set to 0.5 sec */
#define INNO3PRO_WATCHDOG_TIMER_500MS               1	

/** Watchdog Timer Set to 1 sec */
#define INNO3PRO_WATCHDOG_TIMER_1000MS              2	

/** Watchdog Timer Set to 2 sec */
#define INNO3PRO_WATCHDOG_TIMER_2000MS              3		



/** Constant Voltage Only Fault Response Set to No Response */
#define INNO3PRO_CVOL_FAULT_RESPONSE_NORESPONSE     0		

/** Constant Voltage Only Fault Response Set to Auto-Restart */
#define INNO3PRO_CVOL_FAULT_RESPONSE_AUTORESTART    1		

/** Constant Voltage Only Fault Response Set to Latch-Off  */
#define INNO3PRO_CVOL_FAULT_RESPONSE_LATCHOFF       2		



/** Constant Voltage Only Fault Timer Set to 8ms */
#define INNO3PRO_CVOL_FAULT_TIMER_8MS               0	

/** Constant Voltage Only Fault Timer Set to 16ms */
#define INNO3PRO_CVOL_FAULT_TIMER_16MS              1	

/** Constant Voltage Only Fault Timer Set to 32ms */
#define INNO3PRO_CVOL_FAULT_TIMER_32MS              2	

/** Constant Voltage Only Fault Timer Set to 64ms */
#define INNO3PRO_CVOL_FAULT_TIMER_64MS              3		



/** Interrupt Mask for Control Secondary Fault */
#define INNO3PRO_INTERRUPT_CONTROL_S_MASK           0x40   

/** Interrupt Mask for BPS Current Latch-off Fault */
#define INNO3PRO_INTERRUPT_BPS_CURR_LO_FAULT_MASK   0x20	

/** Interrupt Mask for CVO Mode Peak Load Timer Fault */ 
#define INNO3PRO_INTERRUPT_CVO_PKLOAD_TIMER_MASK    0x10	

/** Interrupt Mask for IS-Pin Short Fault */ 
#define INNO3PRO_INTERRUPT_ISSC_MASK                0x08	

/** Interrupt Mask for Undervoltage Fault */  
#define INNO3PRO_INTERRUPT_VOUT_UV_MASK             0x02	

/** Interrupt Mask for Overvoltage Fault */ 
#define INNO3PRO_INTERRUPT_VOUT_OV_MASK             0x01	



/** Over Temperature Fault Hysteresis Set to 40 Degrees Celsius */
#define INNO3PRO_OTP_FAULT_HYST_40DEG               0		

/** Over Temperature Fault Hysteresis Set to 60 Degrees Celsius */
#define INNO3PRO_OTP_FAULT_HYST_60DEG               1		  



/** Constant Voltage Load Default Settings */
#define INNO3PRO_CVLOAD_DEFAULT                     0x20	

/** Constant Voltage Load Recommended Settings */
#define INNO3PRO_CVLOAD_RECOMMENDED                 0x80	



/** Loop Speed 1 Default Settings */ 
#define INNO3PRO_LOOPSPEED1_DEFAULT                 0x281E	

/** Loop Speed 1 Recommended Settings */
#define INNO3PRO_LOOPSPEED1_RECOMMENDED             0x140A	



/** Loop Speed 2 Default Settings */
#define INNO3PRO_LOOPSPEED2_DEFAULT                 0x08C8	

/** Loop Speed 2 Recommended Settings */
#define INNO3PRO_LOOPSPEED2_RECOMMENDED             0x0F84		

///@}


/** 
	@name 	PI_COMMAND Register Address Assignments	
	@brief	Defines the Command Registers to Control
 */
///@{ 


/**  Series Bus Switch Control Register				*/
#define INNO3PRO_VBEN                   0x04

/**	 Activate Bleeder(Vout) Function Register		*/
#define INNO3PRO_BLEEDER                0x86

/**	 Load (VBUS) Discharge Register					*/
#define INNO3PRO_VDIS                   0x08

/**	 Latch-off Device Register						*/
#define INNO3PRO_TURN_OFF_PSU           0x8A

/**	Speed of Output CV/CC Update Register           */
#define INNO3PRO_FAST_VI_CMD            0x8C

/**  Constant Voltage Only Register					*/
#define INNO3PRO_CVO                    0x0E	

/**  Output Voltage Register						*/
#define INNO3PRO_CV                     0x10	

/**  Over-Voltage Threshold Register				*/	
#define INNO3PRO_OVA                    0x92

/**  Under-Voltage Threshold Register				*/
#define INNO3PRO_UVA                    0x94

/**  Cable Drop Compensation Register				*/
#define INNO3PRO_CDC                    0x16

/**  Constant Current Regulation Register			*/
#define INNO3PRO_CC                     0x98

/**  Constant Output Power Knee Voltage Register	*/
#define INNO3PRO_VKP                    0x1A

/**  Over Voltage Fault Response Register			*/
#define INNO3PRO_OVL                    0x1C

/**  Under Voltage Fault Response Register			*/
#define INNO3PRO_UVL                    0x9E

/**  IS-Pin Short Fault Response  and
     Detection Frequency Register                   */
#define INNO3PRO_ISSC                   0xA2

/**  UVL Fault Timer Register						*/
#define INNO3PRO_UVL_TIMER              0xA4

/**  Communication Rate Monitor Register			*/
#define INNO3PRO_WATCHDOG_TIMER         0x26

/**  Constant Voltage Mode Fault Response Register	*/
#define INNO3PRO_CVOL                   0xA8

/**  Constant Voltage Fault Timer Register          */
#define INNO3PRO_CVOL_TIMER             0x2A

/**  Interrupt Mask Register                        */
#define INNO3PRO_INTERRUPT              0x2C

/**  Secondary Over-Temperature 
     Fault Hysteresis Register                      */
#define INNO3PRO_OTP                    0xAE

/** Constant Voltage Load                           */
#define INNO3PRO_CV_LOAD  				0x30

/** Loop Speed 1                                    */
#define INNO3PRO_LOOP_SPEED_1           0x32

/** Loop Speed 2                                    */
#define INNO3PRO_LOOP_SPEED_2           0x34

///@}



/** 
	@name 	Telemetry(Read-Back) Register Address Assignments	
	@brief	Defines the Telemetry Report Back Registers to Read
 */
///@{ 

/**  Revision ID  Telemetry Register                            */
#define INNO3PRO_READ0               0x00

/**  Output Voltage Set-Point  Telemetry Register               */
#define INNO3PRO_READ1               0x02
    
/**  Under-Voltage Threshold  Telemetry Register                */
#define INNO3PRO_READ2               0x04

/**  Over-Voltage Threshold  Telemetry Register                 */
#define INNO3PRO_READ3               0x06

/**  VBEN,BLEEDER,PSUOFF,FSTVIC,CVO,OTP,CDC	Telemetry Register  */
#define INNO3PRO_READ4               0x08

/**  Constant Current , Constant Power Telemetry Register       */
#define INNO3PRO_READ5               0x0A

/**  OVL,UVL,CCSL,ISSC,UVLTIMER,WDTIMER,CVMODE,CVTIMER	
     Telemetry Register                                         */
#define INNO3PRO_READ6               0x0C

/**  Measured Output Current  Telemetry Register                */
#define INNO3PRO_READ7               0x0E

/**  Measured Output Voltage  Telemetry Register                */
#define INNO3PRO_READ9               0x12

/**  INNTERRUPT,CONTROL_S,VDIS,HIGH_FSW,OTP,VOUT2PCT,VOUT10PCT,
     ISSC, CCSC VOUT_UV,VOUT_OV Telemetry Register              */
#define INNO3PRO_READ10              0x14

/**  AR_CVO,AR_ISSC,CCSC,VOUT_OV,VOUT_UV,LO,LO_CVO,PSU_OFF,LO_ISSC,
     LO_CCSC,LO_VOUT_OV, LO_VOUT_UV, BPS_OV Telemetry Register  */
#define INNO3PRO_READ11              0x16

/**  Interrupts Telemetry Register                				*/
#define INNO3PRO_READ12              0x18

/**  Average Measured Output Current  Telemetry Register        */
#define INNO3PRO_READ13              0x1A

/**  Average Measured Output Voltage  Telemetry Register        */
#define INNO3PRO_READ14              0x1C

/**  Voltage DAC  Telemetry Register        					*/
#define INNO3PRO_READ15              0x5C

/** Loop Speed 1  Telemetry Register                            */
#define INNO3PRO_READ_LOOP_SPEED_1   0x20

/** Loop Speed 2  Telemetry Register                            */
#define INNO3PRO_READ_LOOP_SPEED_2   0x22


///@}



/** 
	@name 	Telemetry READ4 Bit Assignments	
	@brief	Defines the Bit Assignments on READ4  Register
 */
///@{ 

/**  VBUS Switch Enable             */
#define READ4_Reg_VBEN        14

/**  Minimum Load                   */
#define READ4_Reg_BLEEDER     13

/**  Turn PSU Off                   */
#define READ4_Reg_PSUOFF      12

/**  Fast VI Commands               */
#define READ4_Reg_FSTVIC      11

/**  Constant-Voltage Mode Only     */
#define READ4_Reg_CVO         10

/**  Over-Temperature Protection    */
#define READ4_Reg_OTP         9

///@}


/** 
	@name 	Telemetry READ10 Bit Assignments	
	@brief	Defines the Bit Assignments on READ10  Register
 */
///@{ 

/**  Interrupt Enable                       */
#define READ10_Reg_INTERRUPT_EN                15

/**  System Ready Signal                    */
#define READ10_Reg_CONTROL_S                   14

/**  Output Discharge                       */
#define READ10_Reg_VDIS                        13

/**  Switching Frequency High?              */
#define READ10_Reg_HIGH_FSW                    12

/**  Over Temperature Protection            */
#define READ10_Reg_OTP                          9

/**  2% Bleeder Enabled                     */
#define READ10_Reg_VOUT2PCT                     5

/**  VOUTADC > 1.1*Vout                     */
#define READ10_Reg_VOUT10PCT                    4

/**  IS-pin Short Circuit Detected          */
#define READ10_Reg_ISSC                         3

/**  Output Voltage UV Fault                */
#define READ10_Reg_VOUT_UV                      1

/**  Output Voltage OV Fault                */
#define READ10_Reg_VOUT_OV                      0

///@}


/** 
	@name 	Telemetry READ11 Bit Assignments	
	@brief	Defines the Bit Assignments on READ11  Register
 */
///@{ 

/**  CVO Mode AR                            */
#define READ11_Reg_ar_CV                        15

/**  IS-pin Short Circuit AR                */
#define READ11_Reg_ar_ISSC                      12

/**  Output Short-Circuit AR                */
#define READ11_Reg_ar_CCSC                      11

/**  Output Voltage OV AR                   */
#define READ11_Reg_ar_VOUT_OV                   10

/**  Output Voltage UV AR                   */
#define READ11_Reg_ar_VOUT_UV                   9

/**  Latch-Off (LO) Occurred                */
#define READ11_Reg_LO                           7

/**  CVO Mode LO                            */
#define READ11_Reg_Lo_CVO                       6

/**  PSU Turn-Off CMD Received              */
#define READ11_Reg_PSUOFF                       5

/**  IS-pin Short Circuit LO                */
#define READ11_Reg_Lo_ISSC                      4

/**  Output Voltage OV LO                   */
#define READ11_Reg_Lo_VOUT_OV                   2

/**  Output Voltage UV LO                   */
#define READ11_Reg_Lo_VOUT_UV                   1

/**  BPS-pin LO                             */
#define READ11_Reg_BPS_OV                       0

///@}


/** 
	@name 	Telemetry READ12 Bit Assignments	
	@brief	Defines the Bit Assignments on READ12  Register
 */
///@{ 

/**  Interrupts Masks                           */
#define READ12_Reg_CONTROL_S_MASK               14

/**  Interrupts Masks                           */
#define READ12_Reg_LO_Fault_MASK                13

/**  Interrupts Masks                           */
#define READ12_Reg_CCAR_MASK                    12

/**  Interrupts Masks                           */
#define READ12_Reg_ISSC_MASK                    11

/**  Interrupts Masks                           */
#define READ12_Reg_VOUT_UV_MASK                 9

/**  Interrupts Masks                           */
#define READ12_Reg_VOUT_OV_MASK                 8

/**  Interrupts Status                          */
#define READ12_Reg_CONTROL_S_STATUS             6

/**  Interrupts Status                          */
#define READ12_Reg_LO_FAULT_STATUS              5

/**  Interrupts Status                          */
#define READ12_Reg_CCAR_STATUS                  4

/**  Interrupts Status                          */
#define READ12_Reg_ISSC_STATUS                  3

/**  Interrupts Status                          */
#define READ12_Reg_VOUT_UV_STATUS               1

/**  Interrupts Status                          */
#define READ12_Reg_VOUT_OV_STATUS               0
///@}



/** 
	@name 	InnoSwitch3-Pro  Computation Macros	
	@brief	Defines the Computations needed by individual Registers
 */
///@{ 
//INNO3-PRO  COMPUTATION MACROS

/** Current Sense Resistor in	milli Ohm  */
#define INNO3PRO_RSENSE                          (float)(9.0)  

/** Current Sense Resistor Full Range Voltage in mV  */
#define INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE       (float)(31.1) 

 /**	Analog to Digital Full Range  */
#define INNO3PRO_ADC_FULL_RANGE                  (float)(128)  

/**  CC Set Point Computation:  (Value * Rsense * 128 / 32) */
#define INNO3PRO_CC_SET_PT_MULT                  (float)((INNO3PRO_ADC_FULL_RANGE * INNO3PRO_RSENSE) / INNO3PRO_FULL_RANGE_RSENSE_VOLTAGE)

 /**  Multiplier for Output Voltage Step Size of 10mv/LSB  */
#define INNO3PRO_CV_SET_PT_MULT                  (float)(100)  

 /**  Percentage Setting: 124% of CV  */ 
#define INNO3PRO_OV_PERCENTAGE_MULT              (float)(1.24) 

/**  Percentage Setting: 72% of CV  */ 
#define INNO3PRO_UV_PERCENTAGE_MULT              (float)(0.72) 

/**  Multiplier for OverVoltage Step Size of 100mv/LSB  */
#define INNO3PRO_OV_SET_PT_MULT                  (float)(10)

/**  Multiplier for UnderVoltage Step Size of 100mv/LSB  */
#define INNO3PRO_UV_SET_PT_MULT                  (float)(10)	

/**  Divider for Cable Drop Compensation Step Size of 50mv/LSB  */
#define INNO3PRO_CDC_SET_PT_DIV                  (float)(50)	

/**  Multiplier for Constant Output Power Knee Voltage Step Size of 100mv/LSB  */
#define INNO3PRO_VKP_SET_PT_MULT                 (float)(10)	
///@}



/** 
	@name 	InnoSwitch3-Pro  Sample Configuration Settings
	@brief	Defines example  values to be uploaded to InnoSwitch3-Pro 
 */
///@{ 
#define INNO3PRO_DEFAULT_CV_SET_PT_LEVEL          (float)(5)      //V
#define INNO3PRO_DEFAULT_OVA_SET_PT_LEVEL         (float)(6.2)    //V
#define INNO3PRO_DEFAULT_UVA_SET_PT_LEVEL         (float)(3)      //V
#define INNO3PRO_DEFAULT_CDC_ASSERT_LEVEL         (float)(300)    //mV
#define INNO3PRO_DEFAULT_CC_ASSERT_LEVEL          (float)(5.1)    //A
#define INNO3PRO_DEFAULT_VKP_ASSERT_LEVEL         (float)(7)      //V
#define INNO3PRO_DEFAULT_VBEN_CONTROL_LOGIC       (float)(0)      //Disable
#define INNO3PRO_DEFAULT_UVL_CONTROL_LOGIC        (float)(0)      //Auto-Restart


#define INNO3PRO_5V_CV_SET_PT_LEVEL               (float)(5)      //V
#define INNO3PRO_5V_CDC_ASSERT_LEVEL              (float)(300)    //mV
#define INNO3PRO_5V_CC_ASSERT_LEVEL               (float)(5.1)    //A
#define INNO3PRO_5V_VKP_ASSERT_LEVEL              (float)(7)      //V
#define INNO3PRO_5V_VBEN_CONTROL_LOGIC            (float)(1)      //Enable


#define INNO3PRO_8V_CV_SET_PT_LEVEL               (float)(8)      //V
#define INNO3PRO_8V_CDC_ASSERT_LEVEL              (float)(300)    //mV
#define INNO3PRO_8V_CC_ASSERT_LEVEL               (float)(5.1)    //A
#define INNO3PRO_8V_VKP_ASSERT_LEVEL              (float)(7)      //V
#define INNO3PRO_8V_VBEN_CONTROL_LOGIC            (float)(1)      //Enable


#define INNO3PRO_15V_CV_SET_PT_LEVEL              (float)(15)     //V
#define INNO3PRO_15V_CDC_ASSERT_LEVEL             (float)(300)    //mV
#define INNO3PRO_15V_CC_ASSERT_LEVEL              (float)(2.76)   //A
#define INNO3PRO_15V_VKP_ASSERT_LEVEL             (float)(7)      //V
#define INNO3PRO_15V_VBEN_CONTROL_LOGIC           (float)(1)      //Enable


#define INNO3PRO_20V_CV_SET_PT_LEVEL              (float)(20)     //V
#define INNO3PRO_20V_CDC_ASSERT_LEVEL             (float)(300)    //mV
#define INNO3PRO_20V_CC_ASSERT_LEVEL              (float)(2.1)    //A
#define INNO3PRO_20V_VKP_ASSERT_LEVEL             (float)(7)      //V
#define INNO3PRO_20V_VBEN_CONTROL_LOGIC           (float)(1)      //Enable


#define INNO3PRO_3V_CV_SET_PT_LEVEL               (float)(3)      //V
#define INNO3PRO_3V_CDC_ASSERT_LEVEL              (float)(300)    //mV
#define INNO3PRO_3V_CC_ASSERT_LEVEL               (float)(5.1)    //A
#define INNO3PRO_3V_VKP_ASSERT_LEVEL              (float)(7)      //V
#define INNO3PRO_3V_VBEN_CONTROL_LOGIC            (float)(1)      //Enable

///@}

#endif	/* CONFIG_H */

