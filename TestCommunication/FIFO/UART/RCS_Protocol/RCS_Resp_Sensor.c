
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

INT16U CalibRespData = 0;

static void Sensor_GetFwVerResp(RCS_t *rcs)
{
  // DebugSensor("\r\n Sensor_GetFwVerResp");
  //Fw version max lentg is 10
  if(rcs->DataLen < 10 ){
      memset(Sensor.st_SenInfo.FwVer,0,sizeof(Sensor.st_SenInfo.FwVer));
      memcpy(Sensor.st_SenInfo.FwVer,rcs->DataBuf,rcs->DataLen); 
  }else{
   /*
     Need add error action
   */
  }
}
static void Sensor_GetSenSNResp(RCS_t *rcs)
{
   if(rcs->DataLen  < 21 ){
       memset(Sensor.st_SenInfo.SN,0,sizeof(Sensor.st_SenInfo.SN));
       memcpy(Sensor.st_SenInfo.SN,rcs->DataBuf,rcs->DataLen);
   }else{

   }
}
static void Sensor_GetModelNameResp(RCS_t *rcs)
{
  // DebugSensor("\r\n Sensor_GetFwVerResp");
  //Fw Model name max lentg is 20
  if(rcs->DataLen < 20 ){
      memcpy(Sensor.st_SenInfo.ModelName,rcs->DataBuf,rcs->DataLen); 
  }else{
   /*
     Need add error action
   */
  }
}
static void Sensor_GetProdNameResp(RCS_t *rcs)
{
  // DebugSensor("\r\n Sensor_GetFwVerResp");
  //Fw Product name  max lentg is 20
  if(rcs->DataLen < 20 ){
      memset(Sensor.st_SenInfo.ProdName,0,sizeof(Sensor.st_SenInfo.ProdName));
      memcpy(Sensor.st_SenInfo.ProdName,rcs->DataBuf,rcs->DataLen); 
  }else{
   /*
     Need add error action
   */
  }
}
static void Sensor_GetSenIDResp(RCS_t *rcs)
{
  if(rcs->DataLen == 2 ){
       Sensor.st_SenInfo.SenID = rcs->DataBuf[0];
       Sensor.st_SenInfo.SubID = rcs->DataBuf[1];
  }else{
   /*
     Need add error action
   */
  }
}

static void Sensor_GetDataPackResp(RCS_t *rcs)
{
       INT8U i =0,j =0;
       // Sensor Status
       Sensor.st_RunData.Sentatus     = rcs->DataBuf[i ++];
       // Sensor Alarm
       Sensor.st_RunData.SenAlarm     = rcs->DataBuf[i ++];
       // Sensor Error
       Sensor.st_RunData.SensorError.SenErrorNum = rcs->DataBuf[i ++];
       for(j =0;j < Sensor.st_RunData.SensorError.SenErrorNum;j++){
           Sensor.st_RunData.SensorError.ErrorCode[j] = rcs->DataBuf[i ++]; 
       }
       // Gas reading
       Sensor.st_RunData.GasReading   = rcs->DataBuf[i ++];
       Sensor.st_RunData.GasReading <<=8;
       Sensor.st_RunData.GasReading   += rcs->DataBuf[i ++];
       Sensor.st_RunData.GasReading <<=8;
       Sensor.st_RunData.GasReading   += rcs->DataBuf[i ++];
       Sensor.st_RunData.GasReading <<=8;
       Sensor.st_RunData.GasReading   += rcs->DataBuf[i ++];
       // sensor only support PPM now 2020-05-09
       //DebugSensor("\r\n Sensor.st_RunData.GasReading = %d",Sensor.st_RunData.GasReading);

      //  //DebugSensor("\r\n Sensor.st_RunData.Sentatus_bit.SS_WARMUP = %d",Sensor.st_RunData.Sentatus_bit.SS_WARMUP);
      //  if(Sensor.st_RunData.GasReading < 0){
      //      U32_PidReading =0;    
      //  }
      //  U32_PidReading = Sensor.st_RunData.GasReading ;
      //  if(Sensor.st_RunData.Sentatus_bit.SS_WARMUP == 1){
      //      U32_PidReading =0;    
      //  }
      //  DebugSensor("\r\n U32_PidReading = %d",U32_PidReading);
       // Raw count
       Sensor.st_RunData.SensorRawCount.SenRawCountNum     = rcs->DataBuf[i ++];
       for(j =0;j < Sensor.st_RunData.SensorRawCount.SenRawCountNum;j++){
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] = rcs->DataBuf[i ++];
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] <<=8;
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] += rcs->DataBuf[i ++];
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] <<=8; 
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] += rcs->DataBuf[i ++];
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] <<=8;
           Sensor.st_RunData.SensorRawCount.SenRawCount[j] += rcs->DataBuf[i ++]; 
           DebugSensor("\r\n SenRawCount[%d]= %ld",j,Sensor.st_RunData.SensorRawCount.SenRawCount[j]);
       }
       // Temperature
       Sensor.st_RunData.Temperature  = rcs->DataBuf[i ++];
       Sensor.st_RunData.Humidity     = rcs->DataBuf[i ++];

       if(Sensor.st_RunData.Temperature !=0XFF){
           Sensor.st_RunData.Temperature -= 127;   
       }
       //Sensor.st_RunData.UnCompGasReading = rcs->DataBuf[i ++];

       // Uncompensated Gas Reading
       Sensor.st_RunData.UnCompGasReading   = rcs->DataBuf[i ++];
       Sensor.st_RunData.UnCompGasReading <<=8;
       Sensor.st_RunData.UnCompGasReading   += rcs->DataBuf[i ++];
       Sensor.st_RunData.UnCompGasReading <<=8;
       Sensor.st_RunData.UnCompGasReading   += rcs->DataBuf[i ++];
       Sensor.st_RunData.UnCompGasReading <<=8;
       Sensor.st_RunData.UnCompGasReading   += rcs->DataBuf[i ++];

       
}

static void Sensor_GetDataFMTResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen == 5 ){
       switch(rcs->DataBuf[i++]){
          case 0: //PPM
              Sensor.st_SenInfo.UnitCode = MEASUNIT_PPM;
          break;
          case 2:  //PPB
              Sensor.st_SenInfo.UnitCode = MEASUNIT_PPB;
          break;
          default:
          break;
       }
       Sensor.st_SenInfo.ResInt       = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ResExp       = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ParaMask_H   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ParaMask_L   = rcs->DataBuf[i++];
   }else{

   }
}
static void Sensor_GetSenParaResp(RCS_t *rcs)
{
   INT8U i =0;
   //SpanValue
   Sensor.st_RunData.SpanValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanValue <<=8;
   Sensor.st_RunData.SpanValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanValue <<=8;
   Sensor.st_RunData.SpanValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanValue <<=8;
   Sensor.st_RunData.SpanValue   += rcs->DataBuf[i ++];

   //LowAlarmValue
   Sensor.st_RunData.LowAlarmValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.LowAlarmValue <<=8;
   Sensor.st_RunData.LowAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.LowAlarmValue <<=8;
   Sensor.st_RunData.LowAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.LowAlarmValue <<=8;
   Sensor.st_RunData.LowAlarmValue   += rcs->DataBuf[i ++];
   //HightAlarmValue
   Sensor.st_RunData.HightAlarmValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.HightAlarmValue <<=8;
   Sensor.st_RunData.HightAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.HightAlarmValue <<=8;
   Sensor.st_RunData.HightAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.HightAlarmValue <<=8;
   Sensor.st_RunData.HightAlarmValue   += rcs->DataBuf[i ++];
   //SpanHValue
   Sensor.st_RunData.SpanHValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanHValue <<=8;
   Sensor.st_RunData.SpanHValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanHValue <<=8;
   Sensor.st_RunData.SpanHValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.SpanHValue <<=8;
   Sensor.st_RunData.SpanHValue   += rcs->DataBuf[i ++];

   //OverRangeValue
   Sensor.st_RunData.OverRangeValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.OverRangeValue <<=8;
   Sensor.st_RunData.OverRangeValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.OverRangeValue <<=8;
   Sensor.st_RunData.OverRangeValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.OverRangeValue <<=8;
   Sensor.st_RunData.OverRangeValue   += rcs->DataBuf[i ++];

   //STELAlarmValue
   Sensor.st_RunData.STELAlarmValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.STELAlarmValue <<=8;
   Sensor.st_RunData.STELAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.STELAlarmValue <<=8;
   Sensor.st_RunData.STELAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.STELAlarmValue <<=8;
   Sensor.st_RunData.STELAlarmValue   += rcs->DataBuf[i ++];
   //TWAAlarmValue
   Sensor.st_RunData.TWAAlarmValue   = rcs->DataBuf[i ++];
   Sensor.st_RunData.TWAAlarmValue <<=8;
   Sensor.st_RunData.TWAAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.TWAAlarmValue <<=8;
   Sensor.st_RunData.TWAAlarmValue   += rcs->DataBuf[i ++];
   Sensor.st_RunData.TWAAlarmValue <<=8;
   Sensor.st_RunData.TWAAlarmValue   += rcs->DataBuf[i ++];

   if(Sensor.st_SenInfo.UnitCode == MEASUNIT_PPM){
      Sensor.st_RunData.SpanValue *=  10 ;  // 10 =1000/100change to PPB
      Sensor.st_RunData.LowAlarmValue *=  10 ;  // 10 =1000/100change to PPB  
      Sensor.st_RunData.HightAlarmValue *=  10 ;  // 10 =1000/100change to PPB
      Sensor.st_RunData.SpanHValue *=  10 ;  // 10 =1000/100change to PPB 
      Sensor.st_RunData.OverRangeValue *=  10 ;  // 10 =1000/100change to PPB
      Sensor.st_RunData.STELAlarmValue *=  10 ;  // 10 =1000/100change to PPB   
      Sensor.st_RunData.TWAAlarmValue *=  10 ;  // 10 =1000/100change to PPB 
   }else if(Sensor.st_SenInfo.UnitCode == MEASUNIT_PPB){
      Sensor.st_RunData.SpanValue /= 100;
      Sensor.st_RunData.LowAlarmValue /= 100;
      Sensor.st_RunData.HightAlarmValue /= 100;
      Sensor.st_RunData.SpanHValue /= 100;
      Sensor.st_RunData.OverRangeValue /= 100;
      Sensor.st_RunData.STELAlarmValue /= 100;
      Sensor.st_RunData.TWAAlarmValue /= 100;
   }



}

static void Sensor_GetSenNameResp(RCS_t *rcs)
{
   if(rcs->DataLen < 6 ){
      memset(Sensor.st_SenInfo.SenName,0,sizeof(Sensor.st_SenInfo.SenName));
      memcpy(Sensor.st_SenInfo.SenName,rcs->DataBuf,rcs->DataLen); 
   }else{

   }
}

static void Sensor_GetSenUFResp(RCS_t *rcs)
{
   if(rcs->DataLen == 2 ){
       Sensor.st_SenInfo.UserFactor_H   = rcs->DataBuf[0];
       Sensor.st_SenInfo.UserFactor_L   = rcs->DataBuf[1];
   }else{

   }
}

static void Sensor_GetOEMCodeResp(RCS_t *rcs)
{
   if(rcs->DataLen <7 ){
      memset(Sensor.st_SenInfo.OEMCode,0,sizeof(Sensor.st_SenInfo.OEMCode));
      memcpy(Sensor.st_SenInfo.OEMCode,rcs->DataBuf,rcs->DataLen); 
   }else{

   }
}
static void Sensor_GetParterResp(RCS_t *rcs)
{
   if(rcs->DataLen <7 ){
      memset(Sensor.st_SenInfo.OEMCode,0,sizeof(Sensor.st_SenInfo.OEMCode));
      memcpy(Sensor.st_SenInfo.OEMCode,rcs->DataBuf,rcs->DataLen); 
   }else{

   }
}
static void Sensor_GetEndOfLifeResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 2 ){
       Sensor.st_SenInfo.EndOfLifeDays     =rcs->DataBuf[i++];
       Sensor.st_SenInfo.EndOfLifeDays <<=8;
       Sensor.st_SenInfo.EndOfLifeDays += rcs->DataBuf[i++];
   }else{

   }
}
static void Sensor_GetCalDueDaysResp(RCS_t *rcs)
{
   INT8U i=0;
   if(rcs->DataLen  == 2 ){
       Sensor.st_SenInfo.CalDueDays    = rcs->DataBuf[i++];
       Sensor.st_SenInfo.CalDueDays <<=8;
       Sensor.st_SenInfo.CalDueDays    += rcs->DataBuf[i++];
   }else{

   }
}
static void Sensor_GetSenSumResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 3 ){
       Sensor.st_SenInfo.MaximalSenNum     = rcs->DataBuf[i++];
       Sensor.st_SenInfo.InstalledSenMap   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.InstalledSenMap <<= 8;
       Sensor.st_SenInfo.InstalledSenMap += rcs->DataBuf[i++];
   }else{

   }
}
static void Sensor_GetProdDataResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 5 ){
       Sensor.st_SenInfo.ProdDay[0]   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ProdDay[1]   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ProdDay[2]   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.WarrantyDays   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.WarrantyDays <<= 8;
       Sensor.st_SenInfo.WarrantyDays += rcs->DataBuf[i++];
   }else{

   }
}
static void Sensor_GetCalTimeResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 2 ){
       Sensor.st_SenInfo.CalTime   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.CalTime <<= 8;
       Sensor.st_SenInfo.CalTime += rcs->DataBuf[i++];
   }else{

   }
}

static void Sensor_GetSenSensitivityResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 4 ){
       Sensor.st_SenInfo.ActaulSensitivity   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.ActaulSensitivity <<= 8;
       Sensor.st_SenInfo.ActaulSensitivity += rcs->DataBuf[i++];

       Sensor.st_SenInfo.MinimumSensitivity   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.MinimumSensitivity <<= 8;
       Sensor.st_SenInfo.MinimumSensitivity += rcs->DataBuf[i++];
   }else{

   }
}

static void Sensor_GetSenDeadBandResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 9 ){
       Sensor.st_SenInfo.Deadband.Enable   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.OutLimit   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.OutLimit <<= 8;
       Sensor.st_SenInfo.Deadband.OutLimit += rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.OutLimit <<= 8;
       Sensor.st_SenInfo.Deadband.OutLimit += rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.OutLimit <<= 8;
       Sensor.st_SenInfo.Deadband.OutLimit += rcs->DataBuf[i++];

       Sensor.st_SenInfo.Deadband.InLimit   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.InLimit <<= 8;
       Sensor.st_SenInfo.Deadband.InLimit += rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.InLimit <<= 8;
       Sensor.st_SenInfo.Deadband.InLimit += rcs->DataBuf[i++];
       Sensor.st_SenInfo.Deadband.InLimit <<= 8;
       Sensor.st_SenInfo.Deadband.InLimit += rcs->DataBuf[i++];
   }else{

   }
}

static void Sensor_GetSencalDataResp(RCS_t *rcs)
{
    INT8U i = 0,j =0;
    Sensor.st_CaliData.ChannelNum = rcs->DataBuf[i++];

   //Zero cal date
    Sensor.st_CaliData.ZeroCal.CalValue = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalValue   <<= 8;
    Sensor.st_CaliData.ZeroCal.CalValue  += rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalValue   <<= 8;
    Sensor.st_CaliData.ZeroCal.CalValue   += rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalValue   <<= 8;
    Sensor.st_CaliData.ZeroCal.CalValue  += rcs->DataBuf[i++];
    for(j =0;j< Sensor.st_CaliData.ChannelNum;j++){
        Sensor.st_CaliData.ZeroCal.CalRAW[j] = rcs->DataBuf[i++];
        Sensor.st_CaliData.ZeroCal.CalRAW[j] <<= 8;
        Sensor.st_CaliData.ZeroCal.CalRAW[j] += rcs->DataBuf[i++];
    }
    Sensor.st_CaliData.ZeroCal.CalTemperature = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalHumidity = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.year = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.month = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.day = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.hour = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.minute = rcs->DataBuf[i++];
    Sensor.st_CaliData.ZeroCal.CalDate.second = rcs->DataBuf[i++];
    //Span cal date
    Sensor.st_CaliData.SpanCal.CalValue = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanCal.CalValue  += rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanCal.CalValue   += rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanCal.CalValue  += rcs->DataBuf[i++];
    for(j =0;j< Sensor.st_CaliData.ChannelNum;j++){
        Sensor.st_CaliData.SpanCal.CalRAW[j] = rcs->DataBuf[i++];
        Sensor.st_CaliData.SpanCal.CalRAW[j] <<= 8;
        Sensor.st_CaliData.SpanCal.CalRAW[j] += rcs->DataBuf[i++];
    }
    Sensor.st_CaliData.SpanCal.CalTemperature = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalHumidity = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.year = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.month = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.day = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.hour = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.minute = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.second = rcs->DataBuf[i++];
    //SpanH cal date
    Sensor.st_CaliData.SpanHCal.CalValue = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanHCal.CalValue  += rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanHCal.CalValue   += rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalValue   <<= 8;
    Sensor.st_CaliData.SpanHCal.CalValue  += rcs->DataBuf[i++];
    for(j =0;j< Sensor.st_CaliData.ChannelNum;j++){
        Sensor.st_CaliData.SpanHCal.CalRAW[j] = rcs->DataBuf[i++];
        Sensor.st_CaliData.SpanHCal.CalRAW[j] <<= 8;
        Sensor.st_CaliData.SpanHCal.CalRAW[j] += rcs->DataBuf[i++];
    }
    Sensor.st_CaliData.SpanHCal.CalTemperature = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalHumidity = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalDate.year = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalDate.month = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanCal.CalDate.day = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalDate.hour = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalDate.minute = rcs->DataBuf[i++];
    Sensor.st_CaliData.SpanHCal.CalDate.second = rcs->DataBuf[i++];
}

static void Sensor_GetSenBumpDueDaysResp(RCS_t *rcs)
{
   INT8U i =0;
   if(rcs->DataLen  == 9 ){
       Sensor.st_SenInfo.BumpDueDays   = rcs->DataBuf[i++];
       Sensor.st_SenInfo.BumpDueDays <<= 8;
       Sensor.st_SenInfo.BumpDueDays += rcs->DataBuf[i++];
   }else{

   }
}

static void Sensor_GetSenGasListResp(RCS_t *rcs)
{
   if(rcs->DataLen  == 9 ){

   }else{

   }
}

static void Sensor_GetSenGasCalMesResp(RCS_t *rcs)
{
   if(rcs->DataLen  == 9 ){

   }else{

   }
}

static void Sensor_GetAlohaModeResp(RCS_t *rcs)
{
   if(rcs->DataLen  == 9 ){

   }else{

   }
}
static void Sensor_GetSenGasUnitListResp(RCS_t *rcs)
{
   INT8U i =0;
   for(i = 0; i < rcs->DataLen;i++){
       if(i < MAX_SUPPORT_UNIT){
          Sensor.st_SenInfo.SupportUnitList[i] = rcs->DataBuf[i];
       }
       else{
          break;
       }
   }
}

static void Sensor_GetECDatalogResp(RCS_t *rcs)
{
   if(rcs->DataLen  == 9 ){

   }else{

   }
}

static void Sensor_GetECAccurayPrecentResp(RCS_t *rcs)
{
   if(rcs->DataLen  == 9 ){

   }else{

   }
}
static void Sensor_UserCalResp(RCS_t *rcs)
{
   INT8U i = 0;
   if(rcs->DataLen > 0){
    CalibRespData = rcs->DataBuf[i++];
    CalibRespData <<=8;
    CalibRespData += rcs->DataBuf[i++];
   }
}
static void Sensor_GetSpanHCalibrationResp(RCS_t *rcs)
{
  // DebugSensor("\r\n Sensor_GetFwVerResp");
  //Fw Model name max lentg is 20
  INT8U i = 0;
  if(rcs->DataLen ==1 ){
      Sensor.st_SenInfo.EnableSpanhCalFlag = rcs->DataBuf[i++]; 
  }else{

  }
}
/* Command set table */
const RCS_CmdNode SCDC_Sensor_RespTable[] = {
    //-----------------------------------------------
    SDCS_GET_MODEL_NAME,                 RCS_CMD_REV1,     Sensor_GetModelNameResp,        NULL,    
    SDCS_GET_PROD_NAME,                  RCS_CMD_REV1,     Sensor_GetProdNameResp,         NULL,    
    SDCS_GET_SENSOR_FWVER,               RCS_CMD_REV1,     Sensor_GetFwVerResp,            NULL,    
    SDCS_GET_SENSOR_SN,                  RCS_CMD_REV1,     Sensor_GetSenSNResp,            NULL,    
    SDCS_GET_SENSOR_SUM,                 RCS_CMD_REV1,     Sensor_GetSenSumResp,           NULL,    
    SDCS_GET_PROD_DATE,                  RCS_CMD_REV1,     Sensor_GetProdDataResp,         NULL,    
    SCDC_GET_DATA_PACK,                  RCS_CMD_REV1,     Sensor_GetDataPackResp,         NULL,    
    SCDC_GET_SEN_DATA_FMT,               RCS_CMD_REV1,     Sensor_GetDataFMTResp,          NULL,    
    SCDC_GET_SEN_PARA,                   RCS_CMD_REV1,     Sensor_GetSenParaResp,          NULL,    
    SCDC_GET_SEN_ID,                     RCS_CMD_REV1,     Sensor_GetSenIDResp,            NULL,    
    SCDC_GET_SEN_NAME,                   RCS_CMD_REV1,     Sensor_GetSenNameResp,          NULL,    
    SCDC_GET_SEN_UF,                     RCS_CMD_REV1,     Sensor_GetSenUFResp,            NULL,    
    SCDC_GET_OEM_CODE,                   RCS_CMD_REV1,     Sensor_GetOEMCodeResp,          NULL,    
    SCDC_GET_PARTNER_CODE,               RCS_CMD_REV1,     Sensor_GetParterResp,           NULL,    
    SCDC_GET_SEN_END_OF_LIFE,            RCS_CMD_REV1,     Sensor_GetEndOfLifeResp,        NULL,    
    SCDC_GET_SEN_CAL_DUE_DAYS,           RCS_CMD_REV1,     Sensor_GetCalDueDaysResp,       NULL,    
    SCDC_GET_SEN_CAL_TIME,               RCS_CMD_REV1,     Sensor_GetCalTimeResp,          NULL,    
    SCDC_GET_SEN_SENSITIVITY,            RCS_CMD_REV1,     Sensor_GetSenSensitivityResp,   NULL,    
    SCDC_GET_SEN_DEADBAND,               RCS_CMD_REV1,     Sensor_GetSenDeadBandResp,      NULL,    
    SCDC_GET_SEN_CAL_DATA,               RCS_CMD_REV1,     Sensor_GetSencalDataResp,       NULL,    
    SCDC_GET_SEN_BUMP_DUE_DAYS,          RCS_CMD_REV1,     Sensor_GetSenBumpDueDaysResp,   NULL,    
    SCDC_GET_SEN_GAS_LIST,               RCS_CMD_REV1,     Sensor_GetSenGasListResp,       NULL,    
    SCDC_GET_SEN_GAS_CAL_MES,            RCS_CMD_REV1,     Sensor_GetSenGasCalMesResp,     NULL,    
    SCDC_GET_ALOHA_MODE,                 RCS_CMD_REV1,     Sensor_GetAlohaModeResp,        NULL,    
    SCDC_GET_SEN_GASUNIT_LIST,           RCS_CMD_REV1,     Sensor_GetSenGasUnitListResp,   NULL,    
    SCDC_GET_EC_DATALOG,                 RCS_CMD_REV1,     Sensor_GetECDatalogResp,        NULL,    
    SCDC_GET_EC_ACCURACY_PRECENT,        RCS_CMD_REV1,     Sensor_GetECAccurayPrecentResp, NULL,    
    SCDC_SET_SEN_PARA,                   RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_RTC,                    RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_UF,                     RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_OEM_CODE,                   RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_PARTNER_CODE,               RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_DEADBAND,               RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_GAS_CAL_MES,            RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_CMPL_STD,               RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_UF_INDEX,               RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_GASUNIT,                RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_CAL_INTERVAL_DAYS,      RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_BUMP_INTERVAL_DAYS,     RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_SEN_BUMP_TIME,              RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_SET_EC_ACCURACY_PRECENT,        RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_REQ_SEN_STEL_TWA,               RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_WRITE_PROTECT,                  RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_USER_CAL,                       RCS_CMD_REV1,     Sensor_UserCalResp,             NULL,    
    SCDC_SET_SEN_ALOHA,                  RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_ALOHA_DATA_PACK,                RCS_CMD_REV1,     NULL,                           NULL,    
    SCDC_GOTO_MODE,                      RCS_CMD_REV1,     NULL,                           NULL,
    SCDC_GET_SPANH_CAL_FLAG,             RCS_CMD_REV1,     Sensor_GetSpanHCalibrationResp, NULL,
    SCDC_SET_SPANH_CAL_FLAG,             RCS_CMD_REV1,     NULL,                           NULL,
    //-----------------------------------------------
};


const INT8U SCDC_Sensor_RespTotal = dim(SCDC_Sensor_RespTable);



/* EOF */


