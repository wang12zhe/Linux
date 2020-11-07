/*******************************************************************************

      3G PID Sensor

   (C) Copyright 2006, RAE Systems Inc.      All rights reserved

--------------------------------------------------------------------------------

     File name: PID.C
      Hardware: 3G PID main PCB rev. 1
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

--------------------------------------------------------------------------------

   Revision History

   == V1.00.01 ==
      10/30/06 - Wenpeng

*******************************************************************************/


#include "includes.h"

static INT8U Sensor_GetDataPack(INT8U SensorIndex);;
static INT8U Sensor_SetBumpTime(INT8U year,INT8U month,INT8U day,INT8U hour,INT8U min);
#define SCDC_SENSOR_RESP_DATABUF_LEN            64
INT8U SCDC_SensorResp_DataBuf[SCDC_SENSOR_RESP_DATABUF_LEN];
SENSOR Sensor;
RCS_t SCDC_SensorResp;
void SCDC_SensorResp_Init(INT32S fd)
{
    RCS_t *rcs = &SCDC_SensorResp;

    memset(rcs, 0, sizeof(RCS_t));
    memset(SCDC_SensorResp_DataBuf, 0, SCDC_SENSOR_RESP_DATABUF_LEN);
    rcs->fd         =fd;
    rcs->Role       = HOST_RECV;
    rcs->VerPac     = SCDC_SENSOR;
    rcs->DataBuf    = SCDC_SensorResp_DataBuf;
    rcs->DataBufLen = SCDC_SENSOR_RESP_DATABUF_LEN;
   // rcs->RespBuf    = SCDC_SensorHost_RespBuf;
    //rcs->RespBufLen = SCDC_SENSOR_RESPBUF_LEN;
    rcs->pf_FuncPut = (PFNCT)write;
    rcs->CmdTable   = (void *)SCDC_Sensor_RespTable;
    rcs->CmdTotal   = SCDC_Sensor_RespTotal;
}

// Sensor Host Commander
RCS_t SCDC_SensorHost;
#define SCDC_SENSOR_HOST_DATABUF_LEN            64
#define SCDC_SENSOR_HOST_RESPBUF_LEN            80
INT8U SCDC_SensorHost_DataBuf[SCDC_SENSOR_HOST_DATABUF_LEN];
INT8U SCDC_SensorHost_RespBuf[SCDC_SENSOR_HOST_RESPBUF_LEN];

void SCDC_SensorHost_Init(int fd)
{
    RCS_t *rcs = &SCDC_SensorHost;

    memset(rcs, 0, sizeof(RCS_t));
    memset(SCDC_SensorHost_DataBuf, 0, SCDC_SENSOR_HOST_DATABUF_LEN);
    memset(SCDC_SensorHost_RespBuf, 0, SCDC_SENSOR_HOST_RESPBUF_LEN);
    rcs->fd          = fd;
    rcs->Role       = HOST_SEND;
    rcs->VerPac     = SCDC_SENSOR;
    rcs->DataBuf    = SCDC_SensorHost_DataBuf;
    rcs->DataBufLen = SCDC_SENSOR_HOST_DATABUF_LEN;
    rcs->RespBuf    = SCDC_SensorHost_RespBuf;
    rcs->RespBufLen = SCDC_SENSOR_HOST_RESPBUF_LEN;
    rcs->pf_FuncPut = (PFNCT)write;
    rcs->CmdTable   = (void *)SCDC_Sensor_HostTable;
    rcs->CmdTotal   = SCDC_Sensor_HostTotal;
}
  
void SensorComLock(void)
{
    INT8U ret;

   // OSMutexPend(SensorMutex, 0, &ret);
}

void SensorComUnLock(void)
{
    //OSMutexPost(SensorMutex);
}
/* Return 0-fail, 1-success */
INT8U CommHandler_SCDCSensrHost(RCS_t *rcs)
{
    SDCS_SensorCommandSend(rcs);
    return(1);
}

// INT8U CommHandler_SCDCSensrResp(RCS_t *rcs)
// {
//     INT8U ch;
//     INT8U len;
//     INT8U u8_i = 0;


//     return(1);
// }

static INT8U  Sensor_GetFwVer(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SDCS_GET_SENSOR_FWVER;
    rcs->DataLen = 0;
    rcs-> PktIndex = index;
    CommHandler_SCDCSensrHost(rcs);
    //TM_Delay(DELAY_200MS);
    SCDC_SensorResp.PktIndex = index;
    return SUCC;
}
static INT8U Sensor_GetSenSN(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SDCS_GET_SENSOR_SN;
    rcs->DataLen = 0;
    rcs-> PktIndex = index;
    CommHandler_SCDCSensrHost(rcs);
    //TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    index ++;
    SensorComUnLock();
    return SUCC;
}
static INT8U Sensor_GetModelName(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SDCS_GET_MODEL_NAME;
    rcs->DataLen = 0;
    rcs-> PktIndex = index;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    return SUCC;
}
static INT8U Sensor_GetProdName(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SDCS_GET_PROD_NAME;
    rcs->DataLen = 0;
    rcs-> PktIndex = index;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();
    return SUCC;
}

static INT8U Sensor_SenSum(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SDCS_GET_SENSOR_SUM;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    //
    index ++;
    SensorComUnLock();
    return SUCC;
}

static INT8U Sensor_GetSenID(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_ID;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;

}
static INT8U Sensor_GetDataPack(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
 
    rcs->Cmd = SCDC_GET_DATA_PACK;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    rcs-> DataBuf[rcs->DataLen ++] = 0x00;
    rcs-> DataBuf[rcs->DataLen ++] = 0xFF;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    index ++;

    SensorComUnLock();

    return SUCC;
    
}
INT8U Sensor_GetDataFMT(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_DATA_FMT;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    index ++;

    SensorComUnLock();

    return SUCC;
    
}
INT8U Sensor_GetSenPara(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_PARA;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    rcs-> DataBuf[rcs->DataLen ++] = (0X7F >> 8) & 0XFF;
    rcs-> DataBuf[rcs->DataLen ++] = (0X7F     ) & 0XFF;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    index ++;
    SensorComUnLock();

    return SUCC;
}

static INT8U Sensor_GetSenName(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SCDC_GET_SEN_NAME;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;
}
static INT8U Sensor_GetSenUF()
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_UF;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
}

static INT8U Sensor_GetOEMCode()
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_OEM_CODE;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
}
static INT8U Sensor_GetParterCode()
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SCDC_GET_PARTNER_CODE;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;
}
static INT8U Sensor_GeEndOfLife(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SCDC_GET_SEN_END_OF_LIFE;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;
}

static INT8U Sensor_GeSenCalDueDays(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_CAL_DUE_DAYS;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();
    return SUCC;
}

static INT8U Sensor_GeSenCaTime(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_CAL_TIME;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
    }

static INT8U Sensor_GeSenSensitivity(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_SENSITIVITY;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}


static INT8U Sensor_GeSenDeadBand(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_SENSITIVITY;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;
}

INT8U Sensor_GeSenCalData(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_CAL_DATA;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}
static INT8U Sensor_GeSenBumpDays(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_BUMP_DUE_DAYS;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}
static INT8U Sensor_GeSenGasCalMes(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
 
    rcs->Cmd = SCDC_GET_SEN_GAS_CAL_MES;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}

static INT8U Sensor_GeAlohaMode(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_ALOHA_MODE;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
}
static INT8U Sensor_GeSenGasUnitList(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SEN_GASUNIT_LIST;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
}

static INT8U Sensor_GeECDatalog(INT16U DatalogIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_EC_DATALOG;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = DatalogIndex >> 8;
    rcs-> DataBuf[rcs->DataLen ++] = DatalogIndex & 0X00FF;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;
    
}
static INT8U Sensor_GeECAccuracyPrecent(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_EC_ACCURACY_PRECENT;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}
static INT8U Sensor_GeSpanCalibrationFlag(INT8U SensorIndex)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_GET_SPANH_CAL_FLAG;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;

    SensorComUnLock();

    return SUCC;

}

// /*
//  WriteProtectFlag：
//   0--Disable
//   1--Enable
// */
INT8U Sensor_WriteProtect(INT8U WriteProtectFlag)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;

    rcs->Cmd = SCDC_WRITE_PROTECT;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] = WriteProtectFlag;
    CommHandler_SCDCSensrHost(rcs);
    // TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;
    
    index ++;
    SensorComUnLock();

    return SUCC;

}


// INT8U Sensor_UserCal(INT16U SenBitMap,INT8U CalType,INT8U Operation)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//     do{
//         rcs->Cmd = SCDC_USER_CAL;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] = (SenBitMap>> 8) & 0x00FF;
//         rcs-> DataBuf[rcs->DataLen ++] = SenBitMap & 0x00FF;
//         rcs-> DataBuf[rcs->DataLen ++] = CalType;
//         rcs-> DataBuf[rcs->DataLen ++] = Operation;
//         CommHandler_SCDCSensrHost(rcs);
//         // TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();

//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }

// INT8U Sensor_GetGasList(INT16U SenIndx)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//     do{
//         rcs->Cmd = SCDC_GET_SEN_GAS_LIST;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] =SenIndx;
//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();
//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }

// INT8U Sensor_SetSenGasUnit(INT16U SenIndx,INT8U Uint)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//        switch(Uint){
//           case MEASUNIT_PPM: //PPM
//               Uint= SUC_PPM;
//           break;
//           case MEASUNIT_PPB:  //PPB
//                Uint = SUC_PPB ;
//           break;
//           default:
//           break;
//        }

//     do{
//         rcs->Cmd = SCDC_SET_SEN_GASUNIT;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] =SenIndx;
//         rcs-> DataBuf[rcs->DataLen ++] =Uint;
//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();
//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }

// static INT8U Sensor_SetSenCalInterval(INT16U SenIndx,INT16U Interval)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;

//     do{
//         rcs->Cmd = SCDC_SET_SEN_CAL_INTERVAL_DAYS;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] =SenIndx;
//         rcs-> DataBuf[rcs->DataLen ++] = (Interval >> 8) & 0XFF ;
//         rcs-> DataBuf[rcs->DataLen ++] = Interval & 0XFF ;
//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();
//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }


// INT8U Sensor_SetSenPARA(INT16U SenIndx,INT16U ParamMask,INT32U Span,INT32U Low,\
// INT32U High,INT32U SpanH,INT32U Stel,INT32U Twa,INT8U UnitCode )
// {

//     INT8U ret;
//     INT8U index =0;

//     if(UnitCode == MEASUNIT_PPM){
//       Span /=  10 ;  // 10 =1000/100change to PPM*100
//       Low /=  10 ;  // 10 =1000/100change to PPB  
//       High /=  10 ;  // 10 =1000/100change to PPB
//       SpanH /=  10 ;  // 10 =1000/100change to PPB 
//       Stel /=  10 ;  // 10 =1000/100change to PPB   
//       Twa /=  10 ;  // 10 =1000/100change to PPB 
//    }else if(UnitCode == MEASUNIT_PPB){
//       Span *= 100;
//       Low *= 100;
//       High *= 100;
//       SpanH *= 100;
//       Stel *= 100;
//       Twa *= 100;
//    }
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//     do{
//         rcs->Cmd = SCDC_SET_SEN_PARA;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] =SenIndx;
//         //rcs-> DataBuf[rcs->DataLen ++] = ParamMask & 0XFF;
//         rcs-> DataBuf[rcs->DataLen ++] = (ParamMask << 8) & 0XFF;
//         rcs-> DataBuf[rcs->DataLen ++] = ParamMask & 0XFF;
//         //Span
//         if(ParamMask & SET_SPAN){
//             rcs-> DataBuf[rcs->DataLen ++] = (Span>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Span>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Span>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Span      ) & 0XFF;
//         }
//         //Low
//         if(ParamMask & SET_LOW){
//             rcs-> DataBuf[rcs->DataLen ++] = (Low>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Low>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Low>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Low      ) & 0XFF;
//         }
//         //High
//         if(ParamMask & SET_HIGH){
//             rcs-> DataBuf[rcs->DataLen ++] = (High>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (High>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (High>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (High      ) & 0XFF;
//         }
//         //SpanH
//         if(ParamMask & SET_SPANH){
//             rcs-> DataBuf[rcs->DataLen ++] = (SpanH>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (SpanH>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (SpanH>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (SpanH      ) & 0XFF;
//         }

//         //Stel
//         if(ParamMask & SET_STEL){
//             rcs-> DataBuf[rcs->DataLen ++] = (Stel>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Stel>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Stel>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Stel      ) & 0XFF;
//         }
//         //Twa
//         if(ParamMask & SET_TWA){
//             rcs-> DataBuf[rcs->DataLen ++] = (Twa>> 24 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Twa>> 16 ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Twa>> 8  ) & 0XFF;
//             rcs-> DataBuf[rcs->DataLen ++] = (Twa      ) & 0XFF;
//         }
//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();
//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }

// static INT8U Sensor_SetBumpTime(INT8U year,INT8U month,INT8U day,INT8U hour,INT8U min)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//     do{
//         rcs->Cmd = SCDC_SET_SEN_BUMP_TIME;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] =year;
//         rcs-> DataBuf[rcs->DataLen ++] =month;
//         rcs-> DataBuf[rcs->DataLen ++] =day;
//         rcs-> DataBuf[rcs->DataLen ++] =hour;
//         rcs-> DataBuf[rcs->DataLen ++] =min;

//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0) &&(index <5));
//     SensorComUnLock();
//     if(index >=5){
//         return FAIL;
//     }else{
//         return SUCC;
//     }
// }

#define MODE_RESET      1
#define MODE_SLEEP      2
#define MODE_WORK       3

static INT8U Sensor_GoToMode(INT8U Mode)
{
    INT8U ret;
    INT8U index =0;
    SensorComLock();
    RCS_t *rcs = &SCDC_SensorHost;
    rcs->Cmd = SCDC_GOTO_MODE;
    rcs-> PktIndex = index;
    rcs->DataLen = 0;
    rcs-> DataBuf[rcs->DataLen ++] =Mode;

    CommHandler_SCDCSensrHost(rcs);
    //TM_Delay(DELAY_100MS);
    SCDC_SensorResp.PktIndex = index;

    index ++;
    SensorComUnLock();
    return SUCC;
}


// static INT8U Sensor_SeSpanCalibrationFlag(INT8U SensorIndex,INT8U Flag)
// {
//     INT8U ret;
//     INT8U index =0;
//     SensorComLock();
//     RCS_t *rcs = &SCDC_SensorHost;
//     do{
//         rcs->Cmd = SCDC_SET_SPANH_CAL_FLAG;
//         rcs-> PktIndex = index;
//         rcs->DataLen = 0;
//         rcs-> DataBuf[rcs->DataLen ++] = SensorIndex;
//         rcs-> DataBuf[rcs->DataLen ++] = Flag;
//         CommHandler_SCDCSensrHost(rcs);
//         TM_Delay(DELAY_100MS);
//         SCDC_SensorResp.PktIndex = index;
//         
//         index ++;
//     }while((ret == 0));
//     SensorComUnLock();
    
//     return SUCC;
// }

// INT8U Sensor_Init(void)
// {
//     INT8U Res =0;
//     //CS_ON;
//     if(Sensor_GetFwVer()== FAIL) return FAIL;
//     if(Sensor_SenSum()== FAIL) return FAIL;
//     if(Sensor_GetSenSN()== FAIL) return FAIL;
//     if(Sensor_GetModelName()== FAIL) return FAIL;
//     if(Sensor_GetProdName()== FAIL) return FAIL;
//     if(Sensor_GetSenID(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GetDataFMT(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GetSenPara(SENINDEX,0X007F)== FAIL) return FAIL;
//     if(Sensor_GetSenName(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GeEndOfLife(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GeSenSensitivity(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GeSenDeadBand(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GeSenGasUnitList(SENINDEX)== FAIL) return FAIL;
//     if(Sensor_GeSenCaTime(SENINDEX)== FAIL) return FAIL;  
//     if(Sensor_WriteProtect(0)== FAIL) return FAIL; 
//     //if(Sensor_SetSenCalInterval(SENINDEX,Cfg.PolicyData.calInterval)== FAIL) return FAIL;
//     if(Sensor_GoToMode(MODE_WORK)== FAIL) return FAIL;
//     if(Sensor_WriteProtect(1)== FAIL) return FAIL;  
//     if(Sensor_GeSpanCalibrationFlag(1)== FAIL) return FAIL;  

//     return SUCC;
// }




// void SaveDataToSensor(void){
    
//     Sensor.st_RunData.SpanValue = CalRef.SpanLow;
//     Sensor.st_RunData.SpanHValue =  CalRef.SpanHigh;
    
//     Sensor_WriteProtect(0); 

//     Sensor.st_RunData.PreSpanValue = Sensor.st_RunData.SpanValue;
//     Sensor.st_RunData.PreSpanHValue = Sensor.st_RunData.SpanHValue;
// //Sensor_SetSenGasUnit(SENINDEX,Sensor.st_SenInfo.UnitCode);
//     Sensor_SetSenPARA(SENINDEX,(SET_SPAN | SET_SPANH),Sensor.st_RunData.SpanValue,\
//                                         Sensor.st_RunData.LowAlarmValue,\
//                                         Sensor.st_RunData.HightAlarmValue,\
//                                         Sensor.st_RunData.SpanHValue,\
//                                         Sensor.st_RunData.STELAlarmValue,\
//                                         Sensor.st_RunData.TWAAlarmValue,\
//                                         Sensor.st_SenInfo.UnitCode
//                                         );
//     Sensor_SeSpanCalibrationFlag(SENINDEX,Cfg.U8_3PointCal);                 

// /*
//     //Save bump time to sensor
//     if(Cfg.PolicyData.result.SS_BUMP_FAIL == 0){
//         Sensor_SetBumpTime(Cfg.PolicyData.lastBumpDate[0],\
//                         Cfg.PolicyData.lastBumpDate[2],\
//                         Cfg.PolicyData.lastBumpDate[3],\
//                         Cfg.PolicyData.lastBumpDate[4],\
//                         Cfg.PolicyData.lastBumpDate[5]\
//                         );
//     } */

//     Sensor_WriteProtect(1);    
// }

// INT8U showMenu(void){
//     INT16U i =0;
//     INT16U  CmdLen = CmdTotal;
//     for(i =0; i< CmdLen; i ++){
//        printf("%c : %s \n",Cmd[i].Index,Cmd[i].Description); 
//     }
// }



struct Command SensorTable[] ={
    {ENABLE,   Sensor_GetFwVer,                      SENINDEX  },           
    {ENABLE,   Sensor_SenSum,                        SENINDEX  },
    {ENABLE,   Sensor_GetSenSN,                      SENINDEX  },
    {ENABLE,   Sensor_GetModelName,                  SENINDEX  },
    {ENABLE,   Sensor_GetProdName,                   SENINDEX  },
    {ENABLE,   Sensor_GetSenID,                      SENINDEX  },
    {ENABLE,   Sensor_GetDataFMT,                    SENINDEX  },
    {ENABLE,   Sensor_GetSenPara,                    SENINDEX  },
    {ENABLE,   Sensor_GetSenName,                    SENINDEX  },
    {ENABLE,   Sensor_GeEndOfLife,                   SENINDEX  },
    {ENABLE,   Sensor_GeSenSensitivity,              SENINDEX  },
    {ENABLE,   Sensor_GeSenDeadBand,                 SENINDEX  },
    {ENABLE,   Sensor_GeSenGasUnitList,              SENINDEX  },
    {ENABLE,   Sensor_GeSenCaTime,                   SENINDEX  },
    {ENABLE,   Sensor_WriteProtect,                  0         },           
    {ENABLE,   Sensor_GoToMode,                      MODE_WORK },          
    {ENABLE,   Sensor_WriteProtect,                  1         },            
    {ENABLE,   Sensor_GeSpanCalibrationFlag,         1         },


    {ENABLE,   Sensor_GetDataPack,                    SENINDEX},



};
const INT8U SensorTableTotal = dim(SensorTable);
// /* EOF */
