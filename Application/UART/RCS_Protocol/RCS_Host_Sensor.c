
/*******************************************************************************

   (C) Copyright 2009 RAE Systems Inc.   All rights reserved

----------------- File Information ---------------------------------------------
       File Name: RCS_Host_PID.c
     Description: RCS Protocol Host Commander.

---------------- Important Notes -----------------------------------------------


----------------- Rivision History ---------------------------------------------
         Version: V1.00
          Author: Alven Lu
Last Modify Date: 3/23/2009
     Description: Initial version

*******************************************************************************/


#include "includes.h"


static void HostParaPack(RCS_t *rcs)
{
    memcpy(rcs->RespBuf + rcs->RespLen, rcs->DataBuf, rcs->DataLen);
    rcs->RespLen += rcs->DataLen;
}


void SDCS_SensorCommandSend(RCS_t *rcs)
{
    if (RCS_Builder(rcs, NULL) == 1) {
        RCS_SendPackage(rcs);
    }
}

/* Command set table */
const RCS_CmdNode SCDC_Sensor_HostTable[] = {
    //-----------------------------------------------
    // SDCS_GET_MODEL_NAME,                 RCS_CMD_REV1,     NULL,              NULL,    
    // SDCS_GET_PROD_NAME,                  RCS_CMD_REV1,     NULL,              NULL,    
    SDCS_GET_SENSOR_FWVER,               RCS_CMD_REV1,     NULL,              NULL,    
    // SDCS_GET_SENSOR_SN,                  RCS_CMD_REV1,     NULL,              NULL,    
    // SDCS_GET_SENSOR_SUM,                 RCS_CMD_REV1,     NULL,              NULL,    
    // SDCS_GET_PROD_DATE,                  RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_GET_DATA_PACK,                  RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_DATA_FMT,               RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_PARA,                   RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_ID,                     RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_NAME,                   RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_UF,                     RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_GET_OEM_CODE,                   RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_GET_PARTNER_CODE,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_GET_SEN_END_OF_LIFE,            RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_CAL_DUE_DAYS,           RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_CAL_TIME,               RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_SENSITIVITY,            RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_DEADBAND,               RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_CAL_DATA,               RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_BUMP_DUE_DAYS,          RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_GAS_LIST,               RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_GAS_CAL_MES,            RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_ALOHA_MODE,                 RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_SEN_GASUNIT_LIST,           RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_EC_DATALOG,                 RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_GET_EC_ACCURACY_PRECENT,        RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_SEN_PARA,                   RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_SEN_RTC,                    RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_UF,                     RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_OEM_CODE,                   RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_PARTNER_CODE,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_DEADBAND,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_GAS_CAL_MES,            RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_CMPL_STD,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_UF_INDEX,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_GASUNIT,                RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_SEN_CAL_INTERVAL_DAYS,      RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_SEN_BUMP_INTERVAL_DAYS,     RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_SET_SEN_BUMP_TIME,              RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_EC_ACCURACY_PRECENT,        RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_REQ_SEN_STEL_TWA,               RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_WRITE_PROTECT,                  RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_USER_CAL,                       RCS_CMD_REV1,     HostParaPack,      NULL,    
    // SCDC_SET_SEN_ALOHA,                  RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_ALOHA_DATA_PACK,                RCS_CMD_REV1,     NULL,              NULL,    
    // SCDC_GOTO_MODE,                      RCS_CMD_REV1,     HostParaPack,      NULL,
    // SCDC_GET_SPANH_CAL_FLAG,             RCS_CMD_REV1,     HostParaPack,      NULL,
    // SCDC_SET_SPANH_CAL_FLAG,             RCS_CMD_REV1,     HostParaPack,      NULL,
    //-----------------------------------------------
};


const INT8U SCDC_Sensor_HostTotal = dim(SCDC_Sensor_HostTable);



/* EOF */


