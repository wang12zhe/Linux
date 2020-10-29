#ifndef __DEBUG_H__
#define __DEBUG_H__


#define  DEBUGINFOR       1
#define  OUTPUT      1
#define  OUTPUTWITHTIME     1

#if DEBUGINFOR
    #define DdebugInfor(fmt, args...)     printf("\033[33m[%s:%d]\033[0m  "fmt"  \r\n", __func__, __LINE__, ##args)
#else
     #define DdebugInfor(...)    
#endif

#if OUTPUT
     #define Output(...)    printf(__VA_ARGS__)
#else
     #define Output(...)    
#endif





#endif