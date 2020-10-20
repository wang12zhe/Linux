
/*******************************************************************************

   (C) Copyright 2009, RAE Systems Inc.      All rights reserved

----------------- File Information ---------------------------------------------
       File Name: SenRelatedDef.h
     Discription: Sensor related macro definition file.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 8/24/2007
     Discription: Initial version

            Version: V2.00
          Author: Alven Lu
Last Modify Date: 8/11/2009
     Discription: Change to enum/bit definition

*******************************************************************************/



#ifndef __SEN_RELATED_H__
#define __SEN_RELATED_H__

#define BUMP                     0x10


#define FRESH                    0x01
#define SPAN                     0x02
#define SPAN_0                   SPAN
#define ZERO                     0x04
#define SPANH                    0x08
#define MULTI_BIT                0x80
#define MULTI_L                  0x82
#define MULTI_H                  0X88
/*
The following are DH[0]=Operation commands for RCS commands:
0x4060   REQ_CAL_ZERO
0x4061   REQ_CAL_SPAN
0x406A   REQ_CAL_SPANH
0x406B   REQ_CAL_FRESHAIR
*/
#define CT_SETUP                 0x80  //Prepare for calib
#define CT_ABORT                 0x81  //Abort calib process
#define CT_RESULT                0x83  //Get calib result
#define CT_MANU                  0x10  //Start manufactory calib
#define CT_USER                  0x00  //Start user calib


#define BT_SETUP                 0x80    // Prepare for bump
#define BT_ABORT                 0x81    // Abort bump process
#define BT_RESULT                0x82    // Get bump result
#define BT_START                 0x00    // Start bump test

typedef struct {
    INT8U SS_INSTALLED               : 1;
    INT8U SS_STARTED                 : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U SS_CALED_ZERO              : 1;
    INT8U SS_CALED_SPAN              : 1;
    INT8U SS_CALED_SPANH             : 1;
} __senStatus_bits;

typedef struct {
    INT8U SA_OVR                     : 1;
    INT8U                            : 1;
    INT8U TIME_NOT_AYNC              : 1;
    INT8U SA_HIGH                    : 1;
    INT8U SA_LOW                     : 1;
    INT8U SA_STEL                    : 1;
    INT8U SA_TWA                     : 1;
    INT8U SA_DRIFT                   : 1;
} __senAlarm_bits;

typedef struct {
    INT8U                           : 1;     // sensor STEL accumulative total to 15 minutes
    INT8U SS_WARMUP                 : 1;
    INT8U                           : 1;
    INT8U SS_IN_CAL                 : 1;
    INT8U                           : 1;
    INT8U                           : 1;
    INT8U SS_SLEEP                  : 1;
    INT8U                           : 1;
} __senRtSta_bits;

typedef struct {
    INT8U SS_CAL_DUE                : 1;     // sensor STEL accumulative total to 15 minutes
    INT8U SS_CAL_FAIL               : 1;
    INT8U SS_BUMP_DUE               : 1;
    INT8U SS_BUMP_FAIL              : 1;
    INT8U SS_REF_CALDUE             : 1;
    INT8U SS_IN_BUMP                : 1;
    INT8U                           : 1;
    INT8U                           : 1;
} __senRtSta2_bits;

/* Sensor Error Definition */
#define SEN_INWARMUP            0x02
typedef struct {
    INT8U SE_NUM_CODE                   : 1;
    INT8U SE_IN_WARMUP               : 1;
    INT8U SE_EE_DATA_ERR             : 1;
    INT8U SE_CAL_FAIL                : 1;
    INT8U SE_CAL_DUE                 : 1;
    INT8U SE_BUMP_DUE                : 1;
    INT8U SE_BUMP_FAIL               : 1;
    INT8U                            : 1;
} __senError_bits;

typedef struct {
    INT16U SPC_SPAN                  : 1;
    INT16U SPC_LOW                   : 1;
    INT16U SPC_HIGH                  : 1;
    INT16U SPC_SPANH                 : 1;
    INT16U SPC_OVR_RANGE             : 1;
    INT16U SPC_STEL                  : 1;
    INT16U SPC_TWA                   : 1;
    INT16U SPC_CF                    : 1;

    INT16U                           : 1;
    INT16U                           : 1;
    INT16U                           : 1;
    INT16U SPC_DRIFT                 : 1;
    INT16U SPC_OVR_LOAD              : 1;
    INT16U                           : 1;
    INT16U                           : 1;
    INT16U                           : 1;
} __senPara_bits;

typedef enum {
    P_SPAN = 0,
    P_LOW,
    P_HIGH,
    P_SPANH,
    P_OVRRANGE,
    P_STEL,
    P_TWA,
    P_CF,
    P_DRIFT = 11,
    P_OVRLOAD,
} SPARA;

typedef struct {
    INT8U SCT_FRESH                  : 1;
    INT8U SCT_SPAN                   : 1;
    INT8U SCT_ZERO                   : 1;
    INT8U SCT_SPANH                  : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
} __senCalType_bits;

typedef struct {
    INT8U SDF_DATA_LEN               : 2;
    INT8U                            : 4;
    INT8U SDF_DATA_RANG              : 2;
} __senDataFmtCode1_bits;

typedef struct {
    INT8U                            : 2;
    INT8U SDF_DF                     : 3;
    INT8U SDF_DP                     : 3;
} __senDataFmtCode2_bits;

typedef struct {
    INT8U PEAK_AVAILABLE             : 1;
    INT8U MIN_AVAILABLE              : 1;
    INT8U STEL_AVAILABLE             : 1;
    INT8U TWA_AVAILABLE              : 1;
    INT8U RT_AVAILABLE               : 1;
    INT8U AVG_AVAILABLE              : 1;
    INT8U RT_INSPECIAL               : 1;
    INT8U TWA_INVALID                : 1;
} __senReading_bits;

typedef struct {
    INT32U UC_DATA_FMT               : 1;
    INT32U UC_DATA_LEN               : 1;
    INT32U UC_DEC_P                  : 1;
    INT32U UC_DIF_V                  : 1;
    INT32U UC_RES_INT                : 1;
    INT32U UC_RES_EXP                : 1;
    INT32U UC_RES                    : 1;
    INT32U UC_CF                     : 1;

    INT32U UC_LOW                    : 1;
    INT32U UC_HIGH                   : 1;
    INT32U UC_DRIFT                  : 1;
    INT32U UC_OVERRANGE              : 1;
    INT32U UC_OVERLOAD               : 1;
    INT32U UC_STEL                   : 1;
    INT32U UC_TWA                    : 1;
    INT32U UC_ZERO                   : 1;

    INT32U UC_SPAN                   : 1;
    INT32U UC_SPANH                  : 1;
    INT32U UC_DBTHRE_OUT             : 1;
    INT32U UC_DBTHRE_IN              : 1;
    INT32U                           : 1;
    INT32U                           : 1;
    INT32U                           : 1;
    INT32U                           : 1;

    INT32U                           : 8;
} __senRisParaChgMap;

typedef enum {
    DATALEN_1_BYTE,
    DATALEN_2_BYTE,
    DATALEN_4_BYTE,
    DATALEN_8_BYTE,
} __dataLen_enum;

typedef enum {
    UNSIGNED,
    SIGNED,
} __dataRange_enum;

typedef struct {
    INT8U RS_InitDue                 : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
    INT8U                            : 1;
} __risStatus;

typedef enum {
    DF_1,
    DF_10,
    DF_100,
    DF_1000,
} __divF_enum;

typedef enum {
    DP_0,
    DP_1,
    DP_2,
    DP_3,
} __decP_enum;


typedef enum {
    SEN_RESET,
    SEN_SLEEP,
    SEN_OFF,
    SEN_WAKEUP,
    SEN_RESTORE,
    SEN_SAVECD2E2,                  // need to save cal data to EEPROM
    SEN_UNSAVECD2E2,
    SEN_BA_CALDATA,
    SEN_RE_CALDATA,
    SEN_SA_CALDATA,
    SEN_BA_BUMPDATA,
    SEN_RE_BUMPDATA,
    SEN_SA_BUMPDATA
} SEN_OP;

typedef enum {
    BOTH_OFF = 0,
    LEL_ON,
    TC_WARMUP,
    TC_ON,
} LELPWR;

typedef enum {
    RMODE_NORMAL = 1,
    RMODE_DIAG = 3,
    RMODE_SLEEP,
    RMODE_MENU = 15,
} RUNMODE;

typedef enum {
    MV_AVG = 0,
    TWA_AVG,
    NO_AVG,
} TWATYPE;

/* Sensor Map */
typedef struct {
    INT16U enabled          : 1;
    INT16U logEnabled       : 1;
    INT16U installed        : 1;
    INT16U multiCal         : 1;
    INT16U legal            : 1;
    INT16U                  : 1;
    INT16U preInstalled     : 1;
    INT16U restoreReq       : 1;

    INT16U                  : 8;
} SENMAP;

#endif  /* #ifndef __SEN_RELATED_H__ */


/* End of File */

