#ifndef __DEBUG_H__
#define __DEBUG_H__


#define  DEBUG       1
#define  OUTPUT      1

#if DEBUG
     #define Debug(...)    printf(__VA_ARGS__)
#else
     #define Debug(...)    
#endif

#if OUTPUT
     #define Output(...)    printf(__VA_ARGS__)
#else
     #define Output(...)    
#endif



#endif