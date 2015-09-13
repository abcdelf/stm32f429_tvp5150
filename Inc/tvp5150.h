#ifndef __tvp5150_H
#define __tvp5150_H

#include <stdint.h>
#include <stdbool.h>
//#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"

//#define AIP1A 0
//#define AIP1B 2
//#define AIP_S 1
typedef enum
{
  TVP_CS_AIP1A             = 0x00,  /*!< Composite AIP1A    */
  TVP_CS_AIP_S             = 0x01,  /*!< S-Video            */
  TVP_CS_AIP1B             = 0x02   /*!< Composite AIP1B    */
}TVP_CS_TypeDef; //ChanelSource

typedef enum
{																		/*!<        === offset or gain ===        */
  TVP_ACC_DISABLED         = 0x00,  /*!< Disabled                             */
  TVP_ACC_AUTO             = 0x01,  /*!< Automatic                            */
  TVP_ACC_FROZEN           = 0x03   /*!< Level frozen to previously set value */
}TVP_ACC_TypeDef;          //AnalogChannelControls

typedef enum
{
  TVP_VS_AUTO             = 0x00,  /*!< AUTO          */
  TVP_VS_NTSC             = 0x02,  /*!< NTSC          */
  TVP_CS_PAL              = 0x04,  /*!< PAL BGH       */
  TVP_CS_PALM             = 0x06,  /*!< PAL M         */
  TVP_CS_COMB             = 0x08,  /*!< Combination-N */
  TVP_CS_NTSC4            = 0x0A   /*!< NTSC 4.43     */
}TVP_VS_TypeDef; //VideoStandart

typedef struct
{
	TVP_ACC_TypeDef Offset;
	TVP_ACC_TypeDef Gain;
	uint8_t VAL;
}TVP_ACC_StructTypeDef;

typedef struct
{
	bool PowerDown;
	bool GLCO;
	uint8_t VAL;
}TVP_OMC_StructTypeDef; //OperatingModeControls structure

typedef struct
{
	uint16_t DeviceId;
	uint8_t ROM;
	uint8_t RAM;
	uint16_t VerticalLineCount;
}TVP_Info_StructTypeDef; //Info structure

typedef struct
{
	uint8_t r1;
	uint8_t r2;
	uint8_t AGC;
	uint8_t SCH;
	uint8_t r5;
	uint8_t int_r1;
	uint8_t int_r2;
}TVP_Status_StructTypeDef; //Status structure

typedef enum
{
  TVP_P09_SCLK             = 0x00,  /*!< SCLK (default)  */
  TVP_P09_PCLK             = 0x01,  /*!< PCLK            */
}TVP_P09_TypeDef; //Pin 9

typedef enum
{
  TVP_P27_INTREQ           = 0x00,  /*!< INTREQ (default)  */
  TVP_P27_GPCL             = 0x01,  /*!< GPCL or VBLK      */
}TVP_P27_TypeDef; //Pin 27

typedef enum
{
  TVP_P24_VSYNC            = 0x00,  /*!< VSYNC (default)   */
  TVP_P24_PALI             = 0x01,  /*!< PALI              */
  TVP_P24_LOCK             = 0x02,  /*!< Lock indicator    */
}TVP_P24_TypeDef; //Pin 24

typedef enum
{
  TVP_P23_FID              = 0x00,  /*!< FID                */
  TVP_P23_GLCO             = 0x01,  /*!< GLCO (default)     */
  TVP_P23_LOCK             = 0x02,  /*!< Lock indicator     */
}TVP_P23_TypeDef; //Pin 24

typedef enum
{
  TVP_AUTO                 = 0x00,  /*!< (default)               */
  TVP_Enabled              = 0x02,  /*!<       */
  TVP_Disabled             = 0x03,  /*!<      */
}TVP_CK_TypeDef; //Color killer

typedef struct
{
	TVP_CK_TypeDef ColorKiller;
	uint8_t Theshold;
	uint8_t VAL;
}TVP_CK_StructTypeDef; //Color killer structure

typedef struct
{
	TVP_P09_TypeDef pin9;
	TVP_P27_TypeDef pin27;
	TVP_P24_TypeDef pin24;
	TVP_P23_TypeDef pin23;
	uint8_t VAL;
}TVP_Pins_StructTypeDef; //Pins config structure

typedef struct
{
	uint8_t Contrast;    //0..128(default)..255
	int8_t Hue;          //-180..0(default)..180
	uint8_t Saturation;  //0..128(default)..255
	uint8_t Brightness;  //0..128(default)..255
}TVP_IC_StructTypeDef; //Image config structure

typedef struct
{
	bool palm;        //1(default)
	bool paln;        //1(default)
	bool n443;        //1(default)
	uint8_t VAL;      
}TVP_ASM_StructTypeDef; //Autoswitch Mask

typedef enum
{
  TVP_LSD_0                 = 0x00,  /*!< (default)               */
  TVP_LSD_Plus1             = 0x01,  /*!<       */
  TVP_LSD_Plus2             = 0x02,  /*!<       */
  TVP_LSD_Plus3             = 0x03,  /*!<       */
  TVP_LSD_Plus4             = 0x04,  /*!<       */
  TVP_LSD_Plus5             = 0x05,  /*!<       */
  TVP_LSD_Plus6             = 0x06,  /*!<       */
  TVP_LSD_Plus7             = 0x07,  /*!<       */
  TVP_LSD_Minus1            = 0x08,  /*!<       */
  TVP_LSD_Minus2            = 0x09,  /*!<       */
  TVP_LSD_Minus3            = 0x0A,  /*!<       */
  TVP_LSD_Minus4            = 0x0B,  /*!<       */
  TVP_LSD_Minus5            = 0x0C,  /*!<       */
  TVP_LSD_Minus6            = 0x0D,  /*!<       */
  TVP_LSD_Minus7            = 0x0E,  /*!<       */
  TVP_LSD_Minus8            = 0x0F,  /*!<       */
}TVP_LSD_TypeDef; //luminance signal dellay

typedef enum
{
  TVP_LPG_0                 = 0x00,  /*!< (default)               */
  TVP_LPG_05                = 0x01,  /*!<       */
  TVP_LPG_1                 = 0x02,  /*!<       */
  TVP_LPG_3                 = 0x03,  /*!<       */
}TVP_LPG_TypeDef; //Peaking gain

typedef enum
{
  TVP_LFS_NO                = 0x00,  /*!< (default)               */
  TVP_LFS_Notch1            = 0x01,  /*!<       */
  TVP_LFS_Notch2            = 0x02,  /*!<       */
  TVP_LFS_Notch3            = 0x03,  /*!<       */
}TVP_LFS_TypeDef; //Luminance filter stop band bandwidth

typedef struct
{
	bool BypassMode;         //Luma bypass mode: 0 (default) - bypass the chroma trap and comb filters; 1 - bypass the whole luma processing
	bool NoPedetal;          //Pedestal on the analog video input signal: 0 (default) - present; 1 -  not present
	bool NoRawHeader;        //656 ancillary headers for raw data: 0 - insert; 1 (default) - disabled
	bool VertBlanckBypass;   //Luminance bypass during vertical blanking: 0 (default) - disabled; 1 - enabled
	TVP_LSD_TypeDef SignalDelay; //Luminance signal delay with respect to chrominance signal
	bool Filter;             //Luminance filter: 0 (default) - comb filter; 1 - chroma trap filter
	TVP_LPG_TypeDef PeakingGain; //Peaking gain: 0 (default)
	TVP_LFS_TypeDef FilterStopBand; //Luminance filter stop band bandwidth (MHz): 0 (default)
	uint8_t VAL1;      
	uint8_t VAL2;      
	uint8_t VAL3;      
}TVP_LC_StructTypeDef; //LuminanceControl

typedef struct
{
	bool VBKO;      //VBKO (pin 27): 0 - GPLC (default); 1 - VBKL
	bool GPLC;      //0 - (default)
	bool GPLC_Mode; //0 - GPLC input (default); 1 - GPLC output
	bool HVLK;      //0 - PALI (default); 1 - HLK
	bool YUV;       //0 - high impendance (default); 1 - active
	bool HSYNK;     //HSYNK, VSYNK: 0 - high impendance (default); 1 - active
	bool VBLK;      //Vertical blanking: 0 - off (default); 1 - onn
	bool SCLK;      //0 - high impendance; 1 - active (default)
	uint8_t VAL;
}TVP_SMC_StructTypeDef; //MiscellaneousControls structure

typedef enum
{
  TVP_YOF_YUV            = 0x00,  /*!< 4:2:2 YUV               */
  TVP_YOF_ITU            = 0x07,  /*!< ITU-R BT.656  (default) */
}TVP_YOF_TypeDef; //YUV output format

typedef enum
{
  TVP_YUD_Normal         = 0x00,  /*!< Normal            (default)   */
  TVP_YUD_Filter         = 0x01,  /*!< Digital composite output pins connected to decimation filter output, decoder function bypassed, 
	                                data output alternately as Y and UV buses at the SCLK rate  */
  TVP_YUD_AD             = 0x02,  /*!< YUV output pins connected to A/D output, decoder function bypassed, data output at SCLK rate  */
}TVP_YUD_TypeDef; //YUV data path bypass

typedef struct
{
	bool YUV_CodeRange;               //YUV output code range: 0 - ITU-R BT.601 ; 1 (default) - Extended
	bool UV_CodeFormat;               //UV code format 0(default) - Offset binary; 1 - Straight binary
	TVP_YUD_TypeDef YUV_Data;         //YUV data path bypass: 0 (default)
	TVP_YOF_TypeDef YUV_OutputFormat; //YUV output format: 7 (default)
	uint8_t VAL;
}TVP_OAR_StructTypeDef; //Outputs and Data Rates Select structure

typedef struct
{
	int16_t Start;    //Active Video Cropping Start Pixel: -512..0(default)..511
	int16_t Stop;     //Active Video Cropping Stop Pixel; -512..0(default)..511
	bool AVID;        //AVID out active in VBLK: 0 (default) - active; 1 - inactive
	uint8_t VAL1;
	uint8_t VAL2;
	uint8_t VAL3;
	uint8_t VAL4;
}TVP_AVC_StructTypeDef; //Active Video Croping structure

typedef struct
{
	bool CDTO_LSB;      //CDTO_LSB_Switch (CDTO_SW) forced to: 0; 1 (default)
	bool GLCO_RTC;      //GLCO/RTC: 1 - GLCO; 0 (default) - RTC
	uint8_t VAL;
}TVP_SG_StructTypeDef; //Genlock and RTC Register structure

typedef struct
{
	int8_t start;               
	int8_t stop;               
}TVP_VB_StructTypeDef; //Vertical Blanking structure

typedef enum
{
  TVP_ACGC_Enabled             = 0x00,  /*!< (default)               */
  TVP_ACGC_Disabled            = 0x02,  /*!<       */
  TVP_ACGC_Previous            = 0x03,  /*!<       */
}TVP_ACGC_TypeDef; //Automatic color gain control

typedef enum
{
  TVP_CCFM_3_121_4_2    = 0x00,  /*!< 3-line (1, 2, 1)/4 and 2-line comb filter                */
  TVP_CCFM_3_121_4      = 0x01,  /*!< 3-line (1, 2, 1)/4 comb filter (default NTSC)            */
  TVP_CCFM_3_101_2_2    = 0x02,  /*!< 3-line (1, 0, 1)/2 comb filter and 2-line comb filter    */
  TVP_CCFM_3_101_2      = 0x03,  /*!< 3-line (1, 0, 1)/2 comb filter and no comb filte         */
  TVP_CCFM_4_1111_4_2   = 0x04,  /*!< 4-line (1, 1, 1, 1)/4 and 2-line comb filter                       */
  TVP_CCFM_4_1111_4     = 0x05,  /*!< 4-line (1, 1, 1, 1)/4 comb filter and no comb filter (default PAL)  */
  TVP_CCFM_4_1331_4_2   = 0x06,  /*!< 4-line (1, 3, 3, 1)/8 comb filter and 2-line comb filter            */
  TVP_CCFM_4_1331_4     = 0x07,  /*!< 4-line (1, 3, 3, 1)/8 comb filter and no comb filter     */
  TVP_CCFM_2_2          = 0x08,  /*!< 2-line comb filter                                       */
  TVP_CCFM_2            = 0x0F,  /*!< 2-line comb filter                                       */
}TVP_CCFM_TypeDef; //Chrominance comb filter mode

typedef struct
{
	bool ColorPLL_Reset;             //Color PLL: 0 - not reset; 1 (default) - reset               
	bool CE;                         //Chrominance comb filter (CE): 0 - disable; 1 (default) - enable          
	bool ACE;                        //Chrominance adaptive comb filter (ACE): 0 - not disable; 1 (default) - enable          
	TVP_ACGC_TypeDef ACGC;           //Automatic color gain control (ACGC): 0 (default) - enabled         
	TVP_CCFM_TypeDef CombFilterMode; //Chrominance comb filter mode: 0 (default) - enabled         
	bool WCF;                        //Wideband chroma filter (WCF): 0 - disable; 1 (default) - enable          
	TVP_LFS_TypeDef FilterSelect;    //Chrominance filter select: 0 (default)
	uint8_t VAL1;
	uint8_t VAL2;
}TVP_CC_StructTypeDef; //Chrominance Control structure

#define		TVP_WRITE_ADDRESS 0xB8 //I2CSEL = 0
//#define	TVP_WRITE_ADDRESS 0xBA //I2CSEL = 1
#define		TVP_READ_ADDRESS 0xB9 //I2CSEL = 0
//#define	TVP_READ_ADDRESS 0xBB //I2CSEL = 1

#define TVP_Addr_InputSource 0x0					 //*
#define TVP_Addr_AnalogChannelControls 0x1 //*
#define TVP_Addr_OperatingModeControls 0x2 //*
#define TVP_Addr_MiscellaneousControls 0x3 //*
#define TVP_Addr_AutoswitchMask 0x4        //*
#define TVP_Addr_SoftwareReset 0x5         //*
#define TVP_Addr_ColorKillerControl 0x6    //*
#define TVP_Addr_LuminanceControl1 0x7     //*
#define TVP_Addr_LuminanceControl2 0x8     //*
#define TVP_Addr_BrightnessControl 0x9     //*
#define TVP_Addr_SaturationControl 0x0A    //*
#define TVP_Addr_HueControl 0x0B           //*
#define TVP_Addr_ContrastControl 0x0C      //*
#define TVP_Addr_OutputAndRatesSelect 0x0D //*
#define TVP_Addr_LuminanceControl3 0x0E    //*
#define TVP_Addr_PinsConfig 0x0F           //*
#define TVP_Addr_ActiveVideoCropingStartMSB 0x11 //*
#define TVP_Addr_ActiveVideoCropingStartLSB 0x12 //*
#define TVP_Addr_ActiveVideoCropingStopMSB 0x13  //*
#define TVP_Addr_ActiveVideoCropingStopLSB 0x14  //*
#define TVP_Addr_Genlock 0x15                    //*
#define TVP_Addr_HorisontalSynkStart 0x16        //*
#define TVP_Addr_VerticalBlankingStart 0x18      //*
#define TVP_Addr_VerticalBlankingStop 0x19       //*
#define TVP_Addr_CrominanceControl1 0x1A         //*
#define TVP_Addr_CrominanceControl2 0x1B         //*
#define TVP_Addr_InterruptResetRegisterB 0x1C
#define TVP_Addr_InterruptEnableRegisterB 0x1D
#define TVP_Addr_InterruptConfigRegisterB 0x1E
#define TVP_Addr_VideoStandart 0x28        //*

#define TVP_Addr_DeviceMSB 0x80            //*//Only read
#define TVP_Addr_DeviceLSB 0x81            //*
#define TVP_Addr_ROMVersion 0x82           //*
#define TVP_Addr_RAMVersion 0x83 					 //*
#define TVP_Addr_VerticalLineCountMSB 0x84 //*
#define TVP_Addr_VerticalLineCountLSB 0x85 //*

#define TVP_Addr_InterruptStatusRegisterB 0x86
#define TVP_Addr_InterruptActiveRegisterB 0x87
#define TVP_Addr_StatusRegister1 0x88
#define TVP_Addr_StatusRegister2 0x89
#define TVP_Addr_StatusRegister3 0x8A      //*
#define TVP_Addr_StatusRegister4 0x8B      //*
#define TVP_Addr_StatusRegister5 0x8C

#define TVP_Addr_ClosedCaptionData1 0x90
#define TVP_Addr_ClosedCaptionData2 0x91
#define TVP_Addr_ClosedCaptionData3 0x92
#define TVP_Addr_ClosedCaptionData4 0x93
#define TVP_Addr_WSS_Data1 0x94
#define TVP_Addr_WSS_Data2 0x95
#define TVP_Addr_WSS_Data3 0x96
#define TVP_Addr_WSS_Data4 0x97
#define TVP_Addr_WSS_Data5 0x98
#define TVP_Addr_WSS_Data6 0x99
#define TVP_Addr_VPS_Data01 0x9A
#define TVP_Addr_VPS_Data02 0x9B
#define TVP_Addr_VPS_Data03 0x9C
#define TVP_Addr_VPS_Data04 0x9D
#define TVP_Addr_VPS_Data05 0x9E
#define TVP_Addr_VPS_Data06 0x9F
#define TVP_Addr_VPS_Data07 0x0A1
#define TVP_Addr_VPS_Data08 0x0A2
#define TVP_Addr_VPS_Data09 0x0A3
#define TVP_Addr_VPS_Data10 0x0A4
#define TVP_Addr_VPS_Data11 0x0A5
#define TVP_Addr_VPS_Data12 0x0A6
#define TVP_Addr_VITC_Data01 0x0A7
#define TVP_Addr_VITC_Data02 0x0A8
#define TVP_Addr_VITC_Data03 0x0A9
#define TVP_Addr_VITC_Data04 0x0A7
#define TVP_Addr_VITC_Data05 0x0AA
#define TVP_Addr_VITC_Data06 0x0AB
#define TVP_Addr_VITC_Data07 0x0AC
#define TVP_Addr_VITC_Data08 0x0AD
#define TVP_Addr_VITC_Data09 0x0AE
#define TVP_Addr_VITC_Data10 0x0AF
#define TVP_Addr_VBI_FIFO 0x0B0

#define TVP_Addr_TeletextFilet11 0x0B1  //read write
#define TVP_Addr_TeletextFilet12 0x0B2
#define TVP_Addr_TeletextFilet13 0x0B3
#define TVP_Addr_TeletextFilet14 0x0B4
#define TVP_Addr_TeletextFilet15 0x0B5
#define TVP_Addr_TeletextFilet21 0x0B6
#define TVP_Addr_TeletextFilet22 0x0B7
#define TVP_Addr_TeletextFilet23 0x0B8
#define TVP_Addr_TeletextFilet24 0x0B9
#define TVP_Addr_TeletextFilet25 0x0BA

void TVP_Init(void);

void TVP_Write(uint8_t addr, uint8_t data);
uint8_t TVP_Read(uint8_t addr);

void TVP_SetInputSource(TVP_CS_TypeDef ChanelSource);
TVP_CS_TypeDef TVP_GetInputSource(void);

void TVP_SetAnalogChannelControls(TVP_ACC_TypeDef OffsetControl, TVP_ACC_TypeDef GainControl);
void TVP_GetAnalogChannelControls(TVP_ACC_StructTypeDef *res);

void TVP_SetOperatingModeControls(bool PowerDown, bool GLCO);
void TVP_GetOperatingModeControls(TVP_OMC_StructTypeDef *res);

void TVP_SetMiscellaneousControls(TVP_SMC_StructTypeDef *res);
void TVP_GetMiscellaneousControls(TVP_SMC_StructTypeDef *res);

void TVP_SetAutoswitchMask(bool paln, bool palm, bool ntsc443);
void TVP_GetAutoswitchMask(TVP_ASM_StructTypeDef *res);

void TVP_SoftwareReset(void);

void TVP_SetColorKillerControl(TVP_CK_TypeDef colorKiller, uint8_t theshold);
void TVP_GetColorKillerControl(TVP_CK_StructTypeDef *res);

void TVP_SetLuminanceControl(TVP_LC_StructTypeDef *res);
void TVP_GetLuminanceControl(TVP_LC_StructTypeDef *res);

void TVP_SetOutputAndRates(TVP_OAR_StructTypeDef *res);
void TVP_GetOutputAndRates(TVP_OAR_StructTypeDef *res);

void TVP_InitImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfig(TVP_IC_StructTypeDef *cfg);
void TVP_SetImageConfigA(uint8_t Brightness, uint8_t Contrast, uint8_t Saturation, int8_t Hue);
void TVP_GetImageConfig(TVP_IC_StructTypeDef *cfg);

void TVP_InitPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_SetPinsConfig(TVP_Pins_StructTypeDef *pins);
void TVP_GetPinsConfig(TVP_Pins_StructTypeDef *pins);

void TVP_SetActiveVideoCroping(TVP_AVC_StructTypeDef *res);
void TVP_GetActiveVideoCroping(TVP_AVC_StructTypeDef *res);

void TVP_SetGenlock(bool CDTO_LSB, bool GLCO_RTC);
void TVP_GetGenlock(TVP_SG_StructTypeDef *res);

void TVP_SetHorizontalSyncStart(uint8_t HSYNC);
uint8_t TVP_GetHorizontalSyncStart(void);

void TVP_SetVerticalBlanking(TVP_VB_StructTypeDef *res);
void TVP_GetVerticalBlanking(TVP_VB_StructTypeDef *res);

void TVP_SetChrominanceControl(TVP_CC_StructTypeDef *res);
void TVP_GetChrominanceControl(TVP_CC_StructTypeDef *res);

void TVP_SetVideoStandart(TVP_VS_TypeDef VideoStandart);
TVP_VS_TypeDef TVP_GetVideoStandart(void);

void TVP_GetInfo(TVP_Info_StructTypeDef *res);
void TVP_GetStatus(TVP_Status_StructTypeDef *res);

#endif /*__ tvp5150_H */

