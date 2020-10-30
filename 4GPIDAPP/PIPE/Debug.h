#ifndef __DEBUG_H__
#define __DEBUG_H__


#define  DEBUG            1
#define  DEBUGINFOR        1
#define  OUTPUT            1
#define  OUTPUTWITHTIME    1
#define  DEBUGUART         0



#if DEBUG
    #define Debug(...)    printf(__VA_ARGS__)
#else
    #define Debug(...)  
#endif

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

#if DEBUGUART
    #define DebugUart(...)    printf(__VA_ARGS__)
#else
    #define DebugUart(...)  
#endif



#endif