#ifndef __INCLUDES_H__ 
#define  __INCLUDES_H__
#include <string.h>
#include<stdio.h>      /*标准输入输出定义*/    
#include<stdlib.h>     /*标准函数库定义*/    
#include<unistd.h>     /*Unix 标准函数定义*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*文件控制定义*/    
#include<termios.h>    /*PPSIX 终端控制定义*/    
#include<errno.h>      /*错误号定义*/    
#include<string.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

#include "./RCS_Protocol/RCS.h"
#include "./RCS_Protocol/RCS_Parser.h"
#include "./RCS_Protocol/RAE_util.h"
#include "./RCS_Protocol/RCS_CmdDef.h"
#include "./RCS_Protocol/RCS_Executer.h"
#include "./RCS_Protocol/RCS_Resp_Sensor.h"
#include "./RCS_Protocol/RCS_Host_Sensor.h"

#include "./Comm/TypeDef.h"
#include "./Comm/TM_Util.h"

#include "./Sensor/Sensor.h"
#include "./Sensor/SenRelatedDef.h"

#define SUCCESS                        1
#define FAIL                           0

#define SUCC                           0

#if DEBUG_SENSOR
#define DebugSensor(...)		  {      \
if(SysMsg.CommFlags_bit.Charging == 0)    \
    printf(__VA_ARGS__);                   \
} 
#else
#define DebugSensor(...)
#endif

#endif