
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.     All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_CmdDef.h
     Description: Common definitions for RCS.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 12/21/2006
     Description: Initial version

         Version: V1.10
          Author: Alven Lu
Last Modify Date: 12/20/2007
     Description: Change for Ver=0x61

         Version: V2.00
          Author: Alven Lu
Last Modify Date: 3/13/2009
     Description: Revised totally, try to support all version code.

*******************************************************************************/



#ifndef __RCS_CMD_H__
#define __RCS_CMD_H__

/* Command Set Definition */

/* Rae Loader */
#define RCS_REQ_LOAD_FIRM           0x2289
#define RCS_SECECT_DEVICE           0x423A
#define RCS_SET_BAUDRATE            0x423B
#define RCS_SET_RELAY_MODE          0x423D

/* Datalog Related */
#define RCS_GET_DATA_TYPE           0x2043
#define RCS_SET_DATA_TYPE           0x2272
#define RCS_GET_LOG_OPTION          0x2063
#define RCS_SET_LOG_OPTION          0x2263
#define RCS_GET_LOG_INTERVAL        0x2064
#define RCS_SET_LOG_INTERVAL        0x2264
#define RCS_GET_SEN_LOGMAP          0x203C
#define RCS_SET_SEN_LOGMAP          0x223c

#define RCS_GET_EVENT_NUM           0x2080
#define RCS_GET_EVENT_HEADER        0x2081
#define RCS_GET_EVENT_DATA          0x2082
#define RCS_GET_DATALOG_SIZE        0x2083
#define RCS_GET_DATALOG_ALL         0x2084
#define RCS_GET_MODE                0x2085
#define RCS_GET_EVENT_HEADERSIZE    0x2086
#define RCS_GET_EVENT_DATASIZE      0x2087
#define RCS_GET_EVENT_SIZE          0x2088
#define RCS_GET_EVENT_ALL           0x2089
#define RCS_REQ_ERASE_EVENT         0x2288
#define RCS_GET_DATALOG_FLAG        0x602E

/*WorkerDown Related*/
#define RCS_GET_WORKER_DOWN         0x4080
#define RCS_SET_WORKER_DOWN         0x4280
#define RCS_GET_LCDFLIP             0x4081
#define RCS_SET_LCDFLIP             0x4281

/* Basic Information */
#define RCS_GET_UNIT_SN             0x2020
#define RCS_GET_INSTR_ID            0x2021
#define RCS_GET_MODEL_NAME          0x2022
#define RCS_GET_FW_VER              0x2023
#define RCS_GET_PROD_NAME           0x2024
#define RCS_GET_SYS_OPTION          0x2025
#define RCS_GET_UNIT_STA            0x2026
#define RCS_GET_BUILD_DATE          0x2027
#define RCS_GET_BUILD_TIME          0x2028

#define RCS_GET_SENS_SUMMARY        0x2030
//#define RCS_GET_SENS_NAME           0x2031
#define RCS_GET_SENS_UNIT           0x2032
#define RCS_GET_SENS_CAL_DATE       0x2033
#define RCS_GET_SENS_SPAN           0x2034
#define RCS_GET_SENS_LOW_ALARM      0x2035
#define RCS_GET_SENS_HIGH_ALARM     0x2036
#define RCS_GET_SENS_STEL_ALARM     0x2037
#define RCS_GET_SENS_TWA_ALARM      0x2038
#define RCS_GET_SENS_RANGE          0x2039
//#define RCS_GET_SENS_READING        0x203A
//#define RCS_GET_SENS_ALARM          0x203B
#define RCS_GET_SENS_LOG_MAP        0x203C
#define RCS_GET_SENS_SPAN2          0x203E
#define RCS_GET_SENS_LAMP_ID        0x203F

#define RCS_GET_BATT_VOLT           0x2040
#define RCS_GET_TEMPERATURE         0x2041
#define RCS_GET_TWAAVG_TYPE         0x2044
#define RCS_GET_SITEUSER            0x2046
#define RCS_GET_SECURE_BEEP         0x2047
#define RCS_GET_POWONZERO           0x2048
#define RCS_GET_TEMP_UNIT           0x2049
#define RCS_GET_HUMI                0x204A
#define RCS_GET_BATTERY_TYPE        0x204C

#define RCS_GET_ALARM_INFO          0x2050
#define RCS_GET_RTC                 0x2052
#define RCS_GET_HOSTSLVAE           0x2054
#define RCS_GET_LANG_INX            0x2055
#define RCS_GET_LASTRUNTIME         0x2056
#define RCS_GET_LCDCONT             0x2057
#define RCS_GET_PUMPINFO            0x2058
#define RCS_GET_BKLIT2              0x205C
#define RCS_GET_LANG_LIST           0x205F
#define RCS_GET_SEN_MULTICAL        0x2068
//#define RCS_GET_SENS_SN             0x206A
#define RCS_GET_DISP_UNIT           0x206E
#define RCS_GET_UNIT_STARTUP_MODE   0x2071
#define RCS_GET_FEATURE_STATUS      0x2074
#define RCS_GET_DATE_FORMAT         0x2075
#define RCS_GET_TIME_FORMAT         0x2076
#define RCS_GET_REAL_TIME_COMM      0x2077

/*Gas Related*/
#define RCS_GET_CAL_REF_IDX         0x2078
#define RCS_GET_RADIO_TYPE          0x2079
#define RCS_GET_MY_GAS_LIST         0x207A
#define RCS_SET_MY_GAS_LIST         0x227A
#define RCS_GET_LAST_GAS_LIST       0x207B
#define RCS_SET_LAST_GAS_LIST       0x227B
#define RCS_GET_CUSTOM_GAS          0x207C
#define RCS_SET_CUSTOM_GAS          0x227C
#define RCS_GET_GAS_TBL_VER         0x207D
#define RCS_GET_GAS_TBL             0x20A1

#define RCS_GET_CAL_REF             0x207E
#define RCS_SET_CAL_REF_DEF         0x228C
#define RCS_SET_CUS_GAS_DEF         0x228D

#define RCS_GET_CALREF_INDEX        0x4078
#define RCS_SET_CALREF_INDEX        0x4278
//#define RCS_GET_MY_GAS_LIST         0x4079
//#define RCS_SET_MY_GAS_LIST         0x4279
//#define RCS_GET_IGT_NUMBER          0x407A
//#define RCS_GET_IGT_TABLE           0x407B
//#define RCS_GET_LAST_GAS_LIST       0x407C
//#define RCS_GET_CAL_REF             0x407D
//#define RCS_SET_CAL_REF_DEF         0x427E
#define RCS_GET_RUNTIMEDATA             0x40A0
#define RCS_GET_SENSOR_SUMMARYINFO      0x40A1
#define RCS_SET_SESSION_CTR             0x40A2


#define RCS_GET_CAL_MEAS_GAS        0x405A
#define RCS_SET_CAL_MEAS_GAS        0x425A

#define RCS_SET_SPAN                0x2220
#define RCS_SET_ALL_SPAN            0x2221
#define RCS_SET_LOW_LIMIT           0x2222
#define RCS_SET_ALL_LOW_LIM         0x2223
#define RCS_SET_HIGH_LIMIT          0x2224
#define RCS_SET_ALL_HIGH_LIM        0x2225
#define RCS_SET_STEL_LIMIT          0x2226
#define RCS_SET_ALL_STEL_LIM        0x2227
#define RCS_SET_TWA_LIMIT           0x2228
#define RCS_SET_ALL_TWA_LIM         0x2229
#define RCS_SET_SENS_INFO           0x222A
#define RCS_SET_SPAN2               0x222B

#define RCS_SET_DISP_UNIT           0x2232
#define RCS_SET_SENS_LOG_MAP        0x223C
#define RCS_SET_ALARM_INFO          0x2240
#define RCS_SET_RTC                 0x2242
#define RCS_SET_HOSTSLAVE           0x2244
#define RCS_SET_LANG_INX            0x2245
#define RCS_SET_LCDCONT             0x2246
#define RCS_SET_TWAAVG_TYPE         0x2248
#define RCS_SET_PUMPINFO            0x224A
#define RCS_SET_SITEUSER            0x224D
#define RCS_SET_BKLIT2              0x224E
#define RCS_SET_POWONZERO           0x2251
#define RCS_SET_SECURE_BEEP         0x2254
//#define RCS_SET_CAL_RTC           0x225f
#define RCS_SET_SEN_MULTICAL        0x2268
#define RCS_SET_TEMP_UNIT           0x2270
#define RCS_SET_UNIT_STARTUP_MODE   0x2271
#define RCS_SET_UNIT_FEATURE        0x2273
#define RCS_SET_DATE_FORMAT         0x2275
#define RCS_SET_TIME_FORMAT         0x2276
#define RCS_SET_RT_COMM             0x2277
#define RCS_SET_CAL_REF_IX          0x2278

#define RCS_REQ_PUMP_ON             0x2284
#define RCS_REQ_PUMP_OFF            0x2285
#define RCS_REQ_GOTOMODE            0x228A
#define RCS_SET_SYS_OPTION          0x228B
#define RCS_SET_SYS_OPTION_W_MASK   0x22A5
#define RCS_REQ_BUMP_TEST           0x2293

#define RCS_GET_BUMP_INTERVAL       0x2623
#define RCS_SET_BUMP_INTERVAL       0x2643
#define RCS_GET_CAL_INTERVAL        0x2624
#define RCS_SET_CAL_INTERVAL        0x2644

#define RCS_GET_RADIO_REGION        0x2700
#define RCS_SET_RADIO_REGION        0x2701
#define RCS_GET_RADIO_DEVTYPE       0x2702
#define RCS_SET_RADIO_DEVTYPE       0x2703
#define RCS_GET_RADIO_TXPOWER       0x2704
#define RCS_SET_RADIO_TXPOWER       0x2705
#define RCS_GET_RADIO_POWER         0x2706
#define RCS_SET_RADIO_POWER         0x2707
#define RCS_GET_RADIO_PANID         0x2708
#define RCS_SET_RADIO_PANID         0x2709
#define RCS_GET_RADIO_CHANNEL       0x270A
#define RCS_SET_RADIO_CHANNEL       0x270B
#define RCS_GET_RADIO_INTERVAL      0x270C
#define RCS_SET_RADIO_INTERVAL      0x270D
#define RCS_GET_RADIO_OFFNETALM     0x270E
#define RCS_SET_RADIO_OFFNETALM     0x270F
#define RCS_SET_RADIO_BATCH         0x2710
#define RCS_SET_RADIO_RST           0x2712
#define RCS_SET_RADIO_TYPE          0x2279
#define RCS_SET_WIRELESS_UID        0x2714
#define RCS_GET_WIRELESS_UID        0x2713
#define RCS_GET_WIRELESS_REGION     0x2717
#define RCS_SET_WIRELESS_REGION     0x2716
/* Soft Reset */
#define RADIO_SOFT_RESET                0x2712

#define RCS_GET_NVMEM_INFO          0x4030
#define RCS_GET_ADC                 0x4031
#define RCS_GET_LEL_PWR             0x4039
#define RCS_GET_SKT_RAW_INFO        0x403A
#define RCS_GET_SENS_ID             0x4040
#define RCS_GET_SENS_NAME           0x4041
#define RCS_GET_SENS_DATAFMT        0x4042
#define RCS_GET_SENS_PARA           0x4043
#define RCS_GET_SENS_READING        0x4044
#define RCS_GET_SENS_ALARM          0x4045
#define RCS_GET_SENS_SN             0x4046
#define RCS_GET_SENS_RAW            0x4047
#define RCS_GET_SENS_BUMPTIME       0x4048
#define RCS_GET_SENS_CALTIME        0x4049
#define RCS_GET_SENS_SUMM           0x404A
#define RCS_GET_SENS_EEREV          0x404B
#define RCS_GET_DATAPACK            0x4050
#define RCS_GET_SENS_PRODDAY        0x4051
#define RCS_GET_SENS_GAIN           0x4052
#define RCS_GET_SENS_PEAK           0x4053
#define RCS_GET_CAL_TYPE            0x4054
#define RCS_GET_CAL_DATA            0x4055
//#define RCS_GET_SPAN_CAL_TYPE     0x4056
#define RCS_GET_SEN_BUMP_DATA       0x4057
#define RCS_GET_SEN_RES             0x4058
#define RCS_GET_SEN_AUTORANGE       0x405B
#define RCS_GET_BUMP_TOLERANCE      0x405C
#define RCS_SET_BUMP_TOLERANCE      0x405D
#define RCS_REQ_ZERO_CAL            0x4060
#define RCS_REQ_SPAN_CAL            0x4061
#define RCS_REQ_HW_TEST             0x4065
#define RCS_REQ_SENS_PEAK           0x4067
#define RCS_REQ_SENS_CNTL           0x4068
#define RCS_REQ_SPANH_CAL           0x406A
#define RCS_REQ_FRESH_CAL           0x406B
#define RCS_GET_HUMI_ZERO           0x4075
#define RCS_GET_PUMPSTALL           0x4076
#define RCS_GET_LCDCONT_PER         0x4077
#define RCS_GET_POLICY              0x4082
#define RCS_SET_POLICY              0x4083
#define RCS_GET_SUBMODS_INFO        0x4085
#define RCS_GET_BDR_LIST            0x4086


#define RCS_GET_SEN_BUMP_DATA_AND_RESULT      0x22A7
#define RCS_GET_CAL_DATA_AND_RESULT            0x20A2

#define RCS_SET_NVMEM_INFO          0x4230
#define RCS_SET_PID_LED             0x4236
#define RCS_SET_LEL_PWR             0x4239
#define RCS_SET_SENS_PARA           0x4243
#define RCS_SET_SENS_ENABLED        0x424A
#define RCS_SET_SEN_GAIN            0x4252
#define RCS_SET_CAL_TYPE            0x4254
#define RCS_SET_CAL_DATA            0x4255
//#define RCS_SET_SPAN_CAL_TYPE     0x4256
#define RCS_SET_SEN_AUTORANGE       0x425B
#define RCS_SET_PID_LAMP            0x4274
#define RCS_SET_HUMI_ZERO           0x4275
#define RCS_SET_PUMPSTALL           0x4276
#define RCS_SET_LCDCONT_PER         0x4277

#define RCS_GET_CALBUMPRPT          0x5014
#define RCS_SET_CALBUMPRPT          0x5015
#define RCS_GET_UNIT_AIRFLOW_MODE   0x5016

#define RCS_REQ_WRITE_SN            0x6026
#define RCS_GET_SPEC_INFO           0x6028
#define RCS_GET_SECURITY_ID         0x6029
#define RCS_SET_INSTR_ID            0x602A
#define RCS_GET_USERRIGHT           0x6054
#define RCS_SET_USERRIGHT           0x6055
#define RCS_REQ_RESTORE_DEFAULT     0x6059
#define RCS_GET_PASSWD              0x605C
#define RCS_SET_PASSWD              0x605D
#define RCS_GET_RUNNING_MODE        0x6066
#define RCS_SET_RUNNING_MODE        0x6067
#define RCS_GET_THP_SN              0x6068
#define RCS_GET_TUBE_TYPE           0x606C
#define RCS_SET_TUBE_TYPE           0x606D
#define RCS_GET_MANU_LAMP_ID        0x606E
#define RCS_SET_MANU_LAMP_ID        0x606F

#define RCS_GET_SLAVE_ID            0x6072
#define RCS_SET_SLAVE_ID            0x6073
#define RCS_GET_PAN_ID              0x6074
#define RCS_SET_PAN_ID              0x6075
#define RCS_GET_ADVN_PWD            0x6078
#define RCS_SET_ADVN_PWD            0x6079
#define RCS_GET_TUBE_STEL_SAMP      0x607A
#define RCS_SET_TUBE_STEL_SAMP      0x607B

#define RCS_ENCRYPT_CMD             0x60D0
#define RCS_GET_MODULE_FIRMVER      0x7210


#define RCS_SET_CF_TO_IBE               0xAABB    //Owen2020-02-1 this is a internal command, nobody use it
#define RCS_GET_CF_TO_IBE               0xACBB    //Owen2020-03-10 this is a internal command, nobody use it


/* RCS command for sensor */
#define SDCS_GET_MODEL_NAME              0x10
#define SDCS_GET_PROD_NAME               0x11
#define SDCS_GET_SENSOR_FWVER            0x12
#define SDCS_GET_SENSOR_SN               0x13
#define SDCS_GET_SENSOR_SUM              0x15
#define SDCS_GET_PROD_DATE               0x37
#define SCDC_GET_DATA_PACK               0x30
#define SCDC_GET_SEN_DATA_FMT            0x31
#define SCDC_GET_SEN_PARA                0x33
#define SCDC_GET_SEN_ID                  0x34
#define SCDC_GET_SEN_NAME                0x35
#define SCDC_GET_SEN_UF                  0x39
#define SCDC_GET_OEM_CODE                0x3B
#define SCDC_GET_PARTNER_CODE            0x40
#define SCDC_GET_SEN_END_OF_LIFE         0x41
#define SCDC_GET_SEN_CAL_DUE_DAYS        0x42
#define SCDC_GET_SEN_CAL_TIME            0x43
#define SCDC_GET_SEN_SENSITIVITY         0x44
#define SCDC_GET_SEN_DEADBAND            0x45
#define SCDC_GET_SEN_CAL_DATA            0x46
#define SCDC_GET_SEN_BUMP_DUE_DAYS       0x47
#define SCDC_GET_SEN_GAS_LIST            0x51
#define SCDC_GET_SEN_GAS_CAL_MES         0x52
#define SCDC_GET_ALOHA_MODE              0x53
#define SCDC_GET_SEN_GASUNIT_LIST        0x54
#define SCDC_GET_EC_DATALOG              0x60
#define SCDC_GET_EC_ACCURACY_PRECENT     0x61
#define SCDC_GET_SPANH_CAL_FLAG          0x64

#define SCDC_SET_SEN_PARA                0X80
#define SCDC_SET_SEN_RTC                 0X82
#define SCDC_SET_SEN_UF                  0X83
#define SCDC_SET_OEM_CODE                0x84
#define SCDC_SET_PARTNER_CODE            0x89
#define SCDC_SET_SEN_DEADBAND            0x8A
#define SCDC_SET_SEN_GAS_CAL_MES         0x8B
#define SCDC_SET_SEN_CMPL_STD            0x8C
#define SCDC_SET_SEN_UF_INDEX            0x8D
#define SCDC_SET_SEN_GASUNIT             0x8E
#define SCDC_SET_SEN_CAL_INTERVAL_DAYS   0x8F
#define SCDC_SET_SEN_BUMP_INTERVAL_DAYS  0x90
#define SCDC_SET_SEN_BUMP_TIME           0x91
#define SCDC_SET_EC_ACCURACY_PRECENT     0x92
#define SCDC_REQ_SEN_STEL_TWA            0x93
#define SCDC_SET_SPANH_CAL_FLAG          0x96
#define SCDC_WRITE_PROTECT               0xA0
#define SCDC_USER_CAL                    0xA1
#define SCDC_SET_SEN_ALOHA               0XA2
#define SCDC_ALOHA_DATA_PACK             0XA2
#define SCDC_GOTO_MODE                   0XA6

//====================================================================


// WSN Commands, Same command code for response package
#define WSN_GET_DEV_INFO            0x20
#define WSN_SET_SEN_MASK            0x21
#define WSN_GET_SEN_NAME_FMT        0x22
#define WSN_GET_SEN_LMT             0x24
#define WSN_SET_SEN_LMT             0x25
#define WSN_SET_SN                  0x27
#define WSN_GET_SEN_NAME_FMT2       0x2A
#define WSN_GET_SEN_LMT2            0x2C
#define WSN_SET_SEN_LMT2            0x2D
#define WSN_GET_DEV_INFO2           0x2E
#define WSN_SET_NWK_DUTY            0x31
#define WSN_REQ_NWK_START           0x32
#define WSN_REQ_NWK_STOP            0x33
#define WSN_REQ_NWK_PING            0x34
#define WSN_REQ_RADIO_RESET         0x36
#define WSN_REQ_SDTE_RESET          0x37
#define WSN_GET_DATA_PAK            0x40
#define WSN_SEND_EVT_PAK            0x44
#define WSN_GET_DATA_PAK2           0x4A
#define WSN_GET_CAL_TIME            0x50


/* Error response command */
#define RCS_ERROR_SLAVE             0x7100

/* Error code definition: 904-E800-124, 060906 */
#define FAIL_UNKNOWN                0x31
#define FAIL_INVALIDCMD             0x32
#define FAIL_DATASIZE               0x33
#define FAIL_INVALIDVALUE           0x34
#define FAIL_SENSORID               0x35
#define FAIL_MODE                   0x36
#define FAIL_NOOPTION               0x37
#define FAIL_NODATA                 0x38
#define FAIL_NORIGHT                0x39
#define FAIL_LOWPOWER               0x3A
#define FAIL_FMTERROR               0x3B
#define FAIL_NOGAS                  0x3C
#define FAIL_CHANNEL_UNAVAIL        0x3D
#define FAIL_MODULE_TIMEOUT         0x3E
#define FAIL_OPERATION              0x3F



// Glance Mode
#define RCS_GET_GLANCE_OPTION       0x4091
#define RCS_SET_GLANCE_OPTION       0x4291
#define RCS_GET_GLANCE_ITEM_INFO    0x4090
#define RCS_GET_GLANCE_SEQUENCE_ITEM    0x4092
#define RCS_SET_GLANCE_SEQUENCE_ITEM    0x4292






#endif /* #ifndef __RCS_CMD_H__ */

/* EOF */

