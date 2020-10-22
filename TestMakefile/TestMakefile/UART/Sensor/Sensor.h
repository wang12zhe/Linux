/*******************************************************************************

      3G PID PID Sensor

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: PID.H
      Hardware: 3G PID main PCB rev. 1
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

--------------------------------------------------------------------------------

   Revision History

   == V1.00.01 ==
      10/30/06 - Wenpeng

*******************************************************************************/
#ifndef __SENSOR_H
#define __SENSOR_H
#include "./../Comm/TypeDef.h"
#include "SenRelatedDef.h"

#define ON                                1
#define OFF                               0

#define SCDC_SENSOR           0x59

#define PID_ADDR                          0x6E
#define PID_BARCODE_ID0                   0
#define PID_BARCODE_ID1                   1
#define PID_10ADC_LAMP                    2
#define PID_10ADC_CHANNELL                3
#define PID_10ADC_CHANNELH                4

#define PID_SENSOR_ID                     0X88
#define SID_106EV                         0X00
#define SID_117EV                         0X01
#define SID_98EV                          0X03
#define SID_106EV_01_5000                 0X04
#define SID_106EV_001_2000                0x05
#define SID_106EV_01_2000                 0X06
#define SID_106EV_1_1000                  0X07
#define SID_98EV_01_1000                  0X08

#define PID_SEN_INSTALL_MAP               0x01
#define PID_SEN_EN_MAP                    0x01

#define PID_AUTOCLEAN_TIME                14400

#define PID_SS_TEST                       0x01        // test mode, via UART
#define PID_SS_LAMP_ON                    0x02        // lamp on is detected
#define PID_SS_QUENCH                     0x04        // quench because of high concentration
#define PID_SS_LAMP_STATUS_CHANGE         0x08        // lamp from on to off or off to on
#define PID_SS_SET_LAMP_FAIL              0x10        // master set lamp on or off but failed

#define PID_FULLSCALE                     8000        // ~12% of full ADC scale(65535)
#define PID_OVER_RANGE                    10000000

#define PID_SUBID_MASK                    0xC0

#define PID_EE_MEM_SIZE                   256L

#define PID_SEN_NAME                      "PID"
#define PID_SEN_PRO_YEAR                  0x0
#define PID_SEN_PRO_MONTH                 0x0
#define PID_SEN_PRO_DAY                   0x0
#define PID_SEN_WARR_DAY                  450   //Sensor Warranty Day

#define PID_SEN_RAW_CHNN                  0x6
#define DFT_BUMP_TOLERANCE                20    //Percent



//SCDC sensor error code
#define DEFAILURE                  001
#define I2CTIMEOUT                 002
#define AKMREBOOT                  003
#define THREBOOT                   004
#define REWORK                     005

#define RAWSENSORLOSE              101
#define REFAILURE                  102 
#define ELECTROLYTEDRYOUT          103
#define ENDOFLIFE                  104
#define CEFAILURE                  105
#define LELBEADBROKEN              106
#define LAMPFAILURE                107
#define LED_PDFAILURE              108
#define CALDUEDAY                  109
#define BUMPDUEDAY                 110
#define UFSETVALURERROR            111
#define TEMOOVERRANGE              112
#define TOOWET                     113
#define LAMPSTATUS                 115
#define CURRENTLEAKAGE             116
#define THSENSOR                   117

#define MEASUNIT_PPM                       0
#define MEASUNIT_PPB                       1
#define MEASUNIT_MG_M3                     2
#define MEASUNIT_UG_M3                     3

#define SUC_PPM                             0x00        // ppm
#define SUC_PER                             0x01        // %LEL, %VOL
#define SUC_PPB                             0x02        // ppb
#define SUC_DEGC                            0x03        // degree C
#define SUC_MG                              0x04        // mg
#define SUC_UG                              0x05        // ug
#define SUC_MA                              0x06        // mA
#define SUC_V                               0x07        // V
#define SUC_DEGF                            0x08        // degree F
#define SUC_USV_H                           0x09        // uSv/h
#define SUC_UR_H                            0x0A        // uR/h
#define SUC_CPS                             0x0B        // cps
#define SUC_M_S                             0x0C        // m/s
#define SUC_DEG                             0x0D        // degree
#define SUC_UG_M3                           0x0E        // ug/m^3
#define SUC_MG_M3                           0x0F        // mg/m^3
#define SUC_MBAR                            0x10        // mBar
#define SUC_W_M2                            0x11        // W/m2
#define SUC_SPACE                           0x12        // ' '
#define SUC_BTS_M                           0x13        // Bts/m for life shirt
#define SUC_BTH_M                           0x14        // Bth/m for life shirt
#define SUC_MSV_H                           0x15        // mSv/h
#define SUC_MR_H                            0x16        // mR/h
#define SUC_KCPS                            0x17        // Kcps
#define SUC_SV_H                            0x18        // Sv/h
#define SUC_R_H                             0x19        // R/h
#define SUC_MCPS                            0x1A        // Mcps
#define SUC_USV                             0x1B        // uSv
#define SUC_UR                              0x1C        // uR
#define SUC_MSV                             0x1D        // mSv
#define SUC_MR                              0x1E        // mR
#define SUC_SV                              0x1F        // Sv
#define SUC_R                               0x20        // R
#define SUC_UREM                            0x21
#define SUC_MREM                            0x22
#define SUC_REM                             0x23
#define SUC_UREM_H                          0x24
#define SUC_MREM_H                          0x25
#define SUC_REM_H                           0x26
#define SUC_PERLEL                          0x27
#define SUC_PERVOL                          0x28
#define SUC_UGY                             0x29
#define SUC_MGY                             0x2A
#define SUC_GY                              0x2B
#define SUC_UGY_H                           0x2C
#define SUC_MGY_H                           0x2D
#define SUC_GY_H                            0x2E
#define SUC_PER_CH4                         0x2F
#define SUC_U                               0x30 //
#define SUC_UMOL_MOL                        0x31 //umol/mol
#define SUC_X10_6                           0x32 //x10e-6
#define SUC_G                               0x33 //g
#define SUC_BPM                             0x34 //bpm
#define SUC_KM_H                            0x35 //km/h

#define SUC_INVALID                         0xFF
typedef struct {
    INT8U year;
    INT8U month;
    INT8U day;
    INT8U hour;
    INT8U minute;
    INT8U second;
    INT8U Reserved0[2];                 // filled with 0x00  This two bytes are very importance
} RTC;



typedef struct {
    INT8U u8_SerialNumber[10];
    INT8U u8_SensorID;
    INT8U u8_FirmwareVersion[4];
    INT8U u8_InitFlag;
} PID_SYSPARA;

#define BUMP_RESP_TIME              9     //CAL_SPAN_RSP_TIME x 30%
#define CAL_FRESH_RESP_TIME         30
#define CAL_ZERO_RESP_TIME          30
#define CAL_SPAN_RESP_TIME          30
#define CAL_SPANH_RESP_TIME         30


#define SENINDEX                    0x00
/* 904-E800-202.01 */
typedef struct {
    INT8U hwVer      : 4;
    INT8U partId     : 3;
    INT8U            : 1;
} _hwId_bits;

typedef struct {
    INT8U id         : 4;
    INT8U            : 1;
    INT8U srv        : 1;
    INT8U pcb        : 1;
    INT8U beta       : 1;
} _fwId_bits;

/* little endian */
typedef union {
    INT32U id;
    struct {
        INT8U_BIT(fwId, _fwId_bits);
        INT8U_BIT(hwId, _hwId_bits);
        INT8U     modelId;
        INT8U     familyId;
    };
} InstrId_t;

typedef struct _fwVer {
    INT8U Major;
    INT8U Minor;
    INT8U Patch;
    INT8U: 8;
} FW_VER;

typedef struct {           // structure size 80 bytes
    INT8U     u8_SN[16];                // Serial number, 16-ASCII(for 10-ASCII SN, unused bytes reserved as 0x00)
    InstrId_t st_InstrID;               // Instrument ID( high 3 byte always 0x00, reserved for future use )
    INT8U     u8_ModelName[16];         // Model Nmae
    INT8U     u8_ProductName[32];       // Product Nmae
    FW_VER    st_FwVer;                 // Firmware version
    RTC       st_FwBuild;               // Firmware build date/time
} DEV_INFO;

typedef struct {
    INT8U MT_Min            : 1;
    INT8U MT_Avg            : 1;
    INT8U MT_Max            : 1;
    INT8U MT_RealTime       : 1;
    INT8U                   : 1;
    INT8U                   : 1;
    INT8U                   : 1;
    INT8U                   : 1;
} __measType_bits;

struct SensorDeadband{
    INT8U Enable;
    INT32U OutLimit;
    INT32U InLimit;
};
typedef struct {
    INT8U NumOfSensorChannels_0      : 4;
    INT8U                            : 4;
} __SenChannels_bits;
struct CalDataStr{
    INT8U_BIT(NumOfSensorCh, __SenChannels_bits); 
};
// only support PPM now ----2020-05-09
#define MAX_SUPPORT_UNIT  4
// total 44 bytes
typedef struct {
   
    INT8U_BIT(CalibTypeDef, __senCalType_bits);
    INT8U_BIT(CalibType, __senCalType_bits);
    INT16U_BIT(ParaMask, __senPara_bits);
    INT16U RespTime;                           // This default for Span Type
    INT16U WarmupTime;
    INT16U BumpTime;
    INT16U BumpInterval;
    INT16U CalInterval;
    INT16U RespTimeFresh;
    INT16U RespTimeZero;
    INT16U RespTimeSpanH;
    INT8U  BumpTolerance;
    INT8U_BIT(logMeasType, __measType_bits);
    struct CalRefStruct *pCalRef;

    INT8U  SenID;
    INT8U  SubID;
    INT8U  UnitCode;
    INT8U  ResInt;
    INT8U  ResExp;
    INT8U  ParaMask_H;
    INT8U  ParaMask_L;   
    INT8U  UserFactor_H;
    INT8U  UserFactor_L;
    INT16U  EndOfLifeDays;
    INT16U  CalDueDays;
    INT8U  MaximalSenNum;
    INT8U  InstalledSenMap;


    INT8U  ModelName[20];
    INT8U  ProdName[20];
    INT8U  FwVer[10];
    INT8U  SN[20];
    INT8U  SenName[10];
    INT8U  ProdDay[3];
    INT16U  WarrantyDays;
    INT16U CalTime;
    INT8U  EnableSpanhCalFlag;   
    INT8U  OEMCode[7];
    INT8U  Parter[7];
    INT8U  SupportUnitList[MAX_SUPPORT_UNIT];
    INT16U ActaulSensitivity;
    INT16U MinimumSensitivity; 
    INT16U BumpDueDays;
    struct SensorDeadband Deadband; 
} SIM; /* Sensor Infomation Map */

/* Sensor Calibration Data Map */
typedef struct {
    INT8U TOTAL_CH       : 4;
    INT8U                : 1;
    INT8U                : 1;
    INT8U                : 1;
    INT8U F_SPH          : 1;           // Support SpanH flag
} __calDataMap_bits;


typedef struct {
    INT32S CalValue;
    INT16U CalRAW[10];
    INT8U CalTemperature;
    INT8U CalHumidity;
    RTC    CalDate;
} SCM;



typedef struct {
    INT8U ChannelNum;
    SCM ZeroCal;
    SCM SpanCal;
    SCM SpanHCal;
} SCDM;

/* Sensor bump test data map */
typedef struct {
    INT8U             : 4;
    INT8U             : 1;
    INT8U             : 1;
    INT8U Enabled     : 1;
    INT8U Status      : 1;
} __bumpDataMap_bits;

// 28 Bytes
typedef struct {
    INT8U_BIT(BumpDataMap, __bumpDataMap_bits);
    INT8U    Reserved[3];
    RTC      BumpDate;
    RTC      BumpDate_BAK;
    INT16S   Temperature;
    INT16U   SigRaw[PID_SEN_RAW_CHNN];
} SBDM;

// 80 Bytes
typedef struct {
    RTC    BumpDate_Last;            // this date is the last bump test date, even the result failed. Initial value =  BumpDate in SBDM.
    RTC    CalDate_Last;             // this date is the last calibration date, even the result failed. Initial value =  CalDate in SCDM.
    INT32U pReading;                 // reading at prepare time
    INT32U sReading;                 // reading at start time
    INT32U u32_BcZeroReading;        // before cali reading
    INT32U u32_BcSpanReading;
    INT32U u32_BcSpanHReading;
    INT32U u32_AcZeroReading;        // after cali reading
    INT32U u32_AcSpanReading;
    INT32U u32_AcSpanHReading;
    INT32U u32_BcSigRaw[PID_SEN_RAW_CHNN];          // before cali raw count
    INT32U u32_AfSigRaw[PID_SEN_RAW_CHNN];          // after cali raw count
} APLD;                             // Added data for policy check or Bump/cal report

// 80 Bytes
typedef struct {
    INT8U SenErrorNum;     //Sensr error num
    INT8U ErrorCode[10];   // error code
} SenError;                             // Added data for policy check or Bump/cal report

// 80 Bytes
typedef struct {
    INT8U SenRawCountNum;     //Sensr error num
    INT32S SenRawCount[2];   // error code
} SenRawCount;                             // Added data for policy check or Bump/cal report

/* Sensor Runtime Data Map */
typedef struct {
    INT8U: 8;
    INT8U: 8;
    INT64U LogSum;
    INT32U LogMin;
    INT32U LogMax;
    INT32U LogAvg;

    INT8U_BIT(Sentatus, __senRtSta_bits);    
    INT8U_BIT(SenAlarm, __senAlarm_bits);
    INT8U_BIT(SenRtSta, __senRtSta2_bits);
    INT32S GasReading;
    INT32S UnCompGasReading;
    
    INT32U SpanValue;
    INT32U PreSpanValue;
    INT32U LowAlarmValue;
    INT32U HightAlarmValue;
    INT32U SpanHValue;
    INT32U PreSpanHValue;
    INT32U SpanHPreValue;
    INT32U OverRangeValue;
    INT32U STELAlarmValue;
    INT32U TWAAlarmValue;

    INT8U RawCount;
    INT8U Temperature;
    INT8U Humidity;
    

    SenRawCount SensorRawCount;
    SenError SensorError;
} SRTDM;

// 824 bytes
typedef struct {
    SIM   st_SenInfo;
    APLD  st_Apld;
    SRTDM st_RunData;
    SBDM  st_BumpData;
    SCDM  st_CaliData;
} SENSOR;


#define  SET_SPAN   0x0001
#define  SET_LOW    0x0002
#define  SET_HIGH   0x0004
#define  SET_SPANH  0x0008
#define  SET_STEL   0x0020
#define  SET_TWA    0X0040
extern SENSOR Sensor;
extern RCS_t SCDC_SensorResp;
INT8U Sensor_Init(void);
void SCDC_SensorResp_Init(INT32S fd);
INT8U Sensor_WriteProtect(INT8U WriteProtectFlag);
INT8U Sensor_UserCal(INT16U SenBitMap,INT8U CalType,INT8U Operation);
INT8U Sensor_GeSenCalData(INT8U SensorIndex);
void Sensor_SetGasList(INT16U SenIndx,INT8U Uint);
INT8U SenChkCalDueAlarm(void);
INT8U SenChkBumpDueAlarm(void);
void PID_RawCountLowSpanWrite(void);
void PID_RawCountZeroWrite(void);
INT32U PID_CalibCheckSpan1(void);
INT32U PID_CalibCheckSpan2(void);
void PID_CalibCurveRestore(void);
void PID_RawCountHighSpanWrite(void);
#endif
/*************************** #ifndef __PID_H****************************/
